#include "uni_log.h"
#include "tuya_led.h"
#include "tuya_pin.h"

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
    OPERATE_RET op_ret = OPRT_OK;
    LED_HANDLE led_handle;

    op_ret = tuya_create_led_handle(TUYA_PA16, TRUE, &led_handle);
    if (OPRT_OK != op_ret) {
        PR_ERR("key_init err:%d", op_ret);
        return;
    }

    tuya_set_led_light_type(led_handle, OL_FLASH_LOW, 500, 3500);

    return;
}
