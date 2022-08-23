#include <Gamebuino-Meta.h>
//#include <map>


int player = 0;


struct Pos {
  int x;
  int y;
};

enum figure {
  NON,
  KING,
  QUEEN,
  ROOK,
  PAWN,
  KNIGHT,
  BISHOP
};

struct Player {
  int x;
  int y;
  Color color;
  figure selected;
};

Player players[2];

figure board[2][8][8];

// std::map<Pos,figure> field {{}} 

void generateField() {
  for (int y = 0; y < 8; y++) {
    for(int x = 0; x < 8; x++) {
      bool white = (x + y) % 2 == 0;
      Color color = white ? WHITE : BLACK;
      gb.display.setColor(color);
      gb.display.fillRect(x*8 + 8,y*8,8,8);
    }
  }
}

void initBoard() {
  int z = 0;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (y >= 3) {
        z = 1;
      } 
      if (y == 1 || y == 6) {
        board[z][x][y] = PAWN;
      }
    }
  }
}

void movePawn(int x, int y) {
  
}

void displayFigures() {
  int z = 0;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (y >= 3) {
        z = 1;
      }
      if (board[z][x][y] == PAWN) {
        gb.display.setColor(PURPLE);
        gb.display.fillRect(x * 8 + 12, y * 8 + 4, 2, 2);
      }
    }
  }
}

void setup() {
  gb.begin();
  players[0] = {
    .x = 0,
    .y = 0,
    .color = RED,
  };
  players[1] = {
    .x = 0,
    .y = 7,
    .color = YELLOW,
  };

  initBoard();
}

void loop() {
  while(!gb.update());
  gb.display.clear();
  generateField();
  gb.display.drawRect(8,0,65,65);
  // 64 x 80

  // Spieler wechseln
  if (gb.buttons.pressed(BUTTON_B)) {
      player += 1;
      player %= 2;
  }

  // Hoch
  if (gb.buttons.pressed(BUTTON_LEFT)) {
    if (players[player].x > 0) {
      players[player].x -= 1;
    }
  } else if (gb.buttons.pressed(BUTTON_RIGHT)) {
    if (players[player].x < 7) {
      players[player].x += 1;
    }
  } else if (gb.buttons.pressed(BUTTON_UP)) {
    if (players[player].y > 0) {
      players[player].y -= 1;
    }
  } else if (gb.buttons.pressed(BUTTON_DOWN)) {
    if (players[player].y < 7) {
      players[player].y += 1;
    }
  }

  displayFigures();
  gb.display.setColor(players[player].color);
  gb.display.drawCircle(players[player].x*8 + 12,players[player].y*8 + 4,2);
}



