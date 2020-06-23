#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);
    unsigned char *p =(unsigned char*)&net_port;
    printf("%#x - %#x\n", p[0], p[1]);
    printf("Network ordered port: %#x \n", net_port);
    printf("Network ordered address: %#lx\n", net_addr);
    return 0;
}
// #include <stdio.h>

// union test//共用一段内存空间，只为最长成员分配空间
// {
// 	short val;
// 	char array[2];
// };
 
// int main()
// {
// 	union test t;
 
// 	t.val = 0x0102;
 
// 	if (t.array[0] == 1 && t.array[1] == 2)//大端字节序：高字节存放在低地址，低字节存放在髙地址
// 	{
// 		printf("big endian!\n");
// 	}
// 	else if (t.array[0] == 2 && t.array[1] == 1)//小端字节序：低字节存放在低地址，低字节存放在低地址
// 	{
// 		printf("little endian!\n");
// 	}
 
// 	return 0;
// }
