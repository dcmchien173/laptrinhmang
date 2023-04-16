#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
typedef struct sinhVien {
    char mssv[100];
    char hoTen[100];
    char ngaySinh[100];
    float diemTb;
} SinhVien;
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


    char buf[256];
    while(1) {
        // Chap nhan ket noi
        SinhVien sv;   

        time_t now = time(0);
        struct tm *local_time = localtime(&now);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);

        int ret = recv(client, &sv, sizeof(sv), 0);
        if(ret < 0) break;

        printf("MSSV: %s\n", sv.mssv);
        printf("Họ và tên: %s\n", sv.hoTen);
        printf("Ngày sinh: %s\n", sv.ngaySinh);
        printf("Điểm TB: %.2f\n\n", sv.diemTb);


        FILE *recv_file = fopen("/Users/macbook/Desktop/LTM16:4/sv_log.txt", "r+");

        fprintf(recv_file, "%s %s %s %s %s %.2f\n", 
            ip, time_str, sv.mssv, sv.hoTen, sv.ngaySinh, sv.diemTb);
        
        fclose(recv_file);
        close(client);
    }

   
    close(client);
    close(listener);
}