#include <msp430.h>
#include "CTS_Layer.h"
#define LED1 BIT7
#define LED2 BIT6  // P1.X e bagðlý LED elemanlarý
#define LED3 BIT4
#define LED4 BIT5


//////////////  UART string gönderme fonksiyonu /////////////
void print(char *text)
{
    unsigned int i = 0;
    while(text[i] != '\0')
    {
        while (!(IFG2&UCA0TXIFG));      // Check if TX is ongoing
        UCA0TXBUF = text[i];            // TX -> Received Char + 1
        i++;
    }
}

//////////////  UART sayý gönderme fonksiyonu /////////////
void printNumber(unsigned int num)
{
    char buf[6];
    char *str = &buf[5];

    *str = '\0';

    do
    {
        unsigned long m = num;
        num /= 10;
        char c = (m - 10 * num) + '0';
        *--str = c;
    } while(num);

    print(str);
}





// Delta Counts returned from the API function for the sensor during characterization


unsigned int raw_data[5];  // Custom fonkisiyonda kullanýlan degiþken dizisi. Tanýmlanan elementlerin capasitelerini tutuyor.

unsigned int position[1];
unsigned int position2;   //TI_CAPT_SLÝDER fonksinun döndürdüðü pozisyon derðerlerini tutuyor.


//struct Element * keyPressed;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Watch_Dog timerý kapatýyor.

    DCOCTL = 0;                         // Select lowest DCO settings
    BCSCTL1 = CALBC1_1MHZ;              // Set DCO to 1 MHz
    DCOCTL = CALDCO_1MHZ;
    BCSCTL3 |= LFXT1S_2;                  // LFXT1 = VLO
    P1SEL = BIT1 + BIT2 ;               // Select UART RX/TX function on P1.1,P1.2
    P1SEL2 = BIT1 + BIT2;
    P1DIR = 0xFF;
    UCA0CTL1 |= UCSSEL_2;               // UART Clock -> SMCLK
    UCA0BR0 = 104;                      // Baud Rate Setting for 1MHz 9600
    UCA0BR1 = 0;                        // Baud Rate Setting for 1MHz 9600
    UCA0MCTL = UCBRS_1;                 // Modulation Setting for 1MHz 9600
    UCA0CTL1 &= ~UCSWRST;               // Initialize UART Module



    TI_CAPT_Init_Baseline(&one_button);

                            // Update baseline measurement (Average 5 measurements)
    TI_CAPT_Update_Baseline(&one_button,50);


      while (1)
      {

         // keyPressed = (struct Element *)TI_CAPT_Buttons(&one_button);

        // Get the raw delta counts for element characterization
                      // Set breakpoint here

        TI_CAPT_Custom(&one_button,raw_data);

        __no_operation();                   // Set breakpoint here


        position2 = TI_CAPT_Slider(&one_button);
            if (position2 == 0XFFFF){

                     position2= 200;
                }

            __delay_cycles(15000);


                 print("posýtýon = ");
                 printNumber( position2)    ;
                 print("\r\n\n\n");
                __delay_cycles(15000);
                    if(position2 <=16 )
                    {
                        __delay_cycles(15000);
                        if(position2 <=16)
                                            {
                                               P1OUT = LED1;
                                            }

                    }
                    else if (position2 >=17 && position2<=41)
                    {  __delay_cycles(15000);

                        if (position2 >=17 && position2<=41 )


                                            {
                                                P1OUT = LED1 | LED2;
                                            }

                    }
                    else if (position2 >= 47 && position2 <= 48 )
                    { __delay_cycles(15000);



                        if (position2 >= 47 && position2 <= 48)
                                            {
                                                P1OUT = LED2;
                                            }
                    }
                    else if (position2 >= 50 && position2 <= 79)
                    { __delay_cycles(15000);


                        if (position2 >= 50 && position2 <= 79)
                                            {
                                                P1OUT = LED2 | LED3;
                                            }
                    }
                    else if (position2 >= 80 && position2 <= 80)
                    {  __delay_cycles(15000);


                        if (position2 >=80 && position2 <= 80)
                                             {
                                                 P1OUT = LED3;
                                              }
                      }
                    else if (position2 >=81 && position2 <= 110)
                    { __delay_cycles(15000);


                        if (position2 >=81 && position2 <= 110)
                                              {
                                                 P1OUT = LED3 | LED4;
                                               }
                       }
                    else if (position2 >=111 && position2 <= 190)
                    {  __delay_cycles(15000);


                        if (position2 >=111 && position2 <= 190)
                                               {
                                                 P1OUT =  LED4;
                                               }
                       }
                    else
                        P1OUT = 0x00;

      }
}
