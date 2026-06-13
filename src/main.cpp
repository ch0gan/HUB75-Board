#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <FastLED.h>

// Your GPIO pin mapping
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

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32

MatrixPanel_I2S_DMA *dma_display = nullptr;

uint16_t time_counter = 0, cycles = 0;
CRGBPalette16 palettes[] = {HeatColors_p, LavaColors_p, RainbowColors_p, RainbowStripeColors_p, CloudColors_p};
CRGBPalette16 currentPalette = palettes[0];
CRGB currentColor;

CRGB ColorFromCurrentPalette(uint8_t index = 0, uint8_t brightness = 255, TBlendType blendType = LINEARBLEND) {
  return ColorFromPalette(currentPalette, index, brightness, blendType);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\nESP32 HUB75 LED Matrix - RGBW POC + Plasma Effect");
  Serial.println("Initializing DMA display...");
  
  HUB75_I2S_CFG::i2s_pins _pins = {R1, G1, B1, R2, G2, B2, CH_A, CH_B, CH_C, CH_D, -1, LAT, OE, CLK};
  
  HUB75_I2S_CFG mxconfig(
    PANEL_WIDTH,
    PANEL_HEIGHT,
    1,
    _pins
  );
  
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  
  if (!dma_display->begin()) {
    Serial.println("ERROR: Failed to allocate I2S DMA memory!");
    while (1) delay(1000);
  }
  
  Serial.println("Display initialized successfully!");
  dma_display->setBrightness8(128);
  dma_display->clearScreen();
  
  // RGBW Test sequence on boot
  Serial.println("Running RGBW test...");
  
  Serial.println("  RED");
  dma_display->fillScreenRGB888(255, 0, 0);
  delay(2000);
  
  Serial.println("  GREEN");
  dma_display->fillScreenRGB888(0, 255, 0);
  delay(2000);
  
  Serial.println("  BLUE");
  dma_display->fillScreenRGB888(0, 0, 255);
  delay(2000);
  
  Serial.println("  WHITE");
  dma_display->fillScreenRGB888(255, 255, 255);
  delay(2000);
  
  Serial.println("  BLACK");
  dma_display->fillScreenRGB888(0, 0, 0);
  delay(1000);
  
  Serial.println("Starting Plasma Effect...");
  currentPalette = RainbowColors_p;
}

void loop() {
  // Plasma effect
  for (int x = 0; x < PANEL_WIDTH; x++) {
    for (int y = 0; y < PANEL_HEIGHT; y++) {
      int16_t v = 128;
      uint8_t wibble = sin8(time_counter);
      v += sin16(x * wibble * 3 + time_counter);
      v += cos16(y * (128 - wibble) + time_counter);
      v += sin16(y * x * cos8(-time_counter) / 8);
      
      currentColor = ColorFromPalette(currentPalette, (v >> 8));
      dma_display->drawPixelRGB888(x, y, currentColor.r, currentColor.g, currentColor.b);
    }
  }
  
  ++time_counter;
  ++cycles;
  
  // Change palette every 1024 cycles
  if (cycles >= 1024) {
    time_counter = 0;
    cycles = 0;
    currentPalette = palettes[random(0, sizeof(palettes) / sizeof(palettes[0]))];
    Serial.println("Palette changed");
  }
}

