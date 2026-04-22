#include <stdio.h>
#include "game.h"
#include <string.h>
#include <stdlib.h>

//function to insert a node in descending order of score
node *insert_sorted(node *head, node *new){
  //if the list is empty or the new node has a higher score than the head:
  if(head == NULL || head->score <= new->score){
    new->next = head;
    head = new;
    return head;
  }

  //if not inserted at start:
  // traversing:
  node *curr = head;
  while(curr->next != NULL && curr->next->score > new->score){
    curr = curr->next;
  }
  //inserting:
  new->next = curr->next;
  curr->next = new;

  return head;

}

//scanning the .txt file into linked list:
//why const char* here?
node *scan_file(const char* filename){
  FILE* file = fopen(filename, "r");
  node * head = NULL;

  if(file == NULL){
    printf("file didnt open, error occured \n");
    return NULL;
  }

  char username[50];
  int score;

  while(fscanf(file, "%49s %d", username, &score)==2){
    node * new;
    new = (node *)malloc(sizeof(node));
    strcpy(new->username, username);
    new->score = score;
    new->next = NULL;

    head = insert_sorted(head, new);
  }

  fclose(file);
  return head;
}

//update leaderboard with new score
node *update_leaderboard(node *head, const char *username, int score){
  node *prev;
  prev = NULL;

  node *curr;
  curr = head;

  //checking if user already exists:
  while(curr != NULL){
    if(strcmp(curr->username, username) == 0){
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  if(curr != NULL){
    //if user exists:
    if(score > curr->score){
      //the node might not be in the same position;
      if(prev == NULL){
        //case when our node is the head node;
        head = curr->next;
      }
      else{
        prev->next = curr->next;
      }

      //in the curr node, update its score and add it back
      curr->score = score;
      curr->next = NULL;
      head = insert_sorted(head, curr);
    }
  } else {
    //if user is new:
    node *new;
    new = (node *)malloc(sizeof(node));
    strcpy(new->username, username);
    new->score = score;
    new->next = NULL;

    head = insert_sorted(head, new);
  }

  return head;
}

// we now have the updated linked list of the game. we have to write it back to the file;

void save_lb(node *head, const char* filename){
  FILE *fp = fopen(filename, "w");
  if(fp == NULL){
    printf("error opening the file\n");
    return;
   }

  node *curr = head;
  while(curr != NULL){
    fprintf(fp,"%s %d\n", curr->username, curr->score);
    curr = curr->next;
  }

  fclose(fp);
}

//free the ll after use:
void free_ll(node *head){
  node *curr = head;
  while(curr != NULL){
    node * next = curr->next;
    free(curr);
    curr = next;
  }
}