#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include <ncurses.h>
#include <string.h>

int main(){
  char username[50];
  printf("Enter your username: ");
  scanf("%s", username);

  char fname[25];
  strcpy(fname, "leader_board.txt");

  const char* filename;
  filename = fname;
  //get a linked list of leader board entries:
  node *leadh;
  leadh = scan_file(filename);

  //flag to ignore this animation if entered game from leaderboard.
  int arr_anim = 1;

  int max_score = 0;
  //leadh contains info of all this
  //header of this ll has the max score;
  if(leadh != NULL){
      max_score = leadh->score;
  }else {
      max_score = 0;
  }
  node *curr;
  curr = leadh;

  int max_prev_score;

  if(curr != NULL){
    while(curr != NULL){
      if(strcmp(curr->username, username) == 0){
        break;
      }
      curr = curr->next;
    }

    if(curr == NULL){
      max_prev_score = 0;
    }else{
      max_prev_score = curr->score;
    }
  }else if(curr == NULL){
    max_prev_score = 0;
  }

  init_rendering();
  //refresh();
  srand(time(NULL));

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);



  entity ship = {max_x/2, max_y/2, 1, 7};
  entity obstacles[MAX_OBSTACLES] = {0};
  entity fuel[MAX_FUELS] = {0};

  int game_over = 1;
  int score = 0;

  //game animation frame count
  int frame_count = 0;

  //title animation frame count
  int ti_fr_count = max_x+max_x/2-15;

  int some =1;

  int title = 1;
  entity select = {max_x/2 - 10, max_y/2 + 2, 1, 7};

  int leader = 0;

  while(ti_fr_count > max_x/2 - 15){
    erase();
    mvprintw(max_y/2-5, ti_fr_count+4, "EEEEE  SSSSS  CCCCC      VV    VV");
    mvprintw(max_y/2-4, ti_fr_count+3, "E      S      C          VV   VV");
    mvprintw(max_y/2-3, ti_fr_count+2, "EEEEE  SSSSS  C     ===  VV  VV");
    mvprintw(max_y/2-2, ti_fr_count+1, "E          S  C          VV VV");
    mvprintw(max_y/2-1, ti_fr_count, "EEEEE  SSSSS  CCCCC      VVVV");
    refresh();
    napms(11);
    ti_fr_count--;
  }

  napms(500);
  erase();
  mvprintw(max_y/2-5, max_x/2 - 10, "EEEEE  SSSSS  CCCCC      VV    VV");
  mvprintw(max_y/2-4, max_x/2 - 11, "E      S      C          VV   VV");
  mvprintw(max_y/2-3, max_x/2 - 12, "EEEEE  SSSSS  C     ===  VV  VV");
  mvprintw(max_y/2-2, max_x/2 - 13, "E          S  C          VV VV");
  mvprintw(max_y/2-1, max_x/2 - 14, "EEEEE  SSSSS  CCCCC      VVVV");
  mvprintw(max_y/2 +2, max_x/2 - 8, ": Start game");
  refresh();

  napms(500);
  erase();
  mvprintw(max_y/2-5, max_x/2 - 10, "EEEEE  SSSSS  CCCCC      VV    VV");
  mvprintw(max_y/2-4, max_x/2 - 11, "E      S      C          VV   VV");
  mvprintw(max_y/2-3, max_x/2 - 12, "EEEEE  SSSSS  C     ===  VV  VV");
  mvprintw(max_y/2-2, max_x/2 - 13, "E          S  C          VV VV");
  mvprintw(max_y/2-1, max_x/2 - 14, "EEEEE  SSSSS  CCCCC      VVVV");
  mvprintw(max_y/2 +2, max_x/2 - 8, ": Start game");
  mvprintw(max_y/2 +4, max_x/2 - 8, ": Leader Board");
  refresh();

  napms(500);
  mvprintw(max_y/2-5, max_x/2 - 10, "EEEEE  SSSSS  CCCCC      VV    VV");
  mvprintw(max_y/2-4, max_x/2 - 11, "E      S      C          VV   VV");
  mvprintw(max_y/2-3, max_x/2 - 12, "EEEEE  SSSSS  C     ===  VV  VV");
  mvprintw(max_y/2-2, max_x/2 - 13, "E          S  C          VV VV");
  mvprintw(max_y/2-1, max_x/2 - 14, "EEEEE  SSSSS  CCCCC      VVVV");
  mvprintw(max_y/2 +2, max_x/2 - 8, ": Start game");
  mvprintw(max_y/2 +4, max_x/2 - 8, ": Leader Board");
  mvprintw(max_y/2 +6, max_x/2 - 8, ": Quit");
  refresh();

  napms(500);
  //making the start screen here....
  while(title){

    erase();
    mvprintw(max_y/2-5, max_x/2 - 10, "EEEEE  SSSSS  CCCCC      VV    VV");
    mvprintw(max_y/2-4, max_x/2 - 11, "E      S      C          VV   VV");
    mvprintw(max_y/2-3, max_x/2 - 12, "EEEEE  SSSSS  C     ===  VV  VV");
    mvprintw(max_y/2-2, max_x/2 - 13, "E          S  C          VV VV");
    mvprintw(max_y/2-1, max_x/2 - 14, "EEEEE  SSSSS  CCCCC      VVVV");
    mvprintw(max_y/2 +2, max_x/2 - 8, ": Start game");
    mvprintw(max_y/2 +4, max_x/2 - 8, ": Leader Board");
    mvprintw(max_y/2 +6, max_x/2 - 8, ": Quit");
    mvprintw(select.y, select.x, ">");
    //draw_ship(&select);
    refresh();
    int c = getch();
    if(c != ERR){
      if(c == 'W' || c == 'w'|| c == 259){
        if( select.y-2 >= max_y/2+1 && select.y <= max_y/2 +7){
          select.y = select.y - 2;
        }
      }
      else if(c == 'S' || c == 's' || c == 258){
        if(select.y+2 <= max_y/2 +7 && select.y >= max_y/2+1){
          select.y = select.y+2;
        }
      }
      else if(c == 10 || c == 13){
        if(select.y == max_y/2 +2){
        game_over = 0;
        title = 0;
        }
        else if(select.y == max_y/2 +6){
          game_over = -1;
          title = 0;
          some = 0;
        }else if(select.y == max_y/2 +4){
          leader = 1;
          title = 0;
        }
      }
    }
  }

  while(leader == 1){
    erase();
    mvprintw(1,1,"Rank");
    mvprintw(1, 7, "Username");
    mvprintw(1,55, "Score");
    mvprintw(1,62, "|");
    mvprintw(1,64, "press Q to exit, press ENTER to start");
    node *point = leadh;
    int i=3;
    while(point != NULL){
      char *name;
      name = point->username;
      char pscore[10];
      sprintf(pscore,"%d", point->score);

      mvprintw(i, 7, name);
      mvprintw(i, 55, pscore);
      i+=2;
      point = point->next;
    }
    mvprintw(3, 1, "1...");
    mvprintw(5, 1, "2...");
    mvprintw(7, 1, "3...");
    refresh();

    char som = getch();
    if(som != ERR){
      if(som == 10 || som == 13){
        game_over = 0;
        leader = 0;
        arr_anim = 0;
      }else if(som == 'q' || som == 'Q'){
        game_over =-1;
        some = -5;
        leader = 0;
      }
    }
  }

  if(game_over == 0){
    //let the postion of pointer be px and py;
    // px intitally max_x/2-10, finally max_x/2
    // py initially max_y/2+2, finally max_y/2
    int px = max_x/2-10;
    int py = max_y/2+2;
    int pX;

    if(arr_anim > 0){
    for(pX = px; pX < max_x/2; pX++){
      erase();
      mvprintw(py, pX, ">");
      refresh();
      napms(40);
    }
    napms(200);

    erase();
    mvprintw(py, pX, "^" );
    refresh();
    napms(100);

    erase();
    mvprintw(py-1, pX, "^");
    refresh();
    napms(40);

    erase();
    mvprintw(py-2, pX, "^");
    refresh();
    napms(400);

    erase();
    mvprintw(py-2, pX, "A");
    refresh();
    napms(400);

    erase();
    mvprintw(py-2, pX, "^");
    refresh();
    napms(200);

    erase();
    mvprintw(py-2, pX, "A");
    refresh();
    napms(100);
  }
  }
  while(some){

  while(game_over == 0){

    int ch;
    int dx = 0, dy = 0;

    while((ch = getch() ) != ERR){
      switch(ch){
        case KEY_UP: dy = -1; break;
        case KEY_DOWN: dy = 1; break;
        case KEY_LEFT: dx = -1; break;
        case KEY_RIGHT: dx = 1; break;
        case 'q': game_over = -1; break;
        case 'p' : game_over = -2; break;
      }
    }

    if(ship.y + dy >0 && ship.y + dy <max_y){
      ship.y += dy;
    }
    if(ship.x + dx >0 && ship.x + dx <max_x){
      ship.x += dx;
    }

    frame_count++;

    //randomly generates obstacles
    if(frame_count % 5 == 0){
      for(int i=0; i<MAX_OBSTACLES; i++){
        if(!obstacles[i].active){

          obstacles[i].x = rand() % max_x;
          obstacles[i].y = 0;
          obstacles[i].active = 1;
          obstacles[i].color_pair = (rand()%5) +1;
          break;

        }
      }
    }

    //randomly generates fuel packets
    if(frame_count % 5 == 0){
      for(int i=0; i<MAX_FUELS; i++){
        if(!fuel[i].active){

          fuel[i].x = rand() % max_x;
          fuel[i].y = 0;
          fuel[i].active = 1;
          fuel[i].color_pair = 6;
          break;
        }
      }
    }

    // move obstacles
    for(int i=0; i< MAX_OBSTACLES; i++){
      if(obstacles[i].active){
        if(frame_count%2 == 0){
          obstacles[i].y++;
        }

        if(obstacles[i].y >= max_y){
          obstacles[i].active = 0;
          //change the code for score here;
          score++;
        }
      }
    }

    //moves fuel
    for(int i=0; i< MAX_FUELS; i++){
      if(fuel[i].active){
        if(frame_count%2 == 0){
          fuel[i].y++;
        }

        if(fuel[i].y >= max_y){
          fuel[i].active = 0;
        }
      }
    }

    apply_gravity(&ship, obstacles, MAX_OBSTACLES, frame_count);
    if(check_collisions(&ship, obstacles, MAX_OBSTACLES)){
      game_over = 1;

    }

    int fuel_num;

    if((fuel_num = fuel_collect(&ship, fuel, MAX_FUELS)) != 0){
      fuel[fuel_num-1].active = 0;
      score += 15;
    }

    erase();

    draw_fuel(fuel, MAX_FUELS);
    draw_obstacles(obstacles, MAX_OBSTACLES);
    draw_ship(&ship);
    draw_hud(score, max_score, max_prev_score);

    refresh();

    napms(72);

  }

  if(game_over == -1){
    break;
  }

   int gflag = 0;

   while(game_over == -2){
     erase();
     mvprintw(max_y/2-1, max_x/2-7, "GAME PAUSED");
     mvprintw(max_y/2+1, max_x/2-15, "Press ENTER to CONTINUE, Q to exit");

     refresh();
     int ch1 = getch();
     if(ch1 != ERR){
       if(ch1 == 10 || ch1 == 13 || ch1 == '\n'){
         game_over = 0;
       }
       else if(ch1 == 'q' || ch1 == 'Q'){
         gflag = 1;
         break;
       }
     }
   }
  while(game_over == 1){
    erase();
    mvprintw(max_y/2-1, max_x/2-5, "GAME OVER");
    mvprintw(max_y/2+1, max_x/2-15, "Press ENTER to PLAY, Q to exit");

    refresh();
    int ch2 = getch();
    if(ch2 != ERR){
     if(ch2 == 10 || ch2 == 13){
       game_over = 0;
       ship.x = max_x/2;
       ship.y = max_y/2;
       for(int i=0; i<MAX_OBSTACLES; i++){

         obstacles[i].x = 0;
         obstacles[i].y = 0;
         obstacles[i].active = 0;
       }
       for(int i=0; i<MAX_FUELS; i++){
         fuel[i].x = 0;
         fuel[i].y = 0;
         fuel[i].active = 0;
       }

    }else if(ch2 == 'q' || ch2 == 'Q'){
       gflag = 1;
      break;
    }
    }
  }
  if(gflag == 1){
    break;
  }
}


  cleanup_rendering();

  leadh = update_leaderboard(leadh, username,score);

  save_lb(leadh, filename);

  if(some == 1){
    printf("=============\n");
    printf("Exited Game \nFinal Score: %d\n", score);
    printf("=============\n");
  }

  else{
    printf("===========\n");
    printf("Exited game\n");
    printf("===========\n");
  }


  return 0;

}