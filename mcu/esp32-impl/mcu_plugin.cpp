#include "../mcu_plugin.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "log.h"

namespace
{
    const char *ssid = "The Box";
    const char *password = "Westinghouse37";
    AsyncWebServer server(80);
}

namespace Gagguino
{
    bool MCUPlugin::Init()
    {
        WiFi.mode(WIFI_STA);
        WiFi.setHostname("Gaggiuino Core");
        WiFi.begin(ssid, password);

        // Wait for connection
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
        }

        LOG_INFO("WiFi connected, IP: %s", WiFi.localIP().toString());

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", "Hi! I am ESP32."); });

        AsyncElegantOTA.begin(&server);
        server.begin();
        return true;
    }

    void MCUPlugin::Tick()
    {
    }
}