#include "TouchCapacitiv.h"
#include "ControlLED.h"
#include "Pwm.h"
#include "Uart.h"
#include "Pit.h"
#include "ClockSettings.h"


int main()
{



	
	SystemClock_Configure();
	SystemClockTick_Configure();
	
	//SYSCLOCK FIRST
	//TOUCH NEXT
	//PWM NEXT
	
	UART0_Init(115200);
	Touch_Init();

	
	TPM2_Init();



	
	
	for(;;){
		if(flag_100ms){
			Signal_Control();

			flag_100ms = 0U;
		}
	}
	
		
	
	

	return 0;


	
}
