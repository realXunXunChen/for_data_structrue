#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/Algorithm/GeneralAgo/head.h"

//The following algorithm is for the exercise 1.1
const int input_size = 3;

void swap(int &a , int &b);
void SortInput(int input[],int size){
	int i , j;
	for(i = size - 1; i != 0; --i){
		for(j = 0;j != i; ++j)
			if(j != i && input[j] > input[j+1])
			{swap(input[j], input[j+1]);}
		input[i] = input[j];
	//	cout << input[i];
	}
}

void swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

//The following program is for the exercise 1.2
double MedianFind(int input[], int size){
	SortInput(input, size);
	if (size % 2 == 0){
		double b = (input[size/2] + input[size/2-1])/2;
		cout << "\tThe median is:\t" << (static_cast<double>(input[size/2])+static_cast<double>(input[size/2-1]))/2 << endl;
		return static_cast<double>((input[size/2]+input[size/2+1])/2); 
	}else{
		cout << "\tThe median is\t" << input[size/2];
		return input[size/2];
	}
}

//The following is for 1.5
template<typename T>
T PolyCal(T a[],T x, int size){
	T sum = 0;
	for (int i = size - 1; i != -1; --i)
		sum = sum*x + a[i];
		return sum;
}

