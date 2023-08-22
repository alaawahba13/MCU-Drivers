/*
 * I2C.h
 *
 *  Created on: 18 Aug 2023
 *      Author: Alaa Wahba
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

//=======================
//       Includes
//=======================
#include "STM32_F103x6.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"

//================================================
//   User type definitions (enums)
//================================================

typedef enum{
	EV_STOP,
	ERR_AF,
	EV_ADDR_Matched,
	EV_DATA_REQ,
	EV_DATA_REC

}Slave_state;

typedef enum{
	NO_STOP,
	STOP

}Stop_Condition_t;

typedef enum{
	NO_REPEATED_START,
	REPEATED_START

}Repeated_Start_t;

typedef enum{
	I2C_ENABLE,
	I2C_DISABLE

}Functional_State_t;

typedef enum{
	RESET,
	SET
}FlagStatus;


typedef enum{
	BUS_BUSY,
	EV5,
	EV6,
	EV8_1,
	EV8,
	EV7,
	MASTER_BYTE_TX
}Status;

typedef enum{
	I2C_TX,
	I2C_RX
}I2C_Direction_t;

//================================================
//   User type definitions (structures)
//================================================

typedef struct{
	uint16 		Enable_Dual_Mode;		// 1- Enable  0- Disable  only in 7-bit addressing mode
	uint16 		slave_primary_address;
	uint16 		slave_secndary_address;
	uint32 		slave_address_mode;   // @ref  slave_address_mode

}slave_address_t;

typedef struct{
	uint32 		Clock_Speed;		// Specifies the clock speed @ref  Clock_Speed
	uint32 		Stretch_Mode;		//Clock stretching in Slave mode @ref StretchMode
	uint32 		I2C_Mode; 			// Specifies whether SMBus mode or I2C 		@ref I2C_Mode

	slave_address_t slave_address;
	uint32 		ACK_Enable; 		//  @ref  ACK_Enable

	void(*P_Slave_CallBack_Fun)(Slave_state state);  // The C function() that is called when IRQ is enabled (slave mode)


}I2C_pinConfig_t;



//===============================================
//      Macros Configuration References
//===============================================
/*
 * @ref  Clock_Speed
 */
#define I2C_CLK_SM_50K						(0x50000)
#define I2C_CLK_SM_100K						(100000)
#define I2C_CLK_FM_200K						(200000)   //Not supported
#define I2C_CLK_FM_400K						(400000)

/*
 * @ref  Stretch_Mode
 */
#define I2C_Stretch_EN						0
#define I2C_Stretch_DIS						(uint32)(1<<7)

/*
 * @ref  Stretch_Mode
 */
#define I2C_Mode_I2C						0
#define I2C_Mode_SMBUS						(uint32)(1<<1)

/*
 * @ref  slave_address_mode
 */
#define I2C_Slave_7Bit						0
#define I2C_Slave_10Bit						(uint32)(1<<15)  //Not supported

/*
 * @ref  ACK_Enable
 */
#define I2C_ACK_EN							(uint32)(1<<10)
#define I2C_SACK_DIS						0


/*
 * @ref I2C_IRQ_LineNumber
 */
#define I2C1_EV_LineNumber						31
#define I2C1_ER_LineNumber						32
#define I2C2_EV_LineNumber						33
#define I2C2_ER_LineNumber						34

/*
* ===============================================
*      APIs Supported by "MCAL I2C DRIVER"
* ===============================================
*/

void I2C_init(I2C_pinConfig_t *I2C_pinConfig , I2C_Registers_t *I2Cx);
void I2C_Deinit(I2C_Registers_t *I2Cx);

void I2C_GPIO_SetPins(I2C_Registers_t *I2Cx);

//Master polling mechanism
void I2C_Master_TX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data, uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start);
void I2C_Master_RX(I2C_Registers_t *I2Cx, uint16 slaveAddress, uint8 *data, uint32 dataLen, Stop_Condition_t stop, Repeated_Start_t start);

//Slave interrupt mechanism
void I2C_Slave_TX(I2C_Registers_t *I2Cx,uint8 data);
uint8 I2C_Slave_RX(I2C_Registers_t *I2Cx);

//Generic APIs
void I2C_GenerateStart(I2C_Registers_t *I2Cx,Repeated_Start_t start ,Functional_State_t State);
void I2C_GenerateStop(I2C_Registers_t *I2Cx ,Functional_State_t State);

FlagStatus I2C_GetFlagStatus(I2C_Registers_t *I2Cx , Status Flag);
void I2C_SendSlaveAddress(I2C_Registers_t *I2Cx , uint16 slaveAddress, I2C_Direction_t Direction);

void I2C_ACKConfig(I2C_Registers_t *I2Cx ,Functional_State_t State);
void Slave_States (I2C_Registers_t* I2Cx  ,Slave_state state);


#endif /* INC_I2C_H_ */
