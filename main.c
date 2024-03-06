#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "LCD.h"
#include "Timers.h"
#include "Ultrasonic.h"

#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h>

u32 dist;

int main(void)
{
	sei();
	DIO_init();
	
	LCD_Init();
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	
	/**********************************************************/

		ultrasonic_Init();

		LCD_Clear();
		ultrasonic_GetDistance(US1,&dist);
		LCD_GoTo(0,0);
		LCD_WriteString("Distance in cm");
		LCD_GoTo(1,5);
		LCD_WriteString("cm");
		
	while (1)
	{

                if (ultrasonic_GetDistance(US1,&dist)==OK)
				{
					LCD_GoToClear(1,0,3);
					LCD_GoTo(1,0);
					LCD_WriteNumber(dist);
					_delay_ms(200);
				}
				else
				{
					LCD_GoToClear(1,0,3);
					LCD_GoTo(1,0);
					LCD_WriteString("No measuring");	
				}
		
	}

}

