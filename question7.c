void handle_redirection(char **args) {
    int i = 0;
    int redirection_handled = 0;


 while (args[i] != NULL) {
     if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                return -1;
            }dup2(fd, STDOUT_FILENO); 
            close(fd);
            args[i] = NULL; 
            redirection_handled = 1;
        }else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                return -1;
            } dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL; 
            redirection_handled = 1;
        }
        i++;
        
}
    return redirection_handled;
}