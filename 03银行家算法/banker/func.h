typedef struct process{
	int max[M];//��ʾ�ø���������Ҫ����Դ�� 
	int allocation[M];//��ʾ�ý��̴�ʱӵ�ж�����Դ 
	int need[M];//��ʾ�ý��̻���Ҫ������Դ 
	
	int flag;//���ڼ�¼�ν����Ƿ��ܹ������� 
}pro;

int m ,n;

void menu();//��ӡ�˵� 

void print(int i , pro p[] , int available[]);//��ӡ����

void readData(pro p[] , int available[]);//��ȡ����

int compare(int a[] , int b[]);//�Ƚ������������Ԫ�صĴ�С

void isSafe(pro p[] , int available[]);//�жϵ�ǰ�Ƿ�ȫ 

void judgeSafe(pro p[] , int available[]);//�ж����������Ƿ�Ϸ� 
