#include <iostream>
using namespace std;
typedef char ListData;

struct LinkNode
{
    ListData data;
    LinkNode *link;
};

class LinkList
{
private:
    LinkNode *first;

public:
    LinkList();
    ~LinkList();
    void inputFront();                  //前插法
    void inputRear();                   //后插法
    bool insertNode(ListData x, int i); //在第i个结点后插入，0<=i<=length
    bool deleteNode(int i);             //删除第i个结点，0<i<=length
    LinkNode *locateNode(int i);        //获取第i个结点，0<=i<=length
    int findNode(ListData x);           //返回值为数据序号，0<i<=length
    void sortNode();
    void reverseNode();
    void outputNode();
};

LinkList::LinkList()
{
    first = new LinkNode; //初始化头结点
    first->data = '\0';
    first->link = NULL;
}

LinkList::~LinkList()
{
    LinkNode *p;
    while (first->link != NULL) //依次删除各结点
    {
        p = first->link;
        first->link = p->link;
        delete p;
    }
    delete first; //删除头结点
}

void LinkList::inputFront()
{
    char val;
    while ((val = getchar()) != '\n')
    {
        LinkNode *newNode = new LinkNode; //分配新结点空间
        newNode->data = val;
        newNode->link = first->link;
        first->link = newNode;
    }
}

void LinkList::inputRear()
{
    char val;
    LinkNode *p = first;
    while (p->link != NULL) //定位到最后一个结点
        p = p->link;
    while ((val = getchar()) != '\n')
    {
        LinkNode *newNode = new LinkNode; //分配新结点空间
        newNode->data = val;
        newNode->link = NULL;
        p->link = newNode;
        p = newNode;
    }
    p->link = NULL;
}

bool LinkList::insertNode(ListData x, int i)
{
    LinkNode *p = locateNode(i); //使用locateNode函数定位到指定结点
    if (p == NULL)
        return false;
    LinkNode *newNode = new LinkNode; //分配新结点空间
    newNode->data = x;
    newNode->link = p->link;
    p->link = newNode;
    return true;
}

bool LinkList::deleteNode(int i)
{
    LinkNode *p = locateNode(i - 1); //使用locateNode函数定位到指定结点
    if (p == NULL)
        return false;
    LinkNode *q = p->link;
    p->link = q->link;
    delete q;
    return true;
}

LinkNode *LinkList::locateNode(int i)
{
    if (i < 0)
        return NULL;
    LinkNode *p = first;
    for (int k = 1; k <= i; k++)
    {
        if (p == NULL)
            return NULL;
        p = p->link;
    }
    return p;
}

int LinkList::findNode(ListData x)
{
    LinkNode *p = first->link;
    int count = 1;
    while (p != NULL)
    {
        if (p->data == x)
            return count;
        p = p->link;
        count++;
    }
    return -1;
}

void LinkList::sortNode()
{
    LinkNode *complete = first;
    while (complete->link != NULL)
    {
        LinkNode *min = complete->link;
        LinkNode *min_pre = complete;
        LinkNode *p = min;
        LinkNode *p_pre = min_pre;
        while (p != NULL)
        {
            if (min->data > p->data)
            {
                min = p;
                min_pre = p_pre;
            }
            p = p->link;
            p_pre = p_pre->link;
        }
        min_pre->link = min->link;
        min->link = complete->link;
        complete->link = min;
        complete = complete->link;
    }
}

void LinkList::reverseNode()
{
    if (first->link == NULL)
        return;
    LinkNode *pre = first->link;
    LinkNode *p = pre->link;
    pre->link = NULL;
    while (p != NULL)
    {
        LinkNode *next = p->link;
        p->link = pre;
        pre = p;
        p = next;
    }
    first->link = pre;
}

void LinkList::outputNode()
{
    LinkNode *p = first->link;
    while (p != NULL)
    {
        cout << p->data;
        p = p->link;
    }
    cout << endl;
}

void merge(LinkList &A, LinkList &B)
{
    A.sortNode();
    B.sortNode();
    LinkNode *pa = A.locateNode(0);
    LinkNode *pb = B.locateNode(0);
    while (pb->link != NULL)
    {
        if (pb->link->data <= pa->link->data)
        {
            LinkNode *start = pb->link;
            LinkNode *end = start;
            ListData compare = pa->link->data;
            while ((end->link != NULL) && (end->link->data <= compare))
                end = end->link;
            pb->link = end->link;
            end->link = pa->link;
            pa->link = start;
            pa = end;
        }
        else
            pa = pa->link;
        if (pa->link == NULL)
        {
            pa->link = pb->link;
            pb->link = NULL;
        }
    }
    A.reverseNode();
}
