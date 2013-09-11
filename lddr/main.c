#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hashmap.h"


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


int printFoundLibs = 1;
int printNotFoundLibs = 1;
int maxDepth=0;


struct hashMap * hm=0;


int runLdd(char * filename,int depth)
{
 if (maxDepth!=0) { if (depth>maxDepth) { return 0; } }

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

        if ( strstr(output,"not found")!=0 ) { //- Line %u , i
                                               if (printNotFoundLibs)  {  printf(RED "Not Found (%s) %s\n" NORMAL,filename,output); }
                                             } else
                                             {
                                               //fprintf(stderr,GREEN "Found - Line %u , %s \n" NORMAL,i,output);
                                               char * link = strstr(output,"=>");
                                               if (link!=0)
                                               {
                                                 link+=3;

                                                 int z=0;
                                                 while (z<strlen(link))
                                                 {
                                                   if (link[z]==' ') { link[z]=0; }
                                                   ++z;
                                                 }
                                                  if (printFoundLibs)  { fprintf(stderr,"%s\n",link); }

                                                 if (!hashMap_ContainsKey(hm,link))
                                                 {
                                                  hashMap_Add(hm,link,0,0);
                                                  runLdd(link,depth+1);
                                                 }
                                               }
                                             }

    }


  // close
  pclose(fp);
  free(command);

  return 1;
}



int main(int argc, const char* argv[])
{
  int i=0;
  for (i=0; i<argc; i++)
  {
    if (strcmp(argv[i],"-n")==0) { printNotFoundLibs=1; printFoundLibs=0; } else
    if (strcmp(argv[i],"-f")==0) { printNotFoundLibs=0; printFoundLibs=1; }
    if (strcmp(argv[i],"-maxDepth")==0)  {
                                          maxDepth = atoi(argv[i+1]);
                                         }
  }

  hm = hashMap_Create(2000,1000,0);
  if ( hm == 0 ) { fprintf(stderr,"Could not create hashMap\n"); return 1; }

  runLdd((char*) argv[argc-1],0);


  hashMap_Destroy(hm);
  return 0;
}
