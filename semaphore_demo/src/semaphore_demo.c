#include "uni_log.h"
#include "uni_thread.h"
#include "tuya_hal_system.h"
#include "tuya_hal_semaphore.h"

SEM_HANDLE my_sem;

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
* @brief semaphore wait task handle
*
* @param[in] none
* @return none
*/
void sem_wait_task_handle(void)
{
    for (;;) {
        tuya_hal_semaphore_wait(my_sem);
        PR_NOTICE("HELLO");
    }
}

/**
* @brief semaphore release task handle
*
* @param[in] none
* @return none
*/
void sem_release_task_handle(void)
{
    tuya_hal_semaphore_create_init(&my_sem, 0, 1);
    for (;;) {
        tuya_hal_semaphore_post(my_sem);
        PR_NOTICE("sem is posted.");
        tuya_hal_system_sleep(5000);
    }
}

/**
* @brief semaphore task init
*
* @param[in] none
* @return none
*/
void sem_task_init(void)
{
    tuya_hal_thread_create(NULL, "sem_release", 1024, TRD_PRIO_5, sem_release_task_handle, NULL);
    tuya_hal_thread_create(NULL, "sem_wait", 1024, TRD_PRIO_5, sem_wait_task_handle, NULL);
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    sem_task_init();

    return OPRT_OK;
}
