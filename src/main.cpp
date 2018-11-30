#include <SPI.h>
#include <Arduino.h>
#include <Ethernet.h>
#include "ControlWebapp.h"
#include "config.h"

EthernetServer server(80);
ControlWebapp app(&server);

void setup()
{
  pinMode(13, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection and the server:
  Ethernet.begin(config_mac, config_ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("EETH");
    while (true)
    {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("ECAB");
  }

  server.begin();
}

void loop()
{
  app.loop();
}
