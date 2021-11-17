#include <stdlib.h>
#include "uni_log.h"
#include "tuya_hal_system.h"
#include "tuya_cloud_error_code.h"

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
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    int *str;

    PR_NOTICE("******************** memory demo begin ********************");
    str = tuya_hal_system_malloc(5*sizeof(int));
    if (NULL == str) {
        PR_ERR("tuya_hal_system_malloc is error");
        return;
    }
    PR_NOTICE("memset");
    memset(str, 0, 5*sizeof(int));
    str[0] = 300;
    str[1] = 200;
    PR_NOTICE("str address: %x", str);
    PR_NOTICE("str[0]:%d, str[1]:%d, str[2]:%d", str[0], str[1], str[2]);
    if (NULL != str) {
        PR_NOTICE("memory will free");
        tuya_hal_system_free(str);
        str = NULL;
        PR_NOTICE("******************** memory demo end ********************");
    }

    return OPRT_OK;
}
