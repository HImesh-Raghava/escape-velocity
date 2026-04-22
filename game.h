#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#define MAX_OBSTACLES 15
#define MAX_FUELS 10
#define GRAVITY_RADIUS 10.0
#define DELAY_NS 30000000L

//structure for linked list, storing scoreboard data
typedef struct Node{
  char username[50];
  int score;
  struct Node *next;
}node;

//structure for an entity in game
typedef struct{
  int x, y;
  int active;
  int color_pair;
}entity;

//intialising and setting up the game
//shortcuts for ncurses
void init_rendering();
void cleanup_rendering();
void draw_ship(entity *ship);
void draw_fuel(entity fuel[], int count);
void draw_obstacles(entity obstacles[], int count);
void draw_hud(int score, int max, int pmax);

//logic for game
void apply_gravity(entity *ship, entity obstacles[], int count, int frame_count);
int check_collisions(entity *ship, entity obstacles[], int count);
int fuel_collect(entity *ship, entity fuel[], int count);

//leaderboard:
node *insert_sorted(node *head, node *new);
node *scan_file(const char* filename);
node *update_leaderboard(node *head, const char* username, int score);
void save_lb(node *head, const char* username);
void free_ll(node *head);

#endif