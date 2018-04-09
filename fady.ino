#include <Adafruit_NeoPixel.h>

//define NeoPixel Pin and Number of LEDs
#define PIN 4
#define NUM_LEDS 4

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
byte retRGB[3] = {0,0,0};
byte i,j;
int l;
void setup() {
  // start the strip and blank it out
  strip.begin();
  strip.show();
}

// Define functions which animate LEDs in various ways.
void colorWipe(byte r,byte g, byte b){
    //Wipe color across display a pixel at a time.
    for(i=0; i<NUM_LEDS; i++){
        strip.setPixelColor(i, r,g,b);
        strip.show();
        delay(1000);
    }
}
void reverseWipe(byte r,byte g, byte b){
    //Wipe color across display a pixel at a time.
    for(i=0; i<NUM_LEDS; i++){
        strip.setPixelColor(((NUM_LEDS-1) - i), r,g,b);
        strip.show();
        delay(1000);
    }
}
void forwardChase(byte r, byte g, byte b){
    //Movie theater light style chaser animation.
    for(j=0; j<10; j++){
          for(i=0; i<NUM_LEDS; i++){
                strip.setPixelColor(i,r,g,b);
            }
            strip.show();
            delay(1000);
            for(i=0; i<NUM_LEDS; i++){
                strip.setPixelColor(i, 0,0,0);
            }
    }
}
void reverseChase(byte r, byte g, byte b){
    //Movie theater light style chaser animation.
    for(j=0; j<10; j++){
          for(i=NUM_LEDS; i>1; i--){
                strip.setPixelColor((i-1),r,g,b);
            }
            strip.show();
            delay(1000);
            for(i=0; i<NUM_LEDS; i++){
                strip.setPixelColor(i, 0,0,0);
            }
    }
}

void wheel(int pos){
    // Generate rainbow colors across 0-255 positions.
    if(pos < 85) {
        retRGB[0] = pos * 3;
        retRGB[1] = 255 - pos * 3;
        retRGB[2] = 0;
        return;
    } else if( pos < 170) {
        pos -= 85;
        retRGB[2] = pos * 3;
        retRGB[0] = 255 - pos * 3;
        retRGB[1] = 0;
        return;
    } else {
        pos -= 170;
        retRGB[1] = pos * 3;
        retRGB[2] = 255 - pos * 3;
        retRGB[0] = 0;
        return;
    }
}
void rainbow(void){
    //Draw rainbow that fades across all pixels at once.
    for(l =0; l<(256 * 1); l++){
        for(i=0; i<NUM_LEDS; i++){
            wheel((i+l) & 255);
            strip.setPixelColor(i, retRGB[0],retRGB[1],retRGB[2]);
        }
        strip.show();
        delay(50);
    }
}

void rainbowCycle(void) {
    //Draw rainbow that uniformly distributes itself across all pixels.
    for(l=0; l <(256*5); l++) {
        for(i=0; i<NUM_LEDS; i++){
            wheel((int(i * 256 / NUM_LEDS) + l) & 255);
            strip.setPixelColor(i, retRGB[0],retRGB[1],retRGB[2]);
        }
        strip.show();
        delay(50);
    }
}

void theaterChaseRainbow(void){
    //Rainbow movie theater light style chaser animation.
    for(l = 0 ; l<256; l++){
            for(i=0; i<NUM_LEDS; i++){
                wheel((i+j) % 255);
                strip.setPixelColor(i, retRGB[0],retRGB[1],retRGB[2]);
            }
            strip.show();
            delay(100);
            for(i=0; i<NUM_LEDS; i++){
                strip.setPixelColor(i, 0,0,0);
            }
    }
}

void loop() {
  colorWipe(255, 0, 0);  // Red wipe
  colorWipe(0, 0, 0);  // Red wipe off
  reverseWipe(0, 255, 0);  // Blue wipe
  reverseWipe(0, 0, 0);  // Blue wipe off
  colorWipe(0, 0, 255);  // Green wipe
  colorWipe(0, 0, 0);  // Green wipe off
 
  //forwardChase(127, 127, 127); // white theater chase
  //reverseChase(127, 127, 127); // white theater chase
  //forwardChase(127,   0,   0); // Red theater chase
  //reverseChase(127,   0,   0); // Red theater chase
  //forwardChase(0,   127,   0); // green theater chase
  //reverseChase(0,   127,   0); // green theater chase
  //forwardChase(0,   0,   127); // Blue theater chase
  //reverseChase(0,   0,   127); // Blue theater chase

  rainbow();
  rainbowCycle();
  theaterChaseRainbow();
}
