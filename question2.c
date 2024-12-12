void checkPid(){ //Check the answer of the user and show errors
    if (pid == 0) {
            if (handle_redirection(args) < 0) {
                
                exit(EXIT_FAILURE);
            }
            execvp(args[0], args);
            perror("execvp");
            write(STDOUT_FILENO, "Command not found.\n",19);
            exit(EXIT_FAILURE);

            } else if (pid > 0) {
            wait(&status);
            clock_gettime(CLOCK_MONOTONIC, &end);
            long elapsed_time = calculate_elapsed_time(start, end);

            write_prompt(elapsed_time);
            
            } else {
                exit(EXIT_FAILURE);
            }

        }