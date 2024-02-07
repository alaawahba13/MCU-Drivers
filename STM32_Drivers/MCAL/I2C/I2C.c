/*
 * I2C.c
 *
 *  Created on: 18 Aug 2023
 *      Author: Alaa Wahba
 */

//=======================
//       Includes
//=======================
#include "I2C.h"

/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
I2C_pinConfig_t Global_I2C_pinConfig[2] = { NULL, NULL };

#define I2C1_Index 			0
#define I2C2_Index 			1

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

void I2C_init(I2C_pinConfig_t *I2C_pinConfig, I2C_Registers_t *I2Cx) {

	uint16 tmpreg=0, freqrange = 0, result = 0;
	uint32 pclk1 = 8000000;
	/*            		Enable I2C clocks  					    */
	if (I2Cx == I2C1) {
		Global_I2C_pinConfig[I2C1_Index] = *I2C_pinConfig;
		RCC_CLK_EN(APB1_ID,I2C1_ID);
	} else if (I2Cx == I2C2) {
		Global_I2C_pinConfig[I2C2_Index] = *I2C_pinConfig;
		RCC_CLK_EN(APB1_ID,I2C2_ID);
	}

	if (I2C_pinConfig->I2C_Mode == I2C_Mode_I2C) {
		/*            		Init periphral clocks  					    */
		/*
		 * 1. Configure CR2 register
		 * The FREQ bits must be configured with the APB clock frequency value (I2C peripheral connected to APB)
		 */

		tmpreg = I2Cx->CR2;
		tmpreg &= ~(0x3F << 0);
		pclk1 = RCC_getPCKL1_Freq();
		freqrange = (uint16) (pclk1 / 1000000); // to configure xMegaHz in register CR2, write xHz
		tmpreg |= freqrange;
		I2Cx->CR2 = tmpreg;

		/*
		 * 2. Configure CCR register
		 * Sm mode or SMBus:
		 * Thigh = Tlow = CCR * TPCLK1
		 */

		//The CCR register must be configured only when the I2C is disabled
		I2Cx->CR1 &= ~(1 << 0);
		tmpreg = 0;

		if ((I2C_pinConfig->Clock_Speed == I2C_CLK_SM_100K)	|| (I2C_pinConfig->Clock_Speed == I2C_CLK_SM_50K)) {
			result = (uint16)(pclk1 / ( I2C_pinConfig->Clock_Speed << 1   )   );

			tmpreg |= result;

			I2Cx->CCR = tmpreg;

			// Maximum rise time in Fm/Sm mode (Master mode)
			//  the value of FREQ[5:0] bits + 1
			I2Cx->TRISE = freqrange + 1;

		} else {
			//FM Not supported
		}
		/*            		Configure CR1   					    */
		tmpreg = 0;
		tmpreg = I2Cx->CR1;
		tmpreg |= (uint16) (I2C_pinConfig->ACK_Enable
				| I2C_pinConfig->Stretch_Mode | I2C_pinConfig->I2C_Mode);
		I2Cx->CR1 = tmpreg;

		/*            		Configure ORA1 & ORA2   					    */
		tmpreg = 0;
		if (I2C_pinConfig->slave_address.Enable_Dual_Mode) {
			tmpreg |= (1 << 0); 	//Dual addressing mode enable
			tmpreg |=
					(I2C_pinConfig->slave_address.slave_secndary_address << 1);
			I2Cx->ORA2 = tmpreg;
		}
		tmpreg = 0;
		tmpreg |= (I2C_pinConfig->slave_address.slave_primary_address << 1);
		tmpreg |= I2C_pinConfig->slave_address.slave_address_mode; // 10 bit mode not supported
		I2Cx->ORA1 = tmpreg;
	} else {
		//Not supported SMUBUS mode
	}

	//Interrupt Mode (slave mode)
	if (I2C_pinConfig->P_Slave_CallBack_Fun != NULL) {
		I2Cx->CR2 |= (1 << 8) | (1 << 9) | (1 << 10);
		if (I2Cx == I2C1) {
			NVIC_Enable(NVIC_I2C1_EV);
			NVIC_Enable(NVIC_I2C1_ER);

		} else if (I2Cx == I2C2) {
			NVIC_Enable(NVIC_I2C1_EV);
			NVIC_Enable(NVIC_I2C1_ER);

		}
	}

	/*            		Periphral Enable 					    */

	I2Cx->CR1 |= (1 << 0);
}
void I2C_Deinit(I2C_Registers_t *I2Cx) {
	if (I2Cx == I2C1) {
		RCC_CLK_RST(APB1_ID,I2C1_ID);
		NVIC_Disable(NVIC_I2C1_ER);
		NVIC_Disable(NVIC_I2C1_EV);
	} else if (I2Cx == I2C2) {
		RCC_CLK_RST(APB1_ID,I2C2_ID);
		NVIC_Disable(NVIC_I2C2_ER);
		NVIC_Disable(NVIC_I2C2_EV);
	}
}

void I2C_GPIO_SetPins(I2C_Registers_t *I2Cx) {

	GPIO_PinConfig_t GPIO_pinConfig;

	if (I2Cx == I2C1) {
		//I2C1 SDA : PB7   SCL : PB6
		GPIO_pinConfig.MODE = MODE_OUTPUT_AF_OD;
		GPIO_pinConfig.Output_Speed = SPEED_10M;
		GPIO_pinConfig.Pin_Number = PIN_7;
		GPIO_init(GPIOB, &GPIO_pinConfig);

		GPIO_pinConfig.Pin_Number = PIN_6;
		GPIO_init(GPIOB, &GPIO_pinConfig);

	} else if (I2Cx == I2C2) {
		//I2C2 SDA : PB11   SCL : PB10
		GPIO_pinConfig.MODE = MODE_OUTPUT_AF_OD;
		GPIO_pinConfig.Output_Speed = SPEED_10M;
		GPIO_pinConfig.Pin_Number = PIN_11;
		GPIO_init(GPIOB, &GPIO_pinConfig);

		GPIO_pinConfig.Pin_Number = PIN_10;
		GPIO_init(GPIOB, &GPIO_pinConfig);

	}
}

void I2C_Master_TX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data,
		uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start) {
	// 1.Generate start condition.
	I2C_GenerateStart(I2Cx, start, I2C_ENABLE);
	// 2.Set when a Start condition generated.
	while (!I2C_GetFlagStatus(I2Cx, EV5))
		;
	//3.Send slave address
	I2C_SendSlaveAddress(I2Cx,slaveAddress, I2C_TX);
	//4.Set by hardware as soon as the received slave address matched with the OAR registers
	while (!I2C_GetFlagStatus(I2Cx, EV6));
	//5. check TRA , BUSY, TXE, MSL
	while (!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TX));
	//6. Send data
	for(uint8 i =0 ; i <dataLen ; i++){
		I2Cx->DR = data[i];
		while (!I2C_GetFlagStatus(I2Cx, EV8));

	}
	//7. Send Stop condition
	if(stop == STOP)
		I2C_GenerateStop(I2Cx, I2C_ENABLE);

}
void I2C_Master_RX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data,
		uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start) {
	uint8 index = (I2Cx == I2C1) ? I2C1_Index: I2C2_Index;

	// 1.Generate start condition.
	I2C_GenerateStart(I2Cx, start, I2C_ENABLE);
	// 2.Set when a Start condition generated.
	while (!I2C_GetFlagStatus(I2Cx, EV5))
		;
	//3.Send slave address
	I2C_SendSlaveAddress(I2Cx,slaveAddress, I2C_RX);
	//4.Set by hardware as soon as the received slave address matched with the OAR registers
	while (!I2C_GetFlagStatus(I2Cx, EV6));

	//5.  Enable Ack
	I2C_ACKConfig(I2Cx, I2C_ENABLE);

	//6. Recieve data
	if(dataLen){
		for(uint8  i = dataLen; i >1 ; i--){
			// Set when data register is not empty in receiver mode
			while (!I2C_GetFlagStatus(I2Cx, EV7));

			*data = I2Cx->DR ;
			data++;
		}
		// send NACK
		I2C_ACKConfig(I2Cx, I2C_DISABLE);
	}
	//7. Send Stop condition
	if(stop == STOP)
		I2C_GenerateStop(I2Cx, I2C_ENABLE);

	// reset ACK to default
	if(Global_I2C_pinConfig[index].ACK_Enable == I2C_ACK_EN)
		I2C_ACKConfig(I2Cx, I2C_ENABLE);


}

void I2C_GenerateStart(I2C_Registers_t *I2Cx, Repeated_Start_t start,
		Functional_State_t State) {

	// Setting the START bit causes the interface to generate a Start condition and to switch to
	//Master mode (MSL bit set) when the BUSY bit is cleared

	if (start != REPEATED_START) {
		while (I2C_GetFlagStatus(I2Cx, BUS_BUSY))
			;

	}
	if (State != I2C_DISABLE) {
		/*
		 * In Master Mode:
		 0: No Start generation
		 1: Repeated start generation
		 */
		I2Cx->CR1 |= (1 << 8);
	} else {
		I2Cx->CR1 &= ~(1 << 8);

	}

}
void I2C_GenerateStop(I2C_Registers_t *I2Cx ,Functional_State_t State){

	if (State != I2C_DISABLE) {
			/*
			 * In Master Mode:
			0: No Stop generation.
			1: Stop generation after the current byte transfer or after the current Start condition is sent.
			 */
			I2Cx->CR1 |= (1 << 9);
		} else {
			I2Cx->CR1 &= ~(1 << 9);

		}

}

void I2C_ACKConfig(I2C_Registers_t *I2Cx ,Functional_State_t State){
	if (State != I2C_DISABLE) {
				// ACK: Acknowledge enable
				I2Cx->CR1 |= (1 << 10);
			} else {
				I2Cx->CR1 &= ~(1 << 10);

			}
}

FlagStatus I2C_GetFlagStatus(I2C_Registers_t *I2Cx, Status Flag) {
	FlagStatus bitStatus = RESET;
	uint32 dummyRead = 0;

	switch (Flag) {
	case BUS_BUSY:
		bitStatus = (I2Cx->SR2 & (1 << 1)) ? SET : RESET;
		break;
	case EV5:
		bitStatus = (I2Cx->SR1 & (1 << 0)) ? SET : RESET;
		break;
	case EV6:
		bitStatus = (I2Cx->SR1 & (1 << 1)) ? SET : RESET;
		break;
	case EV8:
	case EV8_1:  //Data register empty (transmitters)
		bitStatus = (I2Cx->SR1 & (1 << 7)) ? SET : RESET;
		break;
	case MASTER_BYTE_TX:
		bitStatus = ((I2Cx->SR1 & (1 << 7)) && (I2Cx->SR2 & (1 << 1)) &&(I2Cx->SR2 & (1 << 0)) &&(I2Cx->SR2 & (1 << 2))) ? SET : RESET;
		break;
	case EV7:
			bitStatus = (I2Cx->SR1 & (1 << 6)) ? SET : RESET;
			break;
	}


	return bitStatus;
}

void I2C_SendSlaveAddress(I2C_Registers_t *I2Cx , uint16 slaveAddress, I2C_Direction_t Direction){
	// 10 bit mode is not supported
		uint8 index = (I2Cx == I2C1) ? I2C1_Index: I2C2_Index;
if(Global_I2C_pinConfig[index].slave_address.slave_address_mode == I2C_Slave_7Bit){
	  slaveAddress = (slaveAddress <<1);
	  if(Direction == I2C_TX){
		  // To enter Transmitter mode, a master sends the slave address with LSB reset.
		  slaveAddress &= ~(1<<0);
	  }else{
		  //  To enter Receiver mode, a master sends the slave address with LSB set.
		  slaveAddress |= (1<<0);
	  }

	I2Cx->DR = slaveAddress;
}else{
	// not supported
}


}

void I2C_Slave_TX(I2C_Registers_t *I2Cx,uint8 data){
		I2Cx->DR = data;
}
uint8 I2C_Slave_RX(I2C_Registers_t *I2Cx){
	return (uint8)I2Cx->DR;
}

void I2C1_EV_IRQHandler(void){
	volatile uint32 dummy_read = 0 ;
	I2C_Registers_t* I2Cx = I2C1 ;
		//Interrupt handling for both master and slave mode of a device
		uint32 temp1, temp2, temp3;

		temp1   = I2Cx->CR2 & (  1<<9) ;
		temp2   = I2Cx->CR2 & ( 1<<10) ;
		temp3  = I2Cx->SR1 & ( 1<<8);


		// Handle For interrupt generated by STOPF event
			// Note : Stop detection flag is applicable only slave mode
			if(temp1 && temp3)
			{
				//STOF flag is set
				//Clear the STOPF ( i.e 1) read SR1 2) Write to CR1 )
				I2Cx->CR1 |= 0x0000;
				Slave_States(I2Cx,EV_STOP);


			}
			//----------------------------------------------------------
			temp3  = I2Cx->SR1 & (1<<1);
			// Handle For interrupt generated by ADDR event
			//Note : When master mode : Address is sent
			//		 When Slave mode   : Address matched with own address
			if(temp1 && temp3)
			{
				// interrupt is generated because of ADDR event
				//check for device mode
				if(I2Cx->SR2 & ( 1<<0))
				{
					//master

				}else
				{
					//slave mode
					//clear the ADDR flag ( read SR1 , read SR2)
					dummy_read = I2Cx->SR1;
					dummy_read = I2Cx->SR2;
					Slave_States(I2Cx,EV_ADDR_Matched);

				}
			}
			//----------------------------------------------------------

			temp3  = I2Cx->SR1 & ( 1<<7);
			// Handle For interrupt generated by TXE event
			if(temp1 && temp2 && temp3)
			{
				//Check for device mode
				if(I2Cx->SR2 & (1<<0))
				{

				}else
				{
					//slave
					Slave_States(I2Cx,EV_DATA_REQ);
				}
			}

			//----------------------------------------------------------

			temp3  = I2Cx->SR1 & ( 1<<6);
			// Handle For interrupt generated by 	SB=1, cleared by reading SR1 register followed by writing DR register with Address.
			if(temp1 && temp2 && temp3)
			{
				//check device mode .
				if(I2Cx->SR2 & ( 1<<0))
				{
					//The device is master

				}else
				{
					//slave
					Slave_States(I2Cx,EV_DATA_REC);

				}
			}
}


void Slave_States (I2C_Registers_t* I2Cx  ,Slave_state state)
{
	uint8_t index =    I2Cx == I2C1 ? I2C1_Index: I2C2_Index ;

	switch (state)
	{

	case ERR_AF:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( 1<<2))
		{
			//Slave Shouldn't Send anything else

		}

		break ;
	}

	case EV_STOP:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( 1<<2))
		{
			//Notify APP that the Stop Condition is sent by the master
			Global_I2C_pinConfig[index].P_Slave_CallBack_Fun (EV_STOP) ;
		}

		break ;
	}

	case EV_ADDR_Matched:
	{
		//Notify APP that the Stop Condition is sent by the master
		Global_I2C_pinConfig[index].P_Slave_CallBack_Fun (EV_ADDR_Matched) ;


		break ;
	}

	case EV_DATA_REQ:
	{
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & ( 1<<2))
		{
			//the APP layer should send the data (MCAL_I2C_SlaveSendData ) in this state
			Global_I2C_pinConfig[index].P_Slave_CallBack_Fun (EV_DATA_REQ) ;

		}

		break ;
	}
	case EV_DATA_REC:
	{
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & ( 1<<2)))
		{
			//the APP layer should read the data (MCAL_I2C_SlaveReceiveData ) in this state
			Global_I2C_pinConfig[index].P_Slave_CallBack_Fun (EV_DATA_REC) ;

		}

		break ;
	}
	}

}


