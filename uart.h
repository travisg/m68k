#pragma once

void uart_putc(char c);
void uart_early_init(void);
void uart_init(void);
void uart_puts(const char *s);

void uart_put_hex(unsigned int x);

