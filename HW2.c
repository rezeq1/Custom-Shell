#include "header.h"


void ExecuteCommand(char** CommandParsed)
{


    pid_t pid = fork(); 
  
    if (pid == -1) 
    {
        printf("\nError : Cannot Create a fork for a child.");
        return;
    } 
    else if (pid == 0) 
    {
      execvp(CommandParsed[0], CommandParsed); 		
      exit(0);
    } 
    else {
        wait(NULL); 
        return;
    }
}

void ExecutePipe (char ** args1, char ** args2) {

    int fds[2];
    pipe(fds);
    int i;
    pid_t pid = fork();

        if (pid == -1) {
        printf("\nError : Cannot Create a fork for a child.");
       
    } else 
    if (pid == 0) { 
        close(fds[1]);
        dup2(fds[0], 0);
        execvp(args2[0], args2); 
        

        
       
    } else { 
        close(fds[0]);
        dup2(fds[1], 1);
        printf("\n");
        execvp(args1[0], args1); 

       
        
    }
}
  



int ParsePipeString(char* InputCommand, char** PipeParts)
{

    int i;
    for (i = 0; i < 2; i++) {
        PipeParts[i] = strsep(&InputCommand, "|");
        if (PipeParts[i] == NULL)
            break;
    }
  
    if (PipeParts[1] == NULL)
        return 0;
    else {
        return 1;
    }
}
  

void ParseCommandString(char* InputCommand, char** CommandParts)
{

    int i;
  
    for (i = 0; i < MAX_LEN; i++) {
        CommandParts[i] = strsep(&InputCommand, " ");
  
        if (CommandParts[i] == NULL)
            break;
        if (strlen(CommandParts[i]) == 0)
            i--;
    }
}
  
int parse(char* InputCommand, char** CommandParsed, char** PipeParsed)
{

    char* PipeParts[2];
    int IsPipe = 0;
  
    IsPipe = ParsePipeString(InputCommand, PipeParts);
  
    if (IsPipe) 
    {

        ParseCommandString(PipeParts[0], CommandParsed);
        ParseCommandString(PipeParts[1], PipeParsed);
  
    } else 

        ParseCommandString(InputCommand, CommandParsed);
    
  

    return 1 + IsPipe;
}

int main()
{
    char *InputCommand, *CommandParsed[MAX_LEN],*username=getenv("USER");
    char* PipeParsed[MAX_LEN],Current_dir[MAX_LEN];
    int info = 0;
    pid_t pid;
    	printf("---Starting Custom Shell---\n");
	printf("---------------------------\n");
  
    while (1) 
    {

	getcwd(Current_dir, sizeof(Current_dir));
	printf("\%s:%s",username,Current_dir);

        InputCommand = readline(" >> ");
        
        
    	      
         if (strlen(InputCommand) != 0)
         {
	    
            info = parse(InputCommand,CommandParsed, PipeParsed);
	    
	    if (strcmp(CommandParsed[0],"exit") == 0)
    	                      exit(0);
    	      
    	   if (strcmp(CommandParsed[0],"cd") == 0)
    	                     chdir(CommandParsed[1]);
    	      else{
    	      
            		if (info == 1)
                		            ExecuteCommand(CommandParsed);
	    	else if (info == 2)
	    	{
		                       pid = fork();
	      

        			if (pid == 0)
                                                                    {
        				
        			     ExecutePipe(CommandParsed, PipeParsed);
        					
         			}
         			else
         			{
         				
         			     waitpid(pid,NULL,WUNTRACED);
         			}
         					
				
                                           }
         			    
                              }
	
              }
    }
    
    return 0;
}

