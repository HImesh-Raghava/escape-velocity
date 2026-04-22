#include <math.h>
#include "game.h"

void apply_gravity(entity *ship, entity obstacles[], int count, int frame_count){
  if(frame_count % 3 != 0) return;

  for(int i=0; i<count; i++){
    if(obstacles[i].active){
      double dx = (double)(obstacles[i].x - ship->x);
      double dy = (double)(obstacles[i].y - ship->y);
      double distance = sqrt(dx*dx + dy*dy);

      if(distance <= GRAVITY_RADIUS){
        if(obstacles[i].x > ship->x){
            ship->x++;
          }
        else if(obstacles[i].x < ship->x){
            ship->x--;
          }

        if(obstacles[i].y > ship->y)
          {
          ship->y++;
        }
        else if(obstacles[i].y < ship->y)
          {
          ship->y--;
        }

      }

    }
  }
}

// checks if our ship is collided by any obstacle
int check_collisions(entity *ship, entity obstacles[], int count){
  for(int i=0; i<count; i++){
    if(obstacles[i].active && obstacles[i].x == ship->x && obstacles[i].y == ship->y){
    return 1;

    }
  }
  return 0;

}


// checks if any of the fuel is collected by ship
int fuel_collect(entity *ship, entity fuel[], int count){
  for(int i=0; i<count; i++){
    if(fuel[i].active && fuel[i].x == ship->x && fuel[i].y == ship->y){
      return i+1;
    }
  }
  return 0;
}