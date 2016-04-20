#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <regex.h>

int validateFilename(char *filename)
{
    regex_t r;
    char expression[100]="^[a-zA-Z0-9_.]";

    //^[A-Za-z0-9_]+\\.[A-Za-z]+
    // Please insert the file extensions over here
    int compilestatus=regcomp (&r, "^[A-Za-z0-9_]+\\.(jpg|JPG|gif|GIF|doc|DOC|pdf|PDF)",REG_EXTENDED);
    if(compilestatus)
    {
        printf("error compiling regular expression");
    }
   // printf("filename is %s",filename);
    int match=regexec(&r, filename, 0, NULL, 0);
    if(!match)
        return 1;
    if(match==REG_NOMATCH)
        return 0;

    return 0;
}


/*
 Module to detect if it is a device or not
 1 - device
 0 - regular file
 */

int fileOrDevice(char * filename)
{
    struct stat buffer;
    int         status;
    status = stat(filename, &buffer);
    if(S_ISDIR(buffer.st_mode)!=0 || S_ISCHR(buffer.st_mode)!=0|| S_ISBLK(buffer.st_mode)!=0)
        return 1; // it is a device
    return 0; // it is file
}


int main(int argc, const char * argv[]) {
    
    char filename[100];
    
    printf("Enter a file name\n");
    scanf("%s",filename);
    int filestatus=validateFilename(filename);
    printf("%d",filestatus);
    return 0;
}
