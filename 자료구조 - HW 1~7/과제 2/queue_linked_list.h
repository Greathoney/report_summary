#include <stdio.h>
#include <stdlib.h>

//#include <stdbool.h>를 담는 내용
#pragma once
#define false   0
#define true    1
#define bool int
#include <string.h>

typedef struct tQueueNode{
  void* data;
  struct tQueueNode* next;
}QueueNode;

typedef struct{
  int count;
  QueueNode* front, *rear;
}Queue;

Queue* CreateQueue(){
  Queue *pQueue = (Queue*)malloc(sizeof(Queue));
  if(pQueue == NULL){
    printf("[Warning]No Memory.\n");
    return NULL;
  }

  pQueue->count = 0;
  pQueue->front = pQueue->rear = NULL;

  printf("Made new queue successfully.\n");
  return pQueue;
}

void EnQueue(Queue* pQueue, char* item){
  QueueNode* pNewNode = (QueueNode*)malloc(sizeof(QueueNode));
  if (pNewNode == NULL){
    printf("[Warning]Not enough memory.\n");
    return;
  }
  if (pNewNode == NULL){
    printf("[Warning]Not enough memory.\n");
    return;
  }
  pNewNode->data = item;
  pNewNode->next = NULL;

  if(pQueue->count == 0){
	  pQueue->rear = pQueue->front = pNewNode;
  }
  else{
	  pQueue->rear->next = pNewNode;
	  pQueue->rear = pNewNode;
  }
  pQueue->count++;
}

void* DeQueue(Queue* pQueue){
	void* answer = pQueue->front->data;

	if(pQueue->count == 0){
		printf("[Warning] Now Queue is empty.\n");
		return NULL;
	}
	if(pQueue->count-- == 1){
		free(pQueue->front);
		pQueue->front = pQueue->rear = NULL;
		return answer;
	}
	else {
		QueueNode* recycleNode = pQueue->front;
		pQueue->front = pQueue->front->next;
		free(recycleNode);
		return answer;
	}
}

void DestroyQueue(Queue *pQueue){
	QueueNode *removeNode, *removeNextNode;

	if(pQueue == NULL){
		printf("[Warning] This queue is NULL.\n");
	}

	for(removeNode = pQueue->front; removeNode != NULL; removeNode = removeNextNode){
		removeNextNode = removeNode->next;
		free(removeNode);
	}
	free(pQueue);
}

int CountQueueItem(Queue *q){
	return q->count;
}

void ClearQueue(Queue *pQueue){
	QueueNode* removeNode, *removeNextNode;
	for(removeNode = pQueue->front; removeNode != NULL; removeNode = removeNextNode){
		removeNextNode = removeNode->next;
		free(removeNode);
	}
}
