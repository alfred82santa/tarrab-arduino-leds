#include <SoftwareSerial.h>

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
#define DEFAULT_PIXELS 1

#define ACTION_SET_PIXEL 1
#define ACTION_SET_SECTOR 2
#define ACTION_SHOW 3
#define ACTION_CONFIG_STRIP 4
#define ACTION_SET_8_PIXELS 5
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel *strip = new Adafruit_NeoPixel(DEFAULT_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel. Avoid connecting
// on a live circuit...if you must, connect GND first.
byte op;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  // End of trinket special code
  Serial.begin(500000);
  strip->begin();
  strip->show(); // Initialize all pixels to 'off'
}
void loop() {
  if (Serial.available()) {
    op = get_param();
    switch (op) {
      case ACTION_SET_PIXEL:
        set_pixel_action();
        send_ACK();
        break;
      case ACTION_SET_SECTOR:
        set_sector_action();
        send_ACK();
        break;
      case ACTION_SHOW:
        strip->show();
        send_ACK();
        break;
      case ACTION_CONFIG_STRIP:
        config_strip_action();
        send_ACK();
        break;  
      case ACTION_SET_8_PIXELS:
        set_8_pixels_action();
        send_ACK();
        break;
    }
  }
}

/**
 * Send ACK to serial port
 */
void send_ACK() {
  
}

/**
 * Read strip length (16 bits) from serial port and config it.
 */
void config_strip_action() {
  uint16_t numPixels;
  
  if (NULL != strip) {
    delete strip;
  }
  
  numPixels = get_param_16b();
  
  strip = new Adafruit_NeoPixel(numPixels, PIN, NEO_GRB + NEO_KHZ800);
  strip->begin();
  strip->show();
}
  
/**
 * Read 8 bits parameter from serial port.
 */
byte get_param() {
  while (!Serial.available()) {
  }
  return Serial.read();
}

/**
 * Read 16 bits parameter from serial port.
 */
uint16_t get_param_16b() {
  uint16_t param;
  byte data;
  
  data = get_param();
  param = data << 8;
  data = get_param();
  param += data;
  return param;
}

/**
 * Read pixel number from serial port (16 bits)
 */
uint16_t get_pixel() {
  uint16_t pixel;

  pixel = get_param_16b();  
  return pixel;  
}

/**
 * Read data to draw a pixel from serial port (40 bits).
 * 1st param (16bits): pixel position
 * 2nd param (8 bits): red
 * 3rd param (8 bits): green
 * 4th param (8 bits): blue
 */
void set_pixel_action() {
  byte pixel;
  pixel = get_pixel();
  strip->setPixelColor(pixel, get_color());
}

void set_8_pixels_action() {
  byte pixel;
  pixel = get_pixel();
  for (int i = 0; i < 8; i++) {
    strip->setPixelColor(pixel + i, get_color());
  }
}

/**
 * Read data to draw a sector from serial port (56 bits).
 * 1st param (16bits): pixel position (start position)
 * 2nd param (16bits): sector length 
 * 3rd param (8 bits): red
 * 4th param (8 bits): green
 * 5th param (8 bits): blue
 */
void set_sector_action() {
  byte pixel, length;
  uint32_t color;
  
  pixel = get_pixel();
  
  length = get_param_16b();  
  color = get_color();

  for (int i=0; i < length; i++) {
    strip->setPixelColor(pixel + i, color);
  }
}

/**
 * Read color from serial port (24 bits).
 * 1st param (8 bits): red
 * 2nd param (8 bits): green
 * 3rd param (8 bits): blue
 */
uint32_t get_color() {
  byte red, green, blue;
  
  red = get_param();
  green = get_param();
  blue = get_param();
  
  return strip->Color(red, green, blue);
}



