#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h> 
#include <unistd.h>  
#include <errno.h>   
#include <sys/wait.h>
#include <sys/stat.h>
#include<linux/limits.h>

char fixedpath[PATH_MAX];

void rm(char string[]){
	struct stat buff;
	const char *path = string;
	printf("%s\n", path);
	int p = stat(path,&buff);
	
	if (p==0){
		int val2 = remove(string);
		if (val2!=0){
			printf("%s\n","This file cannot be deleted");
		}
		else{
			printf("%s\n", "This file is succesfully deleted.");
		}
	}
	else if (p<0){
		printf("%s\n","This file does not exist");
	}
	else if (p>0){
		printf("%s\n","This path is a directory which cannot be deleted");
	}
}

void irm(char string[]){
	struct stat buff;
	const char *path = string;
	printf("%s\n", path);
	int p = stat(path,&buff);
	if (p==0){
		char s[100];
		memset(s,0,100);
		printf("Do you want to remove '%s' file?",string);
		scanf("%s",s);
		if (strcmp(s,"y")==0){
			int val2 = remove(string);
			if (val2!=0){
				printf("%s\n","This file cannot be deleted");
			}
			else{
				printf("%s\n", "This file is succesfully deleted.");
			}
		}
		else{
			printf("%s\n","This file is not deleted");
		}
	}
	else if (p<0){
		printf("%s\n","This file does not exist");
	}
	else if (p>0){
		printf("%s\n","This path is a directory which cannot be deleted");
	}
}

void vrm(char string[]){
	struct stat buf;
	const char *path = string;
	int p = stat(path,&buf);
	printf("%s\n", path);
	if (p==0){
		int val2 = remove(string);
		if (val2==0){
			printf("%s\n", "This file is succesfully deleted.");
		}
		else{
			printf("%s\n","This file cannot be deleted");
		}
		
	}
	else if (p<0){
		printf("%s\n","This file does not exist");
	}
	else if (p>0){
		printf("%s\n","This path is a directory which cannot be deleted");
	}
}


void main(int argc,char** argv){
	char string[PATH_MAX];
	char temp[100];
	memset(string, '\0', sizeof(string));
	memset(fixedpath, '\0', sizeof(fixedpath));
	getcwd(fixedpath, sizeof(fixedpath));
	chdir(argv[0]);


	if (argc==2){
		strcpy(temp, argv[1]);
		strcpy(string, argv[0]);
		strncat(string, "/", 1);
		strncat(string, temp, sizeof(temp));
		//printf("%s\n", string);
		rm(string);
	}
	else if (argc==3){
		strcpy(temp, argv[2]);
		strcpy(string, argv[0]);
		strncat(string, "/", 1);
		strncat(string, temp, sizeof(temp));
		//printf("%s\n", string);
		//printf("%s %s %ld\n", argv[0], fixedpath, sizeof(argv[0]));
		if (!strcmp(argv[1],"-i\n") || !strcmp(argv[1],"-i")){
			irm(string);
		}
		else if (!strcmp(argv[1],"-v") || !strcmp(argv[1],"-v\n")){
			vrm(string);
		}
	}
	else{
		printf("%s\n", "Incorrect syntax");
	}
	chdir(fixedpath);
	memset(string,0,sizeof(string));
	return;
}
