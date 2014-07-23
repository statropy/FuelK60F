/* ###################################################################
**     Filename    : main.c
**     Project     : FuelK60F
**     Processor   : MK61FN1M0VMJ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-07-22, 19:01, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "CsIO1.h"
#include "IO1.h"
#include "WAIT1.h"
#include "CI2C1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "MAX17043.h"
#include <stdio.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  	LDD_I2C_MASTER i2c0;
  	i2c0.flags.rxFlag = FALSE;
  	i2c0.flags.txFlag = FALSE;
    	
    printf("Running...\r\n");
    
  	i2c0.handle = CI2C1_Init(&i2c0.flags);
  	i2c0.send = CI2C1_MasterSendBlock;
  	i2c0.receive = CI2C1_MasterReceiveBlock;
  	
  	MAX17043_PowerUp(&i2c0);
  	WAIT1_Waitms(10); //should query BUSY status instead
  	MAX17043_Config(&i2c0);
  	WAIT1_Waitms(10); //should query BUSY status instead
  	
  	uint16_t version = 0;
  	MAX17043_ReadVersion(&i2c0, &version);
  	WAIT1_Waitms(10); //should query BUSY status instead
  	
  	uint8_t percent = 0;
  	
  	printf("MAX17034 Version %d\r\n\r\n", version);
  	
  	while(1)
  	{
  		if(MAX17043_ReadPercent(&i2c0, &percent))
  			printf("%d%%\r\n", percent);
  		WAIT1_Waitms(3000);
  	}

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
