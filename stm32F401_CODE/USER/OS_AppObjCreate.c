#include <OS_AppObjCreate.h>




/***********************************************************
						 ������Ϣ����
************************************************************/


#define KEYMSG_Q_NUM    1  		//������Ϣ���е�����  

//������Ϣ����
void Key_QueueCreat(void)
{
	extern QueueHandle_t Key_Queue;
	Key_Queue =xQueueCreate(KEYMSG_Q_NUM,sizeof(uint8_t));
	
	if (Key_Queue==0)
	{
	/*��Ϣ����ʧ�ܴ������*/
	printf("������Ϣ���д���ʧ��");
	}
	else 
	{
	printf("������Ϣ���д����ɹ�");
	}
}



void QueueCreate(void)
{

Key_QueueCreat();
	
}



void OS_AppObjCreate(void)
{
//��Ϣ���д���
QueueCreate();

	
	
}

 
 
 
 
 
 
 
 
 
 
 
 







