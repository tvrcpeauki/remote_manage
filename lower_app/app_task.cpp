/*
 * File      : app_task.cpp
 * This file is template file
 * COPYRIGHT (C) 2020, zc
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-5-12      zc           the first version
 */

/**
 * @addtogroup IMX6ULL
 */
/*@{*/
#include "driver/led.h"
#include "app_task.h"

/**************************************************************************
* Local Macro Definition
***************************************************************************/

/**************************************************************************
* Local Type Definition
***************************************************************************/

/**************************************************************************
* Local static Variable Declaration
***************************************************************************/

/**************************************************************************
* Global Variable Declaration
***************************************************************************/
app_reg *app_sytem_reg_ptr;

/**************************************************************************
* Function
***************************************************************************/
/*app接口初始化*/
app_reg::app_reg(void)
{
    /*清除内部寄存状态*/
    memset(this->reg, 0, REG_NUM);
    if(pthread_mutex_init(&this->reg_mutex, NULL) != 0)
    {
        printf("mutex init failed\n");
    }
}

app_reg::~app_reg()
{
    pthread_mutex_destroy(&this->reg_mutex);
}

/*多字节读取寄存器的值*/
uint16_t app_reg::get_multiple_val(uint16_t reg_index, uint16_t size, uint8_t *pstart)
{
    uint16_t index;

    if(size > REG_NUM)
        size = REG_NUM;

    pthread_mutex_lock(&this->reg_mutex);
    for(index=0; index<size; index++)
    {
        *(pstart+index) = this->reg[reg_index+index];
    }
    pthread_mutex_unlock(&this->reg_mutex);
    #if __SYSTEM_DEBUG
    printf("get array:");
    log_array(this->reg, size);
    #endif
    return size;
}

/*多字节写入内部寄存器*/
void app_reg::set_multiple_val(uint16_t reg_index, uint16_t size, uint8_t *pstart)
{
    uint16_t index, end_index;

    end_index = reg_index+size;
    if(end_index>REG_NUM)
        end_index = REG_NUM;

    pthread_mutex_lock(&this->reg_mutex);
    for(index=reg_index; index<end_index; index++)
    {
        this->reg[index] = *(pstart+index);
    }
    pthread_mutex_unlock(&this->reg_mutex);
    #if __SYSTEM_DEBUG
    printf("set array:");
    log_array(this->reg, size);
    #endif
}

/*更新内部状态寄存器, 写入硬件或者从硬件更新*/
void app_reg::hardware_refresh(void)
{
    uint8_t *reg_ptr;
    uint8_t reg_cache_buf[REG_NUM];
    uint8_t is_reg_modify = 0;
    uint16_t reg_set_status;

    reg_ptr = (uint8_t *)malloc(REG_NUM);
    if(reg_ptr != NULL)
    {
        /*读取所有的寄存值*/
        this->get_multiple_val(0, REG_NUM, reg_ptr);
        reg_set_status = reg_ptr[1] <<8 | reg_ptr[0];

        /*有设置消息*/
        if(reg_set_status&0x01)
        {
            /*LED设置处理*/
            if(reg_set_status&(1<<1))
            {
                //USR_DEBUG("LED convert, 0x%x, %d\n", reg_set_status, reg_ptr[2]&0x01);
                led_convert(reg_ptr[2]&0x01);
            }

             /*修改beep*/

            reg_ptr[0] = 0;
            reg_ptr[1] = 0;
            is_reg_modify = 1;
        }
  
        memcpy(reg_cache_buf, reg_ptr, REG_NUM);
        /*更新寄存器状态*/

        if(memcmp(reg_cache_buf, reg_ptr, REG_NUM) != 0)
        {
            is_reg_modify = 1;
        }
        if(is_reg_modify == 1)
        {
            this->set_multiple_val(0, REG_NUM, reg_cache_buf);
            is_reg_modify = 0;
        }

        free(reg_ptr);
    }
    else{
        USR_DEBUG("malloc error\n");
    }

}

/**
 * 获取寄存器配置指针
 * 
 * @param fd
 *  
 * @return NULL
 */
app_reg *get_app_reg(void)
{
    return app_sytem_reg_ptr;
}

/**
 * app模块初始化
 * 
 * @param fd
 *  
 * @return NULL
 */
void app_init(void)
{
    app_sytem_reg_ptr = new app_reg();
}

/**
 * app模块初始化
 * 
 * @param NULL
 *  
 * @return NULL
 */
void *app_loop_task(void *arg)
{
    USR_DEBUG("app Task Start\n");
    for(;;){
        app_sytem_reg_ptr->hardware_refresh();
        usleep(800);
    }
}

/**
 * app模块测试代码
 * 
 * @param NULL
 *  
 * @return NULL
 */
void app_module_test(void)
{
    app_sytem_reg_ptr->hardware_refresh();
}