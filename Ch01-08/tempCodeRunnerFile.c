
#include <stdio.h>
 
union test//共用一段内存空间，只为最长成员分配空间
{
	short val;
	char array[2];
};
 
int main()
{
	union test t;
 
	t.val = 0x0102;
 
	if (t.array[0] == 1 && t.array[1] == 2)//大端字节序：高字节存放在低地址，低字节存放在髙地址
	{
		printf("big endian!\n");
	}
	else if (t.array[0] == 2 && t.array[1] == 1)//小端字节序：低字节存放在低地址，低字节存放在低地址
	{
		printf("little endian!\n");
	}
 
	return 0;
}
