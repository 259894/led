/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: 16-Sep-2021
 *      Author: varsha
 */

#include "stm32f407xx_gpio_driver.h"

/*
 * API for Peripheral clock control of GPIO's
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi)
{
	if (EnorDi== ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
				{
					GPIOC_PCLK_EN();
				}
		else if (pGPIOx == GPIOD)
				{
					GPIOD_PCLK_EN();
				}
		else if (pGPIOx == GPIOE)
				{
					GPIOE_PCLK_EN();
				}
		else if (pGPIOx == GPIOF)
				{
					GPIOF_PCLK_EN();
				}
		else if (pGPIOx == GPIOG)
				{
					GPIOG_PCLK_EN();
				}
		else if (pGPIOx == GPIOH)
				{
					GPIOH_PCLK_EN();
				}
		else if (pGPIOx == GPIOI)
				{
					GPIOI_PCLK_EN();
				}
	}
	else
	{
		if(pGPIOx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				else if (pGPIOx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}
				else if (pGPIOx == GPIOC)
						{
							GPIOC_PCLK_DI();
						}
				else if (pGPIOx == GPIOD)
						{
							GPIOD_PCLK_DI();
						}
				else if (pGPIOx == GPIOE)
						{
							GPIOE_PCLK_DI();
						}
				else if (pGPIOx == GPIOF)
						{
							GPIOF_PCLK_EN();
						}
				else if (pGPIOx == GPIOG)
						{
							GPIOG_PCLK_DI();
						}
				else if (pGPIOx == GPIOH)
						{
							GPIOH_PCLK_DI();
						}
				else if (pGPIOx == GPIOI)
						{
							GPIOI_PCLK_DI();
						}

	}

}


/*
 * API's for initialization and deinitialization
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

/*
 * 1. Configure the mode
 */

	uint32_t temp=0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->MODER |= temp;
	//2. Configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &=(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |=temp;
	temp = 0;
	//3. Configure the pull up or pull down settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOx->PUPDR &=(0x3 <<(2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOx->PUPDR |=temp;

	    //4. Configure the output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->OTYPER |=temp;





	//5. Configure Alternating Function mode

	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1, temp2;
		temp1= pGPIOHandle->GPIO_PinConfig.GPIO_PinMode/8;
		temp2= pGPIOHandle->GPIO_PinConfig.GPIO_PinMode%8;
		pGPIOHandle->pGPIOx->AFR[temp1] &=~(0xf <<(4*temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));



	}






}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
       if(pGPIOx == GPIOA)
       {
    	   GPIOA_REG_RESET();
       }
       else if (pGPIOx == GPIOB)
       {
           GPIOB_REG_RESET();
       }
       else if (pGPIOx == GPIOC)
             {
             GPIOC_REG_RESET();
             }
       else if (pGPIOx == GPIOD)
             {
             GPIOD_REG_RESET();
             }

        else if (pGPIOx == GPIOE)
             {
             GPIOE_REG_RESET();
             }

        else if (pGPIOx == GPIOF)
              {
              GPIOF_REG_RESET();
              }

         else if (pGPIOx == GPIOG)
              {
              GPIOG_REG_RESET();
              }

         else if (pGPIOx == GPIOH)
              {
               GPIOH_REG_RESET();
              }

         else if (pGPIOx == GPIOI)
              {
               GPIOI_REG_RESET();
              }






}


/*
 * API's for Data read, Data write and Toggle of GPIO's
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
	uint8_t Value;
	Value =  (uint8_t) ((pGPIOx ->IDR >> PinNumber) &  0x00000001);
	return Value;



}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t Value;
	Value =  (uint16_t) pGPIOx->IDR;
	return Value;



}
void WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value)
{
       if (Value == GPIO_PIN_SET)
       {
    	   pGPIOx->ODR |= (1<<PinNumber);
       }
       else
       {
    	   pGPIOx->ODR &= ~(1<<PinNumber);
       }



}
void WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint8_t Value)
{

	pGPIOx->ODR = Value;

}
void ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1<<PinNumber);



}
