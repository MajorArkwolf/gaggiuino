#include "../mcu_plugin.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "log.h"

/**
 * @brief Define SSID_NAME and SSID_PASSWORD inside of
 * extra_defines.ini. It should look something like this
 * [extra]
 *   build_flags =
 *      -DDREAM_STEAM_DISABLED
 *      -DSSID_NAME='"The Wifi Name"'
 *      -DSSID_PASSWORD='"WifiPassword123"'
 */

#ifndef SSID_NAME
#define SSID_NAME "WirelessName"
#endif

#ifndef SSID_PASSWORD
#define SSID_PASSWORD "WirelessPassword"
#endif

#ifndef CORE_HOSTNAME
#define CORE_HOSTNAME "Gaggiuino Core"
#endif

namespace
{
    const char *ssid = SSID_NAME;
    const char *password = SSID_PASSWORD;
    AsyncWebServer server(80);
}

namespace Gagguino
{
    bool MCUPlugin::Init()
    {
        WiFi.mode(WIFI_STA);
        WiFi.setHostname(CORE_HOSTNAME);
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
