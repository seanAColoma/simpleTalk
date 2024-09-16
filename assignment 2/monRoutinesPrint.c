#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include"list.h"

static pthread_mutex_t monWrite = PTHREAD_MUTEX_INITIALIZER;
//use these function as monitor subroutines - will be atomic
int monPPrepend(List* list, char* message)
{
    pthread_mutex_lock(&monWrite);
    {
        prepVal = List_prepend(list, message);
    }
    pthread_mutex_unlock(&monWrite);
}
char* monPTrim(List* list)
{
    char* message;
    pthread_mutex_lock(&monWrite);
    {
        message = List_trim(list);
    }
    pthread_mutex_unlock(&monWrite);

    return message;
}

int monPCount(List* list)
{
    int count;
    pthread_mutex_lock(&monWrite);
    {
        count = List_count(list);
    }
    pthread_mutex_unlock(&monWrite);

    return count;
}