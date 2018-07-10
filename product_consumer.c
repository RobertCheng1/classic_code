#include <stdio.h>
#include <pthread.h>
#define QUEUE_SIZE 5

int g_queue[QUEUE_SIZE] = {0};
int head = 0;
int tail = 0;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock =  PTHREAD_MUTEX_INITIALIZER;

int init_queue(int *p)
{
    int i = 0;
    for (i = 0; i < QUEUE_SIZE; i++ )
        *(p + i) = 0;
}
int display_queue(char *pc, int *p)
{
    int i = 0;
    for (i = 0; i <QUEUE_SIZE; i++)
        printf("\t[%s] *(p + %d) = %d\n",pc, i, *(p + i));
}

void* consumer(void *args)
{
    
    printf("Begin in consumer\n");
    sleep(6);
    while(1)
    {
        pthread_mutex_lock(&qlock);
        while(g_queue[tail] == 0)
            pthread_cond_wait(&qready, &qlock);
        
        g_queue[tail] = 0;
        tail = tail + 1;
        if(tail == QUEUE_SIZE)
            tail = 0;
        
        printf("After consume:\n");
        display_queue("consumer", g_queue);
        pthread_mutex_unlock(&qlock);
        pthread_cond_signal(&qready);
        
        sleep(2);
        
    }
    pthread_exit((void *) 0);    
}

void* productor(void *args)
{
    int loop = 1;    
    printf("Begin in productor\n");
    while(1)
    {
        pthread_mutex_lock(&qlock);
        while(g_queue[head] != 0)
            pthread_cond_wait(&qready, &qlock);
        
        g_queue[head] = loop;
        head = head + 1;
        if(head == QUEUE_SIZE)
            head = 0;
        
        printf("After produce:\n");
        display_queue("productor", g_queue);
        pthread_mutex_unlock(&qlock);
        pthread_cond_signal(&qready);
        
        
        loop++;
        sleep(1);
        
    }
    pthread_exit((void *) 0);
}


int main()
{
    pthread_t pidProductor;
    pthread_t pidCousumer;
    int err;
    void * tret;
    
    init_queue(g_queue);
    display_queue("main",g_queue);
    pthread_create(&pidProductor, NULL, productor, NULL);
    pthread_create(&pidCousumer, NULL, consumer, NULL);
    
    //This is to hold on in main process
    err = pthread_join(pidProductor, &tret);
    if(err != 0)
        printf("Can not join with thread %s", strerror(err));
    
    err = pthread_join(pidCousumer, &tret);
    if(err != 0)
        printf("Can not join with thread %s", strerror(err));
    return 0;
}
