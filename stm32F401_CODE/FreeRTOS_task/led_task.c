#include <led_task.h>

//��Ϣ���о��
extern QueueHandle_t Key_Queue;
//LEDtask������
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
	
		
    vTaskDelay(500);                           //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
}





