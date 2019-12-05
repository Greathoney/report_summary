#include <stdio.h>
#include "queue_linked_list.h"

void SeeQueue(Queue* q){
  int i;
  printf("The current status of Queue: (");
  if (q->count != 0){
    QueueNode* node = q->front;
    for(i = 0; i < q->count; i++){
      printf("%s, ", node->data);
      node = node->next;
    }
    printf("\b\b");
  }
  printf(")\n");
}

int main(void){
  int menu;
  char* name;

  Queue* nameQueue = CreateQueue();

  while (1){
    printf("In (0), Out (1), exit(2) : ");
	 scanf("%d", &menu);

    if (menu == 0){
      printf("Customer: ");
      name = (char*)malloc(sizeof(char)*20);
      scanf(" %[^\n]s", name);
      EnQueue(nameQueue, name);
      SeeQueue(nameQueue);
    }
    else if (menu == 1){
      DeQueue(nameQueue);
      SeeQueue(nameQueue);
    }
    else if (menu == 2){
      break;
    }
    else{
      printf("Wrong Input. Try again.\n");
    }
	printf("\n");
  }

    DestroyQueue(nameQueue);
    printf("Program successfully Ended.\n");
    return 0;
  }
