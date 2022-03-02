/******************************************************************************
* File Name: WIPER.h
* Description:  This file contains function Prototypes of WIPER.c
* Tool-Chain: AVR GCC
*
*  Modification History:
*  Created by: () V1.0    26/Feb/22
*  Description:     V1.0
******************************************************************************/
#ifndef WIPER_H
#define WIPER_H
/******************************************************************************
*                      Defines and data types
******************************************************************************/
typedef enum{
    No_rain=0,
    Low_rain,
    Medium_rain,
    High_rain,
    Very_high_rain=4
    }Intensity_of_Rain;
/******************************************************************************
*                      Global variables
******************************************************************************/
/******************************************************************************
*                      Public function prototypes
******************************************************************************/
void Wiper_AutoMode(void);
void Wiper_ManualMode(void);
Intensity_of_Rain Read_RainSensor(void);
#endif
/******************************************************************************
*                      End of File
******************************************************************************/

