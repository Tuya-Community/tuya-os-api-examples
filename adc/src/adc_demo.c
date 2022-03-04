#include "tuya_adc.h"
#include "tuya_driver.h"
#include "uni_log.h"

tuya_adc_t *adc_init(tuya_adc_port_t adc_port);
uint16_t get_adc_value(tuya_adc_t *adc_handle);

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
    uint16_t volt = 0;
    tuya_adc_t *adc0_handle = NULL;

    adc0_handle = adc_init(TUYA_ADC2);
    for (;;) {
        volt = get_adc_value(adc0_handle);
        PR_NOTICE("adc voltage: %d", volt);
        tuya_hal_system_sleep(1000);
    }

    return;
}

/**
* @brief init adc driver
*
* @param[in] adc_port: this parameter must be a value of @ref TUYA_ADCx.
*                       TUYA_ADC0 --- P26
*                       TUYA_ADC1 --- P24
*                       TUYA_ADC2 --- P23
* @return adc handle
*/
tuya_adc_t *adc_init(tuya_adc_port_t adc_port)
{
    tuya_adc_t *adc_handle = NULL;
    adc_handle = (tuya_adc_t *)tuya_driver_find(TUYA_DRV_ADC, adc_port);
    if (NULL == adc_handle) {
        PR_ERR("find adc failed");
        return;
    }

    TUYA_ADC_CFG(adc_handle, adc_port, 0);
    tuya_adc_init(adc_handle);

    return adc_handle;
}

/**
* @brief get adc value
*
* @param[in] adc_handle: adc handle
* @return voltage value
*/
uint16_t get_adc_value(tuya_adc_t *adc_handle)
{
    uint16_t voltage = 0;
    uint16_t adc_value = 0;

    tuya_adc_convert(adc_handle, &adc_value, 1);
    voltage = (float)adc_value * 2400 / 4096;

    return voltage;
}
