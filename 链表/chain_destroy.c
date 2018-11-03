#include <stdio.h>
#include <stdlib.h>


 //销毁链表    销毁：是先销毁了链表的头，然后接着一个一个的把后面的销毁了，这样这个链表就不能再使用了，即把包括头的所有节点全部释放。
int DestroyList(struct student *head)  
{  
    struct student *p;  
    if(head==NULL)  
        return 0;  
    while(head)      //--------------------记住！！！--------------------
    {  
        p=head->next;  
        free(head);  
        head=p;  
    }  
    return 1;  
} 


 //清空链表    清空：是先保留了链表的头，然后把头后面的所有的都销毁，最后把头里指向下一个的指针设为空，这样就相当与清空了，但这个链表还在，还可以继续使用；即保留了头，后面的全部释放。
int ClearList(struct student *head)  
{  
    struct student *p,*q;  
    if(head==NULL)  
        return 0;  
    p=head->next;  
    while(p!=NULL)  
    {  
        q=p->next;  
        free(p);  
        p=q;  
    }  
    head->next=NULL;  
    return 1;  
}  








//practice
int Destory(listnode* head)
{
	listnode* p = NULL;
	if(NULL == head) return 0;

	while(head)
	{
		p = head->next;
		free(head); //or delete head;
		head = p;
	}
	return 0;
}


int Clear_chain(listnode* head)
{
	listnode* p = NULL;	
	listnode* q = NULL;
	if(NULL == head) return -1;

	p = head->next;
	while(p)
	{
		q = p->next;
		free(q);
		p = q;
	}
	head->next = NULL;
	return 0;
}









