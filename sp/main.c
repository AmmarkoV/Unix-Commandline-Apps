/***************************************************************************
* Copyright (C) 2010 by Ammar Qammaz *
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
/*
 Small command line utility to pick randomly between N arguments

*/
int main(int argc, const char* argv[] )
{
    if ( argc != 3 )
     {
       printf("Usage : sp arg1 arg2!\n");
       printf("Will swap two files\n");
       return 0;
     }


    /* We want to make 3 cp operations and one rm */
    int i=0;
    char command[2048]={0};

    sprintf(command,"mv %s intermediate_copy_file_123456789_1\n",argv[1]);
    i=system(command);
    if ( i!=0 ) { printf("Error moving to intermediate file for swapping\n");
                  return 1; }

    sprintf(command,"mv %s %s\n",argv[2],argv[1]);
    i=system(command);
    if ( i!=0 ) { printf("Error moving from target file to target while swapping\n"); return 1; }

    sprintf(command,"mv intermediate_copy_file_123456789_1 %s\n",argv[2]);
    i=system(command);
    if ( i!=0 ) { printf("Error moving intermidiate file to target for swapping\n"); return 1; }


    return 0;
}
