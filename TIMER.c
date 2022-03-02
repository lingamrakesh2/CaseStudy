/******************************************************************************
* File Name: TIMER.c
* Description:  This file contains API function definitions for timer Functionalities
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by: () V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/
#include<avr/interrupt.h>
#include"TIMER.h"
/******************************************************************************
*                      Global variables
******************************************************************************/
timer_flag g_Timer2_Flag={.Overflow_Flag=0};
uint8_t g_Update_ocr0a=0;
/******************************************************************************
*                      Public functions definitions
******************************************************************************/
/******************************************************************************
* Name: Timer0Config
* Description:  Configures the timer 0 in pwm mode
* Arguments: None
* Returns: None
******************************************************************************/
void Timer0Config(void)
{
    TCCR0A |= ((1 << WGM01) | (1 << WGM00));
    TCCR0A |= (1 << COM0A1);    //COM0A1=1
    TCCR0B |= ((1 << CS00) | (1 << CS02));
    TCCR0B &= ~(1 << CS01);     //CS02=CS00=1
    OCR0A=g_Update_ocr0a;
    sei();
}
/******************************************************************************
* Name: Timer2Config
* Description:  Configures the timer2 in normal mode with prescaler clk/1024
* Arguments: None
* Returns: None
******************************************************************************/
void Timer2Config(void)
{
    TCCR2A=0x00;                             // Normal mode of operation
    TCCR2B|=((1<<CS22)|(1<<CS21)|(1<<CS20));
    TIMSK2|=(1<<TOIE2);                 // INT enable
    sei();
}
/******************************************************************************
* Name: Stop_Timer0
* Description: Configures the to stop the pwm operation and reset all register
* Arguments: None
* Returns: None
******************************************************************************/
void Stop_Timer0(void)
{
    ////Clearing timer 0 register to stop timer 0
    TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
    TCCR0A &= ~(1 << COM0A1);
    TCCR0A &= ~(1 << COM0A0);
    TCCR0B &= ~((1 << CS00) | (1 << CS02));
    TCCR0B &= ~(1 << CS01);
}
/******************************************************************************
* Name: Stop_Timer2
* Description:  Configures the timer2 to stop normal mode operation be reset register
* Arguments: None
* Returns: None
******************************************************************************/
void Stop_Timer2(void)
{
    TCCR2A=0x00;   ////Clearing timer 2 register to stop timer 2
    TCCR2B&=~((1<<CS22)|(1<<CS21)|(1<<CS20));
    TIMSK2&=~(1<<TOIE2); //disable timer 0 interrupt
}
/******************************************************************************
*                      ISR functions
******************************************************************************/
/******************************************************************************
* Name:Timer 2 overflow
* Description:Timer overflow set timer 2 flag after each 2 sec
******************************************************************************/
ISR(TIMER2_OVF_vect){
    static uint16_t counter;
    cli();
    counter++;
    if (counter >= 306)
    {
        g_Timer2_Flag.Overflow_Flag= 1;
        counter = 0;
    }
    sei();
}
/******************************************************************************
*                      End of File
******************************************************************************/

