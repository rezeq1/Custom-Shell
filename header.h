#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
  
#define MAX_LEN 200

void ExecuteCommand(char** CommandParsed);
void ExecutePipe (char ** args1, char ** args2);
int ParsePipeString(char* InputCommand, char** PipeParts);
void ParseCommandString(char* InputCommand, char** CommandParts);
int parse(char* InputCommand, char** CommandParsed, char** PipeParsed);
