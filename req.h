#include <sys/un.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define MAX_MSG_SIZE 128
#define SOCKA "./sockN1"
#define SOCKB "./sockN2"

#define NAME1 "Person 1"
#define NAME2 "Person 2"


char *name_1;
char *name_2;
int fd_1, fd_2;
int flag = 1;


struct message {
    char name[32];
    char msg[MAX_MSG_SIZE];
};