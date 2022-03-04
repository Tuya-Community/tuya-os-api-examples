#include "tuya_uart.h"
#include "uni_log.h"
#include "tuya_driver.h"

#define UART_NONBLOCK_EN    0 // 1: Set the serial port to non-blocking
#define BUF_SIZE    256

tuya_uart_t * uart0;

void uart0_init(void);
void uart_set(tuya_uart_t *uart, 
              tuya_uart_baudrate_t baudrate, 
              tuya_uart_databits_t data_bits, 
              tuya_uart_stopbits_t stop_bits, 
              tuya_uart_parity_t parity);

/**
* @brief application initialization interface
*
* @param[in] none
* @return none
*/
void app_init(void)
{
    return;
}

/**
* @brief thread demo task handle
*
* @param[in] none
* @return none
*/
void device_init(void)
{
    int32_t op_ret;
    uint8_t uart0_rx_buf[BUF_SIZE];

    uart0_init();

    tuya_uart_write(uart0, "hello uart0, baudrate 115200\r\n", 31);

    for (;;) {
        op_ret = tuya_uart_read(uart0, uart0_rx_buf, BUF_SIZE);
        if (op_ret>0) {
            tuya_uart_write(uart0, uart0_rx_buf, op_ret);
        } else {
            tuya_uart_write(uart0, "no recv data\r\n", 15);
            tuya_hal_system_sleep(1000);
        }
    }

    return;
}

/**
* @brief init uart0
*
* @param[in] none
* @return none
*/
void uart0_init(void)
{
    int32_t op_ret;
    
/* TY_UART0:
 *      TX <-> TX1
 *      RX <-> RX1
 * TY_UART1:
 *      TX <-> TX2
 *      RX <-> RX2
 */
    uart0 = (tuya_uart_t *)tuya_driver_find(TUYA_DRV_UART, TY_UART0);
    if (NULL == uart0) {
        PR_DEBUG("find uart0 fail");
        return;
    }

#if UART_NONBLOCK_EN
    TUYA_UART_8N1_CFG(uart0, TUYA_UART_BAUDRATE_115200, 256, (TUYA_DRV_INT_RX_FLAG | TUYA_DRV_NONBLOCK_FLAG));
#else
    TUYA_UART_8N1_CFG(uart0, TUYA_UART_BAUDRATE_115200, 256, TUYA_DRV_INT_RX_FLAG);
#endif

    op_ret = tuya_uart_init(uart0);
    if (OPRT_OK != op_ret) {
        PR_ERR("uart init fail, error code: %d", op_ret);
    }

    return;
}

/**
* @brief set uart baudrate
*
* @param[in] uart: uart handle
* @param[in] baudrate: uart baudrate, this parameter must be a value of @ref TUYA_UART_BAUDRATE_xxx
* @param[in] data_bits: uart data bits, this parameter must be a value of @ref TUYA_UART_DATA_BITx
* @param[in] stop_bits: uart stop bits, this parameter must be a value of @ref TUYA_UART_STOP_BITx
* @param[in] parity: uart parity bits, this parameter must be a value of @ref TUYA_UART_PARITY_xxx
* @return none
*/
void uart_set(tuya_uart_t *uart, 
              tuya_uart_baudrate_t baudrate, 
              tuya_uart_databits_t data_bits, 
              tuya_uart_stopbits_t stop_bits, 
              tuya_uart_parity_t parity)
{
    int32_t op_ret;

    uart->cfg.baudrate = baudrate;
    uart->cfg.databits = data_bits;
    uart->cfg.stopbits = stop_bits;
    uart->cfg.parity = parity;

    op_ret = tuya_uart_control(uart, TUYA_DRV_CONFIG_CMD, &(uart->cfg));
    if (OPRT_OK != op_ret) {
        PR_ERR("uart0 cfg baud failed, error code: %d", op_ret);
    }
}
