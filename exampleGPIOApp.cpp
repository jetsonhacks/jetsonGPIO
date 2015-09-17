// exampleApp.c

#include <iostream>
#include <string>
#include <unistd.h>
#include "jetsonGPIO.h"
using namespace std;

int main(int argc, char *argv[]){

    cout << "Testing the GPIO Pins" << endl;

    jetsonGPIO redLED = gpio165 ;
    jetsonGPIO pushButton = gpio166 ;
    // Make the button and led available in user space
    gpioExport(pushButton) ;
    gpioExport(redLED) ;
    gpioSetDirection(pushButton,inputPin) ;
    gpioSetDirection(redLED,outputPin) ;
    // Reverse the button wiring; this is for when the button is wired
    // with a pull up resistor
    // gpioActiveLow(pushButton, true);


    // Flash the LED 5 times
    for(int i=0; i<5; i++){
        cout << "Setting the LED on" << endl;
        gpioSetValue(redLED, on);
        usleep(200000);         // on for 200ms
        cout << "Setting the LED off" << endl;
        gpioSetValue(redLED, off);
        usleep(200000);         // off for 200ms
    }

    // Wait for the push button to be pressed
    cout << "Please press the button!" << endl;

    unsigned int value = low;
    int ledValue = low ;
    // Turn off the LED
    gpioSetValue(redLED,low) ;
    for (int i = 0 ; i < 10000 ; i++) {
        gpioGetValue(pushButton, &value) ;
        // Useful for debugging
        // cout << "Button " << value << endl;
        if (value==high && ledValue != high) {
            // button is pressed ; turn the LED on
            ledValue = high ;
            gpioSetValue(redLED,on) ;
        } else {
            // button is *not* pressed ; turn the LED off
            if (ledValue != low) {
                ledValue = low ;
                gpioSetValue(redLED,off) ;
            }

        }
        usleep(1000); // sleep for a millisecond
    }

    cout << "GPIO example finished." << endl;
    gpioUnexport(redLED);     // unexport the LED
    gpioExport(pushButton);      // unexport the push button
    return 0;
}


