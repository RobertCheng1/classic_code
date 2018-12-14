//The author is RobertCheng
#include <stdio.h>
#include <stdlib.h>

struct Node{
  char value;
  struct Node * pLeft;
  struct Node * pRight;
};
struct Node * root = NULL;
int maxsize = 20;

int max(int a, int b){
  return a > b ? a: b;
}
//Define a Queue as a tool to wideFirstDisplay
/*
struct Queue{
  Struct Queue * front;
  Struct Queue * rear;
  Struct Node * pData;
  Struct Queue * pNext;
};
*/
struct Queue{
  struct QueueNode * front;
  struct QueueNode * rear;
};

struct QueueNode{
  struct Node * pData;
  struct QueueNode * pNext;
};

struct Queue * q = NULL;
void initQueue(){
  q = (struct Queue *)malloc(sizeof(struct Queue));
  q->front = NULL;
  q->rear = NULL;
}
int isEmpty(struct Queue *queue){
  if(queue->rear == NULL)
    return 1;
  else
    return 0;
}
void enQueue(struct Node *pNode){
  struct QueueNode * tmp = (struct QueueNode *) malloc(sizeof(struct QueueNode));
  //printf("In enQueue pNode->value = %c\n", pNode->value);
  tmp->pData = pNode;
  tmp->pNext = NULL;

  //The queue is blank
  if(q->rear == NULL)
  {
    q->front = tmp;
    q->rear = tmp;
  }
  else 
  {
    q->rear->pNext = tmp;
    q->rear=tmp;
  }
  return; 
}

int deQueue(struct Node ** ppNode){
  //The queue is blank
  if(q->rear == NULL)
  {
    return 0;
  }

  struct QueueNode *tmp = q->front;
  //There is only one node in the queue
  if(q->front == q->rear)
  {
    q->rear = NULL;
  }
  q->front = q->front->pNext;
  *ppNode = tmp->pData;
  //printf("In deQueue tmp->value = %c\n", tmp->pData->value);
  free(tmp);
  return 1;
}

//char treeStr[40] = "A(B(D(,G)),C(E,F))";
char treeStr[40] = "A(B(D(G,H),E),C(,F))";


void initTree(){
  root = (struct Node *)malloc(sizeof(struct Node));
  //memset(root, 0, sizeof(struct Node));
  root->value = 97;
  root->pLeft = NULL;
  root->pRight = NULL;
  return ;
}


void createTree(char * pstr){
  printf("In Create Tree, pstr = %s\n", pstr);
  
  struct Node * tmp[maxsize];
  int top = -1;
  int flag = -1;
  struct Node * pNode = NULL;
  int i = 0;
  char ch = *(pstr + i);
  while(ch != '\0'){
    switch (ch){
      case '(':
        top++;
        tmp[top] = pNode;
        flag = 1; // Left chidlren
        break;
      case ')':
        top--;
        flag = 2; // Right chidlren
        break;
      case ',':
        flag = 2;
        break;
      default:
        pNode = (struct Node *)malloc(sizeof(struct Node));
        pNode->value = ch;
        if (root == NULL)
        {
          root = pNode;
        } 
        else 
        {
          switch (flag){
            case 1:
              tmp[top]->pLeft = pNode;
              break;
            case 2:
              tmp[top]->pRight = pNode;
              break;
          }
        }  
    }
    i++;
    ch = *(pstr+i);
  }
  return;
}

int heightOfTree(struct Node * pNode){
  if(pNode == NULL)
  {
    return 0;
  }
  else
  {
    int lh = heightOfTree(pNode->pLeft);
    int rh = heightOfTree(pNode->pRight);
    return max(lh, rh) + 1; 
  }
}

int countOfLeafs(struct Node * pNode){
  if(pNode == NULL)
  {
    return 0;
  }
  if(pNode->pLeft == NULL && pNode->pRight == NULL)
  {
    //printf("In if pNode->value = %c\n",pNode->value);
    return 1;
  }
  else
  {
    //printf("pNode->value = %c\n",pNode->value);
    int lc = countOfLeafs(pNode->pLeft);
    int rc = countOfLeafs(pNode->pRight);
    return lc + rc;
  }
}

void deepFirstDisplay(struct Node * pNode){
  if(pNode == NULL)
  {
    //printf("The tree is blank\n");
    return;
  }
  else
  {
    printf("%c\n", pNode->value);
    deepFirstDisplay(pNode->pLeft);
    deepFirstDisplay(pNode->pRight);
  }
}

//We need a queue to wideFirstDisplay
void wideFirstDisplay(struct Node * pNode){
  if(pNode == NULL)
  {
    //printf("The tree is blank\n");
    return;
  }
  else
  {
    initQueue();
    struct Node *tmp = NULL;
    
    enQueue(pNode);
    while(!isEmpty(q))
    {
      deQueue(&tmp);
      printf("%c\n", tmp->value);
      if(tmp->pLeft != NULL)
        enQueue(tmp->pLeft);
      if(tmp->pRight != NULL)
        enQueue(tmp->pRight);
    }
    return;
  }
}

int main(){
  //initTree();
  //printf("root->value = %c\n", root->value);
  createTree(treeStr);
  printf("root->value = %c\n", root->value);

  printf("deepFirstDisplay is:\n");
  deepFirstDisplay(root);
  printf("wideFirstDisplay is:\n");
  wideFirstDisplay(root);

  int height = heightOfTree(root);
  printf("height = %d\n", height);

  int totalLeafs = countOfLeafs(root);
  printf("totalLeafs = %d\n", totalLeafs);

  return 0;
}
