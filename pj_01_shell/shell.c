#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

//str is the command line and delim is the 
char ** split(char * str, char * delim) {
    char ** components = calloc(5, sizeof(char *));
    char * c = strsep(&str, delim);
    int i = 0;
    while (c != NULL) {
        components[i] = c;
        i++;
        c = strsep(&str, delim);
    }
	components[i] = 0;
    return components;
}

// char *** parse_args(char * line) {
// 	char ** args = split(line, ";");
//     char *** commands = calloc(5, sizeof(char **));;
//     int i = 0;
//     while (args[i] != NULL) {
//         commands[i] = split(args[i], " ");
//         i++;
//     }
//     commands[i] = NULL;
//     return commands;
// }

//in execute we parsed the command so that it separates before and after the < and > into an array, we're passing the command before as the first_command and whats after as the second_command
//the function uses dup and dup2 to redirect
//it returns 0 after finishing
int redirection(char * first_command, char * second_command) {
    int filename = open(second_command, O_RDONLY, 0);
    int f = dup(STDIN_FILENO);
    dup2(filename, STDIN_FILENO);

    char *args[2] = {first_command };
    execvp(first_command, args);

    dup2(f, STDIN_FILENO);
    return 0;
}

int pipe_command(char * first_command, char * second_command) {
    FILE * f = popen(first_command, "r");
    int fd = fileno(f);
    
    if (f) {
        int backup = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
          
        char *args[2] = { second_command };
        execvp(second_command, args);
      
        dup2(backup, STDIN_FILENO);
        
        return 0;
    }
    return -1;
}

int str_index_of(char * str, char item) {
    int i = 0;
    while (str[i]) {
        if (str[i] == item) return i;
        i++;
    }
    return -1;
}

int execute_command() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    while (1) {
        printf("\n%s$ ", cwd);

        char line[100];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;

        char ** commands = split(line, ";");
        int i = 0;
        
        while (commands[i]) {
            // printf("\nExecuting command: %s\n", commands[i]);
            char ** args = split(commands[i], " ");
            
            int pid = fork();

            if (pid > 0) {
                int status;
                wait(&status);
                if (WEXITSTATUS(status) == 131) {
                    return 0; 
                } else if (WEXITSTATUS(status) == 130) {
                    chdir(args[1]);
                    getcwd(cwd, sizeof(cwd));
                } else if (WEXITSTATUS(status)) {
                    printf("Error: %d\n", WEXITSTATUS(status));
                } else {
                    printf("Status: %d\n", WEXITSTATUS(status));
                }
                
            } else {
                int res = 0;
                
                // piping commands
                char ** pipe_split = split(commands[i], "|");
                
                //splits command before and after < and adds it to array redir_less_split
                char ** redir_less_split = split(commands[i], "<");
                //same split but >
                char ** redir_greater_split = split(commands[i], ">");
                if (pipe_split[1]) {
                    pipe_command(pipe_split[0], pipe_split[1]);
                //if split[1] exists, then that means there was a <, if not [1] wldnt exist
                } else if(redir_less_split[1]) {
                	//redirecting 
                    redirection(redir_less_split[0], redir_less_split[1]);
                } else if(redir_greater_split[1]) {
                    redirection(redir_greater_split[1], redir_greater_split[0]);
                // executing commands
                } else {
                    if (strcmp(args[0], "cd") == 0) {
                        res = 130;
                    } else if (strcmp(args[0], "exit") == 0) {
                        res = 131;
                    } else {
                        res = execvp(args[0], args);
                    }
                }
                exit(res);
            }   
            i++;
        }
    }
}
