#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLS 7
#define LINES 6
#define OK 1
#define AGAIN 2
#define QUIT 3

struct pattern
{
  unsigned columns;
  unsigned lines;
};

char grid[COLS][LINES];

#include "connect.h"

int main(void)
{
  grillInit();
  grillOutput();
  int value,status,pieces = 'O';
  while (1)
  {
    struct pattern current;
    printf("Player %d >",(pieces == 'O') ? 1 : 2);
    status = input(&value);
    if(status != OK)
    {
      if(status == AGAIN)
      {
        printf("AGAIN\n");
        continue;
      }
      else
      {
        printf("QUIT\n");
        return 0;
      }
    }
    position(&current,value -  1);
    printf("columns = %d \n lines = %d\n",current.columns,current.lines);
    int max = stateCheck(&current,pieces);
    printf("The number of pieces is equal to %d\n",max);
    grillFiller(&current,pieces);
    grillOutput();
    pieces = (pieces == 'O') ? 'X' : 'O';
  }
  
  return 0;
}

int input(int *value)
{
  while(!scanf("%d",value))
  {
    char letter;
    while (scanf("%c",&letter))
    {
      switch(letter)
      {
        case 'q':
        case 'Q':
          return QUIT;
      }
    }
  }
  if(*value < 1 || *value > 7)
  {
    return AGAIN;
  }
  return OK;
}

void grillOutput(void)
{
  for(int i=1;i<=COLS;i++)
    printf("  %d ",i);
  putchar('\n');

    for (int j = 0; j < LINES; j++)
    {
      putchar('+');
      for (int k = 0; k < COLS; k++)
      {
        printf("---+");
      }
      putchar('\n');
      putchar('|');
      for(int l = 0;l < COLS;l++)
      {
        printf(" %c |",grid[l][j]);
      }
    putchar('\n');
  }
  putchar('+');
  for (int k = 0; k < COLS; k++)
  {
    printf("---+");
  }
  putchar('\n');
  for(int i=1;i<=COLS;i++)
    printf("  %d ",i);
  putchar('\n');
}

void grillInit(void)
{
  for (int i = 0; i < COLS; i++)
  {
    for (int j = 0; j < LINES; j++)
    {
      grid[i][j] = ' ';
    }
  }
}

void position(struct pattern *current,int column)
{
  int line = LINES - 1;
  while(grid[column][line] != ' ' && line > 0)
  {
    line--;
  }
  current->columns = column;
  current->lines = line;
}

void grillFiller(struct pattern *current,int pieces)
{
  grid[current->columns][current->lines] = pieces;
}

int stateCheck(struct pattern *current, int pieces) 
{
    int max = dirStateCheck(1,0,pieces,current) + dirStateCheck(-1,0,pieces,current) - 1;
    //max = maximal(max,dirStateCheck(1,1,pieces,current) + dirStateCheck(-1,-1,pieces,current) - 1);
    //max = maximal(max,dirStateCheck(0,1,pieces,current) + dirStateCheck(0,-1,pieces,current)) - 1;
    return max;
}

int dirStateCheck(int horizontal, int vertical, int pieces, struct pattern *current)
{
    int i = 0;
    int vert = current->columns;
    int hor = current->lines;
    while(grid[vert][hor] == pieces) {
      if(!positionCheck(vert,hor))
      {
        break;
      }
      printf("i = %d\n",i);
      i++;
      vert += vertical;
      hor += horizontal;
    }
    return i;
}

bool positionCheck(int cols,int lines)
{
    if (cols > 7 || cols < 0) {
        return false;
    }
    else if(lines > 6 || lines < 0)
    {
        return false;
    }
    return true;
}

int maximal(int a,int b)
{
  return (a > b) ? a : b;
}