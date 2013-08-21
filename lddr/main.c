#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#define NORMAL "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */

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

        if ( strstr(output,"not found")!=0 ) {
                                               fprintf(stderr,RED "Not Found - Line %u , %s \n" NORMAL,i,output);
                                             } else
                                             {
                                               fprintf(stderr,GREEN "Found - Line %u , %s \n" NORMAL,i,output);
                                             }

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
