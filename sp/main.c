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
