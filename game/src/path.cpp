#ifdef __APPLE__
    #include <mach-o/dyld.h>
    #include <unistd.h>
#endif

#include "path.h"
#include <stdlib.h>
#include <string.h>

void InitPath()
{
    #ifdef __APPLE__
        uint32_t buffSize = 0;
        char* buffer = (char*)calloc(1,sizeof(char));
        _NSGetExecutablePath(buffer,&buffSize);
        buffer = (char*)realloc(buffer,(buffSize+1)*sizeof(char));
        memset(buffer,0,sizeof(char)*buffSize);
        _NSGetExecutablePath(buffer,&buffSize);
        
        //Get to home directory
        char* curr = (char*)calloc(2,sizeof(char));
        while (1)
        {
            chdir("..");
            //path should be just '/' and so should return a pointer
            //when the buffer size is capable of holding it
            char* here = getcwd(curr, 2);
            if (here)
                break;

        }   
        free(curr);

        //Traverse buffer until we get to the directory
        char *token = strtok(buffer, "/");
        while(token) {
            chdir(token);  

            token = strtok(NULL, "/");
        }
        free(buffer);
    #endif
}
