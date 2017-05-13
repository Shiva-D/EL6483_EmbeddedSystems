#include "board_led.h"

void board_led_init(void)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_15 | GPIO_PIN_11 | GPIO_PIN_14 | GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	__HAL_RCC_GPIOE_CLK_ENABLE();

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		case LED2:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
			break;
		case LED3:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
			break;
		case LED4:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
			break;
		case LED5:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
			break;
		case LED6:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
			break;
		case LED7:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			break;
		case LED8:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
			break;
		case LED2:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
			break;
		case LED3:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
			break;
		case LED4:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
			break;
		case LED5:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			break;
		case LED6:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
			break;
		case LED7:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		case LED8:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			break;
	}
}

void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
			break;
		case LED2:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
			break;
		case LED3:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_12);
			break;
		case LED4:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
			break;
		case LED5:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_13);
			break;
		case LED6:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_14);
			break;
		case LED7:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_15);
			break;
		case LED8:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
			break;
	}
}