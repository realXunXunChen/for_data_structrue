#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

clock_t startTime, endTime;

//cubic maximum contiguous subsequences sum algorithm
int MaxSubSum1(const vector<int>& a){
    startTime = clock();//计时开始
	int max_sum = 0;
	for(int i = 0; i != a.size();++i){
		for(int j = i; j != a.size();++j){
			int this_sum = 0;
			for(int k = i; k != j+1; ++k)
				this_sum += a[k];
			if(this_sum > max_sum)
				max_sum = this_sum;
		}
	}
 	endTime = clock();//计时结束
   	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return max_sum;
}

//Quadratic maximum contigous subsequence sum algorithm
int MaxSubSum2(const vector<int>& a){
    startTime = clock();//计时开始
	int max_sum = 0;
	for(int i = 0; i != a.size(); ++i){
		int this_sum = 0;
		for(int j = i; j != a.size(); ++j){
			this_sum += a[j];
			if (this_sum > max_sum)
				max_sum = this_sum;
		}
	}
 	endTime = clock();//计时结束
   	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return max_sum;
}

//divide and conquer
//O(NlogN) solution
//Recursive maximum contigous subsequence sum algorithm
//Finds maximum sum in subarray spanning a[left..right].
//Does not attempt to maintain actual best sequence
int max3(int a, int b, int c);
int MaxSumRec( const vector<int>& a, int left, int right){
	if(left == right) //Base case
		if(a[left] > 0)
			return a[left];
		else
			return 0;
	int center = (left+right)/2;
	int max_left_sum = MaxSumRec(a, left, center);
	int max_right_sum = MaxSumRec(a, center+1, right);
	int max_left_border_sum = 0, left_border_sum = 0;
	for (int i = center; i >= left; i--){
		left_border_sum += a[i];
		if(left_border_sum > max_left_border_sum)
			max_left_border_sum = left_border_sum;
	}

	int max_right_border_sum  = 0, right_border_sum = 0;
	for (int i = center + 1; i <= right; i++){
		right_border_sum += a[i];
		if(right_border_sum > max_right_border_sum)
			max_right_border_sum = right_border_sum;
	}
	return max3(max_left_sum, max_right_sum, max_left_border_sum + max_right_border_sum);
}

int max3(int a, int b, int c){
	int max = 0;
	max = a > b ? a : b;
	return max > c ? max : c;
}

int MaxSubSum3(const vector<int>& a){
    startTime = clock();//计时开始
	int num = MaxSumRec(a, 0, a.size()-1);
 	endTime = clock();//计时结束
   	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return num;
}

//linear-time maximum contigous subsequence sum algorithm
int MaxSubSum4(const vector<int> a){
	startTime = clock();
	int max_sum = 0, this_sum = 0;
	for(int j = 0; j != a.size(); j++){
		this_sum += a[j];
		if(this_sum > max_sum)
			max_sum = this_sum;
		else if(this_sum < 0)
			this_sum = 0;
	}
 	endTime = clock();//计时结束
   	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return max_sum;
}
