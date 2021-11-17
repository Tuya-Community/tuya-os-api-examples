#include "uni_log.h"
#include "tuya_hal_mutex.h"
#include "uni_thread.h"
#include "tuya_hal_system.h"
#include "tuya_hal_thread.h"

MUTEX_HANDLE my_mutex;
int demo_value = 0;

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
* @brief mutex task 1 handle
*
* @param[in] none
* @return none
*/
void mutex_task_1_handle(void) 
{
    for (;;) {
        PR_NOTICE("task 1 wait unlock");
        tuya_hal_mutex_lock(my_mutex);
        PR_NOTICE("task 1 lock");

        demo_value = demo_value + 2;
        PR_NOTICE("task 1 demo value:%d", demo_value);
        tuya_hal_system_sleep(3000);

        tuya_hal_mutex_unlock(my_mutex);
        PR_NOTICE("task 1 unlock");
        tuya_hal_system_sleep(100);
    }
}

/**
* @brief mutex task 2 handle
*
* @param[in] none
* @return none
*/
void mutex_task_2_handle(void) 
{
    for (;;) {
        PR_NOTICE("task 2 wait unlock");
        tuya_hal_mutex_lock(my_mutex);
        PR_NOTICE("task 2 lock");

        demo_value--;
        PR_NOTICE("task 2 demo value:%d", demo_value);
        tuya_hal_system_sleep(5000);

        tuya_hal_mutex_unlock(my_mutex);
        PR_NOTICE("task 2 unlock");
        tuya_hal_system_sleep(100);
    }
}

/**
* @brief mutex task init
*
* @param[in] none
* @return none
*/
void mutex_task_init(void)
{
    tuya_hal_mutex_create_init(&my_mutex);
    tuya_hal_thread_create(NULL, "task 1", 64*8, TRD_PRIO_5, mutex_task_1_handle, NULL);
    tuya_hal_thread_create(NULL, "task 2", 64*8, TRD_PRIO_5, mutex_task_2_handle, NULL);
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    mutex_task_init();

    return OPRT_OK;
}
