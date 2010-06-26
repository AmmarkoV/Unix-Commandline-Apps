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
#include <time.h>
/*
 Small command line utility to pick randomly between N arguments

*/
int main(int argc, const char* argv[] )
{
    if ( argc <= 1 )
     {
       printf("Usage : pick arg1 arg2 .. argN !\n");
       printf("Will echo a random argument\n");
       return 0;
     }

    /* initialize random generator */
    srand ( time(NULL) );

    int downlimit=1,uplimit=argc-1;
    int i = rand() % uplimit;
    /* This returns a value between 0 and N - 1 ( remember the argument zero is the exe name ) */

    i+=downlimit;
    /* We pad the result to 1 and N */

    printf("%s\n",argv[i]);

    return 0;
}
