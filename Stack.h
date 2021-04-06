/*
#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template<class Obj>
class Stack{
	public:
		Stack():data(0),Top(-1){}
		void push(Obj& x){
			++Top;
			data.push_back(x);
		}
		Obj pop(){
			return data[Top--];
		}
		Obj top(){
			return data[Top];
		}
		bool empty(){
			return Top == -1; 
		}
		Obj get(int i){ return data[i];}
		int size()const {return data.size();}
		~Stack(){}

	private:
		vector<Obj> data;
		int Top;
};
template<class Object>
ostream& operator<<(ostream& os, Stack<Object>& st){
	for(int i = 0; i != st.size();++i)
		os << st.get(i);
	return os;
}
*/

#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template<class Obj>
class Stack{
    public:
        Stack():data(),Top(-1){data = new Obj[100];}
        void push(Obj& x){
        data[++Top] = x;
        }
        Obj pop(){
            return data[Top--];
        }
        Obj top(){
            return data[Top];
        }
        bool empty(){
            return Top == -1;
        }
        Obj get(int i){ return data[i];}
        int size()const {return Top+1;}
        ~Stack(){}

    private:
        Obj* data;
        int Top;
};
template<class Object>
ostream& operator<<(ostream& os, Stack<Object>& st){
    for(int i = 0; i != st.size();++i)
        os << st.get(i);
    return os;
}
