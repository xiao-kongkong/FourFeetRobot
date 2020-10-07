#include "key_task.h"


//Keytask函数

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
									
                    case WKUP_PRES:		//KEY_UP控制LED1

                     break;

                    case KEY0_PRES:		//KEY0刷新LCD背景
								    if(key_flag)
										key_flag=0;
										else
										key_flag=1;
										xQueueOverwrite(Key_Queue,&key_flag);
										
                    break;
										
                }//扫描按键
            
					
		vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
	}
}
