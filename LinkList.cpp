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
    void inputFront();
    void inputRear();
    bool insertNode(ListData x, int i);
    bool deleteNode(int i);
    LinkNode *LocateNode(int i);
    LinkNode *findNode(ListData x);
    void sortNode();
    void reverseNode();
    void outputNode();
};

LinkList::LinkList()
{
    first = new LinkNode;
    first->link = NULL;
}

LinkList::~LinkList()
{
    LinkNode *p;
    while (first->link != NULL)
    {
        p = first->link;
        first->link = p->link;
        delete p;
    }
}

void LinkList::inputFront()
{
    char val;
    cin >> val;
    while (val != '\n')
    {
        LinkNode *newNode = new LinkNode;
        newNode->data = val;
        newNode->link = first->link;
        first->link = newNode;
        cin >> val;
    }
}

void LinkList::inputRear()
{
    char val;
    LinkNode *p = first;
    while (p->link != NULL)
        p = p->link;
    cin >> val;
    while (val != '\n')
    {
        LinkNode *newNode = new LinkNode;
        newNode->data = val;
        newNode->link = NULL;
        p->link = newNode;
        p = newNode;
        cin >> val;
    }
    p->link = NULL;
}

bool LinkList::insertNode(ListData x, int i)
{
    LinkNode *p = LocateNode(i - 1);
    if (p == NULL)
        return false;
    LinkNode *newNode = new LinkNode;
    newNode->data = x;
    newNode->link = p->link;
    p->link = newNode;
    return true;
}

bool LinkList::deleteNode(int i)
{
    LinkNode *p = LocateNode(i - 1);
    if (p == NULL)
        return false;
    LinkNode *q = p->link;
    p->link = q->link;
    delete q;
    return true;
}

LinkNode *LinkList::LocateNode(int i)
{
    LinkNode *p = first;
    for (int k = 1; k <= i; k++)
    {
        if (p == NULL)
            return NULL;
        p = p->link;
    }
    return p;
}

LinkNode *LinkList::findNode(ListData x)
{
    LinkNode *p = first->link;
    while (p != NULL)
    {
        if (p->data == x)
            return p;
        p = p->link;
    }
    return NULL;
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
    while (p!=NULL)
    {
        cout << p->data << " ";
        p = p->link;
    }
}