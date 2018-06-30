typedef struct process{
	int max[M];//表示该个进程所需要的资源数 
	int allocation[M];//表示该进程此时拥有多少资源 
	int need[M];//表示该进程还需要多少资源 
	
	int flag;//用于记录次进程是否能够被满足 
}pro;

int m ,n;

void menu();//打印菜单 

void print(int i , pro p[] , int available[]);//打印数据

void readData(pro p[] , int available[]);//读取数据

int compare(int a[] , int b[]);//比较两个数组各个元素的大小

void isSafe(pro p[] , int available[]);//判断当前是否安全 

void judgeSafe(pro p[] , int available[]);//判断提出请求后是否合法 
