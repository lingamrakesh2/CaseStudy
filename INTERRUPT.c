/******************************************************************************
* File Name: INTERRUPT.c
* Description:  This file contains API function definitions for external interrupt
        INT0 and INT1
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by: () V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/
#include"INTERRUPT.h"
#include<avr/interrupt.h>
#include<avr/io.h>

/******************************************************************************
*                      Global variables
******************************************************************************/
int_flag g_Ext_Int_Flag={       //initializing zero value
            .flag_Int0=0,
            .flag_Int1=0};
/******************************************************************************
*                      Public functions definitions
******************************************************************************/
/******************************************************************************
* Name: Int0Config
* Description:  Configures the mode external interrupt INT0
* Arguments: None
* Returns: None
******************************************************************************/
void Int0Config(void)
{
    EICRA |= (1 << ISC00);
    EICRA &= ~(1 << ISC01); //Any logical change generates an interrupt request
    EIMSK |= (1 << INT0);   //Local Interrupt enable
    sei();                  //enable global interrupt
}
/******************************************************************************
* Name: Int1Config
* Description:  Configures the mode external interrupt INT1
* Arguments: None
* Returns: None
******************************************************************************/
void Int1Config(void)
{
    EICRA |= (1 << ISC10);
    EICRA &= ~(1 << ISC11); //Any logical change generates an interrupt request
    EIMSK |= (1 << INT1);   //Local Interrupt enable
    sei();                  //enable global interrupt
}
/******************************************************************************
*                      ISR functions
******************************************************************************/
/******************************************************************************
* Name:INT0
* Description:When INT0 interrupt occurred it set INT0 flag to 1
******************************************************************************/
ISR(INT0_vect)
{
    cli();
    g_Ext_Int_Flag.flag_Int0 = 1;
    sei();
}
/******************************************************************************
* Name:INT2
* Description:When INT1 interrupt occurred it set INT1 flag to 1
******************************************************************************/
ISR(INT1_vect)
{
    cli();
    g_Ext_Int_Flag.flag_Int1 = 1;
    sei();
}
/******************************************************************************
*                      End of File
******************************************************************************/
