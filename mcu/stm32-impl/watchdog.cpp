#include "peripherals/internal_watchdog.h"
#include <Arduino.h>
#include <IWatchdog.h>
#include "lcd/lcd.h"
#include "log.h"

void iwdcInit(void)
{
    // IWDC init
    if (IWatchdog.isReset())
    {
        lcdShowPopup("WATCHDOG RESTARTED");
        IWatchdog.clearReset();
    }
    IWatchdog.begin(3000000);
    LOG_INFO("Internal watchdog Init");
}

void watchdogReload(void)
{
    IWatchdog.reload();
}
