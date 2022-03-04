#include "uni_log.h"
#include "tuya_pin.h"

/**
* @brief gpio irq callback
*
* @param[in] none
* @return none
*/
static void pin_irq_cb(void)
{
    PR_NOTICE("This is irq callback");
}

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
* @brief device initialization interface
*
* @param[in] none
* @return none
*/
void device_init(void)
{
    int read_pin = 0;

    /* gpio output init */
    tuya_pin_init(TUYA_PA6, TUYA_PIN_MODE_OUT_PP_HIGH);
    tuya_pin_write(TUYA_PA6, TUYA_PIN_HIGH);

    /* gpio input init */
    tuya_pin_init(TUYA_PA7, TUYA_PIN_MODE_IN_PD);

    /* gpio input irq init*/
    tuya_pin_irq_init(TUYA_PA8, TUYA_PIN_MODE_IN_IRQ_FALL, pin_irq_cb, NULL);
    tuya_pin_irq_enable(TUYA_PA8);

    for (;;) {
        read_pin = tuya_pin_read(TUYA_PA7);
        PR_NOTICE("read_pin is %d", read_pin);

        tuya_hal_system_sleep(1000);
    }
}


