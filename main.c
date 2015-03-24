/* ========================================
 *
 * This is a simple program to drive WS2812b LEDs.
 * It's setup to run using the PSoC 4 breakout board that I designed. You can 
 * find the design files for the board on my GitHub
 *
 *     https://github.com/icchalmers/FabAcademy_PSoC4_Breakout
 * 
 * Assuming everything is working OK, you should see a rainbow pattern on the 
 * LEDs.
 *
 * ========================================
*/
#include <project.h>

uint32_t Wheel(uint8_t WheelPos);

#define NUMPIXELS 9
#define COLOURSTEPSIZE 255/NUMPIXELS

int main()
{
    StripLights_1_Start();    
    StripLights_1_Dim(2); // Dim to 25%
    CyGlobalIntEnable;
    
    uint8_t counter = 0;
    for(;;)
    {
        // Set the colour of each pixel so that between them all, the entire 
        // spectrum of the rainbow is displayed
        uint32_t pixelNumber;
        for(pixelNumber = 0; pixelNumber < NUMPIXELS; pixelNumber++){
            StripLights_1_Pixel(
                pixelNumber,
                0,
                Wheel(counter + (pixelNumber * COLOURSTEPSIZE)));
        }
        
        counter++;
        while( StripLights_1_Ready() == 0);
        StripLights_1_Trigger(1);
        CyDelay(10);
    }
}

// Adapted from the NeoPixel library from Adafruit.
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// Order seems to be BRG for the WS2812 driver
uint32_t Wheel(uint8_t WheelPos) {
    WheelPos = 255 - WheelPos;
    uint8_t R,G,B;
	if(WheelPos < 85) {
        R = 255 - WheelPos * 3l;
        G = 0;
        B = WheelPos * 3;
        return (B<<16) | (R<<8) | G;
    } 
    else if(WheelPos < 170) {
        WheelPos -= 85;
        R = 0;
        G = WheelPos * 3;
        B = 255 - WheelPos * 3;
        return (B<<16) | (R<<8) | G;
    } 
    else {
        WheelPos -= 170;
        R = WheelPos * 3;
        G = 255 - WheelPos * 3;
        B = 0;
        return (B<<16) | (R<<8) | G;
    }
}
/* [] END OF FILE */
