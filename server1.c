#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<ctype.h>

int main()
{   
   char tcp_sv,inp_file,out_file;
    int port;
    //scanf("%s %d %s %s",&tcp_sv,&port,&inp_file,&out_file);
  
    char str;
     FILE *f = fopen("/Users/macbook/Desktop/LTM16:4/input.txt","r+");
     fgets(&str,100,f); //Lệnh đọc xâu
     fclose(f);
     
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
    
    char *msg=&str;
    send(client, msg, strlen(msg), 0);
    char buf[256];
    //ghifile
    FILE *f1 = fopen("/Users/macbook/Desktop/LTM16:4/output.txt","r+");
    while (1)
    {
        int ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            printf("Ket noi bi dong.\n");
            break;    
        }
        if (ret < sizeof(buf))
            buf[ret] = 0;
        if (strncmp(buf, "exit", 4) == 0)
            break;
        printf("%s\n", buf);
        fputs(buf,f1);
       
    }
    fclose(f1);
    close(client);
    close(listener);
}
