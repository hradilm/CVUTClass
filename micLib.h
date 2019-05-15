#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void DisplayText(String strText)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(strText);
  display.display();    
}

void DisplayInit()
{
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done  
  display.clearDisplay();
  display.display();    
}

String strIP = "";

void APCallback(WiFiManager * mgr)
{
  DisplayText("Switched\nto\nWiFi\nManager\n");
}

void SaveCallback()
{
  DisplayText("Saving\nConfig\n");
}

void WiFiInit()
{
  WiFiManager wifiManager;
  wifiManager.setAPCallback(APCallback);
  wifiManager.setSaveConfigCallback(SaveCallback);
  wifiManager.autoConnect("AutoConnectAP");  
  
  strIP = WiFi.localIP().toString();
}