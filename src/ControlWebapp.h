#ifndef CONTROL_WEBAPP_H
#define CONTROL_WEBAPP_H
#include "Webapp.h"
#include "timer.js.h"

class ControlWebapp : public Webapp
{
public:
  ControlWebapp(EthernetServer *server) : Webapp(server)
  {
  }
  void setTimerPin(uint8_t pin);

protected:
  void handler(HttpMethod method, String *path);
  void setOff();
  void setOn(unsigned long timer);
  void onLoop();
  unsigned long getDuration();
  unsigned long getRest();
  void htmlButtonForm(String action, String label);

  uint8_t timerPin;
  unsigned long timerDuration;
  unsigned long timeOn = 0;
  bool isOn = false;
};

#endif