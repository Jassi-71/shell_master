#include <stdio.h>
#include <time.h>
#include <string.h>
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
 
void main(int argc,char **argv){
    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

	time_t T2;
	time(&T2);    
    struct  tm tm2 = *gmtime(&T2);

    char day[40];
    char mon[40];

    if(tm.tm_wday==1){
    	strcpy(day,"Monday");
    }
    else if(tm.tm_wday==2){
    	strcpy(day,"Tuesday");
    }
    else if(tm.tm_wday==3){
    	strcpy(day,"Wednesday");
    }
    else if(tm.tm_wday==4){
    	strcpy(day,"Thursday");
    }
    else if(tm.tm_wday==5){
    	strcpy(day,"Friday");
    }
    else if(tm.tm_wday==6){
    	strcpy(day,"Saturday");
    }
    else if(tm.tm_wday==7){
    	strcpy(day,"Sunday");
    }

    if(tm.tm_mon==1){
    	strcpy(mon,"January");
    }
    else if(tm.tm_mon==2){
    	strcpy(mon,"February");
    }
    else if(tm.tm_mon==3){
    	strcpy(mon,"March");
    }
    else if(tm.tm_mon==4){
    	strcpy(mon,"April");
    }
    else if(tm.tm_mon==5){
    	strcpy(mon,"May");
    }
    else if(tm.tm_mon==6){
    	strcpy(mon,"June");
    }
    else if(tm.tm_mon==7){
    	strcpy(mon,"July");
    }
    else if(tm.tm_mon==8){
    	strcpy(mon,"August");
    }
    else if(tm.tm_mon==9){
    	strcpy(mon,"September");
    }
    else if(tm.tm_mon==10){
    	strcpy(mon,"October");
    }
    else if(tm.tm_mon==11){
    	strcpy(mon,"November");
    }
    else if(tm.tm_mon==12){
    	strcpy(mon,"December");
    }
   

   char* flag;
    if(argc==1){
        flag = argv[0];
    }
    else{
        flag = "";
    }
   // -u
   // -R
    if(!strcmp(flag,"")){
	    if(tm.tm_hour>=12){
	    	printf("%s %d %s %d %02d:%02d:%02d %s %s\n",day,tm.tm_mday,mon,tm.tm_year+1900,tm.tm_hour-12, tm.tm_min, tm.tm_sec,"PM","IST" );
		}
		else if(tm.tm_hour<12){
	    	printf("%s %d %s %d %02d:%02d:%02d %s %s\n",day,tm.tm_mday,mon,tm.tm_year+1900,tm.tm_hour, tm.tm_min, tm.tm_sec,"AM","IST" );
		}
	}
	else if(!strcmp(flag,"-u")){
	    if(tm.tm_hour>=12){
	    	printf("%s %d %s %d %02d:%02d:%02d %s %s\n",day,tm2.tm_mday,mon,tm2.tm_year+1900,tm2.tm_hour-12, tm2.tm_min, tm2.tm_sec,"PM","IST" );
		}
		else if(tm.tm_hour<12){
	    	printf("%s %d %s %d %02d:%02d:%02d %s %s\n",day,tm2.tm_mday,mon,tm2.tm_year+1900,tm2.tm_hour, tm2.tm_min, tm2.tm_sec,"AM","IST" );
		}
	}
	else if(!strcmp(flag,"-R")){
        if(tm.tm_hour>=12){
	        printf("%s, %d %s %d %02d:%02d:%02d %s\n",day,tm.tm_mday,mon,tm.tm_year+1900,tm.tm_hour-12, tm.tm_min, tm.tm_sec,"+0530" );
        }
        else{
            printf("%s, %d %s %d %02d:%02d:%02d %s\n",day,tm.tm_mday,mon,tm.tm_year+1900,tm.tm_hour-12+12, tm.tm_min, tm.tm_sec,"+0530" );   
        }
	}
    else{
        printf("%s\n", "Command not supported");
    }
 
    return;
    
}