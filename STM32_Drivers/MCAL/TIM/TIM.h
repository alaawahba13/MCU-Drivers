///*
// * TIM.h
// *
// *  Created on: Apr 14, 2024
// *      Author: Alaa
// */
//
//#ifndef TIM_TIM_H_
//#define TIM_TIM_H_
//
//
////=======================
////       Includes
////=======================
#include "../Lib/STM32_F103x6.h"
#include "../RCC/RCC.h"
#include <string.h>
#ifndef TIM_H_
#define TIM_H_

#define     TIM_CR1_CEN             0
#define     TIM_CR1_DIR             4
#define     TIM_CR1_URS             2
#define     TIM_CR1_ARPE            7
#define     TIM_DIER_UIE            0
#define     ARPE                    7
#define     TIM_CCER_CC1P                   1
#define     TIM_CCER_CC2P                   5
#define     TIM_CCER_CC3P                   9
#define     TIM_CCER_CC4P                   13
#define     TIM_CCER_CC1E                   0
#define     TIM_CCER_CC2E                   4
#define     TIM_CCER_CC3E                   8
#define     TIM_CCER_CC4E                   12
#define     TIM_CCMR1_OC1PE         3
#define     TIM_CCMR1_OC2PE         11
#define     TIM_CCMR2_OC3PE         3
#define     TIM_CCMR2_OC4PE         11
#define     IC1F                    4
#define     IC2F                    12
#define     IC3F                    4
#define     IC4F                    12
#define     TIM_DIER_UIE            0
#define     TIM_SR_UIF                  0
#define     TIM1EN                  11
#define     TIM8EN                  13
#define     TIM_EGR_CC1G            1
#define     TIM_EGR_CC2G            2
#define     TIM_EGR_CC3G            3
#define     TIM_EGR_CC4G            4
#define     TIM_BDTR_MOE            15
#define     TIM_EGR_UG              0
#define     TIM_DIER_CC1IE          1
#define     TIM_DIER_CC2IE          2
#define     TIM_DIER_CC3IE          3
#define     TIM_DIER_CC4IE          4

  #define TIM_Ratio     MilleSeconds


/*************************TIM Interval modes******************************************** */
#define TIM_SINGLE_INTERVAL_MODE            0
#define TIM_PERIODIC_INTERVAL_MODE          1
/***************typedef******************/

 typedef enum {
     /*count from 0 to auto-reload value*/
     Up_Counting,
     /*count from auto-reload value 0*/
     Down_Counting,
     /*count from 0 to (auto-reload value -1) then count from auto-reload value to 1*/
     Center_Aligned
 }direction_m;

 typedef enum
 {
    TIM_Channel1,TIM_Channel2,TIM_Channel3,TIM_Channel4
 }channel_t;
 typedef enum
 {
    Div_1,
    Div_2,
    Div_3
 }Clk_Div;
 typedef enum
 {
    Disable_ARR_Buffer,
    Enable_ARR_Buffer
 }ARR_Buffer_State;
 typedef enum
 {
     Disable_Interrupt,
    Enable_Interrupts
 }INT_State;
 typedef enum {
  TIMER_CLK_SRC_INTERNAL,
  TIMER_CLK_SRC_EXTERNAL_MODE1,
  TIMER_CLK_SRC_EXTERNAL_MODE2
} timer_clk_src_t;

 typedef enum {
    Active_High,
    Active_Low
 }TIM_Polarity;
 typedef enum
 {
      EdgeAligned_Mode,CenterAligned_Mode
 }state;

 typedef enum
 {
     /*in forced output RISING meaning active and FAllING meaning inactive*/
     RISING, FALLING
 }edge_t;
 typedef enum {
        PWM_11  =   0b110,
        PWM_22  =   0b111
    }PWM_modee;
 typedef struct
{

    uint16 AutoReloadValue;/*value count to it */
    direction_m Tim_Direction;
    state AlignedMode;
    Clk_Div ClockFactor;
    ARR_Buffer_State AutoReloadBuffer;
    INT_State UDI_State;
    uint16 Prescalar;

}TIM_ConfigType;

typedef struct{
    uint16 AutoReloadValue;
    channel_t Channel;
    uint16 Freq;
    PWM_modee Mode;

}PWM_ConfigType;


/***************Functions ProtoTypes***************/
/*Function Description:
 * TIMx Should be (TIM1 ||  TIM2 || TIM3 || TIM4)
 * @TIM_ConfigType
 */
void TIM_Init(TIM_Registers_t* TIMx, TIM_ConfigType *TimConfig);
/*in Config file;
 * if TIM_Ratio     MilleSeconds
 * Ticks type is :1000 for Milliseconds
 *              :1 for microseconds
 * if TIM_Ratio     Seconds
 * Ticks type is :1000 for Seconds
 *              :1 for Milliseconds
 * */
void TIM_SetBusyWait(TIM_Registers_t* TIMx,uint16 Ticks,uint16 TicksTybe);
void TIM_Delay_us (TIM_Registers_t* TIMx ,uint16 us);
//void TIM_Delay_ms (uint8 TIMx,uint16 ms);

void TIM_SetIntervalSingle  (TIM_Registers_t* TIMx, uint16 Ticks, uint16 Copy_u32TicksTybe, void (*Copy_voidpFuncPtr)(void) );
void TIM_SetIntervalPeriodic(TIM_Registers_t* TIMx,uint16 Ticks ,uint16 TicksTybe , void (* Copy_vpFuncPtr) (void));
uint16 TIM_uGetRemainingTime(uint16 TIMx ,direction_m Direction) ;

void TIM1_UP_IRQHandler (void);
void TIM2_UP_IRQHandler (void);
void TIM3_UP_IRQHandler (void);
void TIM4_UP_IRQHandler (void);
uint16 TIM_GetCounterValue(TIM_Registers_t* TIMx);

/**********************PWM Functions****************************************/

void PWM_Init( TIM_Registers_t* TIMx,PWM_ConfigType* PWM_Confnig);
/*Function Description :
 * set auto reload value
 */
void TIM_SetPeriod (TIM_Registers_t* TIMx , uint32 Period);
/*
 * First,call PWM_DeInit ,Then, set auto reload value at TIM_SetPeriod
 */
void PWM_voidSetDutyCycle(TIM_Registers_t* TIMx ,channel_t Channel, float Duty);
void PWM_DeInit(TIM_Registers_t* TIMx ,channel_t Channel);
uint16 PWM_GetCounterValue(TIM_Registers_t* TIMx);
/**********************private functions prototype***************/
/*Function description:
This function stops the timer
*/
void TIM_Disable(TIM_Registers_t* TIMx);
/*Function description:
This function starts the timer
*/
void TIM_Enable(TIM_Registers_t* TIMx);
/*Function description:
This function set timer pre scaler
*/
void TIM_SetPrescaler(TIM_Registers_t* TIMx , uint16 Prescaler);
/*
Function description:
This function set timer auto-reload value
*/

/*Function description:
This function set timer clock source ( Internal | External mode1 | External mode 2)
*/
void TIM_voidSetClkDiv(TIM_Registers_t* TIMx,Clk_Div Copy_ClockDiv);
/*
Function description:
This function select counter mode ( UpCounting | DownCounting | centerAligned )
*/
void TIM_Direction(TIM_Registers_t* TIMx,direction_m Copy_CounterMode);


 /*Function Description
this function is used to enable or disable the update interrupt of a timer.
*/
void TIM_SetARR_Buffer(TIM_Registers_t* TIMx,ARR_Buffer_State AutoReloadBuffer);
void TIM_SetInterrupt(TIM_Registers_t* TIMx,INT_State IntState);
void PWM_SetAlignmentMode(TIM_Registers_t* TIMx, state mode);
/*********************PWM Functions ProtoTypes***************/
void PWM_SetChannel(TIM_Registers_t* TIMx,channel_t Channel,PWM_modee Copy_u32Mod);

#endif

