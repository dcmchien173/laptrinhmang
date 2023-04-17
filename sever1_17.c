#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    struct sockaddr_in clientAddr;
    unsigned int clientAddrLen = sizeof(addr);

    int client = accept(listener, (struct sockaddr *)&clientAddr, &clientAddrLen);
    printf("Client IP: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    char *ip = inet_ntoa(clientAddr.sin_addr);


    char buffer[1024];
    while(1) {
    int valread = read(client, buffer, 1024);
    char *hostname = strtok(buffer, ";");
    int n = atoi(strtok(NULL, ";"));
    char *drives = strtok(NULL, ";");
    
    // In ra các thông tin đã nhận được từ info_client
    printf("Đã nhận được thông tin từ máy tính %s:\n", hostname);
    printf("Số ổ đĩa: %d\n", n);
    printf("Danh sách các ổ đĩa:\n");
    char *token = strtok(drives, " ");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
    }
   
    close(client);
    close(listener);
}