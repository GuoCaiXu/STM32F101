# include "stm32f10x.h"
# include "./led/bsp_led.h"
# include "./uart/bsp_uart_dma.h"
# include "stdio.h"

void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}

int main(void){

		uint32_t i;
    LED_GPIO_Config();
    DEBUG_UART_Config();
	/*DMA 初始化*/
		USARTx_DMA_Config();

    //USART_SendData(DEBUG_USARTx, 'a');
//    Usart_SendString(DEBUG_USARTx, "���Ƴ���\n");
//		printf("����1 ��LED1�� ����2 ��LED2\n");
	
	/*填充将要发送的数据*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'P';
    
  }
	
		//printf->fputc->USART_SendData->   
		LED1_OFF;
		LED2_OFF;
	
	/* USART1 向 DMA发出TX请求 */
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);
    while(1){
			
			LED1_TOGGLE
    Delay(0xFFFFF);
  }
}
