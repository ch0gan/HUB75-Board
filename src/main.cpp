#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

// Your GPIO pin mapping from the crosswalk:
// R1=18, G1=17, B1=19, R2=21, G2=23, B2=27, A=26, B=16, C=25, D=4, CLK=33, OE=32, LAT=2

#define R1  18
#define G1  17
#define B1  19
#define R2  21
#define G2  23
#define B2  27
#define CH_A  26
#define CH_B  16
#define CH_C  25
#define CH_D  4
#define CLK  33
#define LAT  2
#define OE   32

MatrixPanel_I2S_DMA *dma_display = nullptr;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nESP32 HUB75 LED Matrix POC");
  Serial.println("Initializing DMA display...");
  
  // Configure pin mapping
  HUB75_I2S_CFG::i2s_pins _pins = {R1, G1, B1, R2, G2, B2, CH_A, CH_B, CH_C, CH_D, -1, LAT, OE, CLK};
  
  // Configure matrix (64x32, single panel)
  HUB75_I2S_CFG mxconfig(
    64,           // width
    32,           // height
    1,            // chain length (single panel)
    _pins         // pin mapping
  );
  
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  
  // Start the DMA display
  if (!dma_display->begin()) {
    Serial.println("ERROR: Failed to allocate I2S DMA memory!");
    while (1) delay(1000);
  }
  
  Serial.println("Display initialized successfully!");
  dma_display->setBrightness8(128);  // 50% brightness
  dma_display->clearScreen();
}

void loop() {
  // Test RED
  Serial.println("Testing RED...");
  dma_display->fillScreenRGB888(255, 0, 0);
  delay(2000);
  
  // Test GREEN
  Serial.println("Testing GREEN...");
  dma_display->fillScreenRGB888(0, 255, 0);
  delay(2000);
  
  // Test BLUE
  Serial.println("Testing BLUE...");
  dma_display->fillScreenRGB888(0, 0, 255);
  delay(2000);
  
  // Test WHITE
  Serial.println("Testing WHITE...");
  dma_display->fillScreenRGB888(255, 255, 255);
  delay(2000);
  
  // Test BLACK
  Serial.println("Testing BLACK...");
  dma_display->fillScreenRGB888(0, 0, 0);
  delay(2000);
}

