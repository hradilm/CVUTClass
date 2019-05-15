#include <OneWire.h>
#include <DallasTemperature.h>
#include <micLib.h>

#define ONE_WIRE_BUS 2
#define BUTTON_PIN 0

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);

String strUnit = "C";
DeviceAddress termAddr;
int iMillisToWaitTotal = 0;
int iDeviceResolution = 12;

// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);

  DisplayInit();

  DS18B20.begin();
  DS18B20.getAddress(termAddr, 0);

  iMillisToWaitTotal = DS18B20.millisToWaitForConversion(0);
  DS18B20.setResolution(termAddr, iDeviceResolution);

  pinMode(BUTTON_PIN, INPUT);      // set pin as input  
}

int iLastButtonState = 1;

void CheckButton()
{
  int iButtonState = digitalRead(BUTTON_PIN); 
  if (iLastButtonState != iButtonState)
  {
    iLastButtonState = iButtonState;
    if (iButtonState == 0)
    {
      if (strUnit == "C")
        strUnit = "F";
      else
        strUnit = "C";
    }
  }
}

// runs over and over again
void loop() {
  float temp = 0.0;
  float tempConverted = 0.0;
  DS18B20.setWaitForConversion(false);
  DS18B20.requestTemperaturesByAddress(termAddr); 
  DS18B20.setWaitForConversion(true);

  unsigned long tempStart = millis();
  int tempDelay = iMillisToWaitTotal / (1 << (12 - iDeviceResolution));
  while(millis() - tempStart < tempDelay) {
    CheckButton();
  }
  
  temp = DS18B20.getTempC(termAddr);
  if (temp == 85.0 || temp == (-127.0))
  {
    DisplayText("Termometer not working\n");
    return;
  }

  tempConverted = temp;
  if (strUnit == "F")
    tempConverted = DallasTemperature::toFahrenheit(temp);
  
  DisplayText((String) tempConverted + " " + strUnit);
}
