/**
 * Write a simple version of the UNIX find program: find all the files in a directory tree with a specific name.
 * Your solution should be in the file user/find.c.
 * 
 * So, if i got this right: find . a means to search fo file 'a' inside '.' directory
 */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// doc : ok wait, what's the plan here?
// open direcotry, get all file names and compare to passed arg?
void
find(char *path, char *filename)
{
   struct dirent de;
   struct stat st;

    int fd = open(path, 0);
    if (fd < 0)
    {
        fprintf(2, "find: cannot open file %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

}

int
main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("Usage: find filepath(e.g find . a)");
        exit(1);
    }

    find(argv[1], argv[2]);

    exit(0);
}