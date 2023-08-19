// Maame Adwoa Ocran
// Ass5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void executeCommand(char *args[])
{
  pid_t pid;

  pid = fork();

  if (pid == 0)
  {
    if (execvp(args[0], args) == -1)
    {
      perror("shell");
    }
    exit(EXIT_FAILURE);
  }
  else if (pid < 0)
  {
    perror("shell");
  }
  else
  {
    waitpid(pid, NULL, 0);
  }
}

int main()
{
  char input[MAX_INPUT_SIZE];
  char *args[MAX_ARGS];
  char *token;
  int argCount;

  while (1)
  {
    printf("myshell$ ");
    fgets(input, MAX_INPUT_SIZE, stdin);

    input[strcspn(input, "\n")] = 0;

    argCount = 0;
    token = strtok(input, " ");

    while (token != NULL)
    {
      args[argCount] = token;
      argCount++;
      token = strtok(NULL, " ");
    }
    args[argCount] = NULL;

    if (argCount > 0)
    {
      if (strcmp(args[0], "exit") == 0)
      {
        break;
      }
      else if (strcmp(args[0], "cd") == 0)
      {
        if (argCount < 2)
        {
          fprintf(stderr, "cd: missing argument\n");
        }
        else
        {
          if (chdir(args[1]) != 0)
          {
            perror("shell");
          }
        }
      }
      else
      {
        executeCommand(args);
      }
    }
  }

  return 0;
}
