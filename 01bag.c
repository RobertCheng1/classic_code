#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//http://www.tuicool.com/articles/fuQf2uu
//http://www.jianshu.com/p/48f2dd394608
int V[20][20];//前i个物品装入容量为j的背包中获得的最大价值
int max(int a,int b)  //一个大小比较函数，用于当总重大于第I行时 
{
   if(a>=b)
		return a;
   else 
		return b;
}

int Knap(int n,int w[],int v[],int x[],int C)
{
	int i,j;
	for(i=0;i<=n;i++)
		V[i][0]=0;
	for(j=0;j<=C;j++)
		V[0][j]=0;

	for(i=1;i<n;i++)
	{
		for(j=0;j<=C;j++)
		{	
			if(j<w[i])
				V[i][j]=V[i-1][j];
			else
				V[i][j]=max(V[i-1][j],V[i-1][j-w[i]]+v[i]);
		}
	}
	
	j=C;
	for(i=n-1;i>0;i--)
	{
		printf("i = %d , j = %d\n", i , j);
		printf("V[i][j] = %d , V[i-1][j] = %d\n", V[i][j] , V[i-1][j]);
		if(V[i][j]>V[i-1][j])
		{
			x[i]=1;
			j=j-w[i];
		}
		else
		{	
			x[i]=0;   
		}	
	}
	printf("选中的物品是:\n");
	for(i=0;i<n;i++)
		printf("%d ",x[i]);
	printf("\n");
	for(i = 0; i< 20; i++)
	{
		for(j = 0; j<20; j++)
			printf("%2d   ", V[i][j]);			
		printf("\n");
	}	
	return V[n-1][C];
		
}

int main()
{
	int s;//获得的最大价值
	int w[5];//物品的重量   重量  价值  和物品的状态 均对应着存到数组中，物品从1开始。 
	int v[5];//物品的价值
	int x[5];//物品的选取状态   选中则是1  没选中为0 
	int n,i;
	int C;//背包最大容量
	memset(V,0, sizeof(V));
	memset(w,0, sizeof(w));
	memset(v,0, sizeof(v));
	memset(x,0, sizeof(x));
	printf("请输入背包的最大容量:\n");
	scanf("%d",&C);
	
	printf("物品数是4，物品下标从1开始\n");
	n=5;
	//scanf("%d",&n);
	printf("请分别输入物品的重量:\n");
	for(i=1;i<n;i++)
		scanf("%d",&w[i]);

	printf("请分别输入物品的价值:\n");
	for(i=1;i<n;i++)
		scanf("%d",&v[i]);

	s=Knap(n,w,v,x,C);  //调用核心函数 

	printf("最大物品价值为:\n");
	printf("%d\n",s);
	//system("pause");
	return 0;
}
