#ifndef __OS_APPOBJCREATE_H
#define __OS_APPOBJCREATE_H
#include "FreeRTOS.h"
#include "queue.h"






//按键消息队列
void Key_QueueCreat(void);

//消息队列创建
void QueueCreate(void);



//任务通讯机制创建
void OS_AppObjCreate(void);

#endif 







