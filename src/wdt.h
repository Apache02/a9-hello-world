#ifndef _WDT_H_
#define _WDT_H_


void wdt_init(void);

void wdt_ping(void);

void wdt_set(unsigned long period);

void wdt_up(void);

void wdt_down(void);

void wdt_reboot(void);


#endif // _WDT_H_
