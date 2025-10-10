/**
 * @file
 *
 * @date Sep 26, 2025
 * @author Anton Bondarev
 */

#include <drivers/bmcu_cru.h>
//#include <drivers/bmcu_uart.h>

/* UART */
//#define BSP_UART (UART0)
#define BSP_UART_CLK_EN_FN (CRU_APB0_EnableClock)
#define BSP_UART_CLK_PERITH (CRU_APB0_PERIPH_UART0)
#define BSP_UART_GPIO_EN_FN (CRU_APB0_EnableClock)
#define BSP_UART_GPIO_PERITH (CRU_APB0_PERIPH_GPIO0)
#define BSP_UART_AF_PORT (CRU_PORT_0)
#define BSP_UART_AF_PIN_TX (CRU_PIN_6)
#define BSP_UART_AF_PIN_RX (CRU_PIN_7)
//#define BSP_UART_IRQ (CLIC_UART0_IRQn)
//#define BSP_UART_IRQ_HANDLER_FN (UART0_IRQHandler)


void BSP_UART_Init(void)
{
    /* Enable UART clock */
    BSP_UART_CLK_EN_FN(BSP_UART_CLK_PERITH);

    /* Enable GPIO clock */
    BSP_UART_GPIO_EN_FN(BSP_UART_GPIO_PERITH);

    /* Configure alternate function of UART pins */
    CRU_SetPinAF(BSP_UART_AF_PORT, BSP_UART_AF_PIN_TX, CRU_PIN_AF_1);
    CRU_SetPinAF(BSP_UART_AF_PORT, BSP_UART_AF_PIN_RX, CRU_PIN_AF_1);
#if 0
    UART_DeInit(BSP_UART);
    
    UART_InitTypeDef UART_InitStruct;
    UART_StructInit(&UART_InitStruct);

    UART_InitStruct.BaudRate = 115200UL;
    UART_InitStruct.DataWidth = UART_DATAWIDTH_8B;
    UART_InitStruct.StopBits = UART_STOP_1BIT;
    UART_InitStruct.Parity = UART_PARITY_NONE;
    UART_InitStruct.Transfer9b = UART_TRANSFER_9B_DISABLE;
    UART_InitStruct.CtrlFIFO = DISABLE;

    UART_Init(BSP_UART, &UART_InitStruct);
#endif
}
