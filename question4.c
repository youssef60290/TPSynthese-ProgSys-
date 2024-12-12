#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header_msg.h"

int status = 0;

void int_to_string(int value, char *str) {
    char temp[10];
    int i = 0;

    
    do {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);


     int j = 0;
    while (i > 0) {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
}


void write_prompt(){ //function for dynamic prompt
    char buffer[128];
    size_t len = 0;
   

    memcpy(buffer, PROMPT, strlen(PROMPT));
    len = strlen(PROMPT);

    if(WIFEXITED(status)){
        memcpy(buffer, PROMPT_EXIT_PREFIX, strlen(PROMPT_EXIT_PREFIX));
        len += strlen(PROMPT_EXIT_PREFIX);

        char code_str[10];
        int_to_string(WEXITSTATUS(status), code_str);
        memcpy(buffer + len, code_str, strlen(code_str));
        len += strlen(code_str);
    }else if (WIFSIGNALED(status)) {
 
        memcpy(buffer, PROMPT_SIGN_PREFIX, strlen(PROMPT_SIGN_PREFIX));
        len += strlen(PROMPT_SIGN_PREFIX);
        char signal_str[10];

        int_to_string(WTERMSIG(status), signal_str);
        memcpy(buffer + len, signal_str, strlen(signal_str));
        len += strlen(signal_str);
    }else {
     
        memcpy(buffer, PROMPT, strlen(PROMPT));
        len = strlen(PROMPT);
    }
    
    memcpy(buffer + len, PROMPT_SUFFIX, strlen(PROMPT_SUFFIX));
    len += strlen(PROMPT_SUFFIX);
    write(STDOUT_FILENO, buffer, len);

}