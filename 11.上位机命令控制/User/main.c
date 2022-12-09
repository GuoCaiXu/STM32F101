# include "stm32f10x.h"
# include "./led/bsp_led.h"
# include "./uart/bsp_uart.h"
# include "stdio.h"

int main(void){

		uint8_t temp;

    LED_GPIO_Config();
    DEBUG_UART_Config();

    //USART_SendData(DEBUG_USARTx, 'a');
    Usart_SendString(DEBUG_USARTx, "���Ƴ���\n");
		printf("����1 ��LED1�� ����2 ��LED2\n");
	
		//printf->fputc->USART_SendData->   
		LED1_OFF;
		LED2_OFF;
    while(1){
      temp = getchar();
      printf("���յ�������Ϊ��%c\n", temp);
			
			switch(temp){
				case '1' : 
        LED1_ON; 
        LED2_OFF; 
        break;
				
        case '2' : 
        LED2_ON; 
        LED1_OFF; 
        break;
				
        default: 
				LED2_OFF; 
        LED1_OFF;
        break;
			}
    }
}
