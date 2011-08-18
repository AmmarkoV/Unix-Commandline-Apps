-/***************************************************************************
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

enum errors {
    EARGNUM = 1, /* wrong number of arguments */
    ETMPFAIL,    /* creating temporary file failed */
    ERNMFAIL     /* rename failed */
};

/* rename the given files */
void frename(const char* file_from, const char* file_to) {
    char* errrnm = "error: couldn't rename file: %s %s";
    int status = rename(file_from, file_to);

    if (status) {
        fprintf(stderr, errrnm, file_from, file_to);
        exit(ERNMFAIL);
    }
}

int main(int argc, const char* argv[]) {
    char* errtmpcrt = "error: couldn't create temporary file";
    char* tempfile;

    if (argc != 3) {
        fprintf(stdout, "usage: %s file1 file2\n", __FILE__);
        return EARGNUM;
    }

    /* generate a unique name for the temporary file
     * NOTE: this is dangerous, as the time between the name
     * generation and the rename, could be taken  advantage
     * and be used to actually create a file with the same name
     * as the generated one, and thus failing to use that name.
     * Consider mkstemp or tmpfile which are safer.
     */
    tempfile = tempnam("/tmp", "tmp.mv");
    if (tempfile == NULL) {
        fprintf(stderr, errtmpcrt);
        return ETMPFAIL;
    }

    /* swap the filenames */
    frename(argv[1], tempfile);
    frename(argv[2], argv[1]);
    frename(tempfile, argv[2]);

    /* all good :-) */
    return 0;
}
