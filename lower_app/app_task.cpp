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
#include "include/app_task.h"

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
app_reg *app_reg_ptr;

/**************************************************************************
* Function
***************************************************************************/
/**
 * 内部数据构造函数
 * 
 * @param NULL
 *  
 * @return NULL
 */
app_reg::app_reg(void)
{
    /*清除内部寄存状态*/
    memset((char *)this->reg, 0, REG_NUM);
    if(pthread_mutex_init(&this->reg_mutex, NULL) != 0)
    {
        printf("mutex init failed\n");
    }
}

/**
 * 内部数据析构函数
 * 
 * @param NULL
 *  
 * @return NULL
 */
app_reg::~app_reg()
{
    pthread_mutex_destroy(&this->reg_mutex);
}

/**
 * 获取内部寄存器变量的值
 * 
 * @param reg_index 寄存器的起始地址
 * @param size 读取的寄存器的数量
 * @param pstart 读取数据的地址
 *  
 * @return 读取寄存器的数量
 */
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

/**
 * 设置数据到内部寄存
 * 
 * @param reg_index 寄存器的起始地址
 * @param size 读取的寄存器的数量
 * @param pstart 设置数据的地址
 *  
 * @return NULL
 */
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

/**
 * 根据寄存器更新内部硬件参数
 * 
 * @param NULL
 *  
 * @return NULL
 */
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
 * 获取寄存器数据结构体指针
 * 
 * @param NULL
 *  
 * @return 返回寄存器的信息
 */
app_reg *get_app_reg(void)
{
    return app_reg_ptr;
}

/**
 * 设置寄存器结构体指针
 * 
 * @param NULL
 *  
 * @return 返回寄存器的信息
 */
void set_app_reg(app_reg *arp)
{
   app_reg_ptr = arp;
}

/**
 * app模块任务初始化
 * 
 * @param NULL
 *  
 * @return NULL
 */
void app_task_init(void)
{
    pthread_t tid1;
    int err;
    app_reg_ptr = new app_reg();

    err = pthread_create(&tid1, NULL, app_loop_task, NULL);	
    if(err != 0){
        USR_DEBUG("app task thread create err, %d\n", err);
    }
}

/**
 * app模块初始化
 * 
 * @param arg 线程传递的参数
 *  
 * @return NULL
 */
void *app_loop_task(void *arg)
{
    USR_DEBUG("app Task Start\n");
    for(;;){
        app_reg_ptr->hardware_refresh();
        usleep(800);
    }
}