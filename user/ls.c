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

// doc : tahes file path as an argument
void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st; // doc : used to extract meta info about a file

  // doc : first, try to open the file
  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  // doc : than, get meta info on that file 
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // doc : figure out what type of file(file or dir) is it and proceed accordingly
  switch(st.type){
  // doc : pretty straightforward case. if it's a file, just preatty print stats 
  case T_FILE:
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);    // doc : make scope copy of path into buf
    p = buf+strlen(buf);  // doc : initialize p to point to the END of buf
    *p++ = '/';           // doc : end buf with '/'
    while(read(fd, &de, sizeof(de)) == sizeof(de)){ // doc : get meta info on direcotry
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  // doc : so basically if just 'ls' is run, pass '.' argument to it
  if(argc < 2){
    ls(".");
    exit(0);
  }
  // doc : if multiple args, run ls for each of them
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}
