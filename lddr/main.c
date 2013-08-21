#include <stdio.h>
#include <stdlib.h>


#define SIZEOFOUTPUT 1024

int runLdd(char * filename)
{
 char output[SIZEOFOUTPUT]={0};

 char * command=(char * ) malloc(sizeof(char) * (strlen(filename)+10) );
 if (command==0) { fprintf(stderr,"Could not allocate enough memory\n"); return 0; }
 FILE *fp=0;


 strcpy(command,"ldd ");
 strcat(command,filename);

 // Open the command for reading.
 fp = popen(command, "r");
 if (fp == 0 )
       {
         fprintf(stderr,"Failed to run `%s`\n",filename);
         free(command);
         return 0;
       }

 // Read the output a line at a time - output it.
  unsigned int i=0;
  while (fgets(output, SIZEOFOUTPUT  , fp) != 0)
    {
        ++i;
        fprintf(stderr,"Line %u , %s \n",i,output);
    }


  // close
  pclose(fp);
  free(command);

  return 1;
}













int main(int argc, const char* argv[])
{
    runLdd(argv[1]);
    return 0;
}
