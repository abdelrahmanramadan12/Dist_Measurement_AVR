/*
 *  @file Ultrasonic.c
 *
 *  Created: 12/6/2023 10:05:31 PM
 *  @Author: Abdelrahman Ramadan
 */ 


/* Include necessary header files */
#include "MemMap.h"           
#include "StdTypes.h"
#include "DIO_interface.h"
#include "Timers.h"
#include "Ultrasonic.h"

#define F_CPU 8000000         /* Define CPU frequency */
#include <util/delay.h>       /* Include delay library */


volatile u16 IC_VAL1, IC_VAL2;  /* Global variables to store input capture values */
volatile u8 IS_FirstVal_Captured = 0;  /* Flag to indicate if the first value is captured */

static void IC_voidCallBackFunc(void);  /* Function prototype declaration */


/*
 * Function: ultrasonic_Init
 * --------------------------
 * Initialize ultrasonic sensor module by setting up Timer1 input capture unit.
 * Sets the callback function and enables the input capture interrupt.
 */
void ultrasonic_Init()
{
    Timer1_ICU_SetCallBack(IC_voidCallBackFunc);  /* Set callback function for Timer1 input capture */
    Timer1_ICU_InterruptEnable();                 /* Enable Timer1 input capture interrupt */
}


/*
 * Function: ultrasonic_GetDistance
 * ---------------------------------
 * Measure the distance using an ultrasonic sensor.
 * 
 * copy_USnum: Represents the ultrasonic sensor being used.
 * copy_u8PtrDist: Pointer to a variable where the distance measurement will be stored.
 * 
 * Returns:
 *     - OK if the distance measurement is successful.
 *     - NOK if the distance measurement fails.
 */
Error_Type ultrasonic_GetDistance(ULTRASONIC_type copy_USnum, u8 *copy_u8PtrDist)
{
    u16 local_u16Difference, TimeOut = 0;  /* Local variables for time difference and timeout */
    Error_Type local_errType = NOK;        /* Initialize error type to NOK */
    TCNT1 = 0;                              /* Reset Timer1 counter */
    IS_FirstVal_Captured = 0;               /* Reset flag for first value capture */
    
    Timer1_InputCaptureEdge(RISING);        /* Set input capture edge to rising */
    DIO_Writepin(copy_USnum, HIGH);        /* Trigger ultrasonic sensor */
    _delay_us(TRIGG_DELAY);                 /* Delay for sensor triggering */
    DIO_Writepin(copy_USnum, LOW);          /* Turn off sensor */
    
    while (IS_FirstVal_Captured < 2 && (TimeOut < MAX_TIME))  /* Wait for both edges or timeout */
    {
        TimeOut++;                          /* Increment timeout counter */
        _delay_us(1);                       /* Delay 1 microsecond */
    }
    
    if (IS_FirstVal_Captured == 2)         /* If both edges are captured */
    {
        local_u16Difference = IC_VAL2 - IC_VAL1;  /* Calculate time difference */
        *copy_u8PtrDist = local_u16Difference / 58;  /* Convert time to distance */
        local_errType = OK;                 /* Set error type to OK */
        return local_errType;               /* Return OK */
    }
    
    return local_errType;                   /* Return NOK */
}


/*
 * Function: IC_voidCallBackFunc
 * -----------------------------
 * Callback function for Timer1 input capture interrupt.
 * Records the time of the input capture event and sets the flag to indicate the stage of the measurement process.
 */
static void IC_voidCallBackFunc(void)
{
    if (IS_FirstVal_Captured == 0)         /* If first value is not captured */
    {
        IC_VAL1 = ICR1;                     /* Record the time of the first capture */
        Timer1_InputCaptureEdge(FALLING);   /* Set input capture edge to falling */
        IS_FirstVal_Captured = 1;           /* Set flag to indicate first capture */
    }
    else if (IS_FirstVal_Captured == 1)     /* If first value is captured */
    {
        IC_VAL2 = ICR1;                     /* Record the time of the second capture */
        IS_FirstVal_Captured = 2;           /* Set flag to indicate second capture */
    }
}