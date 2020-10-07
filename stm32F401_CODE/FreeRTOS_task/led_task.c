#include <led_task.h>

//消息队列句柄
extern QueueHandle_t Key_Queue;
//LEDtask任务函数
void led_task(void *pvParameters)
{
static u8 key_flag=0;
	while(1)
	{



LED1=~LED1;

	
		
		xQueuePeek(Key_Queue,&key_flag,10);
		
		if (key_flag==1)
		{

		LED0=~LED0;
		
		}
		else
		{
		
		
		}
	
		
    vTaskDelay(500);                           //延时10ms，也就是10个时钟节拍	
	}
}





