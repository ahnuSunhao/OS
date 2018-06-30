#include <stdio.h>  
#include <windows.h>  
#include <process.h>  
#include <stdlib.h>  
  
#define N 10 //有10个缓冲区 
  
int in = 0, out = 0;  
int Buffer[N] = {0};//表示缓冲池，类型为int  
  
HANDLE mutex, empty, full; //mutex是互斥信号量 ，empty是空缓冲区信号量，full是满缓冲区信号量， 

DWORD WINAPI producer(void *p)  
{  
    while (1)  
    {
        WaitForSingleObject(empty, INFINITE);  //p操作，向空闲缓冲区信号量empty中申请一个缓冲区，如果没有，则阻塞该进程；如果有，则继续执行   
        WaitForSingleObject(mutex, INFINITE);  //p操作，临界区资源需要使用互斥量，保证只有一个线程可以访问，避免多线程访问冲突，即此时把临界资源区锁上，别的线程到来不能的进行下面的操作 
  
        Buffer[in] = 1;  
        in = in  % N+1;  
        printf("生产者线程启动，生产一个产品%d\n", in);  
  		Sleep(100); 
        ReleaseSemaphore(mutex, 1, NULL);  //V操作，释放信号量，临界区访问结束 ，解锁 
        ReleaseSemaphore(full, 1, NULL);  //V操作， 把物品放到缓存区中，满缓冲区信号量full中加 1 
          
    }  
    return 0;  
}  
  
DWORD WINAPI consumer(void *p)  
{  
    while (1)  
    {  
        WaitForSingleObject(full, INFINITE);  //p操作，向满缓冲区信号量full申请一个缓冲区，如果没有，则阻塞该进程；如果有，则继续执行 
        WaitForSingleObject(mutex, INFINITE);  //同上
        
        out = out % N +1 ;  
        printf("消费者线程启动，消费一个产品****%d\n", out);  
  		Sleep(100); 
        ReleaseSemaphore(mutex, 1, NULL);  //V操作，释放信号量，临界区访问结束 ，解锁 
        ReleaseSemaphore(empty, 1, NULL);  //v操作，释放一个缓存区空间，空闲缓冲区empty中加 1  
  
    }  
    return 0;  
}  
  
int main()  
{  
    //创建信号量  
    mutex = CreateSemaphore(NULL, 1, 1, NULL);  //创建互斥信号量，初始值为1，最多有一个线程可以同时使用 
    empty = CreateSemaphore(NULL, N, N, NULL);  //初始值为N，最多有N个线程同时使用 
    full = CreateSemaphore(NULL, 0, N, NULL);  //初始值为0，最多有N个线程可以同时使用 
    int i;
    
  	HANDLE produce[3];
	HANDLE consume[3];
	
  	for(i=0;i<3;i++)
		produce[i] = CreateThread(NULL, 0, producer, NULL, 0, 0); //建立生产者线程 
		
	for(i=0;i<3;i++)
		consume[i] = CreateThread(NULL, 0, consumer, NULL, 0, 0); //建立消费者线程 
  	
    WaitForMultipleObjects(1, produce, TRUE, INFINITE);//等待生产者线程结束  
    WaitForMultipleObjects(1, consume, TRUE, INFINITE);//等待消费者线程结束  
  
    return 0;  
} 
