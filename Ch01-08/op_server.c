#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char *message);
int caculate(int op_cnt, int opinfo[], char op);

int main(int argc, char *argv[]) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;

    if (argc != 2) {
        printf("Usage : %s <port>", argv[0]);
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        error_handling("bind() error");

    if (listen(server_sock, 1) == -1)
        error_handling("listen() error");
    
    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock == -1)
        error_handling("accept() error");
    
    int op_cnt = 0;
    read(client_sock, &op_cnt, 1);
    int index = 0;
    char opinfo[op_cnt * OPSZ + 2];
    while ((op_cnt * OPSZ + 1) > index) {
        int recv_cnt = read(client_sock, &opinfo[index], BUF_SIZE - 1);
        index += recv_cnt;
    }
    int result = caculate(op_cnt, (int*)opinfo, opinfo[index - 1]);
    write(client_sock, (char*)&result, sizeof(result));
    
    close(client_sock);
    close(server_sock);
    return 0;
}

int caculate(int op_cnt, int opinfo[], char op) {
    
    int result = opinfo[0];
    
    switch (op)
    {
    case '+':
        for (int i = 1; i < op_cnt; ++i) result += opinfo[i];
        break;
    case '-':
        for (int i = 1; i < op_cnt; ++i) result *= opinfo[i];
        break;
    case '*':
        for (int i = 1; i < op_cnt; ++i) result *= opinfo[i];
        break;    
    default:
        break;
    }
    return result;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}