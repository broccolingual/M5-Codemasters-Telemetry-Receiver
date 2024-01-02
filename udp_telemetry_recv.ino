#include <stdio.h>
#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include "udp_telemetry_recv.h"
#include "wifi_config.h"

// IP settings
const IPAddress deviceIP(192, 168, 0, 131);
const IPAddress deviceGateway(192, 168, 0, 1);
const IPAddress deviceNetmask(255, 255, 255, 0);
const IPAddress deviceDNS(192, 168, 0, 1);
const int devicePort = 20777;

WiFiUDP udp;                                         // UDP object
LGFX_Sprite sprite = LGFX_Sprite(&StickCP2.Display); // Sprite object

// Telemetry union
Telemetry currentTelemetry;
Telemetry pastTelemetry;

void setup()
{
  StickCP2.begin();                                                         // M5 initialization
  Serial.begin(115200);                                                     // Serial initialization
  sprite.createSprite(StickCP2.Display.width(), StickCP2.Display.height()); // Sprite initialization
  // Telemetry initialization
  memset(&currentTelemetry, 0, sizeof(Telemetry));
  memset(&pastTelemetry, 0, sizeof(Telemetry));
  // WiFi
  Serial.println("Connecting to WiFi network: " + String(WIFI_SSID));
  if (!WiFi.config(deviceIP, deviceGateway, deviceNetmask, deviceDNS)) // Setting IP
  {
    Serial.println("Failed to configure ip.");
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Starting WiFi
  while (WiFi.status() != WL_CONNECTED) // Waiting WiFi connection
  {
    delay(500);
  }
  Serial.print("WiFi connected: ");
  Serial.print(WiFi.localIP());
  // UDP
  udp.begin(devicePort); // Starting UDP
}

void loop()
{
  if (int len = udp.parsePacket())
  {
    udp.read(currentTelemetry.binary, sizeof(Telemetry));
    // Serial.printf("speed:%.2fm/s,gear:%.2f,rpm:%.2f\n", currentTelemetry.speed * 3.6, currentTelemetry.gear, currentTelemetry.engine_rate * 10);
  }

  if (currentTelemetry.gear != pastTelemetry.gear)
  {
    StickCP2.Speaker.tone(4000, 50);
  }
  // RPM percent settings
  float rpmPercent = currentTelemetry.engine_rate / currentTelemetry.max_rpm;
  int rpmColor = WHITE;
  if (rpmPercent > 0.875)
  {
    rpmColor = BLUE;
  }
  float argMax = 244;
  float argEnd = 148 + argMax * rpmPercent;
  if (argEnd > 360)
  {
    argEnd -= 360;
  }
  // Time settings
  int timeSec = (int)currentTelemetry.lap_time % 60;
  int timeMin = (int)currentTelemetry.lap_time / 60;
  // Gear settings
  char strGear[2];
  memset(strGear, '\0', sizeof(strGear));
  switch ((int)currentTelemetry.gear)
  {
  case 0:
    strGear[0] = 'N';
    break;
  case 10:
    strGear[0] = 'R';
    break;
  default:
    snprintf(strGear, sizeof(strGear), "%d", (int)currentTelemetry.gear);
  }
  // Display
  sprite.fillScreen(BLACK);
  sprite.drawArc(StickCP2.Display.width() / 2, StickCP2.Display.height() / 2 - 50, 62, 50, 148, 32, WHITE);
  sprite.fillArc(StickCP2.Display.width() / 2, StickCP2.Display.height() / 2 - 50, 62, 50, 148, argEnd, rpmColor);
  sprite.setTextDatum(4);
  sprite.setFont(&fonts::Font0);
  sprite.setTextColor(rpmColor);
  sprite.setCursor(StickCP2.Display.width() / 2 - 20, StickCP2.Display.height() / 2 - 50);
  sprite.setTextSize(8);
  sprite.print(strGear);
  sprite.setFont(&fonts::Font0);
  sprite.setTextColor(WHITE);
  sprite.setCursor(StickCP2.Display.width() / 2 - 40, StickCP2.Display.height() / 2);
  sprite.setTextSize(2);
  sprite.printf("%03dkm/h", (int)(currentTelemetry.speed * 3.6));
  sprite.setCursor(StickCP2.Display.width() / 2 - 30, StickCP2.Display.height() / 2 + 20);
  sprite.setTextSize(2);
  sprite.printf("%02d:%02d", timeMin, timeSec);
  sprite.pushSprite(0, 0);
  pastTelemetry = currentTelemetry;
}
