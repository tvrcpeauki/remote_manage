/* 
 * File      : app_task.h
 * This file is application task interface
 * COPYRIGHT (C) 2020, zc
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-4      zc            the first version
 */

/**
 * @addtogroup IMX6ULL
 */
/*@{*/
#ifndef _INCLUDE_APP_TASK_H
#define _INCLUDE_APP_TASK_H

/***************************************************************************
* Include Header Files
***************************************************************************/
#include <pthread.h>
#include "typedef.h"

/**************************************************************************
* Global Macro Definition
***************************************************************************/
#define REG_NUM  256

/**************************************************************************
* Global Type Definition
***************************************************************************/
class app_reg
{
public:
    app_reg(void);
        ~app_reg();
    uint16_t get_multiple_val(uint16_t reg_index, uint16_t size, uint8_t *pstart);
    void set_multiple_val(uint16_t reg_index, uint16_t size, uint8_t *pstart);
    void hardware_refresh(void);
private:
    uint8_t reg[REG_NUM];
    pthread_mutex_t reg_mutex; /*数据读取都要执行该锁*/
};

/**************************************************************************
* Global Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Functon Declaration
***************************************************************************/
void app_init(void);
app_reg *get_app_reg(void);
void *app_loop_task(void *arg);
void app_module_test(void);
#endif
