/***************************************************************************
* Copyright (C) 2015 by Ammar Qammaz *
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


int main(int argc, const char* argv[])
{
  FILE * fp = fopen("paramSpy.txt","a");
  if (fp!=0)
  {
    unsigned int i=0;
    fprintf(fp,"New Run \n%u arguments total\n",argc);
    for (i=0; i<argc; i++)
     {
       fprintf(fp,"argument %u is %s \n",i,argv[i]);
     }
    fprintf(fp,"Done\n",argc);
    fclose(fp);
  }

    return 0;
}
