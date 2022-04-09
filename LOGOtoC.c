#include "stdio.h"

#define MAXLINE 1000
#define MAXINPUT 1000000
//max digits for move commands (360 degrees = 3 digits, diagonal field length ~204 = three digits)
#define MAXDIGITS 3
#define MAXREPEAT 1000

getline(s, lim)   /* get line into s, return length */
char s[];
int lim;
{
  int c, i;

  i = 0;
  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';

  if (c == EOF)
    return(c);
  return(i);
}

getWord(s, lim) /* get word into s, return length */
char s[];
int lim;
{
  int c, i;

  i = 0;
  // first get rid of spaces/newlines/tabs
  while ((c=getchar()) == ' ' || c == '\n' || '\t')
    ;
  s[i++] = c;
  while (--lim > 0 && (c=getchar()) != EOF && c != '\n' && c != ' ')
    s[i++] = c;
  s[i] = '\0';

  if (c == EOF)
    return(c);
  return(i);
}

strCmp(s, t)  /* compare two strings */
char s[];
char t[];
{
  int b = 1;
  int i = 0;

  while (s[i] != '\0' && t[i] != '\0') {
    if (s[i] == t[i]) {
      i++;
    } else {
      b = 0;
      break;
    }
  }

  return b;
}

isStringNumber(s) /* return true if string contains a number */
char s[];
{
    int i = 0;
    while (s[i++] != '\0') {
      int number = s[i] <= '9' && s[i] >= '0';
      if (!number)
        return 0;
    }

  return 1;
}

getInputAndRemoveWhitespace(s)
char s[];
{
  int c, i;

  i = 0;
  while ((c = getchar()) != EOF) {
    if (c != '\n' && c != ' ' && c != '\t' && c != '\0') {
      //storecahr
      s[i++] = c;
    }
  }

  s[i] = EOF;
}

main() {
  /* Transcompile LOGO to C code to run on my vex robot drawing program */
  char inputWithoutBlanks[MAXINPUT];
  getInputAndRemoveWhitespace(inputWithoutBlanks);

  /* transcompile LOGO to C */
  char *start = inputWithoutBlanks;
  char *look = start;
  char logoArg[MAXDIGITS];
  char logoRepeatArg[MAXREPEAT];

  int inRepeat = 0;

  while (*look != EOF) {
    //first print two spaces based on for loops
    for (int i = 0; i < inRepeat; i++)
      printf("  ");

    if (*look == 'f') {
      if (*++look == 'd') {
        //forward
        //get distance parameter
        int i = 0;
        for (int j = 0; j < MAXDIGITS; j++)
          logoArg[j] = '\0';
        while (*++look >= '0' && *look <= '9')
          logoArg[i++] = *look;

        printf("forward(");
        for (int j = 0; j < MAXDIGITS; j++) {
          if (logoArg[j] == '\0')
            break;
          printf("%c", logoArg[j]);
        }
        printf("); \n");
      }
    } else if (*look == 'b') {
      if (*++look == 'k') {
        //backward
        //get distance parameter
        int i = 0;
        for (int j = 0; j < MAXDIGITS; j++)
          logoArg[j] = '\0';
        while (*++look >= '0' && *look <= '9')
          logoArg[i++] = *look;

        printf("backward(");
        for (int j = 0; j < MAXDIGITS; j++) {
          if (logoArg[j] == '\0')
            break;
          printf("%c", logoArg[j]);
        }
        printf("); \n");
      }
    } else if (*look == 'r') {
      if (*++look == 't') {
        //right turn
        //get degrees parameter
        int i = 0;
        for (int j = 0; j < MAXDIGITS; j++)
          logoArg[j] = '\0';
        while (*++look >= '0' && *look <= '9')
          logoArg[i++] = *look;

        printf("rightTurn(");
        for (int j = 0; j < MAXDIGITS; j++) {
          if (logoArg[j] == '\0')
            break;
          printf("%c", logoArg[j]);
        }
        printf("); \n");
      } else if (*look == 'e') {
        if (*++look == 'p')
          if (*++look == 'e')
            if (*++look == 'a')
              if (*++look == 't') {
                //repeat
                //get number of repeats parameter
                int i = 0;
                for (int j = 0; j < MAXREPEAT; j++)
                  logoRepeatArg[j] = '\0';
                while (*++look >= '0' && *look <= '9')
                  logoRepeatArg[i++] = *look;

                //to change which character is used for the variable in nested for loops
                char varInForLoop = 'i';
                varInForLoop += inRepeat;
                inRepeat ++;

                printf("for (int %c = 0; %c < ", varInForLoop, varInForLoop);
                for (int j = 0; j < MAXREPEAT; j++) {
                  if (logoRepeatArg[j] == '\0')
                    break;
                  printf("%c", logoRepeatArg[j]);
                }
                printf("; %c++) ", varInForLoop);
              }
        }
    } else if (*look == 'l') {
      if (*++look == 't') {
        //left turn
        //get degrees parameter
        int i = 0;
        for (int j = 0; j < MAXDIGITS; j++)
          logoArg[j] = '\0';
        while (*++look >= '0' && *look <= '9')
          logoArg[i++] = *look;

        printf("leftTurn(");
        for (int j = 0; j < MAXDIGITS; j++) {
          if (logoArg[j] == '\0')
            break;
          printf("%c", logoArg[j]);
        }
        printf("); \n");
      }
    } else if (*look == 'p') {
      if (*++look == 'u') {
        //pen up
        printf("penUp(); \n");
        ++look;
      } else if (*look == 'd') {
        //pen down
        printf("penDown(); \n");
        ++look;
      }
    } else if (*look == ']') {
      printf("\b\b");
      printf("} \n");
      inRepeat --;
      ++look;
    } else if (*look == '[') {
      for (int i = 0; i < inRepeat; i++)
        printf("\b\b");
      printf("{ \n");
      ++look;
    }

    start = look;
  }
}
