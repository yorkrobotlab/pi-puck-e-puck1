#include <libpic30.h>
#include <uart.h>
#include "uart2.h"

// Use UART2 for stdio
int __C30_UART = 2;

void uart2_init() {
    // Set up UART2
    U2BRG = 7; // 115200 bps
    U2MODE = UART_EN & UART_IDLE_STOP & UART_DIS_WAKE & UART_DIS_LOOPBACK & UART_DIS_ABAUD & UART_NO_PAR_8BIT & UART_1STOPBIT;
    U2STA = UART_INT_TX_BUF_EMPTY & UART_TX_PIN_NORMAL & UART_TX_ENABLE & UART_INT_RX_BUF_FUL & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR;
}
