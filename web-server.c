#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char *argv[]) {
    unsigned short      port;
    DIR*                directory = NULL;
    int                 acceptorSocket;
    struct sockaddr_in  server, client;

    /* (1) Überprüfen, ob Port angegeben wurde */
    if (argc != 3) {
        fprintf(stderr, "arguments error\r\n");
        exit(1);
    }

    /* Port setzen */
    port = (unsigned short) atoi(argv[1]);

    /* (2) Verzeichnis setzen */
    directory = opendir(argv[2]);
    if (directory == NULL) {
        fprintf(stderr, "directory error\r\n");
        exit(2);
    }

    /* (3) Socket zum akzeptieren von Clients erstellen */
    if ((acceptorSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "acceptorSocket error\r\n");
        exit(3);
    }

    /* (4) Socket zum akzeptieren an Server binden */
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(acceptorSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        fprintf(stderr, "bind socket error\r\n");
        exit(4);
    }
}