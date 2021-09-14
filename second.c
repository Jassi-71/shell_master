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
#include <ctype.h>
#define _GNU_SOURCE
#include<linux/limits.h>

char fixedpath[PATH_MAX];
char temppath[PATH_MAX];

int isnum(char* p){
	for (int i = 0; i < strlen(p); ++i)
	{
		if(!isdigit(p[i])){
			return 0;
		}
	}
}

void print_cd_help()
{
    printf("cd: cd [-P] [dir]\n   Change the shell working directory.\n\n   Change the current directory to DIR. The default DIR is the value of the\nHOME shell variable.\n\n   If the directory is not found, then an error message \"Directory not found\" would be displayed. In case of synactical error(s), the error message \"Invalid Syntax\" is displayed.\n\n");
    printf("   Options:\n     -P	   use the physical directory structure without following symbolic links: resolve symbolic links in DIR before processing instances of \"..\".\n");
    printf("      -e	   if the -P option is supplied, and the current working directory cannot be determined successfully, exit with a non-zero status\n\n");
    printf("   The default is to not resolve symbolic links, as if \"-P\" were specified. \"..\" is processed by removing the immediately previous pathname component back to a slash or the beginning of DIR. cd * as is in the bash, is not supported.\n\n");
    printf("   Exit Status:\nExits with exit status 0 if the directory is changed. Exits with status 1 otherwise.\n");
}

void print_pwd_help()
{
	printf("Print the name of the current working directory\n  L print the value of PWD if it names the current working");
	printf("directory\n P print the physical directory without any symbolic links\n");
	printf("Exit Status  Returns 0 unless an invalid option is given or the current directory cannot be read\n");
}

void naviagte_to_directory(char remarr[])
{
    //now we handle the modes
    
    char *nav=NULL;

    char first[100][100];
	char* teo = strtok(remarr," ");
	int count=0;
	while (teo!=NULL){
		//printf("%s\n", teo);
		memset(first[count], '\0', sizeof(first[count]));
		strncpy(first[count],teo,strlen(teo));
		count++;
		memset(teo,0,strlen(teo));
		teo = strtok(NULL," ");
	}
	//printf("%d %s %s\n", count, nav, getenv("HOME"));
	count--;
    int ret=-1;
    memset(&nav, '\0', sizeof(nav));
    switch(count)
    {
        case 0:
            nav = getenv("HOME");
            ret = chdir(nav);
            break;
        case 1: 
            if (strcmp(first[1],"--help")==0)
            {
                print_cd_help();
                return;
            }
            if(strcmp(first[1], "-P")==0)
            {
                nav = getenv("HOME");
                printf("%s\n", nav);
                ret = chdir(nav);            
            }
           else if(strcmp(first[1], "-Pe")==0)
            {
                char pres[1024];
                char *ptr;
                ptr= getcwd(pres, sizeof(pres));
                if(ptr==NULL)
                {
                    perror("Error occured in change directory command");
                    exit(1);
                }
                nav = getenv("HOME");
                printf("%s\n", nav);
                ret = chdir(nav);

            }
            else
            {
               	nav = first[1];
               	printf("%s\n", nav);
                ret = chdir(nav);
            }

            break;
        case 2:
            if(strcmp(first[1], "-P")==0)
            {
                nav = first[2];
                printf("%s\n", nav);
                ret = chdir(nav);
            }
            else if(strcmp(first[1], "-Pe")==0)
            {
                char pres[1024];
                char *ptr;
                ptr= getcwd(pres, sizeof(pres));
                if(ptr==NULL)
                {
                    perror("cd");
                    exit(1);
                }
                nav = first[2];
                printf("%s\n", nav);
                ret = chdir(nav);
            } 
            else 
            {
                printf("Invalid syntax\n");
                ret = -3;
                break;
            }
            break;
        default:
            printf("Invalid syntax\n");
            return;
    }
    if (ret==-1)
    {
        perror("cd");
    }
}

void main(){
	char arr[200][2000];
	int i = 0;
	int index = -1;


	getcwd(fixedpath, sizeof(fixedpath));

	printf("%s\n", "welcome to shell_master");
	printf("%s\n", "Supported internal calls - External and Internal system calls");
	printf("%s\n", "Internal system calls - cd, pwd, history, echo, exit");
	printf("%s\n", "External system calls - rm, ls, date, cat, mkdir");

	while(1){
		index++;
		memset(arr[i], '\0', sizeof(arr[i]));
		getcwd(temppath, sizeof(temppath));
		printf("%s :", temppath);
		memset(temppath, '\0', sizeof(temppath));
		fgets(arr[i],sizeof(arr[i]),stdin);

		//printf("%s\n",arr[i]);

		char file[2000];
		memset(file, '\0', sizeof(file));
		strcpy(file,arr[i]);

		char remarr[2000];
		memset(remarr, '\0', sizeof(remarr));
		strncpy(remarr,arr[i],strlen(arr[i])-1);

		char* section = strtok(file," ");

		if(!strcmp(section,"echo") || !strcmp(section,"echo\n")){

			char* flag = strtok(NULL, " ");
			char* stringreq = strtok(NULL,"\0");
			if(!strcmp(section,"echo\n")){
				printf("\n");
			}
			else if(!strcmp(flag,"-e")){
				char temp[100];
				int i = 0, i1 = 0, j = 0, lenght = strlen(stringreq), iopen = -1, iclose = -1;
				while(i<lenght){
					if(i>0 && i<lenght-1 && stringreq[i]=='\\' && stringreq[i-1]==' ' && i>iopen && i<iclose){
						if(stringreq[i+1]=='n'){
						temp[i1] = '\n';
						}
						else if(stringreq[i+1]=='t'){
							temp[i1] = '\t';
						}
						i1 = i1+1;
						i++;
					}
					else if(stringreq[i]!='\\'){
						temp[i1] = stringreq[i];
						i1++;
					}
					i++;

				}
				printf("%s\n", temp);
				memset(temp,0,100);
			}
			else if(!strcmp(flag,"-n")){
				printf("%s", stringreq);
				printf("\n");
			}
			else{
				printf("%s\n", "Invalid Sysntax. supported flags - (-e), (-n)");
			}
			
		}
		else if(!strcmp(section,"pwd\n") || !strcmp(section,"pwd")){
			char s[100]; 
    		char first[100][100];
			char* teo = strtok(remarr," ");
			int count=0;
			while (teo!=NULL){
				//printf("%s\n", teo);
				memset(first[count], '\0', sizeof(first[count]));
				strncpy(first[count],teo,strlen(teo));
				count++;
				memset(teo,0,strlen(teo));
				teo = strtok(NULL," ");
			}
			//printf("%d\n", count);
			if(count == 1){
				printf("%s\n", getcwd(s, 100)); 
			}
			else if(count == 2){
				if(!strcmp(first[1],"help\n") || !strcmp(first[1],"help")){
					print_pwd_help();
				}
			}
			memset(remarr, '\0', sizeof(remarr));
		}
		else if(!strcmp(section,"cd")){
			naviagte_to_directory(remarr);
			memset(remarr, '\0', sizeof(remarr));

		}

		else if(!strcmp(section,"history\n") || !strcmp(section,"history")){
			
				//printf("%s\n", remarr); 
			char first[100][100];
			char* teo = strtok(remarr," ");
			int count=0;
			while (teo!=NULL){
				memset(first[count], '\0', sizeof(first[count]));
				strncpy(first[count],teo,strlen(teo));
				count++;
				memset(teo,0,strlen(teo));
				teo = strtok(NULL," ");
			}
			//printf("%d\n", count);
			if(count == 1){
				printf("\n");
				for (int j = 0; j < i; ++j)
				{
					printf("%s", arr[j]);
				}
				printf("\n");
			}
			else if(count == 2){
				if (strcmp(first[1],"-c")==0){
					printf("All the commands from the history have been removed \n", first[1]);
					memset(arr,0,700);
					index=-1;
					count = 0;
					i = 0;
				}
				else if (isnum(first[1])==1){
					printf("The latest %s commads are as follow: \n", first[1]);
					int n = atoi(first[1]);
					if (n <= i+1){
						for (int historychecker=i-n;historychecker<i;historychecker++){
							printf("%s",arr[historychecker]);
						}
					}
				}
				printf("\n");
			}
			else{
				printf("%s\n", "Invalid Sysntax");
			}
			memset(remarr, '\0', sizeof(remarr));
		}

		else if(!strcmp(section,"ls\n") || !strcmp(section,"ls")){
			pid_t pid;
			pid = fork();

			memset(temppath, '\0', sizeof(temppath));
			getcwd(temppath, sizeof(temppath));

			chdir(fixedpath);

			if(pid<0){
				fprintf(stderr, "%s\n","Fork failed:" );
			}
			else if(pid==0){
				char first[100][100];
				char* teo = strtok(remarr," ");
				int count=0;
				while (teo!=NULL){
					//printf("%s\n", teo);
					memset(first[count], '\0', sizeof(first[count]));
					strncpy(first[count],teo,strlen(teo));
					count++;
					memset(teo,0,strlen(teo));
					teo = strtok(NULL," ");
				}
				//printf("%d %s %s\n", count, first[0], first[1]);
				if(count == 1){
					//printf("%s\n", first[0]);
					execl("./ls", "none", temppath);
				}
				else if(count == 2){
					//printf("%s %s\n", first[0], first[1]);
					execl("./ls",first[1], temppath);
				}
				else{
					printf("%s\n", "Invalid Sysntax.");
				}

			}
			else{
				waitpid(-1,NULL,0);
			}

			chdir(temppath);
			memset(temppath, '\0', sizeof(temppath));
			memset(remarr, '\0', sizeof(remarr));
		}

		else if(!strcmp(section,"date\n") || !strcmp(section,"date")){
			pid_t pid;
			pid = fork();
			if(pid<0){
				fprintf(stderr, "%s\n","Fork failed:" );
			}
			else if(pid==0){
			char first[100][100];
				char* teo = strtok(remarr," ");
				int count=0;
				while (teo!=NULL){
					//printf("%s\n", teo);
					memset(first[count], '\0', sizeof(first[count]));
					strncpy(first[count],teo,strlen(teo));
					count++;
					memset(teo,0,strlen(teo));
					teo = strtok(NULL," ");
				}
				//printf("%d\n", count);
				if(count == 1){
					//printf("%s\n", first);
					execlp("./date",NULL);
				}
				else if(count == 2){
					//printf("%s %s\n", first,second);
					execlp("./date",first[1],NULL);
				}
			}
			else{
				waitpid(-1,NULL,0);
				printf("\n");
			}
			memset(remarr, '\0', sizeof(remarr));
		}
		else if(!strcmp(section,"rm\n") || !strcmp(section,"rm")){
			pid_t pid;

			memset(temppath, '\0', sizeof(temppath));
			getcwd(temppath, sizeof(temppath));

			chdir(fixedpath);

			pid = fork();
			if(pid<0){
				fprintf(stderr, "%s\n","Fork failed:" );
			}
			else if(pid==0){
				if(!strcmp(section,"rm")){
					//printf("%s\n", remarr); 
					char first[100][100];
					char* teo = strtok(remarr," ");
					int count=0;
					while (teo!=NULL){
						//printf("%s\n", teo);
						memset(first[count], '\0', sizeof(first[count]));
						strncpy(first[count],teo,strlen(teo));
						count++;
						memset(teo,0,strlen(teo));
						teo = strtok(NULL," ");
					}
					//printf("%s %ld\n", temppath, sizeof(temppath));
					if(count == 2){
						//printf("%s\n", first);
						execlp("./rmdir", temppath, first[1],NULL);
					}
					else if(count == 3){
						//printf("%s %s\n", first,second);
						execlp("./rmdir", temppath, first[1],first[2],NULL);
					}
				}
				memset(remarr, '\0', sizeof(remarr));
			}
			else{
				waitpid(-1,NULL,0);
				printf("\n");
			}
			chdir(temppath);
			memset(temppath, '\0', sizeof(temppath));
			memset(remarr, '\0', sizeof(remarr));
		}
		else if(!strcmp(section,"mkdir\n") || !strcmp(section,"mkdir")){
			pid_t pid;

			memset(temppath, '\0', sizeof(temppath));
			getcwd(temppath, sizeof(temppath));

			chdir(fixedpath);

			pid = fork();
			if(pid<0){
				fprintf(stderr, "%s\n","Fork failed:" );
			}
			else if(pid==0){
				if(!strcmp(section,"mkdir")){
					//printf("%s\n", remarr); 
					char first[100][100];
					char* teo = strtok(remarr," ");
					int count=0;
					while (teo!=NULL){
						//printf("%s\n", teo);
						memset(first[count], '\0', sizeof(first[count]));
						strncpy(first[count],teo,strlen(teo));
						count++;
						memset(teo,0,strlen(teo));
						teo = strtok(NULL," ");
					}
					//printf("%d\n", count);
					if(count == 2){
						printf("%s\n", first[1]);
						execlp("./mkdir", temppath, first[1],NULL);
					}
					else if(count == 3){
						printf("%s %s\n", first[1], first[2]);
						execlp("./mkdir", temppath, first[1],first[2],NULL);
					}
				}
			}
			else{
				waitpid(-1,NULL,0);
				printf("\n");
			}
			chdir(temppath);
			memset(temppath, '\0', sizeof(temppath));
			memset(remarr, '\0', sizeof(remarr));
		}
		else if(!strcmp(section,"cat")){
			pid_t pid;
			pid = fork();

			memset(temppath, '\0', sizeof(temppath));
			getcwd(temppath, sizeof(temppath));

			chdir(fixedpath);

			if(pid<0){
				fprintf(stderr, "%s\n","Fork failed:" );
			}
			else if(pid==0){
				if(!strcmp(section,"cat")){
					//printf("%s\n", remarr); 
					char first[100][100];
					char* teo = strtok(remarr," ");
					int count=0;
					while (teo!=NULL){
						//printf("%s\n", teo);
						memset(first[count], '\0', sizeof(first[count]));
						strncpy(first[count],teo,strlen(teo));
						count++;
						memset(teo,0,strlen(teo));
						teo = strtok(NULL," ");
					}
					//printf("%d\n", count);
					if(count == 2){
						//printf("%s %s\n", first[1], first[2]);
						execlp("./cat", temppath, first[1]);
					}
					else if(count == 3){
						//printf("%s %s\n", first[1], first[2]);
						execlp("./cat", temppath, first[1],first[2]);
					}
					else{
						printf("%s\n", "Invalid Sysntax");
					}
				}
			}
			else{
				waitpid(-1,NULL,0);
				printf("\n");
			}
			chdir(temppath);
			memset(temppath, '\0', sizeof(temppath));
			memset(remarr, '\0', sizeof(remarr));

		}

		else if(!strcmp(section,"exit\n")){
			break;
		}
		else{
			printf("%s\n", "Invalid syntax. Please check again.");
		}
		i++;
		
	}


}