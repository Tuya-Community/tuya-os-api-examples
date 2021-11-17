#include "tuya_hal_system.h"
#include "uni_log.h"
#include "uni_thread.h"
#include "sys_timer.h"

TIMER_ID sw_timer_id;
static int sw_run_count = 0;

/**
* @brief application initialization interface
*
* @param[in] none
* @return none
*/
VOID app_init(VOID) 
{
    return;
}

/**
* @brief software timer callback function
*
* @param[in] timerID: software timer id
* @param[in] pTimerArg: software timer arg
* @return none
*/
void sw_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    OPERATE_RET op_ret = OPRT_OK;

    PR_NOTICE("------this is timer %d callback, count: %d", timerID, sw_run_count);
    sw_run_count++;

    if (sw_run_count >= 10) {
        if (IsThisSysTimerRun(sw_timer_id)) {
            op_ret = sys_stop_timer(sw_timer_id);
            if (OPRT_OK != op_ret) {
                PR_ERR("sys stop timer failed, error code %d", op_ret);
                return;
            }
            PR_NOTICE("timer %d is stop.", sw_timer_id);
        }
    }
}

/**
* @brief software timer task handle
*
* @param[in] none
* @return none
*/
void sw_timer_task(void)
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = sys_add_timer(sw_timer_cb, NULL, &sw_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys add timer failed, error code %d", op_ret);
        return;
    }
    PR_NOTICE("timer add success, timer id: %d.", sw_timer_id);

    op_ret = sys_start_timer(sw_timer_id, 2000, TIMER_CYCLE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys start timer failed, error code %d", op_ret);
        return;
    }
    PR_NOTICE("timer %d start success.", sw_timer_id);
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    sw_timer_task();

    return OPRT_OK;
}
