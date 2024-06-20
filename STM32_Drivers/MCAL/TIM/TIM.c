/*
 * TIM.c
 *
 *  Created on: Apr 14, 2024
 *      Author: Alaa
 */

//=======================
//       Includes
//=======================
#include "TIM.h"

 /**********************************************************************************/
/* Author   : Hind Fouad                                                          */
/* date     :19 Mar 2022                                                          */
/* Version  : V01                                                                 */
/**********************************************************************************/


static volatile float microSecToTicksRatio = 0;
/* Variable to define interval mode of Timer*/
static volatile uint8 TIM1_u8IntervalMode;
static volatile uint8 TIM2_u8IntervalMode;
static volatile uint8 TIM3_u8IntervalMode;
static volatile uint8 TIM4_u8IntervalMode;
uint32 TIM_Clk_Freq = 72000000;

/* Local macros to set and get Interval mode for timer interrupt*/
#define TIM1_SET_INTERVAL_MODE(MODE)                          TIM1_u8IntervalMode = MODE
#define TIM1_GET_INTERVAL_MODE()                               (TIM1_u8IntervalMode & 1)

#define TIM2_SET_INTERVAL_MODE(MODE)                          TIM2_u8IntervalMode = MODE
#define TIM2_GET_INTERVAL_MODE()                               (TIM2_u8IntervalMode & 1)

#define TIM3_SET_INTERVAL_MODE(MODE)                          TIM3_u8IntervalMode = MODE
#define TIM3_GET_INTERVAL_MODE()                               (TIM3_u8IntervalMode & 1)

#define TIM4_SET_INTERVAL_MODE(MODE)                          TIM4_u8IntervalMode = MODE
#define TIM4_GET_INTERVAL_MODE()                               (TIM4_u8IntervalMode & 1)

static void (*TIM1_CallBack)(void);
static void (*TIM2_CallBack)(void);
static void (*TIM3_CallBack)(void);
static void (*TIM4_CallBack)(void);



/************************************************************************************************************* */
void TIM_Init(TIM_Registers_t *TIMx, TIM_ConfigType *TimConfig) {
    if(TIMx == TIM1){
    	RCC_CLK_EN(APB2_ID, TIM1_ID);
    }else if(TIMx == TIM2){
    	RCC_CLK_EN(APB1_ID, TIM2_ID);

    }else if(TIMx == TIM3){
    	RCC_CLK_EN(APB1_ID, TIM3_ID);

    }else if(TIMx == TIM4){
    	RCC_CLK_EN(APB1_ID, TIM4_ID);

    }
    TIM_SetPeriod(TIMx,TimConfig-> AutoReloadValue);
#if TIM_Ratio == MilleSeconds
//        uint16 Prescaler =(uint16)(TIM_Clk_Freq /1000000)-1;
//        TIM_SetPrescaler(TIMx, Prescaler);

#elif TIM_Ratio == Seconds
            uint16 Prescaler =(uint16)(TIM_Clk_Freq /1000)-1;
            TIM_SetPrescaler(TIMx,Prescaler) ;
#endif
    TIM_SetARR_Buffer(TIMx,TimConfig->AutoReloadBuffer);
    TIM_Direction(TIMx, TimConfig->Tim_Direction);
    PWM_SetAlignmentMode(TIMx,TimConfig->AlignedMode);
    TIM_voidSetClkDiv(TIMx,TimConfig->ClockFactor );
    TIM_SetInterrupt(TIMx,TimConfig->UDI_State);
    TIM_SetPrescaler(TIMx, TimConfig->Prescalar);

    TIM_Enable(TIMx);

}
void TIM_Enable(TIM_Registers_t* TIMx){
    SET(TIMx->CR1,TIM_CR1_CEN );
}
void TIM_Direction(TIM_Registers_t* TIMx,direction_m Copy_CounterMode){
    switch (Copy_CounterMode){
  case Up_Counting:
  /*set direction of counter: up */
      CLEAR(TIMx -> CR1 ,TIM_CR1_DIR );

      break;
  case Down_Counting :
    /*set direction of counter: up */
      SET (TIMx -> CR1 ,TIM_CR1_DIR);

      break;
  case Center_Aligned:
      CLEAR ( TIMx -> CR1 , TIM_CR1_DIR);
      SET (TIMx -> CR1 ,6);
      CLEAR (TIMx -> CR1 ,5);
     break;
      default:
      break;
}
}
void TIM_SetPrescaler(TIM_Registers_t* TIMx , uint16 Prescaler){
      /*Set the prescalar value in PSC register*/
    TIMx ->PSC =  Prescaler;

}
void TIM_SetPeriod (TIM_Registers_t* TIMx , uint32 Period){
    /* Set the autoreload value value in ARP register*/
    TIMx->ARR = Period;
}
void TIM_voidSetClkDiv(TIM_Registers_t* TIMx,Clk_Div Copy_ClockDiv)
{
    switch(Copy_ClockDiv)
    {
    case Div_1:
        CLEAR(TIMx->CR1,8);
        CLEAR(TIMx->CR1,9);
        break;

    case Div_2:
        SET(TIMx->CR1,8);
        CLEAR(TIMx->CR1,9);
        break;

    case Div_3:
        CLEAR(TIMx->CR1,8);
        SET(TIMx->CR1,9);
        break;

    default:
        break;
    }
}
void TIM_SetARR_Buffer(TIM_Registers_t* TIMx,ARR_Buffer_State AutoReloadBuffer)
{
    switch(AutoReloadBuffer)
    {
    case Disable_ARR_Buffer:
        CLEAR(TIMx->CR1,TIM_CR1_ARPE);
        break;
    case Enable_ARR_Buffer:
        SET(TIMx->CR1,TIM_CR1_ARPE);
        break;

    }
}
void TIM_SetInterrupt(TIM_Registers_t* TIMx,INT_State IntState)
{
    switch(IntState)
    {
        case Disable_Interrupt:
            CLEAR(TIMx->DIER,TIM_DIER_UIE);
            break;
        case Enable_Interrupts:
            SET(TIMx->DIER,TIM_DIER_UIE);
            break;
    }
}
void TIM_Disable(TIM_Registers_t* TIMx){

    CLEAR(TIMx ->CR1 ,TIM_CR1_CEN);
}
void TIM_Delay_us (TIM_Registers_t* TIMx ,uint16 us)
{

  TIMx->CNT = 0;
  while (TIMx->CNT < us);
}
//
//void TIM_Delay_ms (uint8 TIMx,uint16 ms)
//{
//  for (uint16 i=0; i<ms; i++)
//  {
//      TIM_Delay_us (TIMx,1000); // delay of 1 ms
//  }
//}
uint16 TIM_GetCounterValue(TIM_Registers_t* TIMx) {
    // Assuming the counter register is a 16-bit register
    return (uint16)TIMx->CNT;
}

void TIM_SetBusyWait(TIM_Registers_t* TIMx, uint16 Ticks, uint16 TicksTybe) {
    /*Assign ticks to load register*/

    TIMx->ARR = (uint16) (Ticks * TicksTybe);
    CLEAR(TIMx->DIER, 0);
    /*Start timer*/
    SET(TIMx->CR1, 0);
    /*Wait until CNT is equal to comapre value */
    while (TIMx->CNT != TIMx->ARR)
        ;
    /*Stop timer*/
    TIMx->CNT = 0;
    CLEAR(TIMx->CR1, 0);
    /*Clear Timer registers*/
    TIMx->ARR = 0;

}
void TIM_SetIntervalSingle(TIM_Registers_t* TIMx, uint16 Ticks, uint16 TicksTybe,
        void (*Copy_voidpFuncPtr)(void)) {
    /*Stop timer*/
    TIM_Disable(TIMx);
    /*Clear Timer registers*/
    TIMx->ARR = 0;

    TIMx->ARR = (uint16) (Ticks * TicksTybe);
    /* Assign callBack function */
    if (TIMx == TIM1) {

        TIM1_CallBack = Copy_voidpFuncPtr;
        TIM1_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM2) {

        TIM2_CallBack = Copy_voidpFuncPtr;
        TIM2_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM3) {

        TIM3_CallBack = Copy_voidpFuncPtr;
        TIM3_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    } else if (TIMx == TIM4) {

        TIM4_CallBack = Copy_voidpFuncPtr;
        TIM4_SET_INTERVAL_MODE(TIM_SINGLE_INTERVAL_MODE);

    }

    /*Enable Timer interrupt*/
    SET(TIMx->DIER, TIM_DIER_UIE);

    /*Start timer*/
    TIM_Enable(TIMx);
}
void TIM_SetIntervalPeriodic(TIM_Registers_t* TIMx, uint16 Ticks, uint16 TicksTybe,
        void (*Copy_vpFuncPtr)(void)) {
    /*Assign ticks to load register*/
    TIMx->ARR = (uint16) (Ticks * TicksTybe);
    /*Assign the function to the callback function */
    if (TIMx == TIM1) {
        TIM1_CallBack = Copy_vpFuncPtr;
        TIM1_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);/* Set Mode to periodic */
        CLEAR(TIM1->SR, TIM_SR_UIF);
    } else if (TIMx == TIM2) {
        TIM2_CallBack = Copy_vpFuncPtr;
        TIM2_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);/* Set Mode to periodic */
        CLEAR(TIM2->SR, TIM_SR_UIF);
    } else if (TIMx == TIM3) {
        TIM3_CallBack = Copy_vpFuncPtr;
        TIM3_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
        CLEAR(TIM3->SR, TIM_SR_UIF);
    } else if (TIMx == TIM4) {
        TIM4_CallBack = Copy_vpFuncPtr;
        TIM4_SET_INTERVAL_MODE(TIM_PERIODIC_INTERVAL_MODE);
        CLEAR(TIM4->SR, TIM_SR_UIF);
    }

    /*Enable Timer interrupt*/
    SET(TIMx->DIER, TIM_DIER_UIE);
    /*Start the counter*/
    SET(TIMx->CR1, TIM_CR1_CEN);
}
uint16 TIM_GetRemainingTime(TIM_Registers_t* TIMx,direction_m Direction) {
    static volatile uint16 RemainingTime = 0;

    if (Direction == Up_Counting) {
        RemainingTime = (uint16) ((TIMx->ARR) - (TIMx->CNT));
    } else if (Direction == Down_Counting) {
        RemainingTime = (uint16) (TIMx->CNT);
    }

    return (RemainingTime);
}


void TIM1_UP_IRQHandler (void)
{
    if(TIM1_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLEAR(TIM1 -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLEAR(TIM1 ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM1->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM1_CallBack();

    /*Clear interrupt flag*/
    CLEAR(TIM1->SR,TIM_SR_UIF);
}

void TIM2_UP_IRQHandler (void)
{
    if(TIM2_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLEAR(TIM2 -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLEAR(TIM2 ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM2->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM2_CallBack();

    /*Clear interrupt flag*/
    CLEAR(TIM2->SR,TIM_SR_UIF);
}
void TIM3_UP_IRQHandler (void)
{
    if(TIM3_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLEAR(TIM3 -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLEAR(TIM3 ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM3->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM3_CallBack();

    /*Clear interrupt flag*/
    CLEAR(TIM3->SR,TIM_SR_UIF);
}
void TIM4_UP_IRQHandler (void)
{
    if(TIM4_GET_INTERVAL_MODE() == TIM_SINGLE_INTERVAL_MODE)
    {
        /*Disable Timer interrupt*/
        CLEAR(TIM4 -> DIER ,TIM_DIER_UIE);
        /*Stop the counter*/
        CLEAR(TIM4 ->CR1 ,TIM_CR1_CEN);
        /*Clear timer registers*/
        TIM4->ARR = 0;
    }
    else
    {
        /*do nothing*/
    }

    /*Execute callback function*/
    TIM4_CallBack();

    /*Clear interrupt flag*/
    CLEAR(TIM4->SR,TIM_SR_UIF);
}



/**********************PWM Functions****************************************/
void PWM_Init( TIM_Registers_t* TIMx,PWM_ConfigType* PWM_Config){
    /* turn on channel*/
    PWM_SetChannel( TIMx,PWM_Config->Channel,PWM_Config->Mode);
    /*calculate prescaler*/
//    uint32 Counter =((PWM_Config->Freq)*(PWM_Config->AutoReloadValue));
//    uint16 Prescaler = TIM_Clk_Freq/Counter;
//    TIM_SetPrescaler(TIMx,Prescaler);
    /*set ARR value*/
    TIM_SetPeriod(TIMx,PWM_Config->AutoReloadValue);

    /*turn on timer*/
    SET(TIMx->CR1,TIM_CR1_ARPE);
    SET(TIMx->CR1,TIM_CR1_CEN);
    SET(TIMx->EGR,TIM_EGR_UG);
}
void PWM_SetAlignmentMode(TIM_Registers_t* TIMx, state mode){
    if(mode == EdgeAligned_Mode ) {
        CLEAR(TIMx->CR1,5);
        CLEAR(TIMx->CR1,6);
    }
    else if(mode == CenterAligned_Mode) {
        SET(TIMx->CR1,5);
        CLEAR(TIMx->CR1,6);

}
}
void PWM_SetChannel(TIM_Registers_t* TIMx,channel_t Channel,PWM_modee mode){

    switch(Channel){
    case TIM_Channel1:
        TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<4) ;  //clearing the previous  PWM mode
        TIMx->CCMR1 = TIMx->CCMR1 | (mode <<4);  //setting the PWM mode
        SET(TIMx->CCMR1,TIM_CCMR1_OC1PE);   //preload enable
        SET(TIMx->CCER , TIM_CCER_CC1E );      //capture compare output enable for channel 1
        SET(TIMx->CCER , TIM_CCER_CC1P);
        SET(TIMx->BDTR ,15);
        break;
    case TIM_Channel2:
        TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<12) ;
        TIMx->CCMR1 = TIMx->CCMR1 | (mode <<12);
        SET(TIMx->CCMR1,TIM_CCMR1_OC2PE);
        SET(TIMx->CCER , TIM_CCER_CC2P);
        break;
    case TIM_Channel3:
        TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<4) ;
        TIMx->CCMR2 = TIMx->CCMR2 | (mode <<4);
        SET(TIMx->CCMR2,TIM_CCMR2_OC3PE);
        SET(TIMx->CCER , TIM_CCER_CC3E);
        SET(TIMx->CCER ,  TIM_CCER_CC3P);
        SET(TIMx->BDTR ,15);
        break;
    case TIM_Channel4:
        TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<12) ;
        TIMx->CCMR2 = TIMx->CCMR2 | (mode <<12);
        SET(TIMx->CCMR2,TIM_CCMR2_OC4PE);
        SET(TIMx->CCER , TIM_CCER_CC4E);
        SET(TIMx->CCER , TIM_CCER_CC4P );
        break;

    }

}

void PWM_voidSetDutyCycle(TIM_Registers_t* TIMx ,channel_t Channel, float Duty)
{
    uint16 Pulse = Duty;
    switch(Channel){
    case TIM_Channel1:
        TIMx->CCR[0]=Pulse;
        break;
    case TIM_Channel2:
        TIMx->CCR[1]=Pulse;
        break;
    case TIM_Channel3:
        TIMx->CCR[2]=Pulse;
        break;
    case TIM_Channel4:
        TIMx->CCR[3]=Pulse;
        break;

        }
}


void PWM_DeInit(TIM_Registers_t* TIMx ,channel_t Channel){
        switch(Channel){
        case TIM_Channel1:
            TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<4) ;
            CLEAR(TIMx->CCMR1,TIM_CCMR1_OC1PE);
            CLEAR(TIMx->CCER , TIM_CCER_CC1E);
            break;
        case TIM_Channel2:
            TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<12) ;
            CLEAR(TIMx->CCMR1,TIM_CCMR1_OC2PE);
            CLEAR(TIMx->CCER , TIM_CCER_CC2E);
            break;
        case TIM_Channel3:
            TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<4) ;
            CLEAR(TIMx->CCMR2,TIM_CCMR2_OC3PE);
            CLEAR(TIMx->CCER , TIM_CCER_CC3E);
            break;
        case TIM_Channel4:
            TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<12) ;
            CLEAR(TIMx->CCMR2,TIM_CCMR2_OC4PE);
            CLEAR(TIMx->CCER , TIM_CCER_CC4E);
            break;

        }
}
uint16 PWM_GetCounterValue(TIM_Registers_t* TIMx){
    uint16 CounterValue= TIMx->CNT;
    return CounterValue;
}


///*
// * =======================================================================================
// * 							Generic Variables
// * =======================================================================================
// */
//static TIM_pinConfig_t Global_TIM_pinConfig[4]={NULL};
//
//#define TIM1_Index 			0
//#define TIM2_Index 			1
//#define TIM3_Index 			2
//#define TIM4_Index 			3
//
//void TIM_init(TIM_Registers_t* *TIMx, TIM_pinConfig_t *pinConfig) {
//	if (TIMx == TIM1) {
//		RCC_CLK_EN(APB2_ID, TIM1_ID);
//		Global_TIM_pinConfig[TIM1_Index] = *pinConfig;
//	}
//	if (TIMx == TIM2) {
//		RCC_CLK_EN(APB1_ID, TIM2_ID);
//
//		Global_TIM_pinConfig[TIM2_Index] = *pinConfig;
//	} else if (TIMx == TIM3) {
//		RCC_CLK_EN(APB1_ID, TIM3_ID);
//		Global_TIM_pinConfig[TIM3_Index] = *pinConfig;
//	}else if (TIMx == TIM4) {
//		RCC_CLK_EN(APB1_ID, TIM4_ID);
//		Global_TIM_pinConfig[TIM4_Index] = *pinConfig;
//	}
//	//1. set autoreload value
//	TIMx->ARR = pinConfig->AutoReloadValue;
//	TIMx->CR1 |= (pinConfig->AutoReloadBuffer << 7);
//	//2. prescalar
//	uint32 CLK = RCC_getPCKL2_Freq();
//	  uint16 prescalar;
//#if TIM_Ratio == MilleSeconds
//         prescalar =(uint16)(CLK /1000000)-1;
//#elif TIM_Ratio == Seconds
//             prescalar =(uint16)(CLK/1000)-1;
//#endif
//	TIMx->PSC = prescalar;
//	//3. set Mode
//	switch (pinConfig->Tim_Direction) {
//	case Up_Counting:
//		CLEAR(TIMx->CR1, 4); //DIR bit
//		break;
//	case Down_Counting:
//		SET(TIMx->CR1, 4); //DIR bit
//		break;
//	case Center_Aligned:
//		SET(TIMx->CR1, 5); //CMS bits
//		SET(TIMx->CR1, 6);
//		break;
//
//	}
//	//5. enable interrupt
//	if (pinConfig->IRQ_EN) {
//		SET(TIMx->DIER, 0);
//	}
//	//6. enable timer
//	SET(TIMx->CR1, 0);
//
//}
//
//void TIM_BusyWait(TIM_Registers_t* *TIMx, uint16 ticks) {
//	TIMx->CNT = 0;
//	TIMx->ARR = ticks;
//	CLEAR(TIMx->DIER, 0);
//	SET(TIMx->CR1, 0); // enable
//	//wait for counter to reach ARR
//	while (TIMx->CNT != TIMx->ARR)
//		;
//	// Stop timer
//	TIMx->CNT = 0;
//	CLEAR(TIMx->CR1, 0); // enable
//	TIMx->ARR = 0;
//
//}
//
//void TIM_SetInterval(TIM_Registers_t* *TIMx, uint32 time, void (*CB_ptr)(void)) {
////	// Configure TIMx to generate an interrupt after 'time' milliseconds
////	uint32 timerClockFreq = 72000000; // Assuming timer clock frequency is 72 MHz
////	uint32 ticks = (time * timerClockFreq) / 1000;
////
////	TIMx->PSC = 72 - 1; // Prescaler value for 1MHz timer clock
////	TIMx->ARR = ticks;
////	TIMx->DIER |= TIM_DIER_UIE; // Enable update interrupt
////	NVIC_EnableIRQ(TIM3_IRQn); // Enable TIM3 IRQ in NVIC
////
////	// Set callback function
////	// You may need to store this callback function pointer globally
//}
//
//uint16 TIM_getRemainingTime(TIM_Registers_t* *TIMx, direction_t Direction) {
//	static volatile uint16 RemainingTime = 0;
//
//	if (Direction == Up_Counting) {
//		RemainingTime = (uint16) ((TIMx->ARR) - (TIMx->CNT));
//	} else if (Direction == Down_Counting) {
//		RemainingTime = (uint16) (TIMx->CNT);
//	}
//
//	return (RemainingTime);
//}
//
////Interrupt Handlers
//void TIM1_UP_IRQHandler(void) {
//#if(TIM1_MODE == SINGLE)
//	// Stop timer
//	TIM1->CNT = 0;
//	CLEAR(TIM1->CR1, 0); // enable
//	TIM1->ARR = 0;
//	// disable Interrupt
//	CLEAR(TIM1->DIER, 0);
//#endif
//	Global_TIM_pinConfig[TIM1_Index].CB_Fun();
//	//UIF: Update interrupt flag
//	CLEAR(TIM1->SR, 0);
//
//}
//void TIM2_UP_IRQHandler(void) {
//#if(TIM2_MODE == SINGLE)
//	// Stop timer
//	TIM2->CNT = 0;
//	CLEAR(TIM2->CR1, 0); // enable
//	TIM2->ARR = 0;
//	// disable Interrupt
//	CLEAR(TIM2->DIER, 0);
//#endif
//	Global_TIM_pinConfig[TIM2_Index].CB_Fun();
//	//UIF: Update interrupt flag
//	CLEAR(TIM2->SR, 0);
//
//}
//void TIM3_UP_IRQHandler(void) {
//#if(TIM3_MODE == SINGLE)
//	// Stop timer
//	TIM3->CNT = 0;
//	CLEAR(TIM3->CR1, 0); // enable
//	TIM3->ARR = 0;
//	// disable Interrupt
//	CLEAR(TIM3->DIER, 0);
//#endif
//	Global_TIM_pinConfig[TIM1_Index].CB_Fun();
//	//UIF: Update interrupt flag
//	CLEAR(TIM3->SR, 0);
//
//}
//void TIM4_UP_IRQHandler(void) {
//#if(TIM4_MODE == SINGLE)
//	// Stop timer
//	TIM4->CNT = 0;
//	CLEAR(TIM4->CR1, 0); // enable
//	TIM4->ARR = 0;
//	// disable Interrupt
//	CLEAR(TIM4->DIER, 0);
//#endif
//	Global_TIM_pinConfig[TIM1_Index].CB_Fun();
//	//UIF: Update interrupt flag
//	CLEAR(TIM4->SR, 0);
//
//}
//// PWM functions
//
//void PWM_init(TIM_Registers_t* *TIMx, PWM_pinConfig *pinConfig) {
//	 /* turn on channel*/
//	  switch(pinConfig->Channel){
//	    case TIM_CH1:
//	        TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<4) ;  //clearing the previous  PWM pinConfig->Mode
//	        TIMx->CCMR1 = TIMx->CCMR1 | (pinConfig->Mode <<4);  //setting the PWM mode
//	        SET(TIMx->CCMR1,3);   //preload enable
//	        SET(TIMx->CCER , 0 );      //capture compare output enable for channel 1
//	        SET(TIMx->CCER , 1);
//	        break;
//	    case TIM_CH2:
//	        TIMx->CCMR1 = TIMx->CCMR1 & ~(0b1111<<12) ;
//	        TIMx->CCMR1 = TIMx->CCMR1 | (pinConfig->Mode <<12);
//	        SET(TIMx->CCMR1,11);
//	        SET(TIMx->CCER , 5);
//	        break;
//	    case TIM_CH3:
//	        TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<4) ;
//	        TIMx->CCMR2 = TIMx->CCMR2 | (pinConfig->Mode <<4);
//	        SET(TIMx->CCMR2,7);
//	        SET(TIMx->CCER , 8);
//	        SET(TIMx->CCER ,  9);
//	        break;
//	    case TIM_CH4:
//	        TIMx->CCMR2 = TIMx->CCMR2 & ~(0b1111<<12) ;
//	        TIMx->CCMR2 = TIMx->CCMR2 | (pinConfig->Mode <<12);
//	        SET(TIMx->CCMR2,11);
//	        SET(TIMx->CCER , 12);
//	        SET(TIMx->CCER , 13 );
//	        break;
//
//	    }
//	/*calculate prescaler*/
//	    uint32 Counter =((pinConfig->Freq)*(pinConfig->AutoReloadValue));
//	    uint32 CLK = RCC_getPCKL2_Freq();
//	    uint16 prescalar = CLK/Counter;
//
//#if TIM_Ratio == MilleSeconds
//         prescalar =(uint16)(CLK /1000000)-1;
//#elif TIM_Ratio == Seconds
//             prescalar =(uint16)(CLK/1000)-1;
//#endif
//	TIMx->PSC = prescalar;
//	/*set ARR value*/
//	TIMx->ARR = pinConfig->AutoReloadValue;
//
//	    /*turn on timer*/
//	    SET(TIMx->CR1,7);
//	    SET(TIMx->CR1,0);
//	    SET(TIMx->EGR,0);
//
//
//}
//
//
//void PWM_voidSetDutyCycle(TIM_Registers_t* *TIMx, Channel_t Channel, uint8 Duty) {
//	// Set PWM duty cycle
//	switch (Channel) {
//	case TIM_CH1:
//		TIMx->CCR[0] = (Duty * TIMx->ARR) / 100.0;
//		break;
//	case TIM_CH2:
//		TIMx->CCR[1] = (Duty * TIMx->ARR) / 100.0;
//		break;
//	case TIM_CH3:
//		TIMx->CCR[2] = (Duty * TIMx->ARR) / 100.0;
//		break;
//	case TIM_CH4:
//		TIMx->CCR[3] = (Duty * TIMx->ARR) / 100.0;
//		break;
//	default:
//		// Handle error
//		break;
//	}
//}
//
//
//
//uint16 PWM_GetCounterValue(TIM_Registers_t* *TIMx) {
//	return TIMx->CNT;
//}
//
