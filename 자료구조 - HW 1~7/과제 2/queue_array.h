#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>를 담는 내용
#pragma once
#define false   0
#define true    1
#define bool int
#include <string.h>

typedef struct{
  void** queue;
  int size;
  int front, rear;
}Queue;

Queue* CreateQueue(int size){
  Queue *pQueue = (Queue*)malloc(sizeof(Queue));
  if(pQueue == NULL){
    printf("[Warning]No Memory.\n");
    return NULL;
  }

  pQueue->queue = (void**)malloc(++size * sizeof(void*));
  if(pQueue->queue == NULL){
    printf("[Warning]No Memory.\n");
    return NULL;
  }
  pQueue->size = size;
  pQueue->front = pQueue->rear = 0;
  printf("Created New Stack.\n");

  return pQueue;
}


bool IsFullQueue(Queue* q){
  if (q->front == (q->rear + 1) % q->size){
    return true;
  }
  return false;
}

bool IsEmptyQueue(Queue* q){
  if (q->rear == q->front){
    return true;
  }
  return false;
}

void EnQueue(Queue* q, void* item){
  if(IsFullQueue(q)){
    // full_queue(q);
    printf("[Warning]Queue is now Full.\n");
  }
  else{
    q->rear = (q->rear + 1) % q->size;
    q->queue[q->rear] = item;
  }
}

void* DeQueue(Queue *q){
  if(IsEmptyQueue(q)){
    printf("[Warning]Queue is now Empty.\n");
    return NULL;
  }
  else{
    q->front = (q->front + 1) % q->size;
    return q->queue[q->front];
  }
}

void DestroyQueue(Queue *q){
	int i;
  if (q != NULL){
    if(q->queue != NULL){
      for(i=0; i<q->size; i++){
		  free(q->queue[i]);
	  }
	  free(q->queue);
    }
    free(q);
    printf("Destroyed a queue.\n");
  }
  else{
    printf("[Warning]Queue is now NULL.\n");
  }
}

int CountQueueItem(Queue *q){
  if (q->rear >= q->front){
    return q->rear - q->front;
  }
  else{
    return q->rear - q->front + q->size;
  }
}

void ClearStack(Queue *q){
  q->front = q->rear = 0;
}
