#define _TUYA_DEVICE_GLOBAL

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
* @brief log print demo
*
* @param[in] none
* @return none
*/
void log_printf_demo(void)
{
    PR_NOTICE("*************************************************");
    SetLogManageAttr(TY_LOG_LEVEL_NOTICE);
    PR_NOTICE("log level is NOTICE");
    PR_ERR("This is error log");
    PR_WARN("This is warn log");
    PR_NOTICE("This is notice log");
    PR_INFO("This is info log");
    PR_DEBUG("This is debug log");
    PR_TRACE("This is trace log");
    PR_NOTICE("*************************************************");
    SetLogManageAttr(TY_LOG_LEVEL_DEBUG);
    PR_NOTICE("log level is DEBUG");
    PR_ERR("This is error log");
    PR_WARN("This is warn log");
    PR_NOTICE("This is notice log");
    PR_INFO("This is info log");
    PR_DEBUG("This is debug log");
    PR_TRACE("This is trace log");
    PR_NOTICE("*************************************************");
}

/**
* @brief device initialization interface
*
* @param[in] none
* @return OPRT_OK: success, others: please refer to tuya error code description document
*/
OPERATE_RET device_init(VOID) 
{
    log_printf_demo();

    return OPRT_OK;
}
