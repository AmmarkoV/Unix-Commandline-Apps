/***************************************************************************
* Copyright (C) 2022 by Ammar Qammaz *
* ammarkov@gmail.com *
* *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 2 of the License, or *
* (at your option) any later version. *
* *
* This program is distributed in the hope that it will be useful, *
* but WITHOUT ANY WARRANTY; without even the implied warranty of *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
* GNU General Public License for more details. *
* *
* You should have received a copy of the GNU General Public License *
* along with this program; if not, write to the *
* Free Software Foundation, Inc., *
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. *
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int countOccurences(const char * bigBuffer,unsigned int bigBufferSize,const char * smallPattern,unsigned int smallPaternSize)
{
  unsigned int occurences = 0;
  unsigned int matched    = 0;

  const char * bigBufferEnd = bigBuffer + bigBufferSize;
  char  * ptr = smallPattern;

  while (bigBuffer<bigBufferEnd)
  {
    if (*bigBuffer==*ptr)
    {
      ++matched;
      ptr+=1;

      if (matched==smallPaternSize)
      {
        matched=0;
        ptr = smallPattern;
        occurences+=1;
       }
    } else
    {
      matched=0;
      ptr = smallPattern;
    }

    bigBuffer+=1;
  }

   return occurences;
}



//I wrote this because of a project I am involved with
//where I need to count occurances of a pattern in ungodly big files
//hope someone else finds it useful.
// It is basically a glorified  ` cat dataset.json | grep -o annotationId | wc -l `

int main(int argc, const char* argv[])
{
  if (argc<2)
   {
     fprintf(stderr,"Usage : focount filename pattern \n");
     return 1;
   }

  const unsigned int blockSize = 32000; //32K
  //------------------------------------------
  const char * filename = argv[1];
  const char * pattern  = argv[2];
  unsigned int patternSize = strlen(pattern);
  //------------------------------------------
  if (patternSize >= blockSize)
  {
      fprintf(stderr,"Pattern is too big, cannot accommodate it\n");
      return 1;
  }
  //------------------------------------------


  FILE * fp = fopen(filename,"r");
  if (fp!=0)
  {
   //Our buffer is always :
   // PATTERN    | ------------------- BUFFER -------------------------------|
   //After each read we copy the last part of the buffer to the pattern area to
   //count it again in case of broken patterns
   char * buffer = (char *) malloc(sizeof(char) * (blockSize+patternSize+1) );
   if (buffer!=0)
   {
    //Make sure initial pattern buffer is clear
    memset(buffer,0,sizeof(char) * (patternSize));
    //Make sure the buffer is
    buffer[blockSize]=0; //<- always null-terminated no matter what

    unsigned long long occurences = 0;
    unsigned int thisReadLength = blockSize;

    while (thisReadLength==blockSize)
    {
      thisReadLength = fread(buffer+patternSize, 1, blockSize , fp);
      occurences += countOccurences(buffer+patternSize-1,thisReadLength,pattern,patternSize);

      memcpy(buffer,buffer+(thisReadLength-patternSize),patternSize*sizeof(char));
    }

    fprintf(stdout,"%llu\n",occurences);

    free(buffer);
    buffer = 0;
   }

    fclose(fp);
    return 0;
  }

  fprintf(stderr,"File %s not found\n",filename);
  return 1;
}
