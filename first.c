//
//  main.cpp
//  cOS
//
//  Created by yihong dai on 9/7/14.
//  Copyright (c) 2014 yihong dai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int readFromStdIn(char * , int);
int runProcess ( char ** );
int main(int argc, const char * argv[])
{
    while(1)
    {
        int initialSize = 2;
        char *bufferReadIn = (char*)malloc(initialSize);
        readFromStdIn(bufferReadIn, initialSize);
        char * delimiter = (char *)" ";
        
        
        
        char *token = strtok(bufferReadIn,delimiter);
        char ** commandLine = (char **)malloc (1024);
        int count = 0 ;
        if(strcmp(token,"exit")==0)
        {
            return EXIT_SUCCESS;
        }
        commandLine[count] = (char *)malloc(strlen(token)+1);
        strcpy(commandLine[count],(const char *)token);
        while(token!= NULL)
        {
            count++;

            token = strtok(NULL, delimiter);
            if(token == NULL)
            {
                break;
            }
            commandLine[count] = (char *)malloc(strlen(token)+1);
            strcpy(commandLine[count],(const char *)token);
        }
        printf("count is, %d", count);
        commandLine[count] = NULL;
        runProcess ( commandLine);
        printf("\n");
        for( int i = 0; i < count; i++ )
        {
            free(commandLine[i]);
        }
        free(commandLine);
    }
	return EXIT_SUCCESS;
}

int readFromStdIn(char * buffer , int initialSize)
{
   // printf(" error messag ", strerror(errno));
    size_t dum;
    int val;
    printf("$ ");
    if((val = (int)getline(&buffer,&dum , stdin) )== -1)
    {
        perror("errorD: something wrong happens\n");
    }
    
    if(strlen(buffer)> initialSize)
    {
        
        buffer  = (char*)realloc(buffer,initialSize*2);
    }
    buffer[strlen(buffer)-1]='\0';
    int strLen = (int)strlen(buffer);
    return strLen;
}

int runProcess ( char ** command)
{
    pid_t pid;
    int status ;
    pid = fork();
    if(pid == 0 )
    {
        execvp(command[0], command);
        printf(" command is %s" , command[0]);
        printf("errorA: %s" ,strerror(errno));
        exit(EXIT_FAILURE);
    }
    else if(pid>0){
        status =  wait(&pid);
        if(status<0)
        {
            printf("errorB: %s" ,strerror(errno));
        }
    }
    else{
        printf("errorC: %s" ,strerror(errno));
        exit(EXIT_FAILURE);
    }
    return 1;
}



