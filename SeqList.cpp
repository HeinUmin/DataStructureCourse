#include <iostream>
using namespace std;
typedef int ListData;

class SeqList
{
private:
    int maxSize;
    int length;
    ListData *data;

public:
    SeqList(int size);
    ~SeqList();
    int addData(int i);
    bool insertData(ListData x, int i); // 0<=i<=length
    bool deleteData(int i);             // 0<i<=length
    ListData getData(int i);
    int findData(ListData x);
    void reverseData();
    void outputData();
};

SeqList::SeqList(int size)
{
    maxSize = size;
    data = new ListData[maxSize];
    if (data == NULL)
    {
        cerr << "存储分配失败！" << endl;
        exit(1);
    }
    length = 0;
}

SeqList::~SeqList()
{
    delete[] data;
}

int SeqList::addData(int i)
{
    int input = 0;
    if (i <= 0)
    {
        cout << "请输入正整数！" << endl;
        return -1;
    }
    cout << "请输入数据：" << endl;
    for (int k = 0; k < i; k++)
    {
        cin >> input;
        if (!insertData(input, length))
            return k;
    }
    return i;
}

bool SeqList::insertData(ListData x, int i)
{
    if (i < 0 || i > length || length >= maxSize)
        return false;
    else
    {
        for (int k = length; k > i; k--)
            data[k] = data[k - 1];
        data[i] = x;
        length++;
        return true;
    }
}

bool SeqList::deleteData(int i)
{
    if (i <= 0 || i > length || length <= 0)
        return false;
    else
    {
        for (int k = i; k < length; k++)
            data[k - 1] = data[k];
        length--;
        return true;
    }
}

ListData SeqList::getData(int i)
{
    if (i >= 0 && i < length)
        return data[i];
    else
    {
        cerr << "参数不合理！" << endl;
        exit(1);
    }
}

int SeqList::findData(ListData x)
{
    for (int k = 0; k < length; k++)
        if (data[k] == x)
            return k;
    return -1;
}

void SeqList::reverseData()
{
    for (int k = 0; k < length / 2; k++)
    {
        int x = data[length - k - 1];
        data[length - k - 1] = data[k];
        data[k] = x;
    }
}

void SeqList::outputData()
{
    for (int k = 0; k < length; k++)
        cout << data[k] << " ";
    cout << endl;
}

int main()
{
    int input = 0;
    int index = 0;
    bool init = false;
    SeqList *list = NULL;
    while (true)
    {
        if (!init)
        {
            cout << "请输入顺序表大小（输入0退出程序）：" << endl;
            cin >> input;
            if (!input)
                return 0;
            if (input < 0)
            {
                cout << "请输入正整数！" << endl;
                continue;
            }
            list = new SeqList(input);
            init = true;
        }
        cout << "请输入序号：" << endl
             << "1.销毁链表；" << endl
             << "2.添加元素；" << endl
             << "3.插入元素；" << endl
             << "4.删除元素；" << endl
             << "5.查找元素（按序号查找）；" << endl
             << "6.查找元素（按值查找）；" << endl
             << "7.倒序排列元素；" << endl
             << "8.按序输出元素；" << endl
             << "0.退出程序。" << endl;
        cin >> input;
        switch (input)
        {
        case 1:
            delete list;
            cout << "顺序表已销毁！" << endl;
            init = false;
            break;
        case 2:
            cout << "请输入数据量：" << endl;
            cin >> index;
            while ((input = getchar()) != '\n')
                continue;
            index = list->addData(index);
            if (index == -1)
                continue;
            cout << "成功插入" << index << "个数据！" << endl
                 << "当前表内数据为：" << endl;
            list->outputData();

            break;
        case 3:
            cout << "请输入数据和序号：" << endl;
            cin >> input >> index;
            if (list->insertData(input, index))
                cout << "插入成功！" << endl;
            else
                cout << "插入失败！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputData();
            break;
        case 4:
            cout << "请输入序号：" << endl;
            cin >> index;
            if (list->deleteData(index))
                cout << "删除成功！" << endl;
            else
                cout << "删除失败！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputData();
            break;
        case 5:
            cout << "请输入序号：" << endl;
            cin >> index;
            cout << "目标结点的数据为 " << list->getData(index) << endl;
            break;
        case 6:
            cout << "请输入数据：" << endl;
            cin >> input;
            index = list->findData(input);
            if (index == -1)
                cout << "未查询到相关数据！" << endl;
            else
                cout << "目标结点的序号为 " << index << endl;
            break;
        case 7:
            list->reverseData();
            cout << "倒序排列完成！" << endl;
            cout << "当前表内数据为：" << endl;
            list->outputData();
            break;
        case 8:
            list->outputData();
            break;
        case 0:
            delete list;
            return 0;
        default:
            cout << "非法输入！" << endl;
            exit(1);
        }
        cout << endl;
    }
    return 0;
}