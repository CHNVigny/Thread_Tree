#include <stdio.h>
#include <stdlib.h>

#define Link 0

#define  Thread 1		//Link==0,Thread==1;线索
typedef char datatype;
//构造线索二叉树节点


typedef struct node1
{
	datatype data;
	struct node1 *lchild;
	struct node1 *rchild;
	int Ltag;
	int Rtag;
}Treenode,* Treep;
Treep pre;                   /*全局变量，用于二叉树的线索化*/

//初始化二叉树
Treep init_tree()
{
    Treep root= (Treep)malloc(sizeof(Treenode));
	printf("初始化成功！\n");
	return root;
}
//创建二叉树,这个功能应该改成可以从文件中读取的。
void creat_tree(Treep rt, FILE *fp)
{
    char ch;
    ch=fgetc(fp);
	if (EOF == ch)
		return;
	else if ('#' == ch)
	{
		free(rt);
		rt = NULL;
	}
    else
    {
        //rt=(Treep)malloc(sizeof(Treenode));
        rt->data=ch;
        rt->Ltag=Link;
        rt->Rtag=Link;
		rt->lchild = (Treep)malloc(sizeof(Treenode));
		rt->rchild = (Treep)malloc(sizeof(Treenode));
        creat_tree(rt->lchild,fp);        //构造左子树
        creat_tree(rt->rchild,fp);    //构造右子树
    }
}
//前序遍历二叉树
void pre_order(Treep rt)
{
    if(rt!=NULL)
    {
        printf("%c ",rt->data);
        pre_order(rt->lchild);
        pre_order(rt->rchild);
    }
}

//前序线索化二叉树
void preThreading(Treep p)
{
		
		if(p)
    {
        if(p->lchild == NULL)
        {
            p->Ltag=Thread;
            p->lchild=pre;        //前继线索
        }
        if(pre->rchild == NULL)
        {
            pre->Rtag=Thread;
            pre->rchild=p;        //后继线索
        }
        pre = p;
        if(Link==p->Ltag) //递归，如果p的左儿子不空，则线索化左子树
            preThreading(p->lchild);
        if(Link==p->Rtag)//同理
            preThreading(p->rchild);
    }
}//InThreading

Treep preorderThreading(Treep rt)
{
    Treep thrt;
    thrt = (Treep) malloc (sizeof(Treenode));
    thrt->Ltag=Link;
    thrt->Rtag=Thread;    //建头结点
    thrt->rchild=thrt;    //右指针回指
    if(rt == NULL)
        thrt->lchild=thrt;    //若二叉树空，则左指针回指
    else
    {
        thrt->lchild=rt;
        pre=thrt;
        preThreading(rt);        //前序遍历进行中序线索化
        pre->rchild=thrt;        //最后一个节点处理
        pre->Rtag=Thread;
        thrt->rchild=pre;
    }
    return thrt;
}



//前序遍历线索二叉树
void preorderTraver(Treep thrt)
{
    Treep p;
    p=thrt->lchild;
    while(p!=thrt)
    {
        printf("%c ",p->data);//cout<<p->data<<"  ";
        if(Link==p->Ltag)
            p=p->lchild;
        else
            p=p->rchild;
    }
}

int main()
{
    Treep root = init_tree();        //初始化树
	FILE *fp;
	if ((fp = fopen("source.txt", "r")) == NULL)
	{
		printf("打开文件失败！\n");
		exit(-1);
	}
    
	//printf("请输入二叉树,空值以#代表，输完以$表示结束:");
    creat_tree(root,fp);        //创建二叉树
	if (fclose(fp) != 0) 
		{
			printf("文件关闭失败！/n");
			exit(1);
		}
    //前序遍历二叉树
    printf("前序遍历序列是:\n");
    pre_order(root);
    printf("\n");

    Treep thrt;
    thrt=preorderThreading(root);
    preorderTraver(thrt);
    printf("\n");
    return 0;
}
