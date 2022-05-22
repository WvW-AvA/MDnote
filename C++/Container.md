# Container

STL主要由以下五模块组成，分别是分配器(Allocator)，迭代器(Iterrators)，容器(Containers)，算法(Algorithms)，仿函数(Functors)。他们之间的关系如下表示。

![img](media/2022-05-19_221410.png)

* 算法通过迭代器操控容器

### Vector

```cpp
#include<vector>
using namespace std;
int main()
{
    vector<int> v={1,2,3,4};
    return 0;
}
```

* vector 的功能是长度可变的数组，数据存储在堆上。
* vector 是一个模板类，第一个模板参数是元素类型。
* vector可以在初始化的时候指定大小。

```cpp
vector<int> v(4);//大小为4的int类型vector
```

#### resize

resize 的大小若**大于**当前容量，则会在内存中重新分配空间，将数据全部拷贝过去后，再释放掉原本的空间，并且若resize的容量小于原来的size的两倍，则会自动扩容到原来的两倍，防止频繁的拷贝。

因此若是之前有个指针指向这个vector，则变成空悬指针导致数据错误，若该内存区域被操作系统收回，则会引发段错误，导致程序中断。

若**小于**当前容量，则不会重新分配空间，而且原来的空间也不会被释放，只是size标志位改变，因此之前指向这个vector的指针不会空悬。

#### push_back

同样的，push_back若超过容量则会自动扩容到2倍，以防止频繁的拷贝。

已下代码可以清晰了解vecotor的扩容机制。

```cpp
#include <vector>
#include <iostream>
using namespace std;

namespace std
{
    template <typename T>
    ostream &operator<<(ostream &os, const vector<T> &v)
    {
        os << "Vector:{";
        for (int i = 0; i < v.size() - 1; i++)
            os
                << v[i] << ' ';
        os << v.back() << "}";
        return os;
    }
}

template <typename T>
int print_vector_info(const vector<T> &v)
{
    const void *p = &v;
    printf("vector value in stack: %x %x %x\n", *(int *)p, *(int *)(p + 4), *(int *)(p + 8));
    cout << "vector data:" << v.data() << endl;
    cout << "vector capacity:" << v.capacity() << endl;
    cout << "vector size:" << v.size() << endl;
    cout << "value:" << v << endl;
}

int main(int argc, char **argv[])
{
    vector<int> v{1, 2, 3, 4, 5, 6};
    print_vector_info(v);
    v.push_back(233);
    printf("After push_back\n");
    print_vector_info(v);
    v.pop_back();
    printf("After pop_back\n");
    print_vector_info(v);
}
```

### 自己实现一个vector

```cpp
#pragma once
#include <memory.h>
#include <string.h>

template <class T>
class tiny_vector
{
private:
    T *beg;
    T *end;
    T *cap_end;

public:
    tiny_vector<T>(size_t size)
    {
        beg = (T *)malloc(size * sizeof(T));
        memset(beg, 0x00, size * sizeof(T));
        end = beg + size;
        cap_end = end;
    }
    ~tiny_vector<T>()
    {
        free(beg);
        beg = nullptr;
        end = nullptr;
        cap_end = nullptr;
    }
    tiny_vector<T>(const tiny_vector<T> &v)
    {
        size_t capacity = v.capacity();
        beg = (T *)malloc(capacity * sizeof(T));
        memcpy(beg, v.data(), capacity * sizeof(T));
        end = beg + v.size();
        cap_end = beg + capacity;
    }
    tiny_vector<T>() : beg(nullptr), end(nullptr), cap_end(nullptr)
    {
    }

    void resize(size_t size)
    {
        if (size < 0)
            throw("Error:you are trying to resize negative size.");
        if (size <= capacity())
            end = beg + size;
        else
        {
            if (size <= 2 * capacity())
                size = capacity() * 2;
            T *tem = beg;
            beg = (T *)malloc(size * sizeof(T));
            memcpy(beg, tem, (end - tem) * sizeof(T));
            cap_end = beg + size;
            end = beg + (end - tem);
            free(tem);
            printf("resize to %d, malloc memory %d in %x\n", size, size * sizeof(T), beg);
            Debug();
        }
    }
    void push_back(const T &value)
    {
        if (end == cap_end)
            resize(capacity() + 1);
        memcpy(end, &value, sizeof(T));
        end++;
    }
    T pop_back()
    {

        if (end != beg)
            end--;
        return *(end + 1);
    }
    size_t size()
    {
        return end - beg;
    }
    size_t capacity()
    {
        return cap_end - beg;
    }

    T *data()
    {
        return beg;
    }
    T &operator[](size_t index)
    {
        return *(beg + index);
    }
#ifdef _DEBUG
    void Debug()
    {
        printf("beg:%x end:%x cap_end:%x\n", beg, end, cap_end);
    }
#endif // DEBUG
};

```



