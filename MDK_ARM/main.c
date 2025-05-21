#include "main.h"  
#include "bsp_uart.h"


uint8_t  FatFs_FileTest(void);	//文件创建和写入测试

int main(void)
{
	board_init();
	
	/* 串口初始化 波特率：115200 */
	bsp_uart_init();


	
    while(1) {
		
    }
}
