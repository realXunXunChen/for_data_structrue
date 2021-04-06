#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif
enum Bool {False, True};

template<class T>
class SeqQueue;
template<class T>
ostream& operator<<(ostream& os, SeqQueue<T>& Q);

template<class T>
class SeqQueue{
	public:
		SeqQueue(int sz = 100): rear(0), front(0), maxSize(sz){
			elements = new T[maxSize];
		}	
		~SeqQueue(){delete[] elements;}
		Bool EnQueue(const T& x);
		Bool DeQueue(T& x);
		Bool getFront(T& x);
		void makeEmpty(){front = rear = 0;}
		Bool IsEmpty()const {return (front == rear)?True:False;}
		Bool IsFull()const{
			return ((rear+1)%maxSize == front)?True:False;}
		int getSize()const {return (rear-front + maxSize)%maxSize;}
		friend ostream& operator<<<T>(ostream& os, SeqQueue<T>& Q);
	protected:
		int rear;
	  	int	front;
		T *elements;
		int maxSize;
};

template<class T>
Bool SeqQueue<T>::EnQueue(const T& x){
	if(IsFull() == True)
	   	return False;
	elements[rear] = x;
	rear = (rear+1)%maxSize;
	return True;
};

template<class T>
Bool SeqQueue<T>::DeQueue(T& x){
	if(IsEmpty() == True) return False;
	x = elements[front];
	front = (front+1)%maxSize;
	return True;
};

template<class T>
Bool SeqQueue<T>::getFront(T& x){
	if(IsEmpty() == True)return False;
	x = elements[front];
	front = (front + 1) % maxSize;
	return True;
};

template<class T>
ostream& operator<<(ostream& os, SeqQueue<T>& Q){
	os << "front" << Q.front << ", rear = "<< Q.rear << endl;
	for(int i = Q.front; i != Q.rear; i = (i+1)%Q.maxSize)
		os<< i << ":" << Q.elements[i]<< endl;
	return os;
}
