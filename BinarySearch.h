#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template <typename Comp>
int BinarySearch(const vector<Comp>& a, const Comp& x){
	int low = 0, high = a.size() - 1;
	
	while(low < high){
		int mid = (low + high)/2;
		if (a[mid] < x)
			low = mid + 1;
		else if(a[mid] > x)
			high = mid-1;
		else
			return mid;
	}
	return -1;
}

