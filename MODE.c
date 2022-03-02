/******************************************************************************
* File Name:MODE.c
* Description:  This file contains API definitions of MODE.c
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by: () V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/
#include "MODE.h"
#include"GPIO.h"
#include"INTERRUPT.h"
#include"WIPER.h"
/******************************************************************************
*                      Public functions definitions
******************************************************************************/
/******************************************************************************
* Name: wiper_IO_Config
* Description:  Implement the wiper input and output
* Arguments: None
* Returns: None
******************************************************************************/
void IO_Config(void)
{
    GPIOConfig(PD2,INPUT);
    GPIOConfig(PD3,INPUT);
    GPIOConfig(PD6,OUTPUT);
    Int0Config();
    Int1Config();
}
/******************************************************************************
* Name: engin_off_mode
* Description: Implement engine OFF mode functionality
* Arguments: None
* Returns: None
******************************************************************************/
void Engine_offMode(void)
{
    while(0==g_Ext_Int_Flag.flag_Int0)
    {
        g_Ext_Int_Flag.flag_Int1=0;
    }
    g_Ext_Int_Flag.flag_Int0=0;
}
/******************************************************************************
* Name: engin_on_mode
* Description: Implement engine ON mode functionality
* Arguments: None
* Returns: None
******************************************************************************/
void Engine_onMode(void)
{

    while(0==g_Ext_Int_Flag.flag_Int0)
    {
        Wiper_ManualMode();
        if(1==g_Ext_Int_Flag.flag_Int0)
        {
            break;
        }
        Wiper_AutoMode();
    }
    g_Ext_Int_Flag.flag_Int0=0;
}
/******************************************************************************
*                      End of File
******************************************************************************/



