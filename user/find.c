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

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

// doc : ok wait, what's the plan here?
// open directory, get all file names and compare to passed arg?
// open directory -> find out what type of files are in there -> if file, compare ->
// if dir -> invoke find recursively.
void
find(char *path, char *filename)
{
   struct dirent de;
   struct stat st;

    int fd = open(path, 0);
    if (fd < 0)
    {
        fprintf(2, "find: cannot open directory %s\n", path);
        return;
    }

    // doc : than, get meta info on that file 
    if(fstat(fd, &st) < 0)
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
        printf("Usage: find filepath(e.g find . a)\n");
        exit(1);
    }

    find(argv[1], argv[2]);

    exit(0);
}