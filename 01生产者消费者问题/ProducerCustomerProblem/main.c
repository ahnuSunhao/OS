#include <stdio.h>  
#include <windows.h>  
#include <process.h>  
#include <stdlib.h>  
  
#define N 10 //��10�������� 
  
int in = 0, out = 0;  
int Buffer[N] = {0};//��ʾ����أ�����Ϊint  
  
HANDLE mutex, empty, full; //mutex�ǻ����ź��� ��empty�ǿջ������ź�����full�����������ź����� 

DWORD WINAPI producer(void *p)  
{  
    while (1)  
    {
        WaitForSingleObject(empty, INFINITE);  //p����������л������ź���empty������һ�������������û�У��������ý��̣�����У������ִ��   
        WaitForSingleObject(mutex, INFINITE);  //p�������ٽ�����Դ��Ҫʹ�û���������ֻ֤��һ���߳̿��Է��ʣ�������̷߳��ʳ�ͻ������ʱ���ٽ���Դ�����ϣ�����̵߳������ܵĽ�������Ĳ��� 
  
        Buffer[in] = 1;  
        in = in  % N+1;  
        printf("�������߳�����������һ����Ʒ%d\n", in);  
  		Sleep(100); 
        ReleaseSemaphore(mutex, 1, NULL);  //V�������ͷ��ź������ٽ������ʽ��� ������ 
        ReleaseSemaphore(full, 1, NULL);  //V������ ����Ʒ�ŵ��������У����������ź���full�м� 1 
          
    }  
    return 0;  
}  
  
DWORD WINAPI consumer(void *p)  
{  
    while (1)  
    {  
        WaitForSingleObject(full, INFINITE);  //p�����������������ź���full����һ�������������û�У��������ý��̣�����У������ִ�� 
        WaitForSingleObject(mutex, INFINITE);  //ͬ��
        
        out = out % N +1 ;  
        printf("�������߳�����������һ����Ʒ****%d\n", out);  
  		Sleep(100); 
        ReleaseSemaphore(mutex, 1, NULL);  //V�������ͷ��ź������ٽ������ʽ��� ������ 
        ReleaseSemaphore(empty, 1, NULL);  //v�������ͷ�һ���������ռ䣬���л�����empty�м� 1  
  
    }  
    return 0;  
}  
  
int main()  
{  
    //�����ź���  
    mutex = CreateSemaphore(NULL, 1, 1, NULL);  //���������ź�������ʼֵΪ1�������һ���߳̿���ͬʱʹ�� 
    empty = CreateSemaphore(NULL, N, N, NULL);  //��ʼֵΪN�������N���߳�ͬʱʹ�� 
    full = CreateSemaphore(NULL, 0, N, NULL);  //��ʼֵΪ0�������N���߳̿���ͬʱʹ�� 
    int i;
    
  	HANDLE produce[3];
	HANDLE consume[3];
	
  	for(i=0;i<3;i++)
		produce[i] = CreateThread(NULL, 0, producer, NULL, 0, 0); //�����������߳� 
		
	for(i=0;i<3;i++)
		consume[i] = CreateThread(NULL, 0, consumer, NULL, 0, 0); //�����������߳� 
  	
    WaitForMultipleObjects(1, produce, TRUE, INFINITE);//�ȴ��������߳̽���  
    WaitForMultipleObjects(1, consume, TRUE, INFINITE);//�ȴ��������߳̽���  
  
    return 0;  
} 
