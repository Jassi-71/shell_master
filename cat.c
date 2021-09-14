#include <stdio.h>
#include <string.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#define _GNU_SOURCE
#include<linux/limits.h>

char fixedpath[PATH_MAX];

void main(int argc,char **argv){
	char arr[200][10000];

	memset(fixedpath, '\0', sizeof(fixedpath));
	getcwd(fixedpath, sizeof(fixedpath));
	chdir(argv[0]);
	int fd ;

	if(argc==2){
		fd = open(argv[1], O_RDONLY);
	}
	else if(argc==3){
		fd = open(argv[2], O_RDONLY);
	}

	char buf[1];


	if(fd == -1 || fd==NULL){
		printf("%s \n", "Failed to find file \n");
		chdir(fixedpath);
		exit(1);
	}

	if(argc==2){
		while(1){
			int p = read(fd,buf,1);
			if(p==0){
				break;
			}
			if(buf[0]=='\n'){
				memset(buf,0,sizeof(buf));
				printf("\n ");
			}
			else{
				printf("%c",buf[0]);
				memset(buf,0,sizeof(buf));
			}
		}
	}
    else if(!strcmp(argv[1],"-n")){
		int counter = 1;
		printf("%d ", counter);
		while(1){
			int p = read(fd,buf,1);
			if(p==0){
				break;
			}
			if(buf[0]=='\n'){
				memset(buf,0,sizeof(buf));
				counter++;
				printf("\n%d ",counter);
			}
			else{
				printf("%c",buf[0]);
				memset(buf,0,sizeof(buf));
			}
		}
	}	
	else if(!strcmp(argv[1],"-E")){
		while(1){
			int p = read(fd,buf,1);
			if(p==0){
				break;
			}
			if(buf[0]=='\n'){
				memset(buf,0,sizeof(buf));
				printf("%s\n","$");
			}
			else{
				printf("%c",buf[0]);
				memset(buf,0,sizeof(buf));
			}
		}
	}
	else{
		printf("%s\n", "Invalid syntax. Working flags - (-E) & (-n)");
	}

	chdir(fixedpath);
}