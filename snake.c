#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef struct Snake{
  int8_t x;
  int8_t y;
} Snake;

Snake body[255];

void die(){
  endwin();
  exit(0);
}

int main() {
  initscr();
  uint8_t maxY, maxX;
  uint8_t winX, winY;
  getmaxyx(stdscr, maxY, maxX);
  WINDOW* win = newwin(50, 110, (maxY / 3) - 15, (maxX / 3)-15);
  box(win, 0, 0);
  keypad(win, true);
  nodelay(win, true);
  curs_set(0);
  uint8_t foodX = rand() % 50;
  uint8_t foodY = rand() % 50;
  int8_t dirx = 1;
  int8_t diry = 0;
  Snake head = {10 ,10};
  uint8_t score = 1;

  while(true) {
    int pressed = wgetch(win);
    if(pressed == KEY_LEFT) {
      if(dirx == 1) continue;
      dirx = -1;
      diry = 0;
    }
    if(pressed == KEY_RIGHT) {
      if(dirx == -1) continue;
      dirx = 1;
      diry = 0;
    }
    if(pressed == KEY_UP) {
      if(diry == 1) continue;
      dirx = 0;
      diry = -1;
    }
    if(pressed == KEY_DOWN) {
      if(diry == -1) continue;
      dirx = 0;
      diry = 1;
    }
    if(pressed == 'q')
      break;

    /* проверка выхода ща границы окна 
     * справа и снизу ничё не работает надо будет доделать когда не западло*/

    if(head.x == -1 || head.y == -1)
      die();


    for(int i = score; i > 0; i--){
      body[i] = body[i - 1];
    }
     body[0] = head;
  
    head.x += dirx;
    head.y += diry;

    /* refresh */
    werase(win);
    box(win, 0, 0);

    for(uint8_t i = 0; i < score; i++){
      mvwaddch(win, body[i].y, body[i].x, 'o');
      if(head.y == body[i].y && head.x == body[i].x) die();
    }
    mvwaddch(win, head.y, head.x, '0');

    mvwaddch(win, foodY, foodX, '*');
    if(foodX == head.x && foodY == head.y) {
      score += 1;
      mvprintw(1, 1, "score: %d", score);
      refresh();
      foodX = (rand() % 50) + 1;
      foodY = (rand() % 50) + 1;
    }
    usleep(45000);
  }
  endwin();
}

