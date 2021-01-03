#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define OK 0                //成功执行
#define Err_Memory -1       //内存分配错误
#define Err_InvalidParam -2 //输入参数无效
#define Err_Overflow -3     //溢出错误
#define Err_IllegalPos -4   //非法位置
#define Err_NoResult -5     //无返回结果或返回结果为空

typedef int Status;
typedef int ElemType;
typedef struct node
{
    ElemType id;
    ElemType password;
    struct node* next;
} ListNode,*LinkList;

//菜单——给出用户清晰选项
int Menu()
{
    printf("\n这是循环链表——约瑟夫环程序...\n");
    printf("\n现在  您有两个选择：\n");
    printf("1.进入程序\n");
    printf("2.退出程序\n");
    return 0;
}

//检查——确保参与人数n，报数上限m，密码password是正整数
int Check(int n)
{
    int num=n;
    while(num<=0)
    {
        printf("\n输入参数无效！请重新输入！");
        printf("\n新的参数为:");
        scanf("%d",&num);
    }
    return num;
}

//创建——分配id以及密码
Status CreateList(LinkList L,int n)
{
    LinkList p,s;
    int i,password;
    if(!L)
        return Err_InvalidParam;
    p=L;
    for(i=1; i<=n; i++)
    {
        s=(LinkList) malloc(sizeof(ListNode));                   //分配空间
        s->id=i;                                                 //分配id
        printf("请输入第%d位的密码（必须为正整数）:",i);
        scanf("%d",&password);
        s->password=Check(password);                             //分配密码password
        s->next=L;
        p->next=s;
        p=s;
    }
    return OK;
}

//遍历——使用户清晰了解各参与人员的密码
Status TraverList(LinkList L)
{
    if(!L)
        return Err_InvalidParam;
    ListNode* p=L->next;
    while(p!=L)
    {
        printf("ID:%d--->密码:%d\n",p->id,p->password);
        p=p->next;
    }
    return OK;
}

//约瑟夫环
int Josephus(LinkList Head,int m,int n,int* array)
{
    int iCount=1,iOrder=0,index=0;
    LinkList pcur,pprev,pdel;
    if(!Head)
        return Err_InvalidParam;
    pprev=Head;
    pcur=Head->next;
    while(pprev!=pcur->next)
    {
        if(pcur!=Head&&iCount==m)
        {
            pdel=pcur;
            pprev->next=pcur->next;
            pcur=pcur->next;
            iOrder++;
            printf("\n第%d个出列序号为:%d\n",iOrder,pdel->id);
            array[index++]=pdel->id;                            //记录序号
            printf("下一次报数上限m=%d\n",pdel->password);
            m=pdel->password;
            free(pdel);
            iCount=1;
        }
        else
        {
            if(pcur!=Head)
                iCount++;
            pprev=pcur;
            pcur=pcur->next;
        }
    }
    printf("\n第%d个出列序号为:%d\n",++iOrder,Head->next->id);
    array[index]=Head->next->id;
    free(pcur);
    free(pprev);
    return OK;
}

//准备函数——将事先准备的功能写入
int Ready()
{
    int n,m;
    int* p;
    ListNode *Joseph;
    printf("请输入参与人数:");
    scanf("%d",&n);
    n=Check(n);
    printf("请输入报数上限:");
    scanf("%d",&m);
    m=Check(m);
    printf("\n");
    Joseph=(ListNode *)malloc(sizeof(ListNode));
    p=(int *)malloc(sizeof(int)*n);
    if(CreateList(Joseph,n)!=OK)
    {
        printf("创建Joseph Circle 失败!\n");
        return 0;
    }
    printf("\n");
    if(TraverList(Joseph)!=OK)
    {
        printf("遍历失败!\n");
        return 0;
    }
    if(Joseph->next==Joseph)
    {
        printf("参与人数输入错误!\n");
        return 0;
    }
    printf("\n");
    Josephus(Joseph,m,n,p);
    printf("\n出列顺序为:");
    for(int i=0; i<n; i++)
    {
        printf(" %d ",p[i]);
    }
    printf("\n");
    return 0;
}

//主函数
int main()
{
    int choice;
    Menu();
    printf("请输入您的选项：");
    scanf("%d",&choice);
    while(choice!=2)
    {
        switch(choice)
        {
        case 1:
            Ready();
            break;
        case 2:
            exit(0);
        }
        Menu();
        printf("\n请输入您的选项choice:");
        scanf("%d",&choice);
    }
    return 0;
}


