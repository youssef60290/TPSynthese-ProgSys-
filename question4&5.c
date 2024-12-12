#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header_msg.h"

int status = 0;

void int_to_string(int value, char *str) {
    char temp[10];
    int i = 0;
    int is_negative = 0;

 if (value < 0) {
        is_negative = 1;
        value = -value;
    }
    
     if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

       while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

      if (is_negative) {
        temp[i++] = '-';
    }
 

     int j = 0;
    while (i > 0) {
        str[j++] = temp[--i];
    }
    str[j] = '\0';
}

long calculate_elapsed_time(struct timespec start, struct timespec end) {
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    return (seconds * 1000) + (nanoseconds / 1000000);
}

void write_prompt(long elapsed_time){ //function for dynamic prompt
    char buffer[128] = {0};
    size_t len = 0;
   

    memcpy(buffer, PROMPT, strlen(PROMPT));
    len = strlen(PROMPT);

    if(WIFEXITED(status)){
        memcpy(buffer, PROMPT_EXIT_PREFIX, strlen(PROMPT_EXIT_PREFIX));
        len += strlen(PROMPT_EXIT_PREFIX);

        char code_str[10] = {0};
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
    }
    memcpy(buffer + len, PROMPT_SEPARATOR, strlen(PROMPT_SEPARATOR));
    len += strlen(PROMPT_SEPARATOR);
    
    char time_str[10] = {0};
    int_to_string(elapsed_time, time_str);
    memcpy(buffer + len, time_str, strlen(time_str));
    len += strlen(time_str);
   

     memcpy(buffer + len, MS_SUFFIX, strlen(MS_SUFFIX));
    len += strlen(MS_SUFFIX);

    memcpy(buffer + len, PROMPT_SUFFIX, strlen(PROMPT_SUFFIX));
    len += strlen(PROMPT_SUFFIX);

    buffer[len] = '\0';

    write(STDOUT_FILENO, buffer, len);

}