#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "beep.h"
#include "string.h"
#include "malloc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <OS_AppObjCreate.h>
/************************************************
天职师大机器人研究所四足机器人项目Ver1.0



************************************************/


/*************************
任务通讯机制句柄
*************************/

//消息队列句柄
QueueHandle_t Key_Queue; //按键消息队列



/*************************
任务函数声明
*************************/
void start_task(void *pvParameters); //start任务
void led_task(void *pvParameters); //LED任务
void key_task(void *pvParameters); //KEY任务
void servo_task(void *pvParameters); //舵机任务



/*************************
任务函数句柄
*************************/
TaskHandle_t StartTask_Handler; //start任务
TaskHandle_t LedTask_Handler;   //LED任务
TaskHandle_t KeyTask_Handler;   //KEY任务
TaskHandle_t Servo_Handler;			//舵机任务


/*************************
任务优先级
*************************/
#define START_TASK_PRIO	 4   //start任务
#define LED_TASK_PRIO		 0	 //LED任务
#define KEY_TASK_PRIO		 2	 //KEY任务
#define SERVO_TASK_PRIO  3	 //舵机任务





/*************************
任务堆栈大小
*************************/


#define START_STK_SIZE  256 //start任务
#define LED_STK_SIZE 		128   //LED任务
#define KEY_STK_SIZE		128   //KEY任务
#define SERVO_STK_SIZE  512   //舵机任务



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(168);					//初始化延时函数
	uart_init(115200);     				//初始化串口
	LED_Init();		        			//初始化LED端口
	KEY_Init();							//初始化按键


	//my_mem_init(SRAMIN);            	//初始化内部内存池

	
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区

		OS_AppObjCreate();
	
	
    //创建LED任务
    xTaskCreate((TaskFunction_t )led_task,             
                (const char*    )"task1_task",           
                (uint16_t       )LED_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )LED_TASK_PRIO,        
                (TaskHandle_t*  )&LedTask_Handler);   
    //创建KEY任务
    xTaskCreate((TaskFunction_t )key_task,     
                (const char*    )"key_task",   
                (uint16_t       )KEY_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KeyTask_Handler); 
	//创建舵机任务
    xTaskCreate((TaskFunction_t )servo_task,     
                (const char*    )"servo_task",   
                (uint16_t       )SERVO_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )SERVO_TASK_PRIO,
                (TaskHandle_t*  )&Servo_Handler); 					
			
								
								
								
    vTaskDelete(StartTask_Handler); //删除开始任务
								
    taskEXIT_CRITICAL();            //退出临界区
}





