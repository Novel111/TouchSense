/*
 * File:   test6_2.c
 * Author: wangyuhao
 *
 * Created on August 22, 2016, 5:10 PM
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#define LEVEL 800
#include <xc.h>
void main()
{
    
}
void TouchSense() {
    LATB = 0;
    TRISB = 0;
    PORTB = 0;
    ADCON2 = 0x0f;
    ADCON1 = 0x70;
    ANSELA = 0;  
    while(1)
    {
        TRISAbits.TRISA0 = 0;
        TRISAbits.TRISA1 = 0;  //设为输出

        PORTAbits.RA0 = 1;
        PORTAbits.RA1 = 0;

        _delay(1000);  
    
        TRISAbits.TRISA0 = 1;
        ADCON0 = 0b00000001;
        ADCON0bits.GO_nDONE = 1; 
        while (ADCON0bits.GO_nDONE);   //等待此次转换结束 

        TRISAbits.TRISA1 = 1;
        ADCON0 = 0b00000101;
        ADCON0bits.GO_nDONE = 1; 
        while (ADCON0bits.GO_nDONE);  
        
        int ad_key=ADRESH*16+ADRESL/16;  //获取到censor的值
        if(ad_key>LEVEL)
        {
            LATBbits.LATB0 = 0;
        }
        else
        {
            LATBbits.LATB0 = 1;
        }
    }

}
