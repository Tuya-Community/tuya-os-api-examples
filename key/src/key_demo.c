#include "uni_log.h"
#include "tuya_pin.h"
#include "tuya_key.h"

/**
* @brief key callback function
*
* @param[in] port: pressed button port
* @param[in] type: key trigger types
* @param[in] cnt: number of key presses, valid when press type is SEQ_KEY
* @return none
*/
static void key_callback(tuya_pin_name_t port,PUSH_KEY_TYPE_E type, INT_T cnt)
{
    switch (type) {
        case (NORMAL_KEY):
            PR_NOTICE("NORMAL_KEY: port:%d, cnt:%d", port, cnt);
        break;

        case (SEQ_KEY):
            PR_NOTICE("SEQ_KEY: port:%d, cnt:%d", port, cnt);
        break;

        case (LONG_KEY):
            PR_NOTICE("LONG_KEY: port:%d, cnt:%d", port, cnt);
        break;

        default: 
        PR_NOTICE("other type: port:%d, type:%d, cnt:%d", port, type, cnt);
        break;
    }
}

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
    KEY_USER_DEF_S key_def;

    op_ret = key_init(NULL, 0, 50);
    if (op_ret != OPRT_OK) {
        PR_ERR("key_init err:%d", op_ret);
        return;
    }

    memset(&key_def, 0, SIZEOF(key_def));
    key_def.port = TUYA_PA9;
    key_def.long_key_time = 500;
    key_def.low_level_detect = TRUE;
    key_def.lp_tp = LP_ONCE_TRIG;
    key_def.seq_key_detect_time = 400;
    key_def.call_back = key_callback;

    op_ret = reg_proc_key(&key_def);
    if (op_ret != OPRT_OK) {
        PR_ERR("reg_proc_key err:%d", op_ret);
    }

    return;
}
