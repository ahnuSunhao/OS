#include"head.h"
#include"func.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	 
	LinkList K, L;//����������L�ǿ��з�������K���ѷ���������� 
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
	
}//����
