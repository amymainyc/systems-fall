#ifndef SHELL

char ** split(char * str, char * delim);
char *** parse_args(char * line);
void execute_command();

#endif