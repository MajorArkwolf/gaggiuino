
#include "peripherals/internal_watchdog.h"
#include "Esp.h"
/*Checking whether system is booting after a hard reset initiated by the internal watchdog.*/
void iwdcInit(void)
{
    // IWDC init
    //if (IWatchdog.isReset())
    //{
    //    lcdShowPopup("WATCHDOG RESTARTED");
    //    IWatchdog.clearReset();
    //}
    //IWatchdog.begin(3000000);
    //LOG_INFO("Internal watchdog Init");
}

void watchdogReload(void)
{
    //ESP.restart();
}
