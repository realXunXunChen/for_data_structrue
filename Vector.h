#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template<typename Object>
class Vector{
	public:
		explicit Vector(int initSize = 0):
			theSize(initSize),
		   	theCapacity(initSize + SPARE_CAPACITY)
		 	{objects = new Object[theCapacity];}
		Vector(const Vector<Object>& rhs):objects(NULL)
			{operator=(rhs);}
		~Vector(){delete [] objects;}
		const Vector<Object>& operator= (const Vector& rhs);
		void resize(int newSize);
		void reserve(int newCapacity);
		Object& operator[](int index) {return objects[index];}
		const Object& operator[](int index)const {return objects[index];}
		bool empty() const {return size() == 0;}
		int size() const {return theSize;}
		int capacity() const {return theCapacity;}
		void push_back(const Object& x);
		void pop_back() {theSize--;}
		const Object& back()const {return objects[theSize - 1];}
		typedef Object* iterator;
		typedef const Object* const_iterator;
		iterator begin(){return &objects[0];}
		const_iterator begin() const{return &objects[0];}
		iterator end(){return &objects[size()];}
		const_iterator end() const {return &objects[size()];}
		enum {SPARE_CAPACITY = 16};
	private:
		int theSize;
		int theCapacity;
		Object* objects;
};

template<class Object>
const Vector<Object>& Vector<Object>::operator=(const Vector& rhs){
	if( this != &rhs ){
		delete [] objects;
		theSize = rhs.size();
		theCapacity = rhs.capacity();
		objects = new Object[capacity()];
		for( int k = 0; k != size(); k++)
			objects[k] = rhs.objects[k];
	}
	return *this;
}

template<class Object>
void Vector<Object>::resize(int newSize){
	if(newSize > theCapacity)
		reserve(newSize*2 + 1);
	theSize = newSize;
}

template<class Object>
void Vector<Object>::reserve(int newCapacity){
	if(newCapacity < theSize)
		return;
	Object *oldArray = objects;
	objects = new Object[newCapacity];
	for(int k = 0; k < theSize; k++)
		objects[k] = oldArray[k];
	theCapacity = newCapacity;
	delete [] oldArray;
}

template<class Object>
void Vector<Object>::push_back(const Object& x){
	if(theSize == theCapacity)
		reserve(2 * theCapacity + 1);
	objects[ theSize++] = x;
}

template<class Object>
ostream& operator<<(ostream& os, Vector<Object>& a){
	for(int i = 0; i != a.size(); ++i)
		os << a[i]<< endl;
	return os;
}
