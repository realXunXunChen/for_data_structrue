#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"  
#endif

template <typename Comparable>
class BinaryHeap{
	public:
		explicit BinaryHeap(int capacity = 100):
			currentSize(0), array(capacity){}
		explicit BinaryHeap(const vector<Comparable>& items):
			currentSize(items.size()), array(items.size()+10){
				for(int i = 0;i < items.size();++i)
					array[i+1] = items[i];
				buildHeap();
			}
		bool isEmpty()const{return currentSize == 0;}
		const Comparable& findMin()const{
			return array[1];
		}
		void insert(Comparable& x){
			if(currentSize == array.size()-1)
				array.resize(array.size() * 2);
			int hole = ++currentSize;
			for(;hole > 1 && x < array[hole/2]; hole /= 2)
				array[hole] = array[hole/2];
			array[hole] = x;
		}

		void insert(const Comparable& x){
			if(currentSize == array.size()-1)
				array.resize(array.size() * 2);
			int hole = ++currentSize;
			for(;hole > 1 && x < array[hole/2]; hole /= 2)
				array[hole] = array[hole/2];
			array[hole] = x;
		}

		void deleteMin(){
			if(isEmpty())
				throw 0;
			array[1] = array[currentSize--];
			percolateDown(1);
		}
		void deleteMin(Comparable& minItem){
			if(isEmpty())
				throw 0;
			minItem = array[1];
			array[1] = array[currentSize--];
			percolateDown(1);
		}

		void percolateDown(int hole){
			int child;
			Comparable tmp = array[hole];
			for(;hole * 2 <= currentSize;hole = child){
				child = hole*2;
				if(child != currentSize && array[child+1] < array[child])
					++child;
				if(array[child] < tmp)
					array[hole] = array[child];
				else
					break;
			}
			array[hole] = tmp;
		}
		void buildHeap(){
			for(int i = currentSize / 2;i > 0; --i)
				percolateDown(i);
		}




	private:
		int currentSize;
		vector<Comparable> array;
};
