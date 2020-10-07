#include <OS_AppObjCreate.h>




/***********************************************************
						 创建消息队列
************************************************************/


#define KEYMSG_Q_NUM    1  		//按键消息队列的数量  

//按键消息队列
void Key_QueueCreat(void)
{
	extern QueueHandle_t Key_Queue;
	Key_Queue =xQueueCreate(KEYMSG_Q_NUM,sizeof(uint8_t));
	
	if (Key_Queue==0)
	{
	/*消息创建失败处理机制*/
	printf("按键消息队列创建失败");
	}
	else 
	{
	printf("按键消息队列创建成功");
	}
}



void QueueCreate(void)
{

Key_QueueCreat();
	
}



void OS_AppObjCreate(void)
{
//消息队列创建
QueueCreate();

	
	
}

 
 
 
 
 
 
 
 
 
 
 
 







