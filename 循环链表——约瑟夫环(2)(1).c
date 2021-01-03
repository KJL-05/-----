#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define OK 0                //�ɹ�ִ��
#define Err_Memory -1       //�ڴ�������
#define Err_InvalidParam -2 //���������Ч
#define Err_Overflow -3     //�������
#define Err_IllegalPos -4   //�Ƿ�λ��
#define Err_NoResult -5     //�޷��ؽ���򷵻ؽ��Ϊ��

typedef int Status;
typedef int ElemType;
typedef struct node
{
    ElemType id;
    ElemType password;
    struct node* next;
} ListNode,*LinkList;

//�˵����������û�����ѡ��
int Menu()
{
    printf("\n����ѭ��������Լɪ�򻷳���...\n");
    printf("\n����  ��������ѡ��\n");
    printf("1.�������\n");
    printf("2.�˳�����\n");
    return 0;
}

//��顪��ȷ����������n����������m������password��������
int Check(int n)
{
    int num=n;
    while(num<=0)
    {
        printf("\n���������Ч�����������룡");
        printf("\n�µĲ���Ϊ:");
        scanf("%d",&num);
    }
    return num;
}

//������������id�Լ�����
Status CreateList(LinkList L,int n)
{
    LinkList p,s;
    int i,password;
    if(!L)
        return Err_InvalidParam;
    p=L;
    for(i=1; i<=n; i++)
    {
        s=(LinkList) malloc(sizeof(ListNode));                   //����ռ�
        s->id=i;                                                 //����id
        printf("�������%dλ�����루����Ϊ��������:",i);
        scanf("%d",&password);
        s->password=Check(password);                             //��������password
        s->next=L;
        p->next=s;
        p=s;
    }
    return OK;
}

//��������ʹ�û������˽��������Ա������
Status TraverList(LinkList L)
{
    if(!L)
        return Err_InvalidParam;
    ListNode* p=L->next;
    while(p!=L)
    {
        printf("ID:%d--->����:%d\n",p->id,p->password);
        p=p->next;
    }
    return OK;
}

//Լɪ��
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
            printf("\n��%d���������Ϊ:%d\n",iOrder,pdel->id);
            array[index++]=pdel->id;                            //��¼���
            printf("��һ�α�������m=%d\n",pdel->password);
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
    printf("\n��%d���������Ϊ:%d\n",++iOrder,Head->next->id);
    array[index]=Head->next->id;
    free(pcur);
    free(pprev);
    return OK;
}

//׼����������������׼���Ĺ���д��
int Ready()
{
    int n,m;
    int* p;
    ListNode *Joseph;
    printf("�������������:");
    scanf("%d",&n);
    n=Check(n);
    printf("�����뱨������:");
    scanf("%d",&m);
    m=Check(m);
    printf("\n");
    Joseph=(ListNode *)malloc(sizeof(ListNode));
    p=(int *)malloc(sizeof(int)*n);
    if(CreateList(Joseph,n)!=OK)
    {
        printf("����Joseph Circle ʧ��!\n");
        return 0;
    }
    printf("\n");
    if(TraverList(Joseph)!=OK)
    {
        printf("����ʧ��!\n");
        return 0;
    }
    if(Joseph->next==Joseph)
    {
        printf("���������������!\n");
        return 0;
    }
    printf("\n");
    Josephus(Joseph,m,n,p);
    printf("\n����˳��Ϊ:");
    for(int i=0; i<n; i++)
    {
        printf(" %d ",p[i]);
    }
    printf("\n");
    return 0;
}

//������
int main()
{
    int choice;
    Menu();
    printf("����������ѡ�");
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
        printf("\n����������ѡ��choice:");
        scanf("%d",&choice);
    }
    return 0;
}


