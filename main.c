 /*You can use a J (with parameter 2) to clear the screen and an H (with parameters 1,1) to reset the cursor to the top-left:
  *     printf("\033[2J\033[1;1H");
  */

#include "mcc_generated_files/mcc.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    ADCC_StartConversion( 1 );
    int sut;sut=0;
    double kezd,tart;
    while (1)
    {
        tart = ADCC_GetConversionResult();
        if( sut == 1 && ido == 0 || sut == 1 && ido < 0  ) //ha lejar az ido
        {
            sut = 0; 
            INTERRUPT_GlobalInterruptDisable();
            INTERRUPT_PeripheralInterruptDisable();
            LED1_SetLow();
            LED3_SetLow();
            LED2_SetLow();
            ido=0;
        }
        if(ido < 0 && S1_GetValue() == 0 || ido == 0 && S1_GetValue() == 0 )
        {
            ido = tart;
            ido = ido / 10;
            ido = 12 * ido;
            kezd = ido-2;
        }
        if(S1_GetValue() == 0 && LED1_GetValue() == 0) //sutes kezd
        {
            sut = 1;
            LED1_SetHigh();
            LED2_SetHigh();
            kezd = ido-2;
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
        }
        if(S2_GetValue() == 0) //ajtonyitas
        {
            LED1_SetLow();
            LED2_SetHigh();
            while(S2_GetValue() == 0);
            sut = 0;
            LED2_SetLow();
        }
        if( sut == 1 && S1_GetValue() == 0 && kezd > ido ) //leallitas
        {
            INTERRUPT_GlobalInterruptDisable();
            INTERRUPT_PeripheralInterruptDisable();
            LED1_SetLow();
            LED3_SetLow();
            LED2_SetLow();
            LED4_SetHigh();
            ido=0;
            printf("\033[0m\033[2J\033[1;1H\033[?25l0");            //\033[A is go up a line \033[2K is clear that line
            while(S1_GetValue() == 0);
            __delay_ms(500);
            LED4_SetLow();
        }
    }    
}
/**
 End of File
*/