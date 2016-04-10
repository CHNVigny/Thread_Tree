#include <stdio.h>
#include <stdlib.h>

#define Link 0

#define  Thread 1		//Link==0,Thread==1;����
typedef char datatype;
//���������������ڵ�


typedef struct node1
{
	datatype data;
	struct node1 *lchild;
	struct node1 *rchild;
	int Ltag;
	int Rtag;
}Treenode,* Treep;
Treep pre;                   /*ȫ�ֱ��������ڶ�������������*/

//��ʼ��������
Treep init_tree()
{
    Treep root= (Treep)malloc(sizeof(Treenode));
	printf("��ʼ���ɹ���\n");
	return root;
}
//����������,�������Ӧ�øĳɿ��Դ��ļ��ж�ȡ�ġ�
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
        creat_tree(rt->lchild,fp);        //����������
        creat_tree(rt->rchild,fp);    //����������
    }
}
//ǰ�����������
void pre_order(Treep rt)
{
    if(rt!=NULL)
    {
        printf("%c ",rt->data);
        pre_order(rt->lchild);
        pre_order(rt->rchild);
    }
}

//ǰ��������������
void preThreading(Treep p)
{
		
		if(p)
    {
        if(p->lchild == NULL)
        {
            p->Ltag=Thread;
            p->lchild=pre;        //ǰ������
        }
        if(pre->rchild == NULL)
        {
            pre->Rtag=Thread;
            pre->rchild=p;        //�������
        }
        pre = p;
        if(Link==p->Ltag) //�ݹ飬���p������Ӳ��գ���������������
            preThreading(p->lchild);
        if(Link==p->Rtag)//ͬ��
            preThreading(p->rchild);
    }
}//InThreading

Treep preorderThreading(Treep rt)
{
    Treep thrt;
    thrt = (Treep) malloc (sizeof(Treenode));
    thrt->Ltag=Link;
    thrt->Rtag=Thread;    //��ͷ���
    thrt->rchild=thrt;    //��ָ���ָ
    if(rt == NULL)
        thrt->lchild=thrt;    //���������գ�����ָ���ָ
    else
    {
        thrt->lchild=rt;
        pre=thrt;
        preThreading(rt);        //ǰ�������������������
        pre->rchild=thrt;        //���һ���ڵ㴦��
        pre->Rtag=Thread;
        thrt->rchild=pre;
    }
    return thrt;
}



//ǰ���������������
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
    Treep root = init_tree();        //��ʼ����
	FILE *fp;
	if ((fp = fopen("source.txt", "r")) == NULL)
	{
		printf("���ļ�ʧ�ܣ�\n");
		exit(-1);
	}
    
	//printf("�����������,��ֵ��#����������$��ʾ����:");
    creat_tree(root,fp);        //����������
	if (fclose(fp) != 0) 
		{
			printf("�ļ��ر�ʧ�ܣ�/n");
			exit(1);
		}
    //ǰ�����������
    printf("ǰ�����������:\n");
    pre_order(root);
    printf("\n");

    Treep thrt;
    thrt=preorderThreading(root);
    preorderTraver(thrt);
    printf("\n");
    return 0;
}
