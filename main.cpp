/*
Filename: main.cpp
Description: LRD reading is written to the serail output, one via a low pass filter. The filtered LDR reading controls the PWM for an LED.
Author: A Redfern
Date: 13/03/2025
Input/Output: 
Version: 01.00
Change log: 01.00 - Initial issue
*/
 
#include "mbed.h"
 
AnalogIn LDRIN(A3);
AnalogIn FiltLDRIN(A4);
PwmOut LED(PA_0);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
float LDRVal; 
float FiltLDRVal;
float PWMDuty;
 
int main()
{

    while( true ) {
    LDRVal = LDRIN.read()*3.3;
    FiltLDRVal = FiltLDRIN.read()*3.3; 
    char str[10] = "";

    str[0] = '\0';
    sprintf ( str, "LDR reading: %.3fV\r\n", LDRVal);
    uartUsb.write( str, strlen(str) );
    
    str[0] = '\0';
    sprintf ( str, "Filtered LDR reading: %.3fV\r\n", FiltLDRVal);
    uartUsb.write( str, strlen(str) );

    PWMDuty = 1-(FiltLDRVal/3.3); //as LDR value decreases LED duty increases
    LED.write(PWMDuty);
   
    ThisThread::sleep_for(200);

    }
}
 