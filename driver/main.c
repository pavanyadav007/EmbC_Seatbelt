/*
 * main.c
 *
 *  Created on: Jun 26, 2021
 *      Author: pavan
 */

#include "stm32f407xx.h"

void delay(uint32_t n)
{
	// system clock is 16MHz delay function
	for(uint32_t i = 0 ; i < n ; i ++)
	{  for(uint32_t j=0;j<500000;j++);
	}
}
/*uint8_t ButtonValue(){
 static	uint8_t value=0;
	GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0);
	value++;
	return 0;
}
*/
int main(void)
{

	GPIO_Handle_t GpioLed, GpioLed1, GpioLed2, GPIOBtn;

	//this is led gpio configuration
	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed);

	GpioLed1.pGPIOx = GPIOD;
	GpioLed1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioLed1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed1);

	GpioLed2.pGPIOx = GPIOD;
	GpioLed2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GpioLed2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);

	GPIO_Init(&GpioLed2);


	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClockControl(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);
while(1)
{
	 GPIO_IRQInterruptConfig(IRQ_NO_EXTI0,ENABLE);
	 GPIO_IRQInterruptConfig(IRQ_NO_EXTI1,ENABLE);
	 GPIO_IRQPriorityConfig(IRQ_NO_EXTI0,NVIC_IRQ_PRI0);
	 GPIO_IRQPriorityConfig(IRQ_NO_EXTI1,NVIC_IRQ_PRI15);

     if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)==SET){
		GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_13,GPIO_PIN_SET);
		delay(2250);
		GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);
		GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_13,GPIO_PIN_RESET);
		}
}

}
void EXTI0_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
	delay(3000);
	GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_14,GPIO_PIN_RESET);



}
void EXTI1_IRQHandler(void){

	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_13,GPIO_PIN_SET);
	delay(8);
	GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_13,GPIO_PIN_RESET);

}
