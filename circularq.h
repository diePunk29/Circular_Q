/**
  Author: Cristian Mosqueda
  Purpose: To build a circular queue data structure.
  Date: 08/05/20
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node
struct node {
  char chPayLoad;
  struct node *next;
  struct node *prev;
};
typedef struct node qNode;

//queue data structure
struct CircularQueue {
  qNode *head;
};
typedef struct CircularQueue CircQ;

//CircularQueue function definitions
qNode* NewItem(char specifier) {
  //generating a new node item
  qNode *newNode = (qNode*)malloc(sizeof(qNode));
  newNode->chPayLoad = specifier;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

//initializing the circular q
void InitCircQ(CircQ **front) {
  (*front)->head = NULL;
}

//adding to the circular q
void AddCircQ(CircQ **front, qNode *item) {
  //if the circq is empty
  if((*front)->head == NULL) {
    (*front)->head = item;
    item->next = item;
    item->prev = item;
    return;
  }
  //else if the circq is not empty
  qNode *last = (*front)->head->prev; //point to the last node in the CircQ
  last->next = item; //last node is now pointing to item
  item->prev = last; //item is now pointing to the last qNode
  item->next = (*front)->head; //item next is now pointing to head
  (*front)->head->prev = item; //heads previous is now poiting to the newly added qNode
}

//dequeue from the front of the queue
qNode* DelCircQ(CircQ **front) {
  //temp pointer to the front
  qNode *delNode = (*front)->head;
  //if there is only one node in circq then
  if((*front)->head->next == (*front)->head->prev) {
    //just set head pointer to null since their is only one element
    (*front)->head = NULL;
    return delNode;
  }


  if(delNode != NULL) {
    //tracking the last
    qNode* currLast = (*front)->head->prev;
    //advance the head pointer to next node in CircQ
    (*front)->head = (*front)->head->next;
    //making the head nodes prev point to current last node
    (*front)->head->prev = currLast;
    //making last nodes next point to the new head
    currLast->next = (*front)->head;
    //nulling delNodes next * prev pointers
    delNode->next = delNode ->prev = NULL;
  }
  return delNode;
}

//rotate the circq
void RotateCircQ(CircQ **front) {
  //if the queue is empty or their is only one node return
  if((*front)->head == NULL)
    return;
  if((*front)->head->next == (*front)->head->prev)
    return;
  //implement mate
  (*front)->head = (*front)->head->next;
}

//print circQ function
void PrintQ(CircQ *begin) {
  qNode *temp = begin->head;
  if(temp == NULL) {
    printf("\n QUEUE IS EMPTY.\n");
    return;
  }
  printf("\n CIRC QUEUE ->");
  while(temp->next != begin->head) {
    printf(" %c", temp->chPayLoad);
    temp = temp->next;
  }
  printf(" %c",temp->chPayLoad);
  printf("\n");
}
