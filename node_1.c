#include <stdio.h>
#include <stdlib.h>
#include "req.h"
void use();
int main(int argc, const char *argv[])
{

    struct sockaddr_un addr;
    struct sockaddr_un des_addr;
        
    socklen_t len;

    char msg[MAX_MSG_SIZE];

    msg[MAX_MSG_SIZE - 1] = '\0';

    addr.sun_family = AF_UNIX;
    des_addr.sun_family = AF_UNIX;

    strcpy(addr.sun_path, SOCKA);
    strcpy(des_addr.sun_path, SOCKB);


   /*  if (argc < 2) 
        use();
     */
    
    if ((fd_1 = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
    {
        perror("failed while trying to create socket");
        exit(EXIT_FAILURE);
    }

    unlink(SOCKA);
    if (bind(fd_1, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("failed while trying to bind the socke");
        exit(EXIT_FAILURE);
    }

    char *msg_to = (char *)malloc(sizeof(char) * MAX_MSG_SIZE);
    char *msg_from = (char *)malloc(sizeof(char) * MAX_MSG_SIZE);
    size_t msg_size = MAX_MSG_SIZE;

    do
    {
        printf("Write a message: ");
        getline(&msg_to, &msg_size, stdin);
        memset(msg, 0, MAX_MSG_SIZE);
        strcpy(msg, msg_to);
        sendto(fd_1, msg, strlen(msg), 0, (struct sockaddr *)&des_addr, sizeof(des_addr));
        printf("You\n%s\n", msg);

        memset(msg, 0, MAX_MSG_SIZE);
        if (recvfrom(fd_1, msg, MAX_MSG_SIZE, 0, (struct sockaddr *)&des_addr, &len) == -1)
        {
            perror("failed while trying to receive");
            exit(EXIT_FAILURE);
        }
        printf("%s\n%s\n", NAME2, msg);

    } while (strcmp(msg, "exit") != 0);
}

void use() {
    printf("./a.out <yourname>\n");
    exit(EXIT_FAILURE);
}