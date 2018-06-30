#include "function.h"
#include "head.h"

int readDate(jc x[])
{
	int i, n; 
	FILE *fp =fopen("date.txt","r");
	if(fp == NULL)
		return 0;
	fscanf(fp,"%d",&n);
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d %c %d", &x[i].arriveTime,&x[i].name, &x[i].serveTime);
		x[i].startFlag = 0;
		x[i].endTime = 0;
	}
	fclose(fp);
	return n;
}

void showDate(jc x[],int n)
{
	int i;
	printf("���̵ĸ���Ϊ��%d\n",n);
	for(i=0;i<n;i++)
	{
		printf("%c���̵���ʱ��%d������ʱ��%d\n",x[i].name, x[i].arriveTime, x[i].serveTime);
	}
} 

void TimePian(jc x[] , int n)
{
	int  length, i = 0, j, t = 0, flag = 0;
	int y[MAXN];
	for(j=0;j<n;j++)
	{
		y[j] = x[j].serveTime;
	}
	
	printf("������ʱ��Ƭ���ȣ�");
	scanf("%d",&length);
	
	printf("\n������  ����ʱ��  ��ʼʱ��  �ȴ�ʱ��  �������ʱ��\n");

	
	while(1)
	{
		if(x[i].endTime == 0)
		{
			if(x[i].startFlag == 0)//��ʾ��һ��ִ�иý��� 
			{
				
				for(j=0;j<length;j++)
				{
					if(x[i].startFlag == 0) 
					{
						if(t>=x[i].arriveTime)
						{
							x[i].startTime = t;
							x[i].waitTime = t - x[i].arriveTime;
							x[i].serveTime -= 1;
							t ++;
						}
						else{//��֤����ʱ�䲻�ǰ�˳�򵽴�� 
							t++;
							break;
						}
						if(x[i].serveTime == 0)
						{//�ý��̽��� 
							x[i].endTime = t;
							flag ++;
							break;
						}
					}
					else
					{
						x[i].serveTime -=  1;
						t ++;
						if(x[i].serveTime == 0)
						{//�ý��̽��� 
							x[i].endTime = t;
							flag ++;
							break;
						}
					}
					x[i].startFlag = 1;
				}
			}
			else//���ǵ�һ��ִ�� 
			{
				for(j=0;j<length;j++)
				{
					x[i].serveTime -=  1;
					t ++;
					if(x[i].serveTime == 0)
					{//�ý��̽��� 
						x[i].endTime = t;
						flag ++;
						break;
					}
				}
			}
		}
		
		printf("%c\t  %d\t    %d\t     %d\t     \t%d\n",x[i].name, x[i].arriveTime, x[i].startTime, x[i].waitTime, x[i].serveTime);

		
		if(flag == n)
			break;
		i++;
		if(i==n)
		{
			i = 0;
			printf("-----------------------------------------\n");
		}
			
	}
	printf("\n������  ����ʱ��  ��ʼʱ��  �ȴ�ʱ��  ����ʱ��  ��תʱ��  ��Ȩ��תʱ��\n");

	for(i=0;i<n;i++)
	{
		x[i].zhouzhuanTime = x[i].endTime - x[i].arriveTime;
		x[i].weightTime = (double)x[i].zhouzhuanTime / (double)y[i];
		printf("%c\t    %d\t      %d\t\t%d\t %-2d\t   %d\t    %.2f\n",x[i].name, x[i].arriveTime, x[i].startTime, x[i].waitTime, x[i].endTime, x[i].zhouzhuanTime, x[i].weightTime);
	}	
}

//�ļ���������
int input(struct zgxyb *p)
{
	int i,n;
	//�ļ�����
	FILE *fpRead=fopen("date.txt","r");  
    if(fpRead==NULL)  //�ļ�Ϊ��
    {  
        return ;  
    }  
	printf("���ļ��ж�ȡ��Ϣ����ҵ����-����ʱ��-����ʱ�䣺\n");
	fscanf(fpRead,"%d",&n);
	for(i=0;i<n;i++)
	{
		//��ȡ����
		fscanf(fpRead," %f %s %f",&p[i].arrivetime,&p[i].name,&p[i].servicetime);
	}
	 fclose(fpRead);//�ر��ļ���
	 return n;
}

void Print(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N)
{
	int k; 
	printf("��ҵ����Ⱥ�˳��Ϊ��");
	printf("%s",p[0].name);
	for(k=1;k<N;k++) 
	{
		printf("-->%s",p[k].name);
	}
	
	printf("\n��ҵ���� ����ʱ�� ����ʱ�� ��ʼʱ��  ���ʱ��    ��תʱ��     ��Ȩ��תʱ��\n");
	for(k=0;k<=N-1;k++) {
		printf("%s\t   %-.2f\t   %-.2f\t     %-.2f\t%-.2f\t    %-.2f\t  %-.2f\t\n",p[k].name,p[k].arrivetime,p[k].servicetime,p[k].starttime,p[k].finishtime,p[k].zztime,p[k].dqzztime);
	}
}



//������ʱ������
 void sort( struct zgxyb *p,int N){ 
	 int i,j; 
	 for(i=0;i<=N-1;i++)
		 for(j=0;j<=i;j++)
			 if(p[i].arrivetime<p[j].arrivetime)
			 { 
				 struct zgxyb temp;
				 temp=p[i];p[i]=p[j];
				 p[j]=temp;
			} 
 }

//���н׶�

 void deal(struct zgxyb *p,float arrivetime,float servicetime,float starttime,float finishtime,float zztime,float dqzztime,int N)
 { 
	 int k; 
	 for(k=0;k<=N-1;k++)
	 { 
		 if(k==0){ 
			 p[k].starttime=p[k].arrivetime;
			 p[k].finishtime=p[k].arrivetime+p[k].servicetime;
			}
		 else{
			 p[k].starttime=p[k-1].finishtime; p[k].finishtime=p[k-1].finishtime+p[k].servicetime;
			}
	 } 
	 //������תʱ��:���ʱ���ȥ��ʼʱ��
	 for(k=0;k<=N-1;k++)
	 { 
		 p[k].zztime=p[k].finishtime-p[k].arrivetime;
		 p[k].dqzztime=p[k].zztime/p[k].servicetime;
	 }
 }

void HHRN (struct zgxyb *p,int N){
	float arrivetime=0,servicetime=0,starttime=0,finishtime=0,zztime=0,dqzztime=0;
	int m,i,n,follow,k;
	float max; 
	float sum=0,sum1=0;//���������Ȩ��תʱ��
	struct zgxyb temp;
	sort(p,N); 
	for(m=0;m<N-1;m++)
	{ 
		//�������
		if(m==0) 
			p[m].finishtime=p[m].arrivetime+p[m].servicetime;
		else
			p[m].finishtime=p[m-1].finishtime+p[m].servicetime; 

		i=0; 
		
		//�жϳ��˵�ǰ��ҵ�����ж�����ҵ�ڵ�ǰʱ���Ѿ�����
		for(n=m+1;n<=N-1;n++)
		{ 
			if(p[n].arrivetime<=p[m].finishtime)
				i++;
		} 
		max=(p[m].finishtime-p[m+1].arrivetime+p[m+1].servicetime)/p[m+1].servicetime;

		follow=m+1; 


		for(k=m+1;k<m+i;k++)
		//�ӵڶ�����ʼ����
		{ 
			if(max<=(p[m].finishtime-p[k+1].arrivetime+p[k+1].servicetime)/p[k+1].servicetime) //�ж����ȼ��Ƿ񳬹���ֵ
			{ 
				max=(p[m].finishtime-p[k+1].arrivetime+p[k+1].servicetime)/p[k+1].servicetime;
				follow=k+1;//ԭ�򣺴ӵڶ�����ʼ�Ƚ�
			}
		} 

		temp=p[m+1];
		p[m+1]=p[follow];
		p[follow]=temp;
	}
	deal(p,arrivetime,servicetime,starttime,finishtime,zztime,dqzztime,N);
	Print(p,arrivetime,servicetime,starttime,finishtime,zztime,dqzztime,N);//������ս��
	for(i=0;i<N;i++)
	{
		sum+=p[i].zztime;
		sum1+=p[i].servicetime;
	}
	printf("�����ƽ����Ȩ��תʱ��Ϊ��%-.2f\n",sum/sum1);
}

