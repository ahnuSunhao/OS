typedef struct jc
{
	char name;//������ 
	int arriveTime;//����ʱ�� 
	int startTime;//��ʼʱ�� 
	int serveTime;//����ʱ�� 
	int waitTime;//�ȴ�ʱ�� 
	int endTime;//����ʱ�� 
	int zhouzhuanTime;//��תʱ��
	double weightTime;//��Ȩ��תʱ�� 
	int startFlag;//��ʼ��־ 
	double reflectRate;//��Ӧ��
}jc;

struct zgxyb{
	char name[10]; //��ҵ����
	float arrivetime;//����ʱ��
	float servicetime;//����ʱ��
	float starttime;//��ʼʱ��
	float finishtime;//���ʱ��
	float zztime;//��תʱ��
	float dqzztime;//ƽ����תʱ��
}; 

int readDate(jc x[]);//��ȡdate.TXT�ļ��е����� ,���ؽ��̸��� 

void showDate(jc x[], int n);//��ʾ������������� 

void TimePian(jc x[] , int n);//ʱ��Ƭ��ת�㷨 

int input(struct zgxyb *p);

void Print(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N);

void sort( struct zgxyb *p,int N);
 
void deal(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N);
 
void HHRN (struct zgxyb *p,int N);//����Ӧ�����ȵ����㷨 

