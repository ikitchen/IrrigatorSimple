#include "ControlWebapp.h"

#define SECONDS *1000
#define MINUTES *60000

void ControlWebapp::setTimerPin(uint8_t pin)
{
    timerPin = pin;
}
void ControlWebapp::onLoop()
{
    if (isOn)
    {
        digitalWrite(timerPin, HIGH);
        unsigned long duration = getDuration();
        if (duration > timerDuration)
        {
            setOff();
        }
    }
    else
    {
        digitalWrite(timerPin, LOW);
    }
}

unsigned long ControlWebapp::getDuration()
{
    return millis() - timeOn;
}

unsigned long ControlWebapp::getRest()
{
    return timerDuration - getDuration();
}

void ControlWebapp::handler(HttpMethod method, String *path)
{
    if (method == GET && path->equals("/"))
    {
        sendHeader();
        if (!isOn)
        {
            htmlButtonForm("/10s", "10 sec");
            htmlButtonForm("/1m", "1 min");
            htmlButtonForm("/3m", "3 min");
            htmlButtonForm("/10m", "10 min");
            htmlButtonForm("/30m", "30 min");
            htmlButtonForm("/1h", "1 hour");
        }
        if (isOn)
        {
            client->print(F("<p>Currently on</p>"));
            client->print(F("<p>Elapsed: <span id=elapsed>--</span>s</p>"));
            htmlButtonForm("/off", "Off");

            client->print(F("<script>var _e="));
            client->print(String(getRest()));
            client->print(F(";</script>"));

            client->print(F("<script>"));
            client->print(TIMER_JS);
            client->print(F("</script>"));
        }
    }

    if (method == POST)
    {
        if (path->equals("/off"))
        {
            setOff();
        }
        if (path->equals("/10s"))
        {
            setOn(10 SECONDS);
        }
        if (path->equals("/1m"))
        {
            setOn(1 MINUTES);
        }
        if (path->equals("/3m"))
        {
            setOn(3 MINUTES);
        }
        if (path->equals("/10m"))
        {
            setOn(10 MINUTES);
        }
        if (path->equals("/30m"))
        {
            setOn(30 MINUTES);
        }
        if (path->equals("/1h"))
        {
            setOn(60 MINUTES);
        }
        redirect("/");
    }
}

void ControlWebapp::setOff()
{
    isOn = false;
}

void ControlWebapp::setOn(unsigned long timer)
{
    isOn = true;
    timeOn = millis();
    timerDuration = timer;
}

void ControlWebapp::htmlButtonForm(String action, String label)
{
    client->print(F("<form method=post action="));
    client->print(action);
    client->print(F("><button>"));
    client->print(label);
    client->print(F("</button></form>"));
}