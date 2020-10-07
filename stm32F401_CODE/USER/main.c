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
��ְʦ��������о��������������ĿVer1.0



************************************************/


/*************************
����ͨѶ���ƾ��
*************************/

//��Ϣ���о��
QueueHandle_t Key_Queue; //������Ϣ����



/*************************
����������
*************************/
void start_task(void *pvParameters); //start����
void led_task(void *pvParameters); //LED����
void key_task(void *pvParameters); //KEY����
void servo_task(void *pvParameters); //�������



/*************************
���������
*************************/
TaskHandle_t StartTask_Handler; //start����
TaskHandle_t LedTask_Handler;   //LED����
TaskHandle_t KeyTask_Handler;   //KEY����
TaskHandle_t Servo_Handler;			//�������


/*************************
�������ȼ�
*************************/
#define START_TASK_PRIO	 4   //start����
#define LED_TASK_PRIO		 0	 //LED����
#define KEY_TASK_PRIO		 2	 //KEY����
#define SERVO_TASK_PRIO  3	 //�������





/*************************
�����ջ��С
*************************/


#define START_STK_SIZE  256 //start����
#define LED_STK_SIZE 		128   //LED����
#define KEY_STK_SIZE		128   //KEY����
#define SERVO_STK_SIZE  512   //�������



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(168);					//��ʼ����ʱ����
	uart_init(115200);     				//��ʼ������
	LED_Init();		        			//��ʼ��LED�˿�
	KEY_Init();							//��ʼ������


	//my_mem_init(SRAMIN);            	//��ʼ���ڲ��ڴ��

	
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���

		OS_AppObjCreate();
	
	
    //����LED����
    xTaskCreate((TaskFunction_t )led_task,             
                (const char*    )"task1_task",           
                (uint16_t       )LED_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )LED_TASK_PRIO,        
                (TaskHandle_t*  )&LedTask_Handler);   
    //����KEY����
    xTaskCreate((TaskFunction_t )key_task,     
                (const char*    )"key_task",   
                (uint16_t       )KEY_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )KEY_TASK_PRIO,
                (TaskHandle_t*  )&KeyTask_Handler); 
	//�����������
    xTaskCreate((TaskFunction_t )servo_task,     
                (const char*    )"servo_task",   
                (uint16_t       )SERVO_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )SERVO_TASK_PRIO,
                (TaskHandle_t*  )&Servo_Handler); 					
			
								
								
								
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
								
    taskEXIT_CRITICAL();            //�˳��ٽ���
}





