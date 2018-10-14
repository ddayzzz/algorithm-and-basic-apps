#pragma once

template<typename T> class ArrayQueue
{
	//这个是线性的队列的实现
	typedef T DataType;

public:
	ArrayQueue(int sz) :size(sz+1), front(0), rear(0),data(nullptr)
	{
		if (sz > 0)
		{
			data = new DataType[sz+1];
		}
		else { size = 0; }
	}
	~ArrayQueue() { delete data; }
	bool isEmpty(){
		return (data == nullptr || front == rear);
	}
	bool isFull() { return front == (rear + 1) % size; }
	void enQueue(DataType d) {
		if (!isFull())
		{
			
			data[rear] = d;
			rear = (rear + 1) % size;
		}
	}
		
	
	DataType deQueue()
	{
		if (!isEmpty())
		{
			T d = data[front];
			front = (front + 1) % size;
			return d;
		}
	}
	DataType &getFront(){
		if (!isEmpty())
		{
			return data[front];
		}
	}
private:
	int size;
	int front;
	int rear;
	T *data;
};
//链队列的实现
template<typename T> struct LinkQueueNode
{
	T data;
	LinkQueueNode *next;
	LinkQueueNode(T da,LinkQueueNode *nt=nullptr):next(nt),data(da){}
};
template<typename T> class LinkQueueList
{
	typedef LinkQueueNode<T> NodeType;
	typedef NodeType *Node;
public:
	LinkQueueList():front(nullptr),back(nullptr){}
	bool isEmpty()
	{
		return front == nullptr;
	}
	void EnQueue(T data)
	{
		if (isEmpty())
		{
			Node nd = nullptr;
			nd= new NodeType(data, nullptr);
			if (nd)
			{
				front = back = nd;
			}
		}
		else
		{
			Node nd = nullptr;
			nd = new NodeType(data, nullptr);
			if (nd)
			{
				back = back->next = nd;
			}
		}
	}
	T DeQueue()
	{
		if (!isEmpty())
		{
			Node temp = front->next;
			T da = front->data;
			delete front;
			front = temp;
			return da;
		}
	}
	T &GetFront()
	{
		if (!isEmpty())
		{
			return front->data;
		}
	}
	~LinkQueueList()
	{
		Node temp = nullptr;
		while (front != nullptr)
		{
			temp = front->next;
			delete front;
			front = temp;
		}
	}
	void makeEmpty()
	{
		while (!isEmpty())
		{
			DeQueue();
		}
	}
private:
	LinkQueueNode<T> *front;
	LinkQueueNode<T> *back;
};

//优先队列的实现
template<typename T> class PriorQueueList
{
	typedef LinkQueueNode<T> NodeType;
	typedef NodeType *Node;
public:
	//原则就是把最小的元素节点放置到第一个元素 优先处理
	PriorQueueList():front(nullptr),back(nullptr){}
	void EnQueue(T data)
	{
		Node nd = new NodeType(data);
		if (nd)
		{
			if (front==nullptr)
			{
				front = back = nd;
			}
			else
			{
				back->next = nd;
				back = nd;
			}
		}
	}
	bool isEmpty()
	{
		return front == nullptr;
	}
	T DeQueue()
	{
		//需要找到最小的节点
		Node tmp = front;
		Node find = nullptr;
		T minData;
		if (isEmpty() == true)
		{
			throw std::runtime_error("ERROR!");
		}
		find = front->next;
		while (find != nullptr)
		{
			if (find->data < tmp->data)
				tmp = find;//寻找比tmp的data小的节点
			find = find->next;
		}
		if (tmp == front)
		{
			minData = front->data;
			front = front->next;
			delete tmp;
			return minData;
		}
		find = front;//find回到头结点
		//开始寻找tmp的前驱
		while (find != nullptr && find->next != tmp)
			find = find->next;
		//现在find是tmp的前驱
		if (tmp->next == nullptr)
		{
			//最小节点位于队列尾部
			back = find;
			back->next = nullptr;
			minData = tmp->data;
			delete tmp;
		}
		else if (find != nullptr)
		{
			//位于队列的中间
			minData = tmp->data;
			find->next = tmp->next;
			delete tmp;
		}
		return minData;
	}
	~PriorQueueList()
	{
		if (!isEmpty())
		{
			while (front !=nullptr)
			{
				Node tmp = front;
				front = front->next;
				delete tmp;
			}
			front = back = nullptr;
		}
	}
	
private:
	Node front;
	Node back;
};