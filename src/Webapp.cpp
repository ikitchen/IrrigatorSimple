#include "Webapp.h"
//TODO: implement these limitations:
#define MAXLEN_METHOD 1
#define MAXLEN_PATH 8

Webapp::Webapp(EthernetServer *server)
{
    this->server = server;
}

void Webapp::sendHeader()
{
    // send a standard http response header
    client->println("HTTP/1.1 200 OK");
    client->println("Content-Type: text/html");
    client->println("Connection: close");
    client->println();
}

void Webapp::redirect(String loc)
{
    // send a standard http response header
    client->println("HTTP/1.1 301 Moved Permanently");
    client->println("Connection: close");
    client->println("Location: " + loc);

    client->println();
}

HttpMethod Webapp::httpMethodFromString(String methodStr)
{
    if (methodStr == "G")
    {
        return GET;
    }
    if (methodStr == "P") //yes, i am aware of PUT/PATCH etc, but i want to use less RAM
    {
        return POST;
    }
    if (methodStr == "O")
    {
        return OPTIONS;
    }
    return UNKNOWN;
}

void Webapp::loop()
{
    onLoop();
    // listen for incoming clients
    EthernetClient client = this->server->available();
    if (client)
    {
        // Serial.println("new client");
        // an http request ends with a blank line
        bool currentLineIsBlank = true;

        String method;
        bool readingMethod = true;
        String path;
        bool readingPath = false;

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();

                if (readingMethod)
                {
                    if (c == ' ')
                    {
                        readingMethod = false;
                        readingPath = true;
                    }
                    else
                    {
                        if (method.length() < MAXLEN_METHOD)
                        {
                            method += c;
                        }
                    }
                }
                else if (readingPath)
                {
                    if (c == ' ')
                    {
                        readingPath = false;
                    }
                    else
                    {
                        if (path.length() < MAXLEN_PATH)
                        {
                            path += c;
                        }
                    }
                }

                // Serial.write(c);
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank)
                {
                    HttpMethod httpMethod = httpMethodFromString(method);
                    this->client = &client;
                    handler(httpMethod, &path);
                    break;
                }
                if (c == '\n')
                {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        // Serial.println("client disconnected");
    }
}
