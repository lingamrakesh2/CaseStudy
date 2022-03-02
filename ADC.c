/******************************************************************************
* File Name: ADC.c
* Description:  This file contains API definitions for ADC functionality
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by:() V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/
#include<avr/io.h>
#include "ADC.h"
/******************************************************************************
*                      Global variables
******************************************************************************/
uint16_t g_ADC_Value=0;
/******************************************************************************
*                      Public functions definitions
******************************************************************************/
/******************************************************************************
* Name: ADC_Config
* Description:  enable adc and set ref voltage vcc=5v and adc channel to ADC0
* Arguments: none
* Returns: None
******************************************************************************/
void ADC_Config(void)
{
    ADMUX &= 0x00;
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN); //enables the ADC
}
/******************************************************************************
* Name: ADC_Read
* Description:  start the adc conversion and afte end of conversion return
        the adc value.
* Arguments: none
* Returns: none
******************************************************************************/
void ADC_Read(void)
{
    ADCSRA |= (1 << ADSC);   //start of converion
    while (ADCSRA & (1 << ADSC)); //wait for conversion complete
    g_ADC_Value=ADC; //update global ADC value
}
/******************************************************************************
* Name: Stop
* Description:  stop the adc conversion
* Arguments: none
* Returns: none
******************************************************************************/
void Stop(void)
{
    ADCSRA &= ~(1 << ADEN);

}
/******************************************************************************
*                      End of File
******************************************************************************/



