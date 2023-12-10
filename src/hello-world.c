#include "drivers/uart.h"
#include "drivers/wdt.h"

void kprint(const char *message) {
    while (*message != '\0') {
        uart_write_byte(UART2_PORT, *message++);
    }
}

void kputchar(const char c) {
    uart_write_byte(UART2_PORT, c);
}

void kputhex(const char c) {
    char cc;
    char d;
    d = ((c >> 4) & 0x0F) + '0';
    if (d > '9') d += 'A' - '0' - 10;
    kputchar(d);
    d = ((c) & 0x0F) + '0';
    if (d > '9') d += 'A' - '0' - 10;
    kputchar(d);
    kputchar(' ');
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

void msleep(unsigned int ms) {
    usleep(ms * 1000);
}

void sleep(unsigned int sec) {
    usleep(sec * 1000000);
}

void hw_reboot(void) {
    wdt_set(10);
    wdt_up();
    while (1);
}

void *memset(void *s, int c, unsigned long count) {
    char *xs = (char *) s;

    while (count--)
        *xs++ = c;

    return s;
}

void memclr(void *ptr, unsigned int length) {
    memset(ptr, 0, length);
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2++)
        if (*s1++ == 0)
            return (0);
    return (*(unsigned char *) s1 - *(unsigned char *) --s2);
}

char rx_buffer[128];
unsigned long rx_length;

int main() {
    uart_hw_init(UART1_PORT);
    uart_hw_init(UART2_PORT);

    memclr(rx_buffer, sizeof(rx_buffer));

    kprint("Hello, World!!1\r\n");
    kprint("> ");

    rx_length = 0;

    int i = 0;
    while (i++ < 1000000) {
        int c = uart_read_byte(UART2_PORT);
        if (c < 0) {
            usleep(1);
        } else {
            if (c == '\n' || c == '\r') {
                if (rx_length > 0) {
                    kprint("\r\ncommand: ");
                    kprint(rx_buffer);
                }
                kprint("\r\n");

                if (strcmp(rx_buffer, "reboot") == 0) {
                    break;
                } else if (strcmp(rx_buffer, "hello") == 0) {
                    kprint_uart(UART1_PORT, "Hello UART1\r\n");
                    kprint_uart(UART2_PORT, "Hello UART2\r\n");
                    sleep(1);
                }

                // reset buffer
                rx_length = 0;
                rx_buffer[0] = 0;

                kprint("> ");
            } else {
                i = 0;
                kputchar(c);

                rx_buffer[rx_length++] = c;
                rx_buffer[rx_length] = 0;
                if (rx_length > sizeof(rx_buffer) - 2) {
                    kprint("\r\nrx overflow\r\n");
                    break;
                }
            }
        }
    }

    kprint("\r\nreboot system\r\n");
    msleep(100);
    hw_reboot();

    return 0;
}
