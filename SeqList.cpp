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
    bool addData(ListData x);
    bool insertData(ListData x, int i); // 0<=i<=length
    bool deleteData(int i);             // 0<=i<length
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

bool SeqList::addData(ListData x)
{
    if (length >= maxSize)
        return false;
    else
    {
        data[length] = x;
        length++;
        return true;
    }
}

bool SeqList::insertData(ListData x, int i)
{
    if (i < 0 || i > length || length >= maxSize)
        return false;
    else
    {
        for (int k = length; k >= i; k--)
            data[k] = data[k - 1];
        data[i] = x;
        length++;
        return true;
    }
}

bool SeqList::deleteData(int i)
{
    if (i < 0 || i >= length || length <= 0)
        return false;
    else
    {
        for (int k = i; k < length - 1; k++)
            data[i] = data[i + 1];
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
        cerr << "参数i不合理！" << endl;
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
}

int main()
{
    
    return 0;
}