#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define PANEL_RES_X 64  // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 64  // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1   // Total number of panels chained one to another

MatrixPanel_I2S_DMA *hub75_display;

void setup() {
  Serial.begin(112500);

  HUB75_I2S_CFG::i2s_pins _pins = {
    25,  //R1_PIN,
    26,  //G1_PIN,
    33,  //B1_PIN,
    13,  //R2_PIN,
    27,  //G2_PIN,
    14,  //B2_PIN,
    19,   //A_PIN,
    21,  //B_PIN,
    4,   //C_PIN,
    22,  //D_PIN, 
    12,  //E_PIN,
    15,   //LAT_PIN, ** 2 **
    2,  //OE_PIN, ** 15 ** 
    16,  //CLK_PIN
  };

  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,
    PANEL_RES_Y,
    PANEL_CHAIN,
    _pins
  );
  mxconfig.clkphase = false;
  hub75_display = new MatrixPanel_I2S_DMA(mxconfig);
  hub75_display->begin();
  hub75_display->setBrightness(255);
  hub75_display->setTextSize(9);      // size 1 == 8 pixels high
  hub75_display->setTextWrap(false);  // Don't wrap at end of line - will do ourselves
  hub75_display->clearScreen();
}

void loop() {
  static char str[] = "A";
  hub75_display->clearScreen();
  hub75_display->setCursor(1, 0);
  hub75_display->print(str);
  Serial.println(str);
  if (str[0]++ == 'Z') {
    str[0] = 'A';
  }
  delay(300);
}
