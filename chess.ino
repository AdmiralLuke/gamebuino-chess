#include <Gamebuino-Meta.h>

enum class Team
{
  NONE,
  BLACK,
  WHITE
};

struct Pos
{
  int x;
  int y;
};

enum FigureType
{
  NONE,
  KING,
  QUEEN,
  ROOK,
  PAWN,
  KNIGHT,
  BISHOP
};

struct Figure
{
  FigureType type;
  Team owner;
};

struct Player
{
  Pos selected;
  Team team;
};

struct
{
  Player black, white;
} players;
Figure board[8][8] = {};
Figure *active;
Team player = Team::WHITE;

void drawField()
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      bool white = (x + y) % 2 == 0;
      Color color = white ? WHITE : BLACK;
      gb.display.setColor(color);
      gb.display.fillRect(x * 8 + 8, y * 8, 8, 8);
    }
  }
}

void initBoard()
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      Team owner = y < 3 ? Team::BLACK : Team::WHITE;
      if (y == 1 || y == 6)
      {
        board[x][y] = {.type = PAWN, .owner = owner};
      }
      else if (y == 0 || y == 7)
      {
        if (x == 0 || x == 7)
        {
          board[x][y] = {.type = ROOK, .owner = owner};
        }
        if (x == 1 || x == 6)
        {
          board[x][y] = {.type = KNIGHT, .owner = owner};
        }
        if (x == 2 || x == 5)
        {
          board[x][y] = {.type = BISHOP, .owner = owner};
        }
        if (x == 3)
        {
          board[x][y] = {.type = QUEEN, .owner = owner};
        }
        if (x == 4)
        {
          board[x][y] = {.type = KING, .owner = owner};
        }
      } else {
        board[x][y] = {.type = NONE, .owner = Team::NONE};
      }
    }
  }
}

void movePawn(int x, int y)
{
}

void drawFigures()
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      if (board[x][y].type == PAWN)
      {
        gb.display.setColor(PURPLE);
        gb.display.fillRect(x * 8 + 12, y * 8 + 4, 2, 2);
      }
      else if (board[x][y].type != NONE)
      {
        gb.display.setColor(ORANGE);
        gb.display.fillRect(x * 8 + 12, y * 8 + 4, 2, 2);
      }
    }
  }
}

void initPlayers()
{
  players = {
      .black = {.selected = {.x = 3, .y = 0}, .team = Team::BLACK},
      .white = {.selected = {.x = 3, .y = 7}, .team = Team::WHITE}};
}

void setup()
{
  gb.begin();
  initPlayers();
  initBoard();
}

void loop()
{
  while (!gb.update())
    ;
  gb.display.clear();
  drawField();
  gb.display.drawRect(8, 0, 65, 65);
  // 64 x 80

  // change player
  if (gb.buttons.pressed(BUTTON_B))
  {
    player = player == Team::WHITE ? Team::BLACK : Team::WHITE; // toggle player
  }

  Player &current = player == Team::WHITE ? players.white : players.black;
  Pos &selectedPos = current.selected;

  if (active == nullptr)
  {
    // controls
    if (gb.buttons.pressed(BUTTON_LEFT))
    {
      if (selectedPos.x > 0)
      {
        selectedPos.x--;
      }
    }
    else if (gb.buttons.pressed(BUTTON_RIGHT))
    {
      if (selectedPos.x < 7)
      {
        selectedPos.x++;
      }
    }
    else if (gb.buttons.pressed(BUTTON_UP))
    {
      if (selectedPos.y > 0)
      {
        selectedPos.y--;
      }
    }
    else if (gb.buttons.pressed(BUTTON_DOWN))
    {
      if (selectedPos.y < 7)
      {
        selectedPos.y++;
      }
    }
    // figure chosing
    if (gb.buttons.pressed(BUTTON_A))
    {
      Figure &tmpFig = board[selectedPos.x][selectedPos.y];
      if (tmpFig.owner == current.team)
      {
        active = &tmpFig;
      }
    }
  }

  // draw functions for player and figures
  drawFigures();
  gb.display.setColor(current.team == Team::WHITE ? WHITE : BLACK);
  gb.display.drawCircle(current.selected.x * 8 + 12, current.selected.y * 8 + 4, 2);
}
