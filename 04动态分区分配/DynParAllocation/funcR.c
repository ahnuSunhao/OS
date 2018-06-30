#include"head.h"
#include"func.h"

void InitList(LinkList *L , int s , char na)
{//初始化L和K链表 
	*L=(LinkList)malloc(sizeof(LNode)); //给头结点分配内存空间
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
		printf("链表为空");
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
		printf("链表为空");
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

/********首次适应算法**************/
void FirstFit(LinkList *L , LinkList *K)
{//首次适应算法 
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
{//首次适应算法申请资源 
	LinkList p, s;
	char name[1];
	int size, temp = -1,length = 0;
	printf("请输入进程名和申请空间大小\n");
	scanf("%s %d",name, &size);
	p = *L;
	while(p != NULL)
	{//遍历所有节点 
		if(size <= p->space)
		{//表示该节点可以给申请的资源分配空间 
			s = (LinkList)malloc(sizeof(LNode));
			
			if(p->space - size <= MinSize)
			{//如果进程申请的资源较大，分配后该节点剩余资源小于等于MinSize，全部分配 
				if(p->before == NULL && p->next == NULL)
				{//表示是链表L整块 
					temp = 0;
				}
				else if(p->before == NULL)
				{//表示该节点在链表首部 
					(*L)->next = p->next;
					p->next->before = NULL;
					s = p;
				}
				else if(p->next == NULL)
				{//表示该节点在链表尾部 
					p->before->next = NULL;
					s = p;
				}
				else
				{//表示该节点在链表中间 
					p->before->next = p->next;
					p->next->before = p->before;
					s = p;
				}
				if(temp == 0)
				{//说明把首部全部分配出去给链表K 
					s->space = p->space;
					s->startAdr = p->startAdr;
					p->space = 0;
				}
				s->name = name[0];
				InsertList_K(K,s);//把s插入到K的尾部 
			}
			else
			{//表示进程申请的资源，该节点有足够空间满足该进程，切割节点 
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
		{//表示该节点不足以分配资源给该进程 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**ERROR:没有可分配资源给该进程**\n\n"); 
			}
		}
	}
}

void InsertList_K(LinkList *K, LinkList s)
{//把s节点插入到链表K的尾部 
	LinkList p;
	int startAd = 0;
	p = *K;
	while(p->next != NULL) 
	{//遍历到最后一个节点 
		p = p->next; 
	}
	p->next = s;
	s->before = p;
	s->next = NULL;
}

void FRelease(LinkList *L , LinkList *K)
{//释放进程资源，资源回收
	LinkList p, q; 
	char fname[1];
	printf("请输入进程名：");
	scanf("%s",fname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == fname[0])
		{//已分区分配列表中存在该进程 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//表示是链表K整块 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//表示该节点在链表首部 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//表示该节点在链表尾部 
				p->before->next = NULL;
				q = p;
			}
			else
			{//表示该节点在链表中间 
				p->before->next = p->next;
				p->next->before = p->before;
				q = p;
			}
			
			InsertList_L(L ,q);
			return ;
		}
		else
		{//不存在该进程 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**请输入合法的进程名，已分配分区链表中无该进程**\n\n");
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
			{//p是L的首节点 
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
					//free(s);//*****///////////////////////////////////////待修改 
				}
			}
			else
			{
				if(s->startAdr + s->space == p->startAdr && p->before->startAdr + p->before->space == s->startAdr)
				{//回收节点与前后节点相接 
					q = p->before;
					q->space += s->space + p->space;
					q->next = p->next;
					if(p->next == NULL)
					{//表示p是尾部 
						q->next = NULL;
						free(s);
						free(p);
						return ; 
					} 
					//p不是尾部 
					p->next->before = q;
					free(s);
					free(p);
				}
				else if(s->startAdr + s->space == p->startAdr)
				{//s后后面节点相连，不与前面节点相连 
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s); 
				}
				else if(p->before->startAdr + p->before->space == s->startAdr)
				{//s和前面节点相连，不与后面几点相连 
					p->before->space += s->space;
					free(s); 
				}
				else
				{//均不相连 
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
			{//到达L的最后一个节点 
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


/********循环适应算法*************/
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
				overall_pointer = *L;//修改全局指针 
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
	printf("请输入进程名和申请空间大小\n");
	scanf("%s %d",name, &size);
	if(overall_pointer == NULL)
	{
		overall_pointer = *L;
	} 
	p = overall_pointer;
	if(p->next == NULL && p->before == NULL)
	{//表示空闲分区分配链表中只有一个节点 
		if(size > p->space)
		{
			printf("\n**ERROR:没有可分配资源给该进程**\n\n");
			return ;
		}
		else
		{//表示该节点空闲空间足够分给该节点
			s = (LinkList)malloc(sizeof(LNode));
			s->name = name[0];
			if(p->space - size <= MinSize)
			{//如果进程申请的资源较大，分配后该节点剩余资源小于等于MinSize，全部分配 
				s->space = p->space;
				s->startAdr = p->startAdr;
				p->space = 0;
				InsertList_K(K,s);//把s插入到K的尾部 
			}
			else
			{//表示进程申请的资源，该节点有足够空间满足该进程，切割节点 
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
		{//上次寻找到尾节点 
			overall_pointer = *L; 
		}
		p = overall_pointer;
		do
		{
			if(overall_pointer->space >= size)
			{//改节点满足分配要求 
				s = (LinkList)malloc(sizeof(LNode));
				if(overall_pointer->space - size <= MinSize)
				{//如果进程申请的资源较大，分配后该节点剩余资源小于等于MinSize，全部分配 
					if(overall_pointer->before == NULL)
					{//表示该节点在链表首部 
						(*L)->next = overall_pointer->next;
						overall_pointer->next->before = NULL;
						s = overall_pointer;
					}
					else if(overall_pointer->next == NULL)
					{//表示该节点在链表尾部 
						overall_pointer->before->next = NULL;
						s = overall_pointer;
					}
					else
					{//表示该节点在链表中间 
						overall_pointer->before->next = overall_pointer->next;
						overall_pointer->next->before = overall_pointer->before;
						s = overall_pointer;
					}
					
					s->name = name[0];
					InsertList_K(K,s);//把s插入到K的尾部 
				}
				else
				{//表示进程申请的资源，该节点有足够空间满足该进程，切割节点 
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
					printf("\n**ERROR:没有可分配资源给该进程**\n\n");
					return ;
				}
			}
		}while(1);
	}
}

void NRelease(LinkList *L , LinkList *K)
{//释放进程资源，资源回收
	LinkList p, q; 
	char fname[1];
	printf("请输入进程名：");
	scanf("%s",fname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == fname[0])
		{//已分区分配列表中存在该进程 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//表示是链表K整块 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//表示该节点在链表首部 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//表示该节点在链表尾部 
				p->before->next = NULL;
				q = p;
			}
			else
			{//表示该节点在链表中间 
				p->before->next = p->next;
				p->next->before = p->before;
				q = p;
			}
			
			NInsertList_L(L ,q);
			return ;
		}
		else
		{//不存在该进程 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**请输入合法的进程名，已分配分区链表中无该进程**\n\n");
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
			{//p是L的首节点 
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
					//free(s);//*****///////////////////////////////////////待修改 
				}
			}
			else
			{
				if(s->startAdr + s->space == p->startAdr && p->before->startAdr + p->before->space == s->startAdr)
				{//回收节点与前后节点相接 
					q = p->before;
					if(p == overall_pointer)
					{
						overall_pointer = q;
					} 
					q->space += s->space + p->space;
					q->next = p->next;
					if(p->next == NULL)
					{//表示p是尾部 
						q->next = NULL;
						free(s);
						free(p);
						return ; 
					} 
					//p不是尾部 
					p->next->before = q;
					free(s);
					free(p);
				}
				else if(s->startAdr + s->space == p->startAdr)
				{//s后后面节点相连，不与前面节点相连 
					p->startAdr = s->startAdr;
					p->space += s->space;
					free(s); 
				}
				else if(p->before->startAdr + p->before->space == s->startAdr)
				{//s和前面节点相连，不与后面几点相连 
					p->before->space += s->space;
					free(s); 
				}
				else
				{//均不相连 
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
			{//到达L的最后一个节点 
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

/********最佳适应算法 *************/
void BestFit(LinkList *L , LinkList *K)
{//最佳适应算法
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
{//最佳适应算法申请资源 
	LinkList p, s;
	char name[1];
	int size,length = 0;
	printf("请输入进程名和申请空间大小\n");
	scanf("%s %d",name, &size);
	p = *L;
	while(p != NULL)
	{//遍历所有节点 
		if(size <= p->space)
		{//表示该节点可以给申请的资源分配空间 
			s = (LinkList)malloc(sizeof(LNode));
			if(p->space - size <= MinSize)
			{//如果进程申请的资源较大，分配后该节点剩余资源小于等于MinSize，全部分配 
				if(p->before == NULL && p->next == NULL)
				{//表示是链表L整块 
					s->space = p->space;
					s->startAdr = p->startAdr;
					p->space = 0;
				}
				else if(p->before == NULL)
				{//表示该节点在链表首部 
					(*L)->next = p->next;
					p->next->before = NULL;
					s = p;
				}
				else if(p->next == NULL)
				{//表示该节点在链表尾部 
					p->before->next = NULL;
					s = p;
				}
				else
				{//表示该节点在链表中间 
					p->before->next = p->next;
					p->next->before = p->before;
					s = p;
				}
				
				s->name = name[0];
				InsertList_K(K,s);//把s插入到K的尾部 
			}
			else
			{//表示进程申请的资源，该节点有足够空间满足该进程，切割节点 
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
		{//表示该节点不足以分配资源给该进程 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**ERROR:没有可分配资源给该进程**\n\n");
				return ; 
			}
		}
	}
}

void BRelease(LinkList *L , LinkList *K)
{//释放进程资源，资源回收 
	LinkList p, q; 
	char Bname[1];
	printf("请输入进程名：");
	scanf("%s",Bname);
	p = *K;
	while(p!=NULL)
	{
		if(p->name == Bname[0])
		{//已分区分配列表中存在该进程 
			q = (LinkList)malloc(sizeof(LNode));
			if(p->before == NULL && p->next == NULL)
			{//表示是链表K整块 
				//temp = 0;
				q = p;
				p->space = 0;
			}
			else if(p->before == NULL)
			{//表示该节点在链表首部 
				q = p;
				(*K)->next = p->next;
				p->next->before = NULL;
			}
			else if(p->next == NULL)
			{//表示该节点在链表尾部 
				q = p;
				p->before->next = NULL;
			}
			else
			{//表示该节点在链表中间 
				q = p;
				p->before->next = p->next;
				p->next->before = p->before;
			}
			BInsertList_L(L ,q);
			return ;
		}
		else
		{//不存在该进程 
			p = p->next;
			if(p==NULL)
			{
				printf("\n**请输入合法的进程名，已分配分区链表中无该进程**\n\n");
			}
		}
	}
}

void BInsertList_L(LinkList *L , LinkList s)
{
	/*思路一：先把L链表按照起始地址排序，再调用first fit中的insertList_L方法，再按照地址大小排序，缺点：排序时间复杂度较大，比较费时，优点：代码简练*/
	/*思路二：先找到该节点的前一个节点，可以则连接，再找到其后的节点，可以再次连接，都没有，再新插入一个节点，再次排序，优点：时间复杂度教排序而言简单，缺点：代码编写不便*/
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
		{//到达链表的尾部 
			s = p->next;
			if(p->before == NULL && s->next ==NULL)
			{//链表中只有两个节点 
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
		{//到达链表的尾部 
			s = p->next;
			if(p->before == NULL && s->next ==NULL)
			{//链表中只有两个节点 
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
	printf("=======菜单一=========\n");
	printf("1.首次适应算法\n");
	printf("2.循环首次适应算法\n");
	printf("3.最佳适应算法\n");
	printf("  其他数字退出程序\n");
	printf("======================\n");
} 

void menu2()
{
	printf("\n******分菜单*******\n");
	printf("    1.申请分区\n    (输入格式：进程名 空间大小。注：进程名为(小写)a-z的字符，一个有符号数)\n");
	printf("    2.释放分区\n   （输入格式：进程名。注：进程名必须在是已经申请分区的进程）\n");
	printf("    3.紧凑\n");
	printf("    4.输出空闲分区分配链表L\n");
	printf("    5.输出已分区分配链表K\n");
	printf("     其他数字退出该方法\n");
	printf("*********************\n");
} 

int choose1()
{
	int i;
	printf("\n请选择 菜单一 功能（1-3）：");
	scanf("%d",&i);
	return i;
} 

int choose2()
{
	int k;
	printf("请选择 分菜单 功能（1-5）：");
	scanf("%d",&k);
	return k;
} 
