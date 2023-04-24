# include <stdlib.h>
# include <unistd.h>
# include <iostream>
# include <string.h>
using namespace std;

typedef int	t_data;

typedef struct	ListNodeType
{
	t_data				data; //int -> t_data
	struct ListNodeType	*pLink;
}	ListNode;

typedef struct	LinkedListType
{
	int			currentElementCount; // 현재 저장된 원소의 개수
	ListNode	*headerNode; // 헤더 노드(Header Node)
}	LinkedList;

LinkedList	*createLinkedList(void)
{
	LinkedList	*lst;

	lst = (LinkedList *)malloc(sizeof(LinkedList));
	if (!lst)
		return (0);
	bzero(lst, sizeof(LinkedList));
	return (lst);
}

ListNode	*createListNode(int data)
{
	ListNode	*node;
	node = (ListNode *)malloc(sizeof(ListNode));
	if (!node)
		return (0);
	bzero(node, sizeof(ListNode));
	node->data = data;
	return (node);
}

bool	addLLElement(LinkedList *pList, int position, ListNode *element)
{
	ListNode	*cur;

	if (!pList)
		return (false);
	if (pList->currentElementCount < position) //position을 인덱스로 생각(0부터 시작)
		return (false);
	if (!pList->currentElementCount || !position)
	{
		if (!position && pList->currentElementCount)
			element->pLink = pList->headerNode;
		pList->headerNode = element;
		pList->currentElementCount++;
		return (true);
	}
	cur = pList->headerNode;
	for (int i = 1; i < position; i++)
		cur = cur->pLink;
	element->pLink = cur->pLink;
	cur->pLink = element;
	pList->currentElementCount++;
	return (true);
}

bool	addLLElementLast(LinkedList *pList, ListNode *element)
{
	ListNode *cur;

	if (!pList || !element)
	{
		printf("invalid input");
		return (false);
	}
	cur = pList->headerNode;
	pList->currentElementCount++;
	if (cur == NULL)
	{
		pList->headerNode = element;
		return (true);
	}
	while (cur->pLink)
		cur = cur->pLink;
	cur->pLink = element;
	return (true);
}

bool	removeLLElement(LinkedList *pList, int position)
{
	ListNode	*cur;
	ListNode	*next;

	if (!pList || !(pList->currentElementCount))
		return (false);
	if (position >= pList->currentElementCount)
		return (false);
	cur = pList->headerNode;
	if (!position)
	{
		pList->headerNode = cur->pLink;
		cur->pLink = 0;
		free(cur);
		pList->currentElementCount--;
		return (true);
	}
	for (int i = 0; i < position - 1; i++)
		cur = cur->pLink;
	next = cur->pLink->pLink;
	if (!(cur->pLink->pLink)) //지우려고 하는 노드가 마지막 노드가 아닐 때
		cur->pLink->pLink = 0;
	free(cur->pLink);
	cur->pLink = next;
	pList->currentElementCount--;
	return (true);
}

t_data	getLLElement(LinkedList *pList, int position)
{
	ListNode	*ret;

	if (!pList || position >= pList->currentElementCount)
		return (0);
	ret = pList->headerNode;
	for (int i = 0; i < position; i++)
		ret = ret->pLink;
	return (ret->data);
}

void	clearLinkedList(LinkedList *pList)
{
	ListNode	*cur;
	ListNode	*next;

	if (!pList || !(pList->currentElementCount))
		return ;
	cur = pList->headerNode;
	while (cur)
	{
		next = cur->pLink;
		free(cur);
		cur = next;
	}
	bzero(pList, sizeof(LinkedList));
}

int	getLinkedListLength(LinkedList *pList)
{
	return (pList->currentElementCount);
}

void	deleteLinkedList(LinkedList *pList)
{
	clearLinkedList(pList);
	free(pList);
}

int num;
LinkedList *list[101];

void input() {
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
		list[i] = createLinkedList();
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		ListNode *newNode = createListNode(b);
		addLLElement(list[a], list[a]->currentElementCount, newNode);
	}
}

int DAT[101] = {0};
int cnt = -1;
void solution(int idx) {
	if (DAT[idx])
		return;
	DAT[idx] = 1;
	cnt++;
	while (list[idx]->currentElementCount) {
		solution(getLLElement(list[idx], 0));
		removeLLElement(list[idx], 0);
	}
}

int main() {
	input();
	solution(1);
	cout << cnt << endl;
	for (int i = 1; i <= num; i++) {
		deleteLinkedList(list[i]);
	}
}
