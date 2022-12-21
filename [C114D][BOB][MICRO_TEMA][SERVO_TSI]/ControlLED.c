#include "MKL25Z4.h"
#include <stdint.h>
#include "ControlLED.h"
#include "Uart.h"
#define PWM_CLOCK      (48000000 / 128)    // 375 Khz
#define PWM_PERIOD			10                 // 50msec
#define PWM_PERIOD_VAL ((PWM_CLOCK * PWM_PERIOD) / 1000) // PWM_PERIOD_VAL

#define PWM_DUTY_CYCLE(x) (PWM_PERIOD_VAL - (PWM_PERIOD_VAL / x))

typedef struct
{
	uint16_t Period;
	uint16_t DutyCycle;
	char Brigtness[5];
}pwm_str;

static pwm_str LEDControl[] = {
	//   PERIOD         DUTY CYCLE     % DUTY CYCLE    HIGH (LED_OFF)  LOW (LED_ON)
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(10),   "10%",     //  90msec         10msec
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(20),   "20%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(30),   "30%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(40),   "40%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(50),   "50%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(60),   "60%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(70),   "70%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(85),   "85%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(90),   "90%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(92),   "92%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(94),   "94%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(96),   "96%",
	PWM_PERIOD_VAL, PWM_DUTY_CYCLE(100),  "100%",
};

#define TOTAL_BRIGHTNEES_LVLS (sizeof(LEDControl) / sizeof(LEDControl[0]))

void control_LED_brightness(void)
{
	
	uint16_t x;
	uint32_t i;
	float y=0.00;
	static uint8_t brightness_level = TOTAL_BRIGHTNEES_LVLS;
	//while(1){
      x = Touch_Scan_HL();    // Get the touch sensor input
		//max=1757; min=1
				//y=(float)(x-1)/(float)1757;
				//y=y*10;
				y = (float)(x - 16);
			
				brightness_level= (int)y;
//				if (brightness_level > TOTAL_BRIGHTNEES_LVLS)
//				{	
//						brightness_level = 0;
//				}
				TPM2_CNT = 0;
				TPM2_MOD = LEDControl[brightness_level].Period;
				UTILS_PrintCounter(brightness_level);
				UART0_Transmit(0x0A);
				UART0_Transmit(0x0D);
				TPM2_C0V = LEDControl[brightness_level].DutyCycle;
        for ( i = 0; i < 2900; i++); // Delay
	//		}

}
