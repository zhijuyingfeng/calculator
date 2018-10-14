#ifndef STACK_H
#define STACK_H
#pragma once
#include <stdio.h>
#include <stdlib.h>

template <typename T>//定义模板类
class stack
{
private:
    struct node//定义栈的节点
    {
        T val;
        node *next;
        node() :val(0), next(NULL){}
        node (T v):val(v),next(NULL){}
    };
    node * L;//链表栈
public:
    stack();//构造函数
    ~stack();//析构函数
    T top();//返回栈顶元素
    void pop();//出栈
    void push(T key);//进栈
    bool IsEmpty();//判断栈是否为空
};

template <typename T>
stack<T>::stack()
{
    L = new node;
}

template <typename T>
bool stack<T>::IsEmpty()
{
    return L->next == NULL;
}

template <typename T>
void stack<T>::push(T key)
{
    node* temp = new node(key);
    temp->next = L->next;
    L->next = temp;
}

template <typename T>
T stack<T>::top()
{
    if (!IsEmpty())//栈非空
    {
        return L->next->val;
    }
    return 0;
}

template <typename T>
void stack<T>::pop()
{
    if (!IsEmpty())//栈非空
    {
        node *temp = L->next;
        L->next = temp->next;
        delete temp;
    }
}

template <typename T>
stack<T>::~stack()
{
    while (!IsEmpty())//栈非空
    {
        pop();
    }
    delete L;
}

#endif // STACK_H
