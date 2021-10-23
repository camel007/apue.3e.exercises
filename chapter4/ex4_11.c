#include "apue.h"
#include <dirent.h>
#include <limits.h>

#define FTW_F 1 /*file other than directory*/
#define FTW_D 2 /*directory*/
#define FTW_DNR 3 /*directory cann't be read*/
#define FTW_NS 4 /*file than cann't stat*/

static long nreg, nblk, nchr, nfifo, nslink, nsock, ndir, ntot;

typedef int MyFunc(const char *pathname, const struct stat *statptr, int type);

static MyFunc myfunc;
static int myftw(char *, MyFunc *);
static int dopath(MyFunc *);

int
main(int argc, char *argv[])
{
int ret;
    if (argc != 2)
        err_quit("usage:  ftw  <starting-pathname>");
    ret = myftw(argv[1], myfunc);       /* does it all */
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;       /* avoid divide by 0; print 0 for all counts */
    printf("regular files  = %7ld, %5.2f %%\n", nreg,
      nreg*100.0/ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir,
      ndir*100.0/ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk,
      nblk*100.0/ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr,
      nchr*100.0/ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo,
      nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink,
      nslink*100.0/ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock,
      nsock*100.0/ntot);
    exit(ret);
}

static char *fullpath;
static char *filename;
static size_t pathlen;

static int myftw(char *pathname, MyFunc *func){
    fullpath = path_alloc(&pathlen);
    
    if(pathlen <= strlen(pathname)){
        if((fullpath = realloc(fullpath, pathlen)) < 0) {
            err_sys("realloc failed\n");
        }
        
    }
    strcpy(fullpath, pathname);
    if(chdir(fullpath) < 0){
        return -1;
    }
    filename = path_alloc(&pathlen);
    filename[0] = '.';
    filename[1] = 0;

    return dopath(func);
}

static int dopath(MyFunc *func){
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;

    printf("filepath1: %s\n", fullpath);
    if(lstat(filename, &statbuf) < 0){
        return func(fullpath, &statbuf, FTW_NS);
    }
    if(S_ISDIR(statbuf.st_mode) == 0){
        return func(fullpath, &statbuf, FTW_F);
    }

    if((ret = func(fullpath, &statbuf, FTW_D)) != 0){
        return ret;
    }

    n = strlen(fullpath); // 递归能使用全局的fullpath，重点在这个n
    if(n + NAME_MAX + 2 > pathlen){
        pathlen *= 2;
        if((fullpath = realloc(fullpath, pathlen)) == NULL) {
            err_sys("realloc failed");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = '\0';

    if(chdir(fullpath) < 0){
        return func(fullpath, &statbuf, FTW_DNR);
    }

    if((dp = opendir(".")) == NULL){
        return func(fullpath, &statbuf, FTW_DNR);
    }

    while((dirp = readdir(dp)) != NULL){
        if(strcmp(dirp->d_name, ".") == 0|| strcmp(dirp->d_name, "..") == 0){
            continue;
        }
        strcpy(&fullpath[n], dirp->d_name);
        strcpy(filename, dirp->d_name);
        if((ret = dopath(func)) != 0){
            break;
        }
    }
    
    fullpath[n-1] = '\0';
    printf("filepath2: %s\n\n", fullpath);
    chdir("..");

    if(closedir(dp) < 0){
        err_ret("cann't close dir: %s\n", fullpath);
    }

    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type){
    switch(type){
        case FTW_F:
            switch(statptr->st_mode & S_IFMT){
                case S_IFREG: nreg++; break;
                case S_IFBLK: nblk++; break;
                case S_IFCHR: nchr++; break;
                case S_IFIFO: nfifo++; break;
                case S_IFLNK: nslink++; break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR: 
                    err_sys("for S_IFDIR for %s", pathname);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can’t read directory %s", pathname);
            break;
        case FTW_NS:
            err_ret("stat error for %s", pathname);
            break;
        default:
            err_dump("unknown type %d for pathname %s", type, pathname);
    }

    return 0;
}