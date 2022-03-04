#include "tuya_timer.h"
#include "uni_log.h"

tuya_timer_t* demo_timer_init(tuya_timer_port_t timer_port, \
                            tuya_timer_mode_t timer_mode, \
                            tuya_timer_isr_cb callback, \
                            void *arg);

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
* @brief timer callback function
*
* @param[in] arg: function arg
* @return none
*/
static void timer_cb(void *arg)
{
    PR_NOTICE("this is timer %d callback", (uint8_t)arg);
}

/**
* @brief device initialization interface 
*
* @param[in] none
* @return none
*/
void device_init(void)
{
    uint8_t tiemr_arg = 0;
    tuya_timer_t *timer0_handle = demo_timer_init(TUYA_TIMER0, TUYA_TIMER_MODE_PERIOD, timer_cb, &tiemr_arg);
    if (NULL != timer0_handle) {
        tuya_timer_start(timer0_handle, 1000*1000);
    } 
}

/**
* @brief timer init function 
*
* @param[in] timer_port: timer port, this parameter must be a value of @ref TUYA_TIMERx.
* @param[in] timer_mode: timer mode, this parameter must be a value of @ref TUYA_TIMER_MODE_ONCE or TUYA_TIMER_MODE_PERIOD.
* @param[in] callback: timer callback function
* @param[in] arg: callback function arg
* @return timer handle
*/
tuya_timer_t* demo_timer_init(tuya_timer_port_t timer_port, \
                            tuya_timer_mode_t timer_mode, \
                            tuya_timer_isr_cb callback, \
                            void *arg)
{
    tuya_timer_t *timer_handle = NULL;

    timer_handle = (tuya_timer_t *)tuya_driver_find(TUYA_DRV_TIMER, timer_port);
    if (NULL == timer_handle) {
        PR_ERR("find timer driver error");
        return NULL;
    }

    TUYA_TIMER_CFG(timer_handle, timer_mode, callback, 0);
    tuya_timer_init(timer_handle);

    return timer_handle;
}
