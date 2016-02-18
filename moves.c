/* moves.c */

/**
 *
 * @author __MadHatter (alias used on https://www.reddit.com/r/dailyprogrammer)
 *
 * [2016-02-17] Challenge #254 [Intermediate] Finding Legal Reversi Moves
 * https://www.reddit.com/r/dailyprogrammer/comments/468pvf/20160217_challenge_254_intermediate_finding_legal/
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define BRD_LEN 8

#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define BLANK '0'
#define LEGAL '*'

#define NORTH     0
#define EAST      1
#define SOUTH     2
#define WEST      3
#define NORTHEAST 4
#define NORTHWEST 5
#define SOUTHEAST 6
#define SOUTHWEST 7

typedef struct
{
  int x;
  int y;
} xy_t;

int check_bounds(int x, int y);
int deq(xy_t a, xy_t b);
void print_board(char** board);
xy_t forward(xy_t src, xy_t direc);
xy_t new_xy(int x, int y);
char opponent(char player);
xy_t to_direc(int d);
int write_legal(char **board, char player, xy_t src, xy_t direc);

int main()
{
  int i;
  int row;
  int col;
  int n_legal = 0;
  char turn;
  char **board;
  xy_t pos;
  xy_t direc;
  
  board = (char**)malloc(sizeof(char*) * BRD_LEN);
  for (i = 0; i < BRD_LEN; i++)
    board[i] = (char*)malloc(sizeof(char) * (BRD_LEN + 1));
  
  scanf("%c\n", &turn);
  for (i = 0; i < BRD_LEN; i++)
    scanf("%s", board[i]);
    
  for (row = 0; row < BRD_LEN; row++)
  {
    for (col = 0; col < BRD_LEN; col++)
    {
      pos = new_xy(col, row);
      write_legal(board, turn, pos, to_direc(NORTH));
      write_legal(board, turn, pos, to_direc(EAST));
      write_legal(board, turn, pos, to_direc(SOUTH));
      write_legal(board, turn, pos, to_direc(WEST));
      write_legal(board, turn, pos, to_direc(NORTHEAST));
      write_legal(board, turn, pos, to_direc(NORTHWEST));
      write_legal(board, turn, pos, to_direc(SOUTHEAST));
      write_legal(board, turn, pos, to_direc(SOUTHWEST));
    }
  }
  
  n_legal = 0;
  for (row = 0; row < BRD_LEN; row++)
    for (col = 0; col < BRD_LEN; col++)
      if (board[row][col] == LEGAL)
        n_legal++;
    
  printf("%d legal moves for %c\n", n_legal, turn);
  print_board(board);

  return 0;
}

int
check_bounds(int x, int y)
{
  return (x >= 0 && x < BRD_LEN && y >= 0 && y < BRD_LEN) ? 1 : 0;
}

int
deq(xy_t a, xy_t b)
{
  return (a.x == b.x && a.y == b.y) ? 1 : 0;
}

void
print_board(char** board)
{
  int i;
  for (i = 0; i < BRD_LEN; i++)
    printf("%s\n", board[i]);
}

xy_t
forward(xy_t src, xy_t direc)
{
  xy_t dest;
  dest = src;
  dest.x += direc.x;
  dest.y += direc.y;
  return dest;
}

xy_t new_xy(int x, int y)
{
  xy_t xy;
  xy.x = x;
  xy.y = y;
  return xy;
}

char
opponent(char player)
{
  return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

xy_t
to_direc(int d)
{
  xy_t direc;
  switch (d)
  {
    case NORTH: direc = new_xy( 0, -1); break;
    case EAST:  direc = new_xy( 1,  0); break;
    case SOUTH: direc = new_xy( 0,  1); break;
    case WEST:  direc = new_xy(-1,  0); break;
    case NORTHEAST: direc = new_xy( 1, -1); break;
    case NORTHWEST: direc = new_xy(-1, -1); break;
    case SOUTHEAST: direc = new_xy( 1,  1); break;
    case SOUTHWEST: direc = new_xy(-1,  1); break;
    default: direc = new_xy(0, 0); break;
  }
  return direc;
}

int
write_legal(char **board, char player, xy_t src, xy_t direc)
{
  char c;
  xy_t current;
  xy_t src_copy;
  
  if (check_bounds(src.y, src.x) == 0 
      || board[src.y][src.x] == PLAYER_X 
      || board[src.y][src.x] == PLAYER_O)
    return 0;
        
  src_copy = src;
  current = forward(src, direc);
  
  if (check_bounds(current.y, current.x) == 0 
      || board[current.y][current.x] == player
      || board[current.y][current.x] != opponent(player))
    return 0;
  
  while (check_bounds(current.y, current.x) 
      && (c = board[current.y][current.x]) != player) 
  {
    current = forward(current, direc);
  }

  src_copy = forward(src_copy, direc);  
  if (deq(src_copy, current) || c != player)
    return 0;
    
  board[src.y][src.x] = LEGAL;
  
  return 1;
}
