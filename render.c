//using this file to do all the job of rendering screen, using ncurses
#include <stdlib.h>
#include "game.h"

void init_rendering(){
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  if(has_colors()){
    start_color();
    use_default_colors();

    init_pair(1, COLOR_RED, -1);
    init_pair(6, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_BLUE, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(2, COLOR_CYAN, -1);

    //ship colour
    init_pair(7, COLOR_WHITE, -1);
  }
}

void cleanup_rendering(){
  endwin();
}

void draw_ship(entity *ship){
  attron(COLOR_PAIR(7) | A_BOLD);
  mvprintw(ship->y, ship->x, "A");
  attroff(COLOR_PAIR(7) | A_BOLD);
}

void draw_obstacles(entity obstacles[], int count){
  for(int i=0; i<count; i++){
    if(obstacles[i].active){
      attron(COLOR_PAIR(obstacles[i].color_pair) | A_BOLD);
      mvprintw(obstacles[i].y, obstacles[i].x, "O");
      attroff(COLOR_PAIR(obstacles[i].color_pair) | A_BOLD);
    }
  }
}

void draw_fuel(entity fuel[], int count){
  for(int i=0; i<count; i++){
    if(fuel[i].active){
      attron(COLOR_PAIR(fuel[i].color_pair) | A_BOLD);
      mvprintw(fuel[i].y, fuel[i].x, "+");
      attroff(COLOR_PAIR(fuel[i].color_pair) | A_BOLD);
    }
  }
}

void draw_hud(int score, int max, int pmax){
  attron(COLOR_PAIR(7));
  mvprintw(0, 2, "SCORE: %d | MAX SCORE: %d | YOUR MAX: %d | use arrows to move, Q to quit, P to pause", score, max, pmax);
  attroff(COLOR_PAIR(7));
}