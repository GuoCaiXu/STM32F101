# include "stm32f10x.h"
# include "./led/bsp_led.h"
# include "./uart/bsp_uart.h"
# include "stdio.h"

int main(void){

    DEBUG_UART_Config();

    //USART_SendData(DEBUG_USARTx, 'a');
    Usart_SendString(DEBUG_USARTx, "�������\n");
		printf("ɵ��\n");
	
		//printf->fputc->USART_SendData->      ����  
	
    while(1);
}
