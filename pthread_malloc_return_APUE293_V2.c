#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
#What I want to say is in sub thread,
#we can return data from sub thread to main process under the help of pthread_exit
#But  the Stack(namely local vairiable) content can not return to main process
#Only the Heap (namely malloc)          content can return to main process
*/

void* thr_fn(void *args)
{
    printf("In thr_fn:\n");
    int i = 0;
    //This is the Key point----
    //int array[4];
    int *array = malloc(16);
    for (i = 0; i < 4; i++ )
        *(array + i) = i;
    
    for (i = 0; i < 4; i++ )
        printf("*(array + %d) = %d\n", i, *(array + i));
    
    pthread_exit((void *)array);
}


int main()
{
    pthread_t tid;
    void * tret;
    int i = 0;
    int err;
    err = pthread_create(&tid, NULL, thr_fn, NULL);
    if(err != 0)
        printf("Can not create thread %s\n", strerror(err));
    
    err = pthread_join(tid, &tret);
    if(err != 0)
        printf("Can not join with thread %s", strerror(err));
    
    int *p = (unsigned int *)tret;
    for(i = 0; i < 4; i++)
        printf("*(tret + %d) = %d\n", i, *(p + i));
    
}
