#include "tuya_pwm.h"
#include "tuya_pin.h"
#include "tuya_driver.h"
#include "uni_log.h"

tuya_pwm_t* demo_pwm_init(tuya_pwm_port_t tuya_pwm, \
                        tuya_pin_name_t pin, \
                        float frequency, \
                        float percent, \
                        tuya_pwm_polarity_t polarity);

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
    tuya_pwm_t* pwm0_handle = NULL;
    pwm0_handle = demo_pwm_init(TUYA_PWM0, TUYA_PA6, 1*1000, 0.1, TUYA_PWM_NEGATIVE);
    if (NULL != pwm0_handle) {
        tuya_pwm_start(pwm0_handle);
    } else {
        PR_NOTICE("PWM0 init error");
    }
}

/*
 * PWM0 <-> TUYA_PA6
 * PWM1 <-> TUYA_PA7
 * PWM2 <-> TUYA_PA8
 * PWM3 <-> TUYA_PA9
 * PWM4 <-> TUYA_PA24
 * PWM5 <-> TUYA_PA26
 */
/**
* @brief initialization pwm 
*
* @param[in] tuya_pwm: pwm port, this parameter must be a value of @ref PWMx 
* @param[in] pin: pwm pin, this parameter must be a value of @ref TUYA_PAx 
* @param[in] frequency: pwm frequency 
* @param[in] percent: pwm percent, range: 0~1.0
* @param[in] polarity: pwm polarity, this parameter must be a value of @ref TUYA_PWM_POSITIVE or TUYA_PWM_NEGATIVE 
* @return 
*/
tuya_pwm_t* demo_pwm_init(tuya_pwm_port_t tuya_pwm, \
                        tuya_pin_name_t pin, \
                        float frequency, \
                        float percent, \
                        tuya_pwm_polarity_t polarity)
{
    tuya_pwm_t* tuya_pwm_handle = NULL;
    tuya_pwm_handle = tuya_driver_find(TUYA_DRV_PWM, tuya_pwm);
//    TUYA_PWM_CFG(tuya_pwm_handle, pin, frequency, percent);

    tuya_pwm_handle->cfg.pin = pin;
    tuya_pwm_handle->cfg.polarity = polarity;
    tuya_pwm_handle->cfg.period_ns = (uint32_t)1000000000 / (frequency);
    tuya_pwm_handle->cfg.percent = percent;
    tuya_pwm_handle->cfg.pulse_ns = (uint32_t)((tuya_pwm_handle)->cfg.period_ns * (percent));

    tuya_pwm_init(tuya_pwm_handle);

    return tuya_pwm_handle;
}
