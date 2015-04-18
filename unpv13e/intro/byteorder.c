#include <stdio.h>

/// 地址是由低往高增长，如果低位存放在低地址，高位存放在高地址，就是小端，否则
/// 就是大端。
/// 测试结果ubuntu是小端。

int main() {
	union {
		short s;
		char ch[sizeof(short)];
	} un;
	un.s = 0x0102;
	printf("un.s     = 0x%04X\n", un.s);
	printf("un.ch[0] = %d\n", un.ch[0]);
	printf("un.ch[1] = %d\n", un.ch[1]);

	printf("Address of un      : %p\n", (void*)(&un));
	printf("Address of un.ch[0]: %p\n", (void*)(&un.ch[0]));
	printf("Address of un.ch[1]: %p\n", (void*)(&un.ch[1]));

	return 0;
}

