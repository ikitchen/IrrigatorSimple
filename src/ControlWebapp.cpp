#include "ControlWebapp.h"

#define SECONDS * 1000
#define MINUTES * 60000
String js =
    "<script>"
    "var end=Date.now()+_e;"
    "setInterval(function () {"
    "var elapsed=end-Date.now();"
    "if(elapsed<=0){"
    /**/ "window.location.reload();"
    "}"
    "else{"
    /**/ "document.getElementById('elapsed').innerText=(elapsed/1000)|0;"
    "}"
    "}, 1000)"
    "</script>";

void ControlWebapp::onLoop()
{
    if (isOn)
    {
        digitalWrite(13, HIGH);
        unsigned long duration = getDuration();
        if (duration > timerDuration)
        {
            setOff();
        }
    }
    else
    {
        digitalWrite(13, LOW);
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
            client->println("<p>Currently on</p>");
            client->println("<p>Elapsed: <span id=elapsed>--</span>s</p>");
            htmlButtonForm("/off", "Off");
            client->println("<script>var _e=" + String(getRest()) + ";</script>");
            client->println(js);
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
    client->println("<form method=post action=" + action + "><button>" + label + "</button></form>");
}