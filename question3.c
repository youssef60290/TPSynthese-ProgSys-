void checkExit(){ //Check if the input is ("exit or CTRL+D")
     if (strcmp(input_user, EXIT_CONDITION) == 0 || user_answer <= 0) {
            write(STDOUT_FILENO, EXIT_MESSAGE, strlen(EXIT_MESSAGE));
            break;
            }
}
