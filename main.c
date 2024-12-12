#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header_msg.h"
#include "question1.c"
#include "question4.c"


int main() {
 

char input_user[64];

    welcome_prompt();

   

    
    while (1) {

            int user_answer = read (STDOUT_FILENO,input_user,sizeof(input_user) - 1);
        
            input_user[user_answer-1] = '\0';

            pid_t pid = fork();

           

            if (strcmp(input_user, EXIT_CONDITION) == 0 || user_answer <= 0) {
            write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
            break;
            }
            
            if (pid == 0) {
            execlp(input_user, input_user, NULL);
            write(STDOUT_FILENO, "Command not found.\n",19);
            exit(EXIT_FAILURE);

            } else if (pid > 0) {
                wait(&status);
            } else {
                exit(EXIT_FAILURE);
            }

             write_prompt(); 

        }


}
