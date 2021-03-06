/* Alan Hale III
 * GCRobotics
 * 2013/3/5
 *
 *
 * I2C Library
 * Functions necessary for proper I2C communication and interrupt handling
 *
 */

#include "I2Clib.h"
#include <pic16f917.h>


// Initialises all the necessary registers for proper I2C communication
void BeginI2C(char address);


// This function, upon a read interrupt, takes velocity and turns it
//  into direction and speed.  Converts speed from revolutions per
//  second into cycles per second.  Returns target speed and direction.
void SetVelocity(int *direction, int *speed, int cycles_per_rev_ratio);


// This function, upon write interrupt, writes the time and counts out
//  to I2C
void ReturnData(int *t_h, int *t_l, int *c_h, int *c_l);


// Upon detection of an interrupt, this function determines what command
//  the PIC has been given, whether a read or a write.  It sets flags
//  according to what it finds.
void I2C_ISR_Handler(int *flag);







/*  Josh's Old Code
void i2cInit(char address){

    TRISC6 = 1;
    TRISC7 = 1;
    SSPEN = 1;
    CKE = 0;
    SMP = 0;
    CKP = 1;

    SSPM0 = 0;
    SSPM1 = 1;
    SSPM2 = 1;
    SSPM3 = 0;

    SSPIE =1;

    SSPADD = address;
    PEIE = 1;
    GIE = 1;
    INTE = 1;
   // i2cBuffer[1] = 0;

    i2cBufferVal = 0;
}

void i2cIsrHandler(){

//SSP_Handler

   // setting up for 3 byte messages as follows:
   // | type byte | msg data |
   // Address is handled by the pic, so is ignored by our isr code.



    if ((SSPSTAT & 0b00100100) == 0b00100000){ // D_A high, R_W low, write w/ data in buffer
        i2cBuffer[i2cBufferVal] = SSPBUF;
        i2cBufferVal++;

    } else if ((SSPSTAT & 0b00100100) == 0b0000000){ // D_A low,R_W low, write w/ addr in buffer
        // Empty the buffer and carry on, this shouldn't happen since the pic does addr matching.
        SSPBUF = 0;

    } else if ((SSPSTAT & 0b00100100) == 0b0000100){ // D_A low,R_W high, read w/ addr in buffer
        // Again shoulnt happen, just here in case we ever need it.

    } else if ((SSPSTAT & 0b00100100) == 0b0010100){ // D_A high,R_W high, read w/ data in buffer

        i2cRequest = SSPBUF;

        if (i2cRequest == 1){ // requesting velocity       // SETUP THIS STUFF
            i2cSend(0x00);
        } else if (i2cRequest == 2){ // requesting errors
            i2cSend(0x00);
        }
    }


    SSPIF = 0;

    if (i2cBufferVal == 2){
        i2cBufferVal = 0;
        i2cDataUpdate();
    }
    return;
}


void i2cDataUpdate(){
    switch (i2cBuffer[0]) { // Check message type
        case 0 : // Velocity
            i2cSpeed = (i2cBuffer[1] & 0b01111111);
            i2cDirection = (i2cBuffer[1] >> 7);
            break;

        // case 1 :
    }
    return;
}

void i2cSend(char msg){

    return;
}*/