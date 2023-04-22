#pragma once

#include<cstddef>
#include<string>
#include<iostream>

#define Maxele 100

using namespace std;
template <class T>
class MyStack
{
public:
    T array[Maxele];
    int TopIndex;
    MyStack()
    {
        TopIndex = 0;
    }
    bool IsEmpty()
    {
        return TopIndex == 0;
    }
    void push(T n)
    {
        array[TopIndex] = n;
        TopIndex++;
    }
    T pop()
    {
        if (IsEmpty()) return NULL;
        TopIndex--;
        return array[TopIndex];
    }
    T top()
    {
        if (IsEmpty()) return NULL;
        return array[TopIndex - 1];
    }
    void show()
    {
        int temp = TopIndex - 1;
        while (temp + 1)
        {
            cout << array[temp] << " ";
            temp--;
        }
        cout << endl;
    }
    int size()
    {
        return TopIndex;
    }
    void fshow(ofstream& ofs)
    {
        int temp = TopIndex - 1;
        while (temp + 1)
        {
            ofs << array[temp];
            temp--;
        }
    }
};

