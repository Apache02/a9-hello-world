#include "uart.h"
#include "wdt.h"

void kprint(const char *message) {
    while (*message != '\0') {
        uart_write_byte(UART2_PORT, *message++);
    }
}

void kprint_256() {
    for (int i = 0; i < 256; i++) {
        char c = (char) i;
        uart_write_byte(UART2_PORT, c);
    }
}

void kprint_uart(int uport, const char *message) {
    while (*message != '\0') {
        uart_write_byte(uport, *message++);
    }
}


void usleep(unsigned int usec) {
    for (unsigned int i = 0; i < usec; i++) {
        // 18 instructions
        // 180 MHz
        for (int i = 0; i < 180000000 / 1000000 / 18; i++) {
            asm volatile ("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;");
        }
    }
}

void sleep(unsigned int sec) {
    usleep(sec * 1000000);
}

int main() {
    uart_hw_init(UART1_PORT);
    uart_hw_init(UART2_PORT);

    kprint("Hello, World!!1\r\n");
    sleep(1);

    for (int i = 0; i < 5; i++) {
        kprint_uart(UART1_PORT, "Hello UART1\r\n");
        kprint_uart(UART2_PORT, "Hello UART2\r\n");
        sleep(1);
    }

    wdt_reboot();

    return 0;
}
