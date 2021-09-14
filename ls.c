#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<linux/limits.h>
#include <unistd.h>

char pathname[PATH_MAX];

void main(int argc,char const* argv[]){
    char* string= (char *)argv[0];
    memset(pathname, '\0', sizeof(pathname));
    strcpy(pathname, argv[1]);

    //printf("%s \n", string);
    if(!strcmp(string,"none")){
        struct dirent **curdir;
        int n=scandir(pathname,&curdir,0,alphasort);
        int i=0;
        while(i<n){
            char* file = curdir[i]->d_name;
            if(file[0]!='.'){
                printf("%s ",file);
                free(curdir[i]);
            }
            i+=1;
        }
        printf("\n");
        free(curdir);
    }
    else if(!strcmp(string, "-a")){
        struct dirent **curdir;
        int n=scandir(pathname,&curdir,0,alphasort);
        int i=0;
        while(i<n){
            char* file = curdir[i]->d_name;
            printf("%s ",file);
            free(curdir[i]);
            i+=1;
        }
        printf("\n");
        free(curdir);

    }
    else if(!strcmp(string, "-R")){
        struct dirent *curdir;
        DIR *dirp=opendir(pathname);        //returns pointer of dir type
        if(dirp==NULL){
            printf("Error as type of directory is null\n");
        }
        else{
            while(curdir!=NULL){
                printf("%s ",curdir->d_name);
                curdir=readdir(dirp);
            }
        }
        printf("\n");
        free(curdir);
        free(dirp);
    }
    else if(!strcmp(string, "-1")){
        struct dirent **curdir;
        int n=scandir(pathname,&curdir,0,alphasort);
        int i=0;
        while(i<n){
            char* file = curdir[i]->d_name;
            if(file[0]!='.'){
                printf("%s \n",file);
                free(curdir[i]);
            }
            i+=1;
        }
        printf("\n");
        free(curdir);
    }
    else{
        printf("%s\n", "Command Not Supported. Please try again.");
    }
    return;
}