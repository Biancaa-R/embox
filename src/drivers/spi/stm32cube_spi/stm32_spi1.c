/**
 * @file
 * @brief
 * @author Denis Deryugin <deryugin.denis@gmail.com>
 * @version
 * @date 25.12.2019
 */

#include <stddef.h>

#include <util/macro.h>

#include <drivers/gpio.h>
#include <drivers/spi.h>

#if defined(STM32F407xx)
#include <framework/mod/options.h>
#include <config/platform/stm32/f4/stm32f4_discovery/bsp.h>
#endif

#include "stm32_spi.h"

#include <config/board_config.h>

#define SPI_BUS_NUM        1

#define SPI_BUS_NAME      MACRO_CONCAT(spi,SPI_BUS_NUM)

#define CONF_SPI          MACRO_CONCAT(CONF_SPI,SPI_BUS_NUM)

#if defined CONF_SPI1_REGION_BASE
#define SPI_REGION_BASE        ((uintptr_t)MACRO_CONCAT(CONF_SPI,_REGION_BASE))
#else
#define SPI_REGION_BASE         ((uintptr_t)MACRO_CONCAT(SPI,SPI_BUS_NUM))
#endif /* defined CONF_SPI1_REGION_BASE */

#define CLK_ENABLE_SPI          MACRO_CONCAT(CONF_SPI,_CLK_ENABLE_SPI)

#define SPI_PIN_SCK_PORT        MACRO_CONCAT(CONF_SPI,_PIN_SCK_PORT)
#define SPI_PIN_SCK_NR          MACRO_CONCAT(CONF_SPI,_PIN_SCK_NR)
#define SPI_PIN_SCK_AF          MACRO_CONCAT(CONF_SPI,_PIN_SCK_AF)

#define SPI_PIN_MISO_PORT       MACRO_CONCAT(CONF_SPI,_PIN_MISO_PORT)
#define SPI_PIN_MISO_NR         MACRO_CONCAT(CONF_SPI,_PIN_MISO_NR)
#define SPI_PIN_MISO_AF         MACRO_CONCAT(CONF_SPI,_PIN_MISO_AF)

#define SPI_PIN_MOSI_PORT       MACRO_CONCAT(CONF_SPI,_PIN_MOSI_PORT)
#define SPI_PIN_MOSI_NR         MACRO_CONCAT(CONF_SPI,_PIN_MOSI_NR)
#define SPI_PIN_MOSI_AF         MACRO_CONCAT(CONF_SPI,_PIN_MOSI_AF)

static const struct pin_description stm32_spi_pins[] = {
	{SPI_PIN_SCK_PORT, SPI_PIN_SCK_NR, SPI_PIN_SCK_AF},
	{SPI_PIN_MISO_PORT, SPI_PIN_MISO_NR, SPI_PIN_MISO_AF},
	{SPI_PIN_MOSI_PORT, SPI_PIN_MOSI_NR, SPI_PIN_MOSI_AF},
};

extern void hw_pins_config(struct spi_controller *spi_c);

static int stm32_spi1_init(void);
static struct stm32_spi stm32_spi1 = {
	.hw_init = stm32_spi1_init,
#if defined(CONF_SPI1_PIN_CS_PORT)
	.nss_port = CONF_SPI1_PIN_CS_PORT,
	.nss_pin  = CONF_SPI1_PIN_CS_NR,
#endif
	.bits_per_word = CONF_SPI1_BITS_PER_WORD,
	.clk_div       = CONF_SPI1_CLK_DIV,
};

static int stm32_spi1_init(void) {
#if defined(STM32F407xx) && !OPTION_MODULE_GET(platform__stm32__f4__stm32f4_discovery__bsp,BOOLEAN,errata_spi_wrong_last_bit)
	#error errata_spi_wrong_last_bit is not enabled for SPI1! \
	       Please, enable this option in platform.stm32.f4.stm32f4_discovery.arch
#endif

	struct spi_controller *spi_c = spi_controller_by_id(SPI_BUS_NUM);

	stm32_spi1.spi_controller = spi_c;
	spi_c->spic_label = SPI_REGION_BASE;
	spi_c->spic_pins = stm32_spi_pins;

	CLK_ENABLE_SPI();

	stm32_spi_init(&stm32_spi1, (void *) SPI_REGION_BASE);

	hw_pins_config(spi_c);

#if defined(CONF_SPI1_PIN_CS_PORT)
	/* Chip Select is usual GPIO pin. */
	gpio_setup_mode(CONF_SPI1_PIN_CS_PORT,
		(1 << CONF_SPI1_PIN_CS_NR),
		GPIO_MODE_OUT | GPIO_MODE_OUT_PUSH_PULL | GPIO_MODE_IN_PULL_UP);
		
	/* Chip Select is in inactive state by default. */
	gpio_set(CONF_SPI1_PIN_CS_PORT, (1 << CONF_SPI1_PIN_CS_NR), GPIO_PIN_HIGH);
#endif

	return 0;
}

SPI_CONTROLLER_DEF(SPI_BUS_NAME, &stm32_spic_ops, &stm32_spi1, SPI_BUS_NUM);
