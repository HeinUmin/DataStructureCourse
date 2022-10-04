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
    LinkNode *locateNode(int i);
    int findNode(ListData x);
    void sortNode();
    void reverseNode();
    void outputNode();
};

LinkList::LinkList()
{
    first = new LinkNode;
    first->data = '\0';
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
    delete first;
}

void LinkList::inputFront()
{
    char val;
    while ((val = getchar()) != '\n')
    {
        LinkNode *newNode = new LinkNode;
        newNode->data = val;
        newNode->link = first->link;
        first->link = newNode;
    }
}

void LinkList::inputRear()
{
    char val;
    LinkNode *p = first;
    while (p->link != NULL)
        p = p->link;
    while ((val = getchar()) != '\n')
    {
        LinkNode *newNode = new LinkNode;
        newNode->data = val;
        newNode->link = NULL;
        p->link = newNode;
        p = newNode;
    }
    p->link = NULL;
}

bool LinkList::insertNode(ListData x, int i)
{
    LinkNode *p = locateNode(i);
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
    LinkNode *p = locateNode(i - 1);
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

void testMerge()
{
    LinkList *A = new LinkList();
    LinkList *B = new LinkList();
    getchar();
    cout << "请输入链表A中的数据（字符型，每个字符间无需隔开，回车结束输入）：" << endl;
    A->inputRear();
    cout << "请输入链表B中的数据（字符型，每个字符间无需隔开，回车结束输入）：" << endl;
    B->inputRear();
    merge(*A, *B);
    cout << "合并后的数据为：" << endl;
    A->outputNode();
    delete A;
    delete B;
}

int main()
{
    bool init = false;
    char input = '\0';
    int index = 0;
    int x = -1;
    LinkNode *p = NULL;
    LinkList *list = NULL;
    while (true)
    {
        if (!init)
        {
            cout << "选择操作：" << endl
                 << "1.初始化链表；" << endl
                 << "2.测试合并链表程序；" << endl
                 << "0.退出程序。" << endl;
            cin >> input;
            switch (input)
            {
            case '1':
                init = true;
                list = new LinkList();
                cout << "初始化成功！" << endl
                     << endl;
                break;
            case '2':
                testMerge();
                cout << endl;
                continue;
            case '0':
                return 0;
            default:
                cout << "非法输入，请重新输入内容！" << endl
                     << endl;
                continue;
            }
        }
        cout << "请输入序号：" << endl
             << "0.销毁链表；" << endl
             << "1.插入元素（头插法）；" << endl
             << "2.插入元素（尾插法）；" << endl
             << "3.插入元素；" << endl
             << "4.删除元素；" << endl
             << "5.查找元素（按序号查找）；" << endl
             << "6.查找元素（按值查找）；" << endl
             << "7.递增元素；" << endl
             << "8.倒序排列元素；" << endl
             << "9.按序输出元素；" << endl
             << "E.退出程序。" << endl;
        cin >> input;
        switch (input)
        {
        case '0':
            delete list;
            cout << "链表已销毁！" << endl;
            init = false;
            break;
        case '1':
            cout << "请输入数据（字符型，每个字符间无需隔开，回车结束输入）：" << endl;
            getchar();
            list->inputFront();
            cout << "插入成功！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '2':
            cout << "请输入数据（字符型，每个字符间无需隔开，回车结束输入）：" << endl;
            getchar();
            list->inputRear();
            cout << "插入成功！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '3':
            cout << "请输入数据（字符型）和位置（整型）：" << endl;
            cin >> input >> index;
            if (list->insertNode(input, index))
                cout << "插入成功！" << endl;
            else
                cout << "插入失败！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '4':
            cout << "请输入序号（整型）：" << endl;
            cin >> index;
            if (list->deleteNode(index))
                cout << "删除成功！" << endl;
            else
                cout << "删除失败！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '5':
            cout << "请输入序号（整型）：" << endl;
            cin >> index;
            p = list->locateNode(index);
            if (p != NULL)
                cout << "目标结点中的数据为 " << p->data << endl;
            else
                cout << "未查询到相关结点！" << endl;
            break;
        case '6':
            cout << "请输入数据（字符型）：" << endl;
            cin >> input;
            x = list->findNode(input);
            if (x != -1)
                cout << "目标结点的序号为 " << x << endl;
            else
                cout << "未查询到相关结点！" << endl;
            break;
        case '7':
            list->sortNode();
            cout << "排序完成！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '8':
            list->reverseNode();
            cout << "倒序排列完成！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputNode();
            break;
        case '9':
            list->outputNode();
            break;
        case 'e':
        case 'E':
            delete list;
            return 0;
        default:
            cout << "非法输入，按回车键继续！" << endl;
            while ((input = getchar()) != '\n')
                continue;
            break;
        }
        cout << endl;
    }
    return 0;
}