# ifndef _BSP_UART_H
# define _BSP_UART_H

# include "stm32f10x.h"
# include "stdio.h"

// 涓插彛1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 寮曡剼瀹忓畾涔?
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


static void NVIC_Configuration(void);

/*调试串口配置*/
void DEBUG_UART_Config(void);

/*****************  发送一个字节 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

/*重定向c 库函数printf 到串口，重定向后可使用printf*/
int fputc(int ch, FILE *f);

/*重定向c 库函数scanf 到串口，重写向后使用scanf ， getchar 等函数*/
int fgetc(FILE* f);

void NVIC_Configuration(void);

# endif
