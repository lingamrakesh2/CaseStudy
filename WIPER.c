/******************************************************************************
* File Name: WIPER.c
* Description:  This file contains API function definitions of WIPER.c
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by: () V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
/******************************************************************************
*                      Includes
******************************************************************************/
#include"WIPER.h"
#include"TIMER.h"
#include"INTERRUPT.h"
#include"ADC.h"
/******************************************************************************
*                      Global variables
******************************************************************************/
static uint8_t g_DutyCycle[5]={0,63,127,190,254};

/******************************************************************************
* Name: Read_RainSensor
* Description:  read rain sensor
* Arguments: None
* Returns: Intensity_of_Rain
******************************************************************************/
Intensity_of_Rain Read_RainSensor(void)
{
  ADC_Read();
  if((0<g_ADC_Value) && (g_ADC_Value<=50))
  {
      return No_rain;
  }
  else if((50<g_ADC_Value) && (g_ADC_Value<=200))
  {
      return Low_rain;
  }
  else if((200<g_ADC_Value) && (g_ADC_Value<=500))
  {
      return Medium_rain;
  }
  else if((500<g_ADC_Value) && (g_ADC_Value<=1000))
  {
      return High_rain;
  }
  else
  {
      return Very_high_rain;
  }
}
/******************************************************************************
*                      Public functions definitions
******************************************************************************/
/******************************************************************************
* Name: Wiper_AutoMode
* Description:  Implement the wiper auto mode functionality
* Arguments: None
* Returns: None
******************************************************************************/
void Wiper_AutoMode(void)
{
    ADC_Config();
    Timer0Config();
    Timer2Config();
    while ((0==g_Ext_Int_Flag.flag_Int0)&&(0==g_Ext_Int_Flag.flag_Int1))
        {
            if(1==g_Timer2_Flag.Overflow_Flag)
            {
                g_Update_ocr0a=g_DutyCycle[Read_RainSensor()];
                Timer0Config();
                g_Timer2_Flag.Overflow_Flag=0;
            }

        }
        g_Ext_Int_Flag.flag_Int1=0;
        Stop();
        Stop_Timer0();
        Stop_Timer2();
}
/******************************************************************************
* Name: Wiper_ManualMode
* Description: Implement the wiper manual mode functionality
* Arguments: None
* Returns: None
******************************************************************************/
void Wiper_ManualMode(void)
{
    g_Update_ocr0a=g_DutyCycle[Medium_rain];
    Timer0Config();
    while((0==g_Ext_Int_Flag.flag_Int1) && (0==g_Ext_Int_Flag.flag_Int0));
    g_Ext_Int_Flag.flag_Int1=0;
    Stop_Timer0();
}
/******************************************************************************
*                      End of File
******************************************************************************/

