#include "pwm_hal.h"

TIM_HandleTypeDef tim_init;
TIM_OC_InitTypeDef tim2_conf;

void init_pwm(void)
{
	tim_init.Instance = TIM2;
	tim_init.Channel = HAL_TIM_ACTIVE_CHANNEL_4 | HAL_TIM_ACTIVE_CHANNEL_3 | HAL_TIM_ACTIVE_CHANNEL_1 | HAL_TIM_ACTIVE_CHANNEL_2;
	
	tim_init.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim_init.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	tim_init.Init.Prescaler = 10;
	tim_init.Init.Period = TIMER_PERIOD_1KHZ;
	tim_init.Init.AutoReloadPreload = 0;

	TIM_ClockConfigTypeDef tim_clk_init;
	tim_clk_init.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	tim_clk_init.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;

	HAL_TIM_PWM_Init(&tim_init);

	tim2_conf.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	tim2_conf.OCMode = TIM_OCMODE_PWM1; // Timer PWM mode 2, if Counter > Pulse, we set the output pin LOW till end of cycle
	tim2_conf.OCNIdleState = TIM_OCIDLESTATE_RESET;
	tim2_conf.Pulse = 500;

	HAL_TIM_PWM_ConfigChannel(&tim_init, &tim2_conf, TIM_CHANNEL_4 | TIM_CHANNEL_3 | TIM_CHANNEL_1 | TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_4 | TIM_CHANNEL_3 | TIM_CHANNEL_1 | TIM_CHANNEL_2);

}

void set_pwm(pwm_channel ch, float duty)
{
	switch(ch)
	{
		case mtr1_pwm1:
			tim2_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim2_conf, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_4);
			break;
		case mtr1_pwm2:
			tim2_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim2_conf, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_3);
			break;
		case mtr2_pwm1:
			tim2_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim2_conf, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_1);
			break;
		case mtr2_pwm2:
			tim2_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim2_conf, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_2);
			break;
	}
}