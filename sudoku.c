//
// resolves sudoku puzzle
//

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define DEBUG 1
#define DBG()  printf("%s(%d)\n", __FUNCTION__, __LINE__)
               
typedef struct 
{
  int val;
  int fixed;
} sfield_t; 

int table[9][9]={
 {0, 6 ,5,  0, 9, 0,  0, 7, 4},
 {0, 0 ,0,  3, 0, 0,  2, 0, 0},
 {0, 0 ,2,  1, 0, 5,  8, 0, 0},
 
 {0, 0 ,0,  7, 0, 0,  6, 4, 0},
 {0, 8 ,0,  2, 1, 4,  0, 3, 0},
 {0, 0 ,4,  0, 0, 8,  0, 0, 0},
 
 {0, 0 ,9,  5, 6, 3,  1, 0, 0},
 {0, 0 ,0,  0, 0, 1,  0, 0, 0},
 {2, 0 ,0,  0, 8, 0,  9, 6, 0},
};

sfield_t work_table[9][9];
int iter = 0;

void init_work_table(int (*input)[9], sfield_t (*work)[9])
{
  int x;
  int y;
  
  for (x = 0; x < 9; x++)
    for (y = 0; y < 9; y++)
    {
      work[x][y].val = input[x][y];
      if (input[x][y] == 0)
        work[x][y].fixed = FALSE;
      else
        work[x][y].fixed = TRUE;
    }
}


void draw_table(sfield_t (*input)[9])
{
  int x, y;
  printf("\n");
  
  for (y=0; y < 9; y++)
  {
    if (y%3 ==0)
      printf("\n");
    
    for (x = 0; x < 9; x++)
    {
      if (x%3 == 0)
        printf(" ");
      if (input[y][x].val != 0)
        printf("%d ", input[y][x].val);
      else
        printf(". ");
    }    
    printf("\n");
  }  
}

void finish(sfield_t (*input)[9])
{
  draw_table(input);
  exit(0);
}

void next_cell(sfield_t (*input)[9], int *x, int *y)
{
  if (*x == 8)
  {
    if (*y == 8)
    {
      finish(input);
    }  
    else
    {
      (*y)++;
    }  
    *x = 0;
  }
  else
    (*x)++;
}

//
// checks if row doesn't contain mutiple fields of the same value
//
int check_row_value(sfield_t (*input)[9], int y, int val)
{ 
  int x;
  int count = 0;
  
  //DBG();
  for (x = 0; x < 9; x++)
  {
    if (input[y][x].val == val)
      count++;
  }
  
  if (count > 0)
    return -1;
  else
    return 0;
}

//
// checks if column doesn't contain mutiple fields of the same value
//
int check_col_value(sfield_t input[9][9], int x, int val)
{ 
  int y;
  int count = 0;
  
  //DBG();
  for (y = 0; y < 9; y++)
  {
    if (input[y][x].val == val)
      count++;
  }
  
  if (count > 0)
    return -1;
  else
    return 0;
}

//
// checks if square 3x3 doesn't contain mutiple fields of the same value
//
int check_sq_value(sfield_t input[9][9], int x, int y, int val)
{ 
  int xs = x - x%3;
  int ys = y - y%3;
  int xi;
  int yi;
  int count = 0;
    
  //DBG();
  //getchar();
  for (yi = ys; yi < ys+3; yi++)
    for (xi = xs; xi < xs+3; xi++)
    {
      if (input[yi][xi].val == val)
        count++;
    }
  
  if (count > 0)
    return -1;
  else
    return 0;
}

void solve(sfield_t input[9][9], int x, int y)
{ 
  int i;
  int xpr, ypr;
  
  printf("\nIteration %d\n", ++iter);
  draw_table(input);
  
  // skip cell if was filled at the beginning 
  while (input[y][x].fixed == TRUE)
  {
    next_cell(input, &x, &y);
  }
  
  for (i = 1; i <= 9; i++)
  {
    input[y][x].val = 0;
    if (check_row_value(input, y, i) == 0 && check_col_value(input, x, i) == 0 && check_sq_value(input, x, y, i) == 0)
    {
      input[y][x].val = i; 
      
      xpr=x;
      ypr=y;
      do 
      {
        next_cell(input, &x, &y);
      } while (input[y][x].fixed == TRUE);
      
      solve(input, x, y);
      x=xpr; 
      y=ypr;
      if (input[y][x].fixed == FALSE)
        input[y][x].val = 0;
    }
  } 
}

int main(int argc, char *argv[])
{
  init_work_table(table, work_table);
  solve(work_table, 0, 0);  
  return 0;
}

