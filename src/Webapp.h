#ifndef WEBAPP_H
#define WEBAPP_H
#include <Ethernet.h>

enum HttpMethod
{
  GET,
  POST,
  OPTIONS,
  UNKNOWN
};

class Webapp
{
private:
  EthernetServer *server;

protected:
  virtual void handler(HttpMethod method, String *path);
  virtual void onLoop() {};
  HttpMethod httpMethodFromString(String methodStr);
  void sendHeader();
  void redirect(String loc);

public:
  EthernetClient *client;
  Webapp(EthernetServer *server);
  void loop();
};

#endif