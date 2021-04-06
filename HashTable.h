#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h" 
#include "HashFunc.h"

bool isPrime(int n){
	if(n <= 1) return false;
	int sqr = static_cast<int>(sqrt(1.0 * n));
	for(int i = 2;i <= sqr; ++i){
		if(n % i == 0) return false;
	}
	return true;
}
int nextPrime( int x){
	while(isPrime(x) != true)
		++x;
	return x;
}


template <typename HashedObj>
class HashTable{
	public:
		explicit HashTable(int size = 101);
		bool contains(const HashedObj& x) const{
			const list<HashedObj>& whichList = theLists[myhash(x)];
			return find(whichList.begin(), whichList.end(), x) != whichList.end();
		}

		void makeEmpty(){
		for(int i = 0; i < theLists.size(); ++i)
			theLists[i].clear();
		}	
		void insert( const HashedObj& x){
			list<HashedObj>& whichList = theLists[ myhash(x)];
			if( find( whichList.begin(), whichList.end(),x) != whichList.end())
				return false;
			whichList.push_back(x);
			if( ++ currentSize > theLists.size())
				rehash();
			return true;
		}


		void remove(const HashedObj& x){
			list<HashedObj>& whichList = theLists[myhash(x)];
			list<HashedObj>::iterator itr = find(whichList.begin(), whichList.end(), x);

			if( itr == whichList.end())
				return false;

			whichList.erase(itr);
			--currentSize;
			return true;
		}
	private:
		vector<list<hashedObj> > theLists;
		int currentSize;
		void rehash(){
			vector<list<HashedObj> > oldLists = theLists;
			theLists.resize(nextPrime(2*theLists.size()));
			for(int j = 0;j < theLists.size();++j)
				theLists[j].clear();
			currentSize = 0;
			for(int i = 0;i < oldLists.size();++i){
				list<HashedObj>::iterator itr = oldLists[i].begin();
				while(itr != oldList[i].end())
					insert(*itr++);// there are some problems
			}
		}
		int hash(const Employee& item){
			return hash(item.getName());
		}
		int myhash(const HashedObj& x) const{
			int hashVal = hash(x);
			hashVal %= theLists.size();
			if(hashVal < 0)
				hashVal += theLists.size();
		return hashVal;
		}
};

class Employee{
	public:
		const string& getName() const{
			return name;
		}
		bool operator==(const Employee& rhs) const{
			return getName() == rhs.getName();}
		bool operator!=(const Employee& rhs)const{
			return !(*this == rhs);}
	private:
		string name;
		double salary;
		int seniority;
};


/*
template <typename HashedObj>
class HashTable1{
	public:
		explicit HashTable(int size = 101):array(nextPrime(size)){
			makeEmpty();}
		bool contains(const HashedObj& x)const{
			return isActive(findPos(x));
		}
		void makeEmpty(){
			currentSize = 0;
			for(int i = 0; i < array.size();++i)
				array[i].info = EMPTY;
		}
		bool insert(const HashedObj& x){
			int currentPos = findPos(x);
			if(isActive(currentPos))
				return false;
			array[currentPos] = HashEntry(x, ACTIVE);
			if(++currentSize > array.size() / 2)
				rehash();
			return true;
		}
		bool remove(const HashedObj& x){
			int currentPos = findPos(x);
			if(!isActive(currentPos))
					return false;
			array[currentPos].info = DELETED;
			return true;
		}
		enum EntryType{ACTIVE, EMPTY, DELETED};
	private:
		struct HashEntry{
			HashedObj element;
			EntryType info;
			HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
				:element(e), info(i){}
		};
		vector<HashEntry> array;
		int currentSize;
		bool isActive(int currentPos)const{
			return array[currentPos].info == ACTIVE;
		}
		int findPos(const HashedObj& x)const{
			int offset == 1;
			int currentPos = myhash(x);
			while(array[currentPos].info != EMPTY&&
					array[currentPos].element != x){
				currentPos += offset;
				offset += 2;
				if(currentPos >= array.size())
					currentPos -= array.size();
			}
			return currentPos;
		}
		void rehash(){
			vector<HashEntry> oldArray = array;
			array.resize(nextPrime(2*oldArray.size()));
			for(int j = 0;j < array.size();j++)
				array[j].info = EMPTY;
			currentSize = 0;
			for(int i = 0; i < oldArray.size();++i)
				if(oldArray[i].info == ACTIVE)
					insert(oldArray[i].element);
		}
		int myhash(const HashedObj& x)const{}
};
*/
