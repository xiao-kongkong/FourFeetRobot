#include "key_task.h"


//Keytask����

extern QueueHandle_t Key_Queue;

void key_task(void *pvParameters)
{

	u8 key;
	u8 key_flag=0;
	while(1)
	{
							key=KEY_Scan(0);
                switch(key)
                {
									
                    case WKUP_PRES:		//KEY_UP����LED1

                     break;

                    case KEY0_PRES:		//KEY0ˢ��LCD����
								    if(key_flag)
										key_flag=0;
										else
										key_flag=1;
										xQueueOverwrite(Key_Queue,&key_flag);
										
                    break;
										
                }//ɨ�谴��
            
					
		vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
}
