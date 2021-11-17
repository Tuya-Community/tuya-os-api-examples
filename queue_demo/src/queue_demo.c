#include "uni_log.h"
#include "tuya_hal_thread.h"
#include "uni_queue.h"
#include "uni_thread.h"

P_QUEUE_CLASS my_queue;

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
* @brief queue demo task
*
* @param[in] none
* @return none
*/
void queue_task(void)
{
    unsigned char ret;
    int i;
    int in_number[] = {31, 32, 33, 5, 7};
    int out_number[5];

    /* create queue */
    my_queue = CreateQueueObj(5, SIZEOF(int));
    if (NULL == my_queue) {
        PR_ERR("creat queue failed.");
        return;
    }
    PR_NOTICE("create queue success.");
    PR_NOTICE("cur queue num: %d", GetCurQueNum(my_queue));
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* in queue */
    ret = InQueue(my_queue, in_number, 5);
    if (1 != ret) {
        PR_ERR("in queue failed.");
    } else {
        PR_NOTICE("queue input 5 numbers success.");
    }
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* out queue */
    ret = OutQueue(my_queue, out_number, 1);
    if (1 != ret) {
        PR_ERR("out queue failed.");
    } else {
        PR_NOTICE("queue out 1 number success.");
    }
    PR_NOTICE("out_number[0]: %d", out_number[0]);
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* GetQueueMember */
    ret = GetQueueMember(my_queue, 1, out_number, 4);
    if (1 != ret) {
        PR_ERR("queue get member failed.");
    } else {
        PR_NOTICE("GetQueueMember success.");
    }
    for (i=0; i<4; i++) {
        PR_NOTICE("out_number[%d]:%d", i, out_number[i]);
    }
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* delete 1 queue number */
    ret = DelQueueMember(my_queue, 1);
    if (1 != ret) {
        PR_ERR("delete queue number error.");
    } else {
        PR_NOTICE("delete queue number success.");
    }
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* clean queue */
    ret = ClearQueue(my_queue);
    if (1 != ret) {
        PR_ERR("clean queue failed.");
    } else {
        PR_NOTICE("clean queue success.");
    }
    PR_NOTICE("cur free num: %d", GetCurFreeQueNum(my_queue));

    /* release queue */
    ReleaseQueueObj(my_queue);
    PR_NOTICE("queue is release.");
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    queue_task();

    return OPRT_OK;
}
