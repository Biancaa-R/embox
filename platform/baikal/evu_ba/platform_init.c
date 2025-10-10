/**
 * @file
 *
 * @date Sep 26, 2025
 * @author Anton Bondarev
 */

#include <hal/platform.h>
#include <hal/reg.h>


extern void board_clocks_init(void);
extern void BSP_UART_Init(void);

void platform_init(void) {
	board_clocks_init();
	BSP_UART_Init();

}
