#pragma once
#include "../stdafx.h"
#include <list>
//���ǽڵ��ͷ�ļ�
//�޸���2017��2��24��
//����һ����ͨ�Ľڵ���Ķ��� ����һ��ָ����һ��������
template<typename ty>
class Node
{
private:
	Node *next;
	ty data;
	
public:
	//���ﲻ��ʵ����ӿڷ���
	Node():next(nullptr){}
	Node(ty _da,Node *_next=nullptr):data(_da),next(_next){}
	Node(const Node&) = delete;
	Node(Node &&) = delete;
	Node &operator=(const Node&) = delete;
	Node &operator=(Node &&) = delete;
	~Node() {}
	//���ݷ���
	//��ȡ���ݵ�����
	ty &Data() { return data; }
	//��ȡ��һ�ڵ��ָ��
	Node *getNext()const { return next; }
	//������һ�ڵ��ָ��
	void setNext(Node *_next) { next = _next; }
};
//����һ����ͨ��˫�ڵ���Ķ��� ��������ָ����һ��������
template<typename ty>
class DoubleNode
{
private:
	DoubleNode *next;
	DoubleNode *prev;
	ty data;

public:
	
	//���ﲻ��ʵ����ӿڷ���
	DoubleNode() :next(nullptr) {}
	DoubleNode(ty _da, DoubleNode *_next = nullptr,DoubleNode *_prev=nullptr) :data(_da), next(_next),prev(_prev) {}
	DoubleNode(const DoubleNode&) = delete;
	DoubleNode(DoubleNode &&) = delete;
	DoubleNode &operator=(const DoubleNode&) = delete;
	DoubleNode &operator=(DoubleNode &&) = delete;
	~DoubleNode() {}
	//���ݷ���
	//��ȡ���ݵ�����
	ty &Data() { return data; }
	const ty &Data() const  { return data; }
	//��ȡ��һ�ڵ��ָ��
	DoubleNode *getNext()const { return next; }
	//������һ�ڵ��ָ��
	void setNext(DoubleNode *_next) { next = _next; }
	//��ȡ��һ�ڵ��ָ��
	DoubleNode *getPrev()const { return prev; }
	//������һ�ڵ��ָ��
	void setPrev(DoubleNode *_p) { prev = _p; }
};