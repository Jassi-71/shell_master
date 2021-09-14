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

void dir(char string[]){
	int check;
	check = mkdir(string,0700);
	if (check!=0){
		printf("Here directory exists.\nUnable to create directory\n");
	}
	else{
		printf("%s\n","Directory created sucessfully");
	}
}

void vd(char string[]){
	int check;
	check = mkdir(string,0700);
	if (check!=0){
		printf("%s\n","Here directory exists.\nUnable to create directory\n");
	}
	else{
		printf("%s\n","Directory created sucessfully");
	}
}

void pd(char string[]){
	struct stat st = {0};
	int check;
	char *arr[1000];
	memset(arr,0,1000);
	char *token = strtok(string,"/");
	int count=0;
	while (token!=NULL){
		arr[count] = token;
		count++;
		token = strtok(NULL,"/");
	}
	char dir[1000];
	int flag = 0;
	for (int i=0;i<count;i++){
		strcat(dir,"/");
		strcat(dir,arr[i]);
		if (stat(dir, &st) == -1){
			check = mkdir(dir,0700);
			if (check!=0){
				//printf("%s\n","Here directory exists.\nUnable to create directory");
			}
			else{
				flag = 1;
			}
		}
		else{
			//printf("%s\n","The directory exists");
		}
	}
	if(flag==1){
		printf("%s\n", "The specified folder is created");
	}
	else{
		printf("%s\n", "the specified folder already exists");
	}
}

void main(int argc,char **argv){
	char string[PATH_MAX];
	char temp[100];
	memset(string, '\0', sizeof(string));
	memset(fixedpath, '\0', sizeof(fixedpath));
	getcwd(fixedpath, sizeof(fixedpath));
	chdir(argv[0]);
	//printf("%d\n", argc);
	if (argc==2){
		strcpy(temp, argv[1]);
		strcpy(string, argv[0]);
		strncat(string, "/", 1);
		strncat(string, temp, sizeof(temp));
		printf("%s\n", string);
		dir(string);
	}
	else if(argc==3){
		strcpy(temp, argv[2]);
		strcpy(string, argv[0]);
		strncat(string, "/", 1);
		strncat(string, temp, sizeof(temp));
		printf("%s\n", string);
		//printf("%s %s\n",argv[0] ,argv[1]);
		if (!strcmp(argv[1],"-v")){
			vd(string);
		}
		else if(!strcmp(argv[1],"-p")){
			//printf("%s\n", argv[1]);
			pd(string);
		}
	}
	else{
		printf("%s\n", "Invalid Syntax");
	}
	
	memset(string,0,100);
	return;
}
