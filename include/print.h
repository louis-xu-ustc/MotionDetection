/**
    * File Name: include/print.h
    * Author: Louis Xu
    * Mail: louis_xu_ustc@163.com
    * Created Time: 01/25/16
*/

#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdio.h>

typedef enum log_lvl_s
{
    LOG_ERR = 0,
    LOG_MSG,
    LOG_INFO,
    LOG_DBG,
    LOG_NUM,
    LOG_LVL_FIRST=LOG_ERR,
    LOG_LVL_LAST=LOG_NUM,
} log_lvl_t;

extern int g_log_lvl;

#define log_print(lvl, fmt, args...) \
    do { \
        if (lvl <= g_log_lvl) { \
            printf(fmt, ##args); \
        } \
    } while (0)

#define log_err(fmt, args...) \
    log_print(LOG_ERR, fmt, ##args)
#define log_msg(fmt, args...) \
    log_print(LOG_MSG, fmt, ##args)
#define log_info(fmt, args...) \
    log_print(LOG_INFO, fmt, ##args)
#define log_dbg(fmt, args...) \
    log_print(LOG_DBG, fmt, ##args)

#endif
