#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif


class DisjSets{
	public:
		explicit DisjSets(int numElement = 10):s(numElement){
			for(int i = 0; i < s.size(); ++i)
				s[i] = -1;
		}

		int find(int x){
			if(s[x] < 0)
				return x;
			else
				return find(s[x]); // return s[x] = find(s[x]);
		}
		void unionSets0(int root1, int root2){
			s[root2] = root1;
		}
		
		void unionSets(int root1, int root2){
			if(s[root2] < s[root1])
				s[root1] = root2;
			else{
				if(s[root1] == s[root2])
					--s[root1];
				s[root2] = root1;
			}
		}
	private:
		vector<int> s;
};

