#ifndef INTERNALWATCHDOG_H
#define INTERNALWATCHDOG_H

/*Checking whether system is booting after a hard reset initiated by the internal watchdog.*/
void iwdcInit(void);

void watchdogReload(void);
#endif
