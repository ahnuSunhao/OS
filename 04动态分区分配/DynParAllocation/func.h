typedef struct Node
{
	char name;
	int startAdr;  //������
	int space;//��С 
	struct Node *before;//ָ����ָ��ǰһ���ڵ� 
	struct Node *next; //ָ����ָ��ֱ�Ӻ��
}LNode, *LinkList;

#define MinSize 15//�����и��ʣ������С 

LinkList overall_pointer; 

void menu1();//��ӡ�˵�һ 

void menu2();//��ӡ�ֲ˵� 

int choose1();//ѡ��˵�һ����

int choose2();//ѡ��ֲ˵����� 

void Display_L(LinkList L);//��ʾ���з�������L

void Display_K(LinkList K);//��ʾ�ѷ����������K 

int ListLength(LinkList L);//�������� 

void InitList(LinkList *L , int s , char na);//��ʼ���ռ�Ϊs������

/********�״���Ӧ�㷨**************/

void FirstFit(LinkList *L , LinkList *K); //�״���Ӧ�㷨 

void FGetSpace(LinkList *L , LinkList *K);//������Դ 

void InsertList_K(LinkList *K , LinkList s);//��s�ڵ���뵽����K��β�� 

void FRelease(LinkList *L , LinkList *K);//�ͷŽ�����Դ 

void InsertList_L(LinkList *L , LinkList s);//��s�ڵ���뵽����L�� 

void FCompact(LinkList *L , LinkList *K);//���� 

/********ѭ����Ӧ�㷨*************/

void NextFit(LinkList *L , LinkList *K);//ѭ����Ӧ�㷨

void NGetSpace(LinkList *L , LinkList *K);//������Դ 

void NRelease(LinkList *L , LinkList *K);//�ͷŽ�����Դ 

void NInsertList_L(LinkList *L , LinkList s);//��s���뵽L�� 

/********�����Ӧ�㷨 *************/

void BestFit(LinkList *L , LinkList *K);//�����Ӧ�㷨 

void sort_L(LinkList *L);//��L���յ�ַ�ռ�������� 

void sort_L_startAdr(LinkList *L);//������ʼ��ַ���� 

void swap(int *a , int *b);

void BGetSpace(LinkList *L , LinkList *K);//������Դ 

void BRelease(LinkList *L , LinkList *K);//�ͷŽ�����Դ 

void BInsertList_L(LinkList *L , LinkList s);//��s�ڵ���뵽����L�� 

void BCompact(LinkList *L , LinkList *K);//���� 

