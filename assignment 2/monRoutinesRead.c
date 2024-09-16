#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <pthread.h>
#include"list.h"

static pthread_mutex_t monRead = PTHREAD_MUTEX_INITIALIZER;
//use these function as monitor subroutines - will be atomic
int monRPrepend(List* list, char* message)
{
    pthread_mutex_lock(&monRead);
    {
        prepVal = List_prepend(list, message);
    }
    pthread_mutex_unlock(&monRead);
}
char* monRTrim(List* list)
{
    char* message;
    pthread_mutex_lock(&monRead);
    {
        message = List_trim(list);
    }
    pthread_mutex_unlock(&monRead);

    return message;
}

int monRCount(List* list)
{
    int count;
    pthread_mutex_lock(&monRead);
    {
        count = List_count(list);
    }
    pthread_mutex_unlock(&monRead);

    return count;
}