#include "uni_log.h"
#include "uni_thread.h"
#include "tuya_error_code.h"
#include "tuya_hal_system.h"

THREAD_HANDLE thread_demo_handle = NULL;
static thread_demo_count = 0;

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
* @brief thread demo task handle
*
* @param[in] none
* @return none
*/
void thread_demo_task_func(void)
{
    OPERATE_RET op_ret = OPRT_OK;

    for (;;) {
        PR_NOTICE("thread demo is running, count: %d", thread_demo_count);
        if (thread_demo_count >= 10) {
            break;
        }

        thread_demo_count++;
        tuya_hal_system_sleep(1000);
    }

    PR_NOTICE("thread demo task will release");
    op_ret = tuya_hal_thread_release(thread_demo_handle);
    if (OPRT_OK != op_ret) {
        PR_ERR("release thread demo task failed, err_num:%d", op_ret);
        return;
    }
}

/**
* @brief thread demo
*
* @param[in] none
* @return none
*/
void thread_demo_init(void) 
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = tuya_hal_thread_create(&thread_demo_handle, "thread demo", 64*8, TRD_PRIO_4, thread_demo_task_func, NULL);
    if (op_ret != OPRT_OK) {
        PR_ERR("creat thread demo task failed, err_num:%d", op_ret);
        return;
    }
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    thread_demo_init();

    return OPRT_OK;
}
