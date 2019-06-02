//******************************************************************************
// structure.c
// 
// Touch the element to turn on/off the LED
// RO method capactiance measurement using PinOsc IO, TimerA0, and WDT+
//
//******************************************************************************

#include "structure.h"

// Element (P2.0)
const struct Element middle_element = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT5,
              // When using an abstracted function to measure the element
              // the 100*(maxResponse - threshold) < 0xFFFF
              // ie maxResponse - threshold < 655
              .maxResponse = 3086+ 655,
              .threshold = 3086
};

const struct Element up_element = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT4,
              // When using an abstracted function to measure the element
              // the 100*(maxResponse - threshold) < 0xFFFF
              // ie maxResponse - threshold < 655
              .maxResponse = 2645 +655,
              .threshold = 2645
};

const struct Element left_element = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT3,
              // When using an abstracted function to measure the element
              // the 100*(maxResponse - threshold) < 0xFFFF
              // ie maxResponse - threshold < 655
              .maxResponse = 2900+655,
              .threshold = 2900
};

const struct Element right_element = {

              .inputPxselRegister = (uint8_t *)&P2SEL,  
              .inputPxsel2Register = (uint8_t *)&P2SEL2,  
              .inputBits = BIT2,
              // When using an abstracted function to measure the element
              // the 100*(maxResponse - threshold) < 0xFFFF
              // ie maxResponse - threshold < 655
              .maxResponse = 3100+655,
              .threshold =3100
};




// One Button Sensor
const struct Sensor one_button =
               { 
                  .halDefinition = RO_PINOSC_TA0_WDTp,	// Sensing Method
                  .numElements = 4,						// # of Elements
                  .baseOffset = 0,						// First element index = 0
                  // Pointer to elements
                  .arrayPtr[0] = &middle_element,  		// point to middle element
                  .arrayPtr[1] = &up_element, 
                  .arrayPtr[2] = &left_element,  		// point to middle element
                  .arrayPtr[3] = &right_element, 

                  // Timer Information
                  .measGateSource= GATE_WDT_ACLK,     //  0->SMCLK, 1-> ACLK
                  .accumulationCycles= WDTp_GATE_64 ,  //64 - Default

                  .points = 128,
                                  .sensorThreshold = 50

               };


