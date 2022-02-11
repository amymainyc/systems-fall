# systems-pj-01

Shell Features
- ';' to separate mutliple commands
- Redirection and piping (there must be no spaces around the pipe character for it to execute properly)
- 

Failed Attempts

- Redirection: 
	- Had int f1, int f2 as my parameteres and I was just dup2ing integers. I don't know why I did that
	- Made 2 redirects for each direction and then realized that I could just use one and then switch the parameters for the reverse redirect 

Bugs

All Function Headers
- char ** split(char * str, char * delim)
- int pipe_command(char * first_command, char * second_command)
- int str_index_of(char * str, char item)
- int execute_command()
