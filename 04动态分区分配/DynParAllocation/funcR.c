#include"head.h"
#include"func.h"

void InitList(LinkList *L , int s , char na)
{//��ʼ��L��K���� 
	*L=(LinkList)malloc(sizeof(LNode)); //��ͷ�������ڴ�ռ�
	(*L)->next=NULL;
	(*L)->before=NULL; 
	(*L)->startAdr = 0;
	(*L)->space = s;
	(*L)->name = na; 
}

void Display_L(LinkList L)
{
	LinkList p;
	p = L;
	if(p==NULL)
	{
		printf("����Ϊ��");
	}
	else
	{
		while(p!=NULL)
		{
			printf("%c %d %d\n",p->name,p->startAdr,p->space);
			p = p->next;
		}
	}
} 

void Display_K(LinkList K)
{
	LinkList p;
	p = K;
	if(p==NULL)
	{
		printf("����Ϊ��");
	}
	else
	{
		while(p!=NULL)
		{
			printf("%c %d %d\n",p->name,p->startAdr,p->space);
			p = p->next;
		}
	}
} 


int ListLength(LinkList L)
{
	int j;
	LinkList p;
	p = L;
	j = 0;
	while(p!=NULL){
		p = p->next;
		j++;
	}
	return j;
}

/********�״���Ӧ�㷨**************/
void FirstFit(LinkList *L , LinkList *K)
{//�״���Ӧ�㷨 
	menu2();
	InitList(L,1024,'L');
	InitList(K,0,'K');
	while(1)
	{ 
		switch(choose2())
		{
			case 1:
				FGetSpace(L , K); 
				break;
			case 2:
				FRelease(L, K); 
				break;
			case 3:
				FCompact(L , K);
				break;
			case 4:
				Display_L(*L);
				break;
			case 5:
				Display_K(*K);
				break; 
			default:
				return;
		}
	}
}

void FGetSpace(LinkList *L , LinkList *K)
{//�״���Ӧ�㷨������Դ 
	LinkList p, s;
	char name[1];
	int size, temp = -1,length = 0;
	printf("�����������������ռ��С\n");
	scanf("%s %d",name, &size);
	p = *L;
	while(p != NULL)
	{//�������нڵ� 
		if(size <= p->space)
		{//��ʾ�ýڵ���Ը��������Դ����ռ� 
			s = (LinkList)malloc(sizeof(LNode));
			
			if(p->space - size <= MinSize)
			{//��������������Դ�ϴ󣬷����ýڵ�ʣ����ԴС�ڵ���MinSize��ȫ������ 
				if(p->before == NULL && p->next == NULL)
				{//��ʾ������L���� 
					temp = 0;
				}
				else if(p->before == NULL)
				{//��ʾ�ýڵ��������ײ� 
					(*L)->next = p->next;
					p->next->before = NULL;
					s = p;
				}
				else if(p->next == NULL)
				{//��ʾ�ýڵ�������β�� 
					p->before->next = NULL;
					s = p;
				}
				else
				{//��ʾ�ýڵ��������м� 
					p->before->next = p->next;
					p->next->before = p->before;
					s = p;
				}
				if(temp == 0)
				{//˵�����ײ�ȫ�������ȥ������K 
					s->space = p->space;
					s->startAdr = p->startAdr;
					p->space = 0;
				}
				s->name = name[0];
				InsertList_K(K,s);//��s���뵽K��β�� 
			}
			else
			{//��ʾ�����������Դ���ýڵ����㹻�ռ�����ý��̣��и�ڵ� 
				s->space = size;
				s->name = name[0];
				s->startAdr = p->startAdr;
				p->space -= size;
				p->startAdr += size;
				InsertList_K(K,s);
			}
			break;
		}
		else
		{//��ʾ�ýڵ㲻���Է�����Դ���ý��� 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**ERROR:û�пɷ�����Դ���ý���**\n\n"); 
			}
		}
	}
}

void InsertList_K(LinkList *K, LinkList s)
{//��s�ڵ���뵽����K��β�� 
	LinkList p;
	int startAd = 0;
	p = *K;
	while(p->next != NULL) 
	{//���������һ���ڵ� 
		p = p->next; 
	}
	p->next = s;
	s->before = p;
	s->next = NULL;
}

void FRelease(LinkList *L , LinkList *K)
{//�ͷŽ�����Դ����Դ����
	LinkList p, q; 
	char fname[1];
	printf("�������������");
	scanf("%s",fname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == fname[0])
		{//�ѷ��������б��д��ڸý��� 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//��ʾ������K���� 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//��ʾ�ýڵ��������ײ� 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//��ʾ�ýڵ�������β�� 
				p->before->next = NULL;
				q = p;
			}
			else
			{//��ʾ�ýڵ��������м� 
				p->before->next = p->next;
				p->next->before = p->before;
				q = p;
			}
			
			InsertList_L(L ,q);
			return ;
		}
		else
		{//�����ڸý��� 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**������Ϸ��Ľ��������ѷ�������������޸ý���**\n\n");
				return ;
			}
		}
	}
}

void InsertList_L(LinkList *L , LinkList s)
{
	LinkList p, q;
	p = *L;
	while(p != NULL)
	{
		if(s->startAdr <= p->startAdr)
		{
			if(p->before == NULL)
			{//p��L���׽ڵ� 
				if(s->startAdr+s->space == p->startAdr)
				{
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s);
				}
				else
				{
					q = (LinkList)malloc(sizeof(LNode));
					q = s;
					q->before = NULL;
					q->name = 'L';
					q->next = p;
					p->before = q;
					*L = q;
					//free(s);//*****///////////////////////////////////////���޸� 
				}
			}
			else
			{
				if(s->startAdr + s->space == p->startAdr && p->before->startAdr + p->before->space == s->startAdr)
				{//���սڵ���ǰ��ڵ���� 
					q = p->before;
					q->space += s->space + p->space;
					q->next = p->next;
					if(p->next == NULL)
					{//��ʾp��β�� 
						q->next = NULL;
						free(s);
						free(p);
						return ; 
					} 
					//p����β�� 
					p->next->before = q;
					free(s);
					free(p);
				}
				else if(s->startAdr + s->space == p->startAdr)
				{//s�����ڵ�����������ǰ��ڵ����� 
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s); 
				}
				else if(p->before->startAdr + p->before->space == s->startAdr)
				{//s��ǰ��ڵ�������������漸������ 
					p->before->space += s->space;
					free(s); 
				}
				else
				{//�������� 
					q = (LinkList)malloc(sizeof(LNode));
					q = s;
					q->name = 'L';
					q->before = p->before;
					q->next = p;
					p->before = q;
					q->before->next = q;
				}
			}
			return ; 
		}
		else 
		{
			if(p->next == NULL)
			{//����L�����һ���ڵ� 
				if(p->startAdr + p->space == s->startAdr)
				{
					p->space += s->space;
					free(s);
					return ;
				}
			}
			p =p->next;
		}
	}
}

void FCompact(LinkList *L , LinkList *K)
{
	LinkList p, q;
	int sum_space = 0, startAdr_K = 0;
	p = *L;
	while(p != NULL)
	{
		sum_space += p->space;
		p = p->next;
	}
	(*L)->startAdr = 1024 - sum_space;
	(*L)->space = sum_space;
	(*L)->next = NULL;
	q = *K;
	while(q != NULL)
	{
		q->startAdr = startAdr_K;
		startAdr_K += q->space;
		q = q->next;
	}
}


/********ѭ����Ӧ�㷨*************/
void NextFit(LinkList *L , LinkList *K)
{
	menu2();
	InitList(L,1024,'L');
	InitList(K,0,'K');
	while(1)
	{ 
		switch(choose2())
		{
			case 1:
				NGetSpace(L, K);
				break;
			case 2:
				NRelease(L, K);
				break;
			case 3:
				FCompact(L , K);
				overall_pointer = *L;//�޸�ȫ��ָ�� 
				break;
			case 4:
				Display_L(*L);
				break;
			case 5:
				Display_K(*K);
				break; 
			default:
				return;
		}
	}
} 

void NGetSpace(LinkList *L , LinkList *K)
{
	LinkList p, s;
	char name[1];
	int size,length = 0;
	printf("�����������������ռ��С\n");
	scanf("%s %d",name, &size);
	if(overall_pointer == NULL)
	{
		overall_pointer = *L;
	} 
	p = overall_pointer;
	if(p->next == NULL && p->before == NULL)
	{//��ʾ���з�������������ֻ��һ���ڵ� 
		if(size > p->space)
		{
			printf("\n**ERROR:û�пɷ�����Դ���ý���**\n\n");
			return ;
		}
		else
		{//��ʾ�ýڵ���пռ��㹻�ָ��ýڵ�
			s = (LinkList)malloc(sizeof(LNode));
			s->name = name[0];
			if(p->space - size <= MinSize)
			{//��������������Դ�ϴ󣬷����ýڵ�ʣ����ԴС�ڵ���MinSize��ȫ������ 
				s->space = p->space;
				s->startAdr = p->startAdr;
				p->space = 0;
				InsertList_K(K,s);//��s���뵽K��β�� 
			}
			else
			{//��ʾ�����������Դ���ýڵ����㹻�ռ�����ý��̣��и�ڵ� 
				s->space = size;
				s->startAdr = p->startAdr;
				p->space -= size;
				p->startAdr += size;
				InsertList_K(K,s);
			}
			return ;
		}
	}
	else
	{
		
		overall_pointer = p->next;
		if(overall_pointer == NULL)
		{//�ϴ�Ѱ�ҵ�β�ڵ� 
			overall_pointer = *L; 
		}
		p = overall_pointer;
		do
		{
			if(overall_pointer->space >= size)
			{//�Ľڵ��������Ҫ�� 
				s = (LinkList)malloc(sizeof(LNode));
				if(overall_pointer->space - size <= MinSize)
				{//��������������Դ�ϴ󣬷����ýڵ�ʣ����ԴС�ڵ���MinSize��ȫ������ 
					if(overall_pointer->before == NULL)
					{//��ʾ�ýڵ��������ײ� 
						(*L)->next = overall_pointer->next;
						overall_pointer->next->before = NULL;
						s = overall_pointer;
					}
					else if(overall_pointer->next == NULL)
					{//��ʾ�ýڵ�������β�� 
						overall_pointer->before->next = NULL;
						s = overall_pointer;
					}
					else
					{//��ʾ�ýڵ��������м� 
						overall_pointer->before->next = overall_pointer->next;
						overall_pointer->next->before = overall_pointer->before;
						s = overall_pointer;
					}
					
					s->name = name[0];
					InsertList_K(K,s);//��s���뵽K��β�� 
				}
				else
				{//��ʾ�����������Դ���ýڵ����㹻�ռ�����ý��̣��и�ڵ� 
					s->space = size;
					s->startAdr = overall_pointer->startAdr;
					overall_pointer->space -= size;
					overall_pointer->startAdr += size;
					s->name = name[0];
					InsertList_K(K,s);
				}
				return ;
			}
			else
			{
				overall_pointer = overall_pointer->next;
				if(overall_pointer == NULL)
				{
					overall_pointer = *L;
				}
				if(overall_pointer == p)
				{
					printf("\n**ERROR:û�пɷ�����Դ���ý���**\n\n");
					return ;
				}
			}
		}while(1);
	}
}

void NRelease(LinkList *L , LinkList *K)
{//�ͷŽ�����Դ����Դ����
	LinkList p, q; 
	char fname[1];
	printf("�������������");
	scanf("%s",fname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == fname[0])
		{//�ѷ��������б��д��ڸý��� 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//��ʾ������K���� 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//��ʾ�ýڵ��������ײ� 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//��ʾ�ýڵ�������β�� 
				p->before->next = NULL;
				q = p;
			}
			else
			{//��ʾ�ýڵ��������м� 
				p->before->next = p->next;
				p->next->before = p->before;
				q = p;
			}
			
			NInsertList_L(L ,q);
			return ;
		}
		else
		{//�����ڸý��� 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**������Ϸ��Ľ��������ѷ�������������޸ý���**\n\n");
				return ;
			}
		}
	}
}

void NInsertList_L(LinkList *L , LinkList s)
{
	LinkList p, q;
	p = *L;
	while(p != NULL)
	{
		if(s->startAdr <= p->startAdr)
		{
			if(p->before == NULL)
			{//p��L���׽ڵ� 
				if(s->startAdr+s->space == p->startAdr)
				{
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s);
				}
				else
				{
					q = (LinkList)malloc(sizeof(LNode));
					q = s;
					q->before = NULL;
					q->name = 'L';
					q->next = p;
					p->before = q;
					*L = q;
					//free(s);//*****///////////////////////////////////////���޸� 
				}
			}
			else
			{
				if(s->startAdr + s->space == p->startAdr && p->before->startAdr + p->before->space == s->startAdr)
				{//���սڵ���ǰ��ڵ���� 
					q = p->before;
					if(p == overall_pointer)
					{
						overall_pointer = q;
					} 
					q->space += s->space + p->space;
					q->next = p->next;
					if(p->next == NULL)
					{//��ʾp��β�� 
						q->next = NULL;
						free(s);
						free(p);
						return ; 
					} 
					//p����β�� 
					p->next->before = q;
					free(s);
					free(p);
				}
				else if(s->startAdr + s->space == p->startAdr)
				{//s�����ڵ�����������ǰ��ڵ����� 
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s); 
				}
				else if(p->before->startAdr + p->before->space == s->startAdr)
				{//s��ǰ��ڵ�������������漸������ 
					p->before->space += s->space;
					free(s); 
				}
				else
				{//�������� 
					q = (LinkList)malloc(sizeof(LNode));
					q = s;
					q->name = 'L';
					q->before = p->before;
					q->next = p;
					p->before = q;
					q->before->next = q;
				}
			}
			return ; 
		}
		else 
		{
			if(p->next == NULL)
			{//����L�����һ���ڵ� 
				if(p->startAdr + p->space == s->startAdr)
				{
					p->space += s->space;
					free(s);
					return ;
				}
			}
			p =p->next;
		}
	}
} 

/********�����Ӧ�㷨 *************/
void BestFit(LinkList *L , LinkList *K)
{//�����Ӧ�㷨
	menu2();
	InitList(L,1024,'L');
	InitList(K,0,'K');
	while(1)
	{ 
		switch(choose2())
		{
			case 1:
				BGetSpace(L, K);
				break;
			case 2:
				BRelease(L, K);
				break;
			case 3:
				FCompact(L , K);
				break;
			case 4:
				Display_L(*L);
				break;
			case 5:
				Display_K(*K);
				break; 
			default:
				return;
		}
	}
}

void BGetSpace(LinkList *L , LinkList *K)
{//�����Ӧ�㷨������Դ 
	LinkList p, s;
	char name[1];
	int size,length = 0;
	printf("�����������������ռ��С\n");
	scanf("%s %d",name, &size);
	p = *L;
	while(p != NULL)
	{//�������нڵ� 
		if(size <= p->space)
		{//��ʾ�ýڵ���Ը��������Դ����ռ� 
			s = (LinkList)malloc(sizeof(LNode));
			if(p->space - size <= MinSize)
			{//��������������Դ�ϴ󣬷����ýڵ�ʣ����ԴС�ڵ���MinSize��ȫ������ 
				if(p->before == NULL && p->next == NULL)
				{//��ʾ������L���� 
					s->space = p->space;
					s->startAdr = p->startAdr;
					p->space = 0;
				}
				else if(p->before == NULL)
				{//��ʾ�ýڵ��������ײ� 
					(*L)->next = p->next;
					p->next->before = NULL;
					s = p;
				}
				else if(p->next == NULL)
				{//��ʾ�ýڵ�������β�� 
					p->before->next = NULL;
					s = p;
				}
				else
				{//��ʾ�ýڵ��������м� 
					p->before->next = p->next;
					p->next->before = p->before;
					s = p;
				}
				
				s->name = name[0];
				InsertList_K(K,s);//��s���뵽K��β�� 
			}
			else
			{//��ʾ�����������Դ���ýڵ����㹻�ռ�����ý��̣��и�ڵ� 
				s->space = size;
				s->startAdr = p->startAdr;
				p->space -= size;
				p->startAdr += size;
				s->name = name[0];
				InsertList_K(K,s);
			}
			return ;
		}
		else
		{//��ʾ�ýڵ㲻���Է�����Դ���ý��� 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**ERROR:û�пɷ�����Դ���ý���**\n\n");
				return ; 
			}
		}
	}
}

void BRelease(LinkList *L , LinkList *K)
{//�ͷŽ�����Դ����Դ���� 
	LinkList p, q; 
	char Bname[1];
	printf("�������������");
	scanf("%s",Bname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == Bname[0])
		{//�ѷ��������б��д��ڸý��� 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//��ʾ������K���� 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//��ʾ�ýڵ��������ײ� 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//��ʾ�ýڵ�������β�� 
				q = p;
				p->before->next = NULL;
			}
			else
			{//��ʾ�ýڵ��������м� 
				q = p;
				p->before->next = p->next;
				p->next->before = p->before;
			}
			BInsertList_L(L ,q);
			return ;
		}
		else
		{//�����ڸý��� 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**������Ϸ��Ľ��������ѷ�������������޸ý���**\n\n");
			}
		}
	}
}

void BInsertList_L(LinkList *L , LinkList s)
{
	/*˼·һ���Ȱ�L��������ʼ��ַ�����ٵ���first fit�е�insertList_L�������ٰ��յ�ַ��С����ȱ�㣺����ʱ�临�ӶȽϴ󣬱ȽϷ�ʱ���ŵ㣺�������*/
	/*˼·�������ҵ��ýڵ��ǰһ���ڵ㣬���������ӣ����ҵ����Ľڵ㣬�����ٴ����ӣ���û�У����²���һ���ڵ㣬�ٴ������ŵ㣺ʱ�临�ӶȽ�������Լ򵥣�ȱ�㣺�����д����*/
	sort_L_startAdr(L);
	InsertList_L(L,s);
	sort_L(L);
}

void swap(int *a , int *b)
{
	int swap;
	swap = *a;
	*a = *b;
	*b = swap;
}

void sort_L_startAdr(LinkList *L)
{
	LinkList p, s;
	int i;
	for(i=0; i<ListLength(*L); i++)
	{
		p = *L;
		while(p->next != NULL)
		{//���������β�� 
			s = p->next;
			if(p->before == NULL && s->next ==NULL)
			{//������ֻ�������ڵ� 
				if(p->startAdr > s->startAdr)
				{
						swap(&s->space , &p->space);
					swap(&s->startAdr , &p->startAdr);
					return;
				} 
			}
			if(p->startAdr > s->startAdr)
			{
				swap(&s->space , &p->space);
				swap(&s->startAdr , &p->startAdr);
			}
			p = p->next;
		}//end of while
	}//end of for
} 

void sort_L(LinkList *L)
{
	LinkList p, s;
	int i;
	for(i=0; i<ListLength(*L); i++)
	{
		p = *L;
		while(p->next != NULL)
		{//���������β�� 
			s = p->next;
			if(p->before == NULL && s->next ==NULL)
			{//������ֻ�������ڵ� 
				if(p->space > s->space)
				{
					swap(&s->space , &p->space);
					swap(&s->startAdr , &p->startAdr);
					return;
				}
			}
			
			if(p->space > s->space)
			{
				swap(&s->space , &p->space);
				swap(&s->startAdr , &p->startAdr);
			}
			
			p = p->next;
		}//end of while
	}//end of for
}

void menu1()
{
	printf("=======�˵�һ=========\n");
	printf("1.�״���Ӧ�㷨\n");
	printf("2.ѭ���״���Ӧ�㷨\n");
	printf("3.�����Ӧ�㷨\n");
	printf("  ���������˳�����\n");
	printf("======================\n");
} 

void menu2()
{
	printf("\n******�ֲ˵�*******\n");
	printf("    1.�������\n    (�����ʽ�������� �ռ��С��ע��������Ϊ(Сд)a-z���ַ���һ���з�����)\n");
	printf("    2.�ͷŷ���\n   �������ʽ����������ע�����������������Ѿ���������Ľ��̣�\n");
	printf("    3.����\n");
	printf("    4.������з�����������L\n");
	printf("    5.����ѷ�����������K\n");
	printf("     ���������˳��÷���\n");
	printf("*********************\n");
} 

int choose1()
{
	int i;
	printf("\n��ѡ�� �˵�һ ���ܣ�1-3����");
	scanf("%d",&i);
	return i;
} 

int choose2()
{
	int k;
	printf("��ѡ�� �ֲ˵� ���ܣ�1-5����");
	scanf("%d",&k);
	return k;
} 
