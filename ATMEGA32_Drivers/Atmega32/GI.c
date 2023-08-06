/*
 * GI.c
 *
 *  Created on: 6 Aug 2023
 *      Author: Alaa Wahba
 */

#include "GI.h"
void GI_Enable(){
	SET(SREG,7);
}
void GI_Disable(){
	CLEAR(SREG,7);
}
