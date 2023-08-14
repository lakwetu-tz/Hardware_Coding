#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <SoftwareSerial.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//SoftwareSerial(A5,

struct {
  int volts;
  float current;
  int energy;
  float temp;
  int smoke;
  int fault;
  bool loads;
  bool protection;
} data;

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(3);
  tft.fillScreen(WHITE);
}

void loop(void) {
  data.volts = random(199, 233);
  data.temp = 28.0 + ((random(0, 10))/10.0);
  data.protection = true;
  writeDisplay();
  delay(5000);

}
unsigned long writeDisplay() {
  tft.fillScreen(WHITE);
  unsigned long start = micros();
  tft.setTextColor(BLACK);
  tft.setCursor(190, 5);
  tft.setTextSize(2);
  tft.println("09/08/2023");
  tft.setCursor(0, 40);
  tft.println("VOLTAGE   CURRENT   ENERGY");
  tft.setTextColor(RED);
  tft.setCursor(0, 60);
  tft.println(" " + String(data.volts) + "V      " + String(data.current) + "A     " + String(data.energy) + "kwh");
  tft.setCursor(0, 90);
  tft.setTextColor(BLACK);
  tft.println("TEMPERATURE   SMOKE  FAULT");
  tft.setTextColor(RED);
  tft.setCursor(0, 110);
  tft.println("  " + String(data.temp) + char(248) + "C       " + String(data.smoke) + "%     " + String(data.fault) + "");
  tft.setTextColor(BLACK);
  tft.println(" ");
  tft.print("LOAD:");
  tft.setTextColor(data.loads == true ? GREEN : RED);
  tft.println(data.loads == true ? "Enabled" : "Disabled");
  tft.println(" ");
  tft.setTextColor(BLACK);
  tft.print("VOLTAGE PROTECTION:");
  tft.setTextColor(data.protection == true ? GREEN : RED);
  tft.println(data.protection == true ? "Active" : "Passive");
  tft.println(" ");
  tft.setTextColor(BLACK);
  tft.print("CURRENT PROTECTION:");
  tft.setTextColor(data.protection == true ? GREEN : RED);
  tft.println(data.protection == true ? "Active" : "Passive");
  return micros() - start;
}
