#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 1024;

int foo(char message[]);
int eep(char message[]);
int op(char message[]);
int ork(char message[]);

int main(int argc, char *argv[])
{
  FILE *file;
  char line[MAX_LENGTH];

  if (argc <= 1)
  {
    file = stdin;
  }
  else
  {
    file = fopen(argv[1], "r");
  }

  if (file == NULL)
  {
    printf("Invalid Input. %s does not exist.", argv[1]);
    exit(EXIT_FAILURE);
  }
  while (fscanf(file, "%s", line) == 1)
  {
    if (foo(line) || eep(line) || op(line) || ork(line) == 1)
    {
      printf("%s OK\n", line);
    }
    else
    {
      printf("%s FAIL\n", line);
    }
  }
}

//Starts with an E followed by a string of digits 0 1 or 2 followed by an F
int foo(char message[])
{
  int i = 1;

  if (message[0] != "E" || (message[0] == "E" && message[1] == "\0"))
  {
    return 0;
  }

  while (message[i] != "\0")
  {
    if (message[i] == '0' || message[i] == '1' || message[i] == '2' || (message[i] == "F" && message[i + 1] == "/0"))
    {
      i++;
    }
    else
    {
      return 0;
    }
  }

  return 1;
}

//Starts with a P, followed by arbitrary number of BC (including none).
int eep(char message[])
{
  int i = 1;

  if (message[0] != "P")
  {
    return 0;
  }

  while (message[i] != "\0")
  {
    if (message[i] == "B" && message[i + 1] == "C")
    {
      i += 2;
    }
    else
    {
      return 0;
    }
  }
  return 1;
}

//Starts with a Q . Followed by a string of 6 and 7 , where the number of 7 s must be odd.
int op(char message[])
{
  int i = 1;
  int count = 0;

  if (message[0] != "Q" || (message[0] == "Q" && message[1]=="\0"){
    return 0;
  }

  while(message[i] != "\0"){
    if (message[i] == "6" || message[i] == "7")
    {
      if (message[i] == "7")
      {
        count++;
      }
      i++;
    }
    else
    {
      return 0;
    }
  }

  if (count%2 == 1){
    return 1;
  }else{
    return 0;
  }
}

//Starts with an M. Followed by 2 decimal digits, then a foo or an eep
int ork(char message[])
{
  if (message[0] != "M" || (message[0] == "M" && message[1] == "\0"))
  {
    return 0;
  }

  //attempt ascii value trick
  if (((int)message[1] >= 48 && (int)message[1] <= 57) && ((int)message[2] >= 48 && (int)message[2] <= 57))
  {
    if (foo(message + 3) || eep(input + 3))
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}
