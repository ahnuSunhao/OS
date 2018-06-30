#include "head.h"
#include "func.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	int k;
	int available[M];//表示当前可用资源 
	pro p[N];//表示有n个进程 
	menu();
	printf("请输入功能数字:");
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
		printf("请再次选择功能数字:");
		scanf("%d",&k);
	}
}
