typedef struct Node
{
	char name;
	int startAdr;  //数据域
	int space;//大小 
	struct Node *before;//指针域：指向前一个节点 
	struct Node *next; //指针域：指向直接后继
}LNode, *LinkList;

#define MinSize 15//不再切割的剩余区大小 

LinkList overall_pointer; 

void menu1();//打印菜单一 

void menu2();//打印分菜单 

int choose1();//选择菜单一功能

int choose2();//选择分菜单功能 

void Display_L(LinkList L);//显示空闲分区链表L

void Display_K(LinkList K);//显示已分配分区链表K 

int ListLength(LinkList L);//求链表长度 

void InitList(LinkList *L , int s , char na);//初始化空间为s的链表

/********首次适应算法**************/

void FirstFit(LinkList *L , LinkList *K); //首次适应算法 

void FGetSpace(LinkList *L , LinkList *K);//申请资源 

void InsertList_K(LinkList *K , LinkList s);//把s节点插入到链表K的尾部 

void FRelease(LinkList *L , LinkList *K);//释放进程资源 

void InsertList_L(LinkList *L , LinkList s);//把s节点插入到链表L里 

void FCompact(LinkList *L , LinkList *K);//紧凑 

/********循环适应算法*************/

void NextFit(LinkList *L , LinkList *K);//循环适应算法

void NGetSpace(LinkList *L , LinkList *K);//申请资源 

void NRelease(LinkList *L , LinkList *K);//释放进程资源 

void NInsertList_L(LinkList *L , LinkList s);//把s插入到L中 

/********最佳适应算法 *************/

void BestFit(LinkList *L , LinkList *K);//最佳适应算法 

void sort_L(LinkList *L);//给L按照地址空间进行排列 

void sort_L_startAdr(LinkList *L);//按照起始地址排序 

void swap(int *a , int *b);

void BGetSpace(LinkList *L , LinkList *K);//申请资源 

void BRelease(LinkList *L , LinkList *K);//释放进程资源 

void BInsertList_L(LinkList *L , LinkList s);//把s节点插入到链表L里 

void BCompact(LinkList *L , LinkList *K);//紧凑 

