# ifndef _BSP_UART_H
# define _BSP_UART_H

# include "stm32f10x.h"
# include "stdio.h"

// 串口1-USART1
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           115200

// USART GPIO 引脚宏定???
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


static void NVIC_Configuration(void);

/*???Դ???????*/
void DEBUG_UART_Config(void);

/*****************  ????һ???ֽ? **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);

/*****************  ?????ַ??? **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

/*?ض???c ?⺯??printf ?????ڣ??ض???????ʹ??printf*/
int fputc(int ch, FILE *f);

/*?ض???c ?⺯??scanf ?????ڣ???д????ʹ??scanf ?? getchar ?Ⱥ???*/
int fgetc(FILE* f);

void NVIC_Configuration(void);

# endif
