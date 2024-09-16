// reads off keyboard and adds to list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "list.h"
#include "sendUDP.h"


// Max size of the message, using theoretical max length for a UDP packet of 65507 - 1 byte for null terminator
#define MAXBUFLEN 256

pthread_mutex_t mutexSendList;
static List* sendList;
static pthread_t readerThread;

static void* readLoop(){
        // Declaring variables
        int numRead;
        while(1) {
            //produce new item
            char msg[256];
            numRead = read(0, msg, MAXBUFLEN);
            msg[numRead] = '\0';
            //attempt to add item to queue *
            //*critical section*
            pthread_mutex_lock(mutexSendList);
            if(List_prepend(sendList, &msg) == -1) {
                //wait
                List_prepend(sendList, &msg);
            }
            pthread_mutex_unlock(mutexSendList);
            //signal sender
        }
}


void readerInit(List* l){
    sendList = l;
    int readingThread =  pthread_create(&readerThread, NULL, readLoop, NULL);
    if(readingThread !=0){//if gave error code of not 0 (0 is success)
        perror("reader: thread creation error");
        exit(-1);
    }
    
}

void readerCancel()
{
    pthread_cancel(readerThread);
}

void readerShutdown()
{
    pthread_join(readerThread,NULL);
}