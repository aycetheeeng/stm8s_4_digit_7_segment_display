/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/

unsigned char DispStat;
unsigned char DispBuff[4];
unsigned int  DispValue;
void SetDisp (void);
void sayiyi_yazdir(int x);
int x;

#define LEDGRP0_PORT    GPIOE
#define LEDGRP0_PIN     GPIO_PIN_5

#define LEDGRP1_PORT    GPIOA
#define LEDGRP1_PIN     GPIO_PIN_1

#define LEDGRP2_PORT    GPIOB
#define LEDGRP2_PIN     GPIO_PIN_0

#define LEDGRP3_PORT    GPIOB
#define LEDGRP3_PIN     GPIO_PIN_1

#define LEDGRP4_PORT    GPIOB
#define LEDGRP4_PIN     GPIO_PIN_2

#define SEG0_PORT       GPIOD
#define SEG0_PIN        GPIO_PIN_6

#define SEG1_PORT       GPIOD
#define SEG1_PIN        GPIO_PIN_5

#define SEG2_PORT       GPIOC
#define SEG2_PIN        GPIO_PIN_1

#define SEG3_PORT       GPIOC
#define SEG3_PIN        GPIO_PIN_2

#define SEG4_PORT       GPIOC
#define SEG4_PIN        GPIO_PIN_3

#define SEG5_PORT       GPIOC
#define SEG5_PIN        GPIO_PIN_4

#define SEG6_PORT       GPIOD
#define SEG6_PIN        GPIO_PIN_2

#define SEG7_PORT       GPIOD
#define SEG7_PIN        GPIO_PIN_0
 
#define TIM4_PERIOD     (124)

static void SYSTEM_Config(void);
static void CLK_Config(void);
static void TIM4_Config(void);
static void GPIO_Config(void);


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

static void SYSTEM_Config(void)
{
   CLK_Config();
	 GPIO_Config();
   TIM4_Config();
}
 
static void CLK_Config(void)
{
   CLK_DeInit();
   CLK_HSECmd(DISABLE);
   CLK_HSICmd(ENABLE);
   CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
   CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
   CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
}
  
static void TIM4_Config(void)
{
   /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
   - With 125 000 Hz we can generate time base:
   max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
   min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
   - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */
 
   /* Time base configuration */
   TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
   /* Clear TIM4 update flag */
   TIM4_ClearFlag(TIM4_FLAG_UPDATE);
   /* Enable update interrupt */
   TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
 
   /* enable interrupts */
   	enableInterrupts();
 
   /* Enable TIM4 */
   TIM4_Cmd(ENABLE);
}


void GPIO_Config(void)
{
	
	GPIO_Init(GPIOE, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST); // ledgrp0
	GPIO_Init(GPIOA, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST); // ledgrp1
	GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST); // ledgrp2
	GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST); // ledgrp3
  GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST); // seg2
	GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST); // seg3
	GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST); // seg4
	GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST); // seg5
	GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST); // seg6
	GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST); // seg7
	
	GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);  // seg0
	GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);  // seg1

}


 
void SetDisp (void) 
{
  DispBuff[0] =  DispValue%10;
  DispBuff[1] = (DispValue/10)%10;
  DispBuff[2] = (DispValue/100)%10;
  DispBuff[3] = (DispValue/1000)%10;	         
}

void sayiyi_yazdir(int x)
{
switch(x){

case 0: 	
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG4_PORT,SEG4_PIN);                          // seg4 -- E 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 

//OFF
GPIO_WriteHigh(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 
break;

/*************************************************************************/
case 1:
//ON
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 

//OFF
GPIO_WriteLow(SEG0_PORT,SEG0_PIN);                          // seg0 -- A 
GPIO_WriteHigh(SEG3_PORT,SEG3_PIN);                         // seg3 -- D 
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
GPIO_WriteHigh(SEG5_PORT,SEG5_PIN);                         // seg5 -- F 
GPIO_WriteHigh(SEG6_PORT,SEG6_PIN);                         // seg6 -- G 
break;

/*************************************************************************/

case 2:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG4_PORT,SEG4_PIN);                          // seg4 -- E 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteHigh(SEG2_PORT,SEG2_PIN);                         // seg2 -- C 
GPIO_WriteHigh(SEG5_PORT,SEG5_PIN);                         // seg5 -- F 
break;

/*************************************************************************/

case 3:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
GPIO_WriteHigh(SEG5_PORT,SEG5_PIN);                         // seg5 -- F 
break;
/*************************************************************************/

case 4:
//ON
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteLow(SEG0_PORT,SEG0_PIN);                          // seg0 -- A 
GPIO_WriteHigh(SEG3_PORT,SEG3_PIN);                         // seg3 -- D 
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
break;
/*************************************************************************/

case 5:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteLow(SEG1_PORT,SEG1_PIN);                          // seg1 -- B 
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
break;
/*************************************************************************/

case 6:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG4_PORT,SEG4_PIN);                          // seg4 -- E 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteLow(SEG1_PORT,SEG1_PIN);                          // seg1 -- B 
break;
/*************************************************************************/

case 7:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 

//OFF
GPIO_WriteHigh(SEG3_PORT,SEG3_PIN);                         // seg3 -- D 
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
GPIO_WriteHigh(SEG5_PORT,SEG5_PIN);                         // seg5 -- F 
GPIO_WriteHigh(SEG6_PORT,SEG6_PIN);                         // seg6 -- G 
break;
/*************************************************************************/

case 8:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG4_PORT,SEG4_PIN);                          // seg4 -- E 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 
break;
//OFF

/*************************************************************************/

case 9:
//ON
GPIO_WriteHigh(SEG0_PORT,SEG0_PIN);                         // seg0 -- A 
GPIO_WriteHigh(SEG1_PORT,SEG1_PIN);                         // seg1 -- B 
GPIO_WriteLow(SEG2_PORT,SEG2_PIN);                          // seg2 -- C 
GPIO_WriteLow(SEG3_PORT,SEG3_PIN);                          // seg3 -- D 
GPIO_WriteLow(SEG5_PORT,SEG5_PIN);                          // seg5 -- F 
GPIO_WriteLow(SEG6_PORT,SEG6_PIN);                          // seg6 -- G 

//OFF
GPIO_WriteHigh(SEG4_PORT,SEG4_PIN);                         // seg4 -- E 
break;
}
}



void main(void){
	SYSTEM_Config();
	DispValue = 4987;
	SetDisp();

while(1){


}
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
