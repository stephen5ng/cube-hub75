#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#define PANEL_RES_X 64  // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 64  // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1   // Total number of panels chained one to another

MatrixPanel_I2S_DMA *dma_display;

void setup() {
  Serial.begin(112500);

  HUB75_I2S_CFG::i2s_pins _pins = {
    25,  //R1_PIN,
    26,  //G1_PIN,
    27,  //B1_PIN,
    14,  //R2_PIN,
    12,  //G2_PIN,
    13,  //B2_PIN,
    23,  //A_PIN,
    19,  //B_PIN,
    5,   //C_PIN,
    17,  //D_PIN,
    32,  //E_PIN,
    4,   //LAT_PIN,
    15,  //OE_PIN,
    16,  //CLK_PIN
  };

  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,
    PANEL_RES_Y,
    PANEL_CHAIN,
    _pins
  );

  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness(255);
  dma_display->setTextSize(8);      // size 1 == 8 pixels high
  dma_display->setTextWrap(false);  // Don't wrap at end of line - will do ourselves
  dma_display->clearScreen();
}

void loop() {
  static char str[] = "A";
  dma_display->clearScreen();
  dma_display->setCursor(12, 4);
  dma_display->print(str);
  Serial.println(str);
  if (str[0]++ == 'Z') {
    str[0] = 'A';
  }
  delay(300);
}
