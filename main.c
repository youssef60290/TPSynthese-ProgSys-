#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "header_msg.h"

int main() {
 

char input_user[64];
char *args[16]; 

    welcome_prompt();

    while (1) {
      
            int user_answer = read (STDOUT_FILENO,input_user,sizeof(input_user) - 1);
        
            input_user[user_answer-1] = '\0';

            pid_t pid = fork();

            parse_input(input_user, args);


            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

           
            checkExit();
            checkPid();


}

