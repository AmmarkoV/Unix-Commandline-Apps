#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


void dumpStreamToTemporaryFile(const char * filename)
{
  FILE * fp = fopen(filename,"w");
  if (fp!=0)
  {
    char *line = NULL;
    size_t size;

    while (getline(&line, &size, stdin) != -1)
    {
        fprintf(fp,"%s",line);
    }

    fclose(fp);
    if (line!=0) { free(line); line=0; }
  }
}


void printCStringList(FILE * stream,const char * dataName)
{
    char *line = NULL;
    size_t size;


    printf("/**\n");
    printf(" * @brief This is an auto-generated list of C-Strings made using serializelist\n");
    printf(" * https://github.com/AmmarkoV/Unix-Commandline-Apps/tree/master/serializelist\n");
    printf(" * Each entry of this %sNames[] array is linked with %sEnum[] to ensure no mistakes\n",dataName,dataName);
    printf(" */\n");

    printf("static const char *%sNames[]={\n",dataName);

    while (getline(&line, &size, stream) != -1)
    {
        unsigned int stringLength = strlen(line);

        if (stringLength!=0)
         {
           //Remove end-line from string
           if ( (line[stringLength-1]==10) || (line[stringLength-1]==13) ) { line[stringLength-1]=0; --stringLength; }
           if (stringLength>0)
           {
            if ( (line[stringLength-1]==10) || (line[stringLength-1]==13) ) { line[stringLength-1]=0; --stringLength; }
           }

           //If string is 0 after the newline removal
           if (stringLength!=0)
            { printf("\"%s\",\n", line); }
         }
    }

    printf("//-------------------------\n");
    printf("\"GUARD_FOR_+1_ERROR\"\n");
    printf("};\n");

    //Rewind STDIN
    //fseek(stream, 0, SEEK_SET);
    rewind(stream);

    if (errno!=0)
    {
      fprintf(stderr,"Error %u ",errno);
    }

    if (line!=0) { free(line); line=0; }
}



void convertStringToCFriendly(char * str)
{
  if (str==0) { return;}
  while (*str!=0)
  {
    switch (*str)
    {
       case '-' :
       case '.' :
       case '_' :
       *str='_';
       break;

       default :
       *str=toupper(*str);
    };
    ++str;
  }

}

void printCEnumList(FILE * stream,const char * dataName)
{
    char dataNameUpcased[512]={"SAMPLE"};
    snprintf(dataNameUpcased,512,"%s",dataName);
    convertStringToCFriendly(dataNameUpcased);


    char *line = NULL;
    size_t size;


    printf("/**\n");
    printf(" * @brief This is an auto-generated list of C-Strings made using serializelist\n");
    printf(" * https://github.com/AmmarkoV/Unix-Commandline-Apps/tree/master/serializelist\n");
    printf(" * Each entry of this %sEnum[] array is linked with %sNames[] to ensure no mistakes\n",dataName,dataName);
    printf(" */\n");


    printf("enum %sEnum {\n",dataName);

    while (getline(&line, &size, stream) != -1)
    {
        unsigned int stringLength = strlen(line);

        if (stringLength!=0)
         {
           //Remove end-line from string
           if ( (line[stringLength-1]==10) || (line[stringLength-1]==13) ) { line[stringLength-1]=0; --stringLength; }
           if (stringLength>0)
           {
            if ( (line[stringLength-1]==10) || (line[stringLength-1]==13) ) { line[stringLength-1]=0; --stringLength; }
           }

           //If string is 0 after the newline removal
           if (stringLength!=0)
            {
              convertStringToCFriendly(line);

              //Skip underscore characters..
              char * startFromNonUnderscore = line;
              while (*startFromNonUnderscore=='_') { ++startFromNonUnderscore; }

              printf("%s_%s,\n",dataNameUpcased,startFromNonUnderscore);
            }
         }
    }



    printf("//-------------------------\n");
    printf("%s_NUMBER\n",dataNameUpcased);
    printf("};\n");

    //Rewind STDIN
    //fseek(stream, 0, SEEK_SET);
    rewind(stream);

    if (line!=0) { free(line); line=0; }
}



int main(int argc, char *argv[])
{
    char dataName[512]={"sample"};


    //Allow change of array names
    for (int i=0; i<argc; i++)
        {
            if (strcmp(argv[i],"--name")==0)
                {
                    snprintf(dataName,512,"%s",argv[i+1]);
                }
        }


    //We need to dump to a temporary file
    //because stdin cannot be rewinded
    dumpStreamToTemporaryFile("tmpfile.mctmp");


    FILE * fp = fopen("tmpfile.mctmp","r");
    if (fp!=0)
    {
     printCStringList(fp,dataName);
     printf("\n\n\n\n");
     printCEnumList(fp,dataName);
     int i=system("rm tmpfile.mctmp");
     if (i!=0)
     {
         fprintf(stderr,"failed cleaning up temp file.. \n");
         return 1;
     }
    }
    return 0;
}
