#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header_msg.h"

void welcome_prompt(){
    	
    write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
    write(STDOUT_FILENO, ASK_MESSAGE, strlen(ASK_MESSAGE));
}

