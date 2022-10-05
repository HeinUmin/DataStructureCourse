#include <iostream>
using namespace std;
typedef int ListData;

class SeqList
{
private:
    int maxSize;    //顺序表最大长度
    int length;     //顺序表当前长度
    ListData *data; //表内数据

public:
    SeqList(int size);
    ~SeqList();
    int addData(int i);                 //返回值为成功添加的数据量，返回值-1表示出错
    bool insertData(ListData x, int i); //在第i个数据后插入，0<=i<=length
    bool deleteData(int i);             //删除第i个数据，0<i<=length
    ListData getData(int i);            //获取第i个数据的值，0<i<=length
    int findData(ListData x);           //返回值为数据序号，0<i<=length
    void reverseData();
    void outputData();
};

SeqList::SeqList(int size)
{
    maxSize = size;               //初始化最大长度
    length = 0;                   //初始化当前长度
    data = new ListData[maxSize]; //分配数据空间
    if (data == NULL)
    {
        cerr << "存储分配失败！" << endl;
        exit(1);
    }
}

SeqList::~SeqList()
{
    delete[] data; //释放数据空间
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
        if (!insertData(input, length)) //使用insertData函数添加数据
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
            data[k] = data[k - 1]; //目标位置之后的数据全部向后移动一格
        data[i] = x;               //在目标位置插入目标数据
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
            data[k - 1] = data[k]; //目标位置之后的数据全部向前移动一格
        length--;
        return true;
    }
}

ListData SeqList::getData(int i)
{
    if (i > 0 && i <= length)
        return data[i - 1];
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
            return k + 1;
    return -1;
}

void SeqList::reverseData()
{
    for (int k = 0; k < length / 2; k++) //将第i个数据与倒数第i个数据交换
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
