#include "head.h"
#include "func.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	int k;
	int available[M];//��ʾ��ǰ������Դ 
	pro p[N];//��ʾ��n������ 
	menu();
	printf("�����빦������:");
	scanf("%d",&k);
	while(1)
	{
		switch(k)
		{
			case 1:
				readData(p , available);
				isSafe(p,available);
				break;
			case 2:
				judgeSafe(p,available);
				break;
			default:
				return 0;
		}
		printf("���ٴ�ѡ��������:");
		scanf("%d",&k);
	}
}
