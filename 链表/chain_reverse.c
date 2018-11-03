/**************链表反转**************/


node *reverseList(node *H)
{
	if(H == NULL || H->next == NULL)
	{
		return H;
	}

	node *p = H, *newH = NULL;
	while(p != NULL)
	{
		node *temp = p->next;
		p->next = newH;
		newH = p;
		p = temp;
	}
	
	return newH;
}
