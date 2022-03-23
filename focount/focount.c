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


//I wrote this because of a project I am involved with
//where I need to count occurances of a pattern in ungodly big files
//hope someone else finds it useful.
int main(int argc, const char* argv[])
{
  if (argc<2)
   {
     fprintf(stderr,"Usage : focount filename pattern \n");
     return 1;
   }

  const unsigned int blockSize = 32000; //32K
  char buffer[blockSize];

  const char * filename = argv[1];
  const char * pattern  = argv[2];
  unsigned int patternSize = strlen(pattern);
  FILE * fp = fopen(filename,"r");
  if (fp!=0)
  {
    unsigned long long occurences = 0;
    unsigned int thisReadLength = blockSize;

    while (thisReadLength==blockSize)
    {
      thisReadLength = fread(buffer, 1, blockSize , fp);
    }
    unsigned int i=0;
    fprintf(fp,"Done\n");
    fclose(fp);
    return 0;
  }

  fprintf(stderr,"File %s not found\n",filename);
  return 1;
}
