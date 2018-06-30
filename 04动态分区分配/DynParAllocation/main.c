#include"head.h"
#include"func.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	 
	LinkList K, L;//两个分区，L是空闲分区链表，K是已分配分区链表 
	menu1();
	while(1)
	{
		switch(choose1())
		{
			case 1:
				FirstFit(&L, &K);
				break;
			case 2:
				NextFit(&L, &K);
				break;
			case 3:
				BestFit(&L, &K);
				break;
			default:
				return 0;
		}
	} 
	
}//结束
