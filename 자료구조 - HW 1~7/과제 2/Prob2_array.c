#include <stdio.h>
#include "queue_array.h"

void SeeQueue(Queue* q){
  int i;
  //printf("%d, %d, %d, %d\n", CountQueueItem(q), q->front, q->rear, q->size);
  printf("The current status of Queue: (");
  if (CountQueueItem(q) != 0){

	  for (i = q->front; i != q->rear; i++){
		if(i != 0 && (i+1) % (q->size) == 0){
			i = -1;
		}
		printf("%s, ", q->queue[i + 1]);
	  }
	  printf("\b\b");
  }
  printf(")\n");
}

int main(void){
  int menu;
  char* name;

  Queue* nameQueue = CreateQueue(10);

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
