/*
  This is the main user software application
  In this case, we have below the code necessary to use PWM with mtrs on an STM32 F3 Discovery PCB.

  (c) Abhimanyu Ghosh, 2017
 */

// C standard include(s):
#include <math.h>
#include <time.h>


// Custom user APIs needed for hardware access specific to this board:
#include "cpu.h"
#include "pwm_hal.h"
#include "board_led.h"
#include "button_hal.h"
// #include "tm_stm32f4_hcsr04.h"
// Custom user APIs needed for generic algorithmic libraries that are hardware-independent:
#include "foo.h"

volatile uint32_t msTicks;
int state = 0;
int tick;
volatile float count;
TIM_HandleTypeDef cnt_init;

int cntr(int condn){
  if(condn == 1){
    /*start counter*/
    count += 1;
  }
  else if(condn == 0){
    /*end counter*/
    count = 0;
  }
  
}
void fwd()
{
    set_pwm(mtr1_pwm1, 0.7f);
    set_pwm(mtr1_pwm2, 0.0f);
    set_pwm(mtr2_pwm1, 0.7f);
    set_pwm(mtr2_pwm2, 0.0f);
}

void bkd()
{
    set_pwm(mtr1_pwm1, 0.0f);
    set_pwm(mtr1_pwm2, 0.7f);
    set_pwm(mtr2_pwm1, 0.0f);
    set_pwm(mtr2_pwm2, 0.7f);
}
void rgt()
{
    set_pwm(mtr1_pwm1, 0.0f);
    set_pwm(mtr1_pwm2, 0.7f);
    set_pwm(mtr2_pwm1, 0.7f);
    set_pwm(mtr2_pwm2, 0.0f);
}

void lft()
{
    set_pwm(mtr1_pwm1, 0.7f);
    set_pwm(mtr1_pwm2, 0.0f);
    set_pwm(mtr2_pwm1, 0.0f);
    set_pwm(mtr2_pwm2, 0.7f);
}

/*
  Function to provide delay (in mSec)
 */
void Delay (uint32_t delayTicks) {                                              
  uint32_t currentTicks;

  currentTicks = msTicks;
  while ((msTicks - currentTicks) < delayTicks);
}

/*
  Function to provide delay (in uSec)
 */
void delayUS(uint32_t us) {
  volatile uint32_t counter = 7*us;
  while(counter--);
}

// void HAL_TIM_IC_CaptureCallback()
// {
//   if (htim->Instance==TIM2)
//     {
//                 input_capture= __HAL_TIM_GetCompare(&htim2, TIM_CHANNEL_1); //read TIM2 channel 1 capture value
//     __HAL_TIM_SetCounter(&htim2, 0);  //reset counter after input capture interrupt occurs
//     }
// }

void count_init(){
    cnt_init.Instance = TIM2;
    HAL_TIM_Base_Start_IT(&cnt_init);
}
void count_stop(){
    count = 0;
    cnt_init.Instance = TIM2;
    HAL_TIM_Base_Stop_IT(&cnt_init);
}

void trigger(){
  delayUS(12);
  count_init();
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
  delayUS(12);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
}

// float SR04read(void) {
//   TIM_SetCounter(TIM2, 0);
//   GPIO_SetBits(GPIOC, SR04_TRIG);
//   while(TIM_GetCounter(TIM2) < 15);
//   GPIO_ResetBits(GPIOC, SR04_TRIG);
//   //TIM_SetCounter(TIM2, 0);
//   while(!GPIO_ReadInputDataBit(GPIOC, SR04_ECHO));// & (TIM_GetCounter(TIM2) < 50000));
//   TIM_SetCounter(TIM2, 0);
//   while(GPIO_ReadInputDataBit(GPIOC, SR04_ECHO));// & (TIM_GetCounter(TIM2) < 50000));
//   return ((float)TIM_GetCounter(TIM2) * 0.01715 + SR04_OFFSET);
// }

void echo(){

}

int main()
{
  /*
    Initialize the PLL, clock tree to all peripherals, flash and Systick 1 ms time reference:
   */
  cpu_init();
  board_led_init();
  uart_debug_init();
  button_init();

  setvbuf(stdin,NULL,_IONBF,0);   // Sets stdin in unbuffered mode (normal for usart com)
  setvbuf(stdout,NULL,_IONBF,0);  // Sets stdin in unbuffered mode (normal for usart com)
  
  printf("Hello World!!\r\n");

  /*
    WARNING: We cannot use one of the GPIOs (PE9) from board_mtr since it is now being used for PWM!!
   */

  /*
    Initialize the PWM outputs :
   */
  init_pwm();

  int i = 0;
  int cnt = 0;
  float dist = 0.0f;

  set_pwm(mtr1_pwm1, 0.0f);
  set_pwm(mtr1_pwm2, 0.0f);
  set_pwm(mtr2_pwm1, 0.0f);
  set_pwm(mtr2_pwm2, 0.0f);




  while(!button_pressed(button_user));

  trigger();

 
  // Do some calculation.

  /*
    In an infinite loop, keep toggling the mtrs in an alternating pattern:
   */
  while(1)
  {
    /*
      Carry out a simple unit test of foo() declared in foo.h:
     */
    if(TEST_FOO(i, i+1) < 0)
    {
      /*
        If the above fails there is either a hardware, code or other undefined error.
        Now we're in an undefined state regarding processor core behavior...
       */
      while(1); // We probably have had a radiation hit or a major malfunction on the ALU of the processor...
    }
    else
    {
      set_pwm(mtr1_pwm1, 0.5f);
      // if(!button_pressed(button_user)){
      //     // printf("%s\n","HI");
      //     trigger();
      //     // state = 1;
      // }
      trigger();
      if (button_pressed(button_user) && state == 0){
          count_init();
          state = 1;
      }
      else if (button_pressed(button_user) && state == 1){
          count = __HAL_TIM_GetCounter(&cnt_init);
          count = count / 406;
          printf("%d\n",count);
          count_stop();
          count = 0;
          state = 0;
      }
      
    }  
  }

  return 0;
}
