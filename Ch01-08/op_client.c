#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
#define RESULT_SIZE 4
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;

    if (argc != 3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        error_handling("connect() error");
    else
        printf("Connected ... ...\n");
    printf("operand count: ");
    int count;
    char opmsg[BUF_SIZE];
    scanf("%d", &count);
    opmsg[0] = (char)count;
    for (int i = 0; i < count; ++i) {
        printf("operand number %d: ", i + 1);
        scanf("%d", (int*)&opmsg[i * OPSZ + 1]);
    }
    fgetc(stdin);
    printf("operator: ");
    scanf("%c", &opmsg[count * OPSZ + 1]);
    write(sock, opmsg, count * OPSZ + 2);
    int result;
    read(sock, &result, RESULT_SIZE);
    printf("result: %d", result);
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}