#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>


int main() {
 char hostname[50], drives[100], buffer[1024];
    // Tao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Khai bao dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);
   printf("121.0.0.1 9000 \n");
    // Ket noi den server
    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if(ret == -1) {
        perror("Kết nối thất bại");
        exit(1);
    }

   while(1){
    // Nhap va gui du lieu
    printf("Nhập tên máy tính: ");
    scanf("%s", hostname);
    printf("Số ổ đĩa: ");
    int n;
    scanf("%d", &n);
    printf("Nhập danh sách các ổ đĩa (mỗi ổ đĩa gồm ký tự và kích thước, phân tách bởi dấu cách):\n");
    scanf(" %[^\n]s", drives);
     snprintf(buffer, sizeof(buffer), "%s;%d;%s", hostname, n, drives);
    send(client, buffer, strlen(buffer), 0);
    printf("Đã gửi thông tin đến info_server.\n");
   
   }

    close(client);
    return 0;
    
}