#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "readInput.h"
#include "writeOutput.h"
#include "receiveUDP.h"
#include "sendUDP.h"

char* myPort;
char* remoteHost;
char* remotePort;
// Launches the s-talk program
pthread_mutex_t mutexSendList;
static List* sendList;
static List* printList;
static pthread_t readerThread;

pthread_cond_t sendEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t sendFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t myconvar = PTHREAD_COND_INITIALIZER;
#define MAXBUFLEN 256

static void* readLoop(){
        // Declaring variables
        int numRead;
        while(1) {
            //produce new item
            char msg[256];
            numRead = read(0, msg, MAXBUFLEN);
            msg[numRead] = '\0';
            //!critical section!
            pthread_mutex_lock(mutexSendList);
            //prepend only returns -1 if all nodes are in use
            if(List_prepend(sendList, &msg) == -1) {
                pthread_cond_wait(&sendFull, &mutexSendList);
                List_prepend(sendList, &msg);
            }
            pthread_cond_signal(&sendEmpty);
            pthread_mutex_unlock(mutexSendList);
            //!critical section end!
            if(strcmp(msg, "!\n") == 0) {
                //end this thread and printing thread and recieving thread
            }
            //signal sender

        }
}

static void UDPsender() {
    //prep socket
    while(1) {
        //whatever
        //send something
        pthread_mutex_lock(mutexSendList);
        if(List_count(sendList) == 0) {
            pthread_cond_wait(&sendEmpty, &mutexSendList);
        }
        msg = List_trim(sendList);
        pthread_cond_signal(&sendFull);
        pthread_mutex_unlock(mutexSendList);
        //send item
        //sent !
        if() {
            //end this thread
        }
    }
}

static void printer() {
    while(1) {
        //if just printed !
        if() {
            //end this thread
        }
    }

}

static void UDPReceiver() {

    //if just received !
    if(){
        //end this thread and sending thread and getting thread
        printf("other user terminated communication, printing last messages now\n");
    }
}
//need to change main to reflect structure
int main (int argc, char * argv[])
{
    // Checks if arguments are correct
    if (argc!=4)
    {
        printf("Invalid arguments\n");
        return -1;
    }

    // Storing arguments
    myPort = argv[1];
    remoteHost = argv[2];
    remotePort = argv[3];

    // Creates a shared list
    sendList = List_create();
    printList = List_create();

    // Initializes the four modules
    // Modules are running in an infinite loop, they will exit when given the exit code "!"
    //needs to have access to print list to check number of nodes used
    readerInit(toBeSent, toBePrint);
    senderInit(remoteHost, remotePort, toBeSent);
    //needs to have access to send list to check number of nodes used
    receiverInit(myPort, toBePrint, toBeSent);
    writerInit(list);

    // Cleans up the threads
    readerShutdown();
    senderShutdown();
    receiverShutdown();
    writerShutdown();

    // Frees the list
    // At this point, the list should already be empty
    List_free(list, free);

    return 0;
}