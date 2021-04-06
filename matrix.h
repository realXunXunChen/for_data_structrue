#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template<typename T>
class Matrix{
	public:
		Matrix(int rows, int cols): data(rows) {
			for(int i = 0; i != rows; ++i)
				data[i].resize(cols);}
		T& operator() (int i) {return data[i];}
		T& operator() (int i, int j){return data[i][j];}
		Matrix& create();
		int numrows() const {return data.size();}
		int numcols() const {return numrows() ? data[0].size() : 0; }
		Matrix<T>& operator+(Matrix<T> &a);
		Matrix<T>& operator-(Matrix<T> &a);
		Matrix<T>& operator*(Matrix<T> &a);
		Matrix<T>& operator=(Matrix<T> &a);
	private:
		vector< vector<T> > data;
};

//The following function is used to create a dafult matrix
template<typename T>
Matrix<T>& Matrix<T>::create(){
	for(int i = 0; i != numrows(); ++i)
		for(int j = 0; j != numcols(); ++j)
			(*this)(i,j) = i + j;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+(Matrix<T> &a){
	int i1 = this->numrows(), j1 = this->numcols();
	int i2 = a.numrows(), j2 = a.numcols();
	try{
		if (i1 == i2 && j1==j2){
			for (int i = 0; i != numrows(); ++i)
				for(int j = 0; j != numcols(); ++j)
					(*this)(i,j) += a(i,j);
		}else{
			throw runtime_error("The dimension of the two matrix doesn't match");
		}
	}catch (runtime_error err){
		cout << err.what() << endl;
	}
	return *this;
}	

template<typename T>
Matrix<T>& Matrix<T>::operator-(Matrix<T> &a){
	int i1 = this->numrows(), j1 = this->numcols();
	int i2 = a.numrows(), j2 = a.numcols();
	try{
		if (i1 == i2 && j1==j2){
			for (int i = 0; i != numrows(); ++i)
				for(int j = 0; j != numcols(); ++j)
					(*this)(i,j) -= a(i,j);
		}else{
			throw runtime_error("The dimension of the two matrix doesn't match");
		}
	}catch (runtime_error err){
		cout << err.what() << endl;
	}
	return *this;
}	

template<typename T>
Matrix<T>& Matrix<T>::operator*(Matrix<T> &a){
	int i1 = this->numrows(), j1 = this->numcols();
	int i2 = a.numrows(), j2 = a.numcols();
	try{
		if (i1 == i2 && j1==j2){
			for (int i = 0; i != numrows(); ++i)
				for(int j = 0; j != numcols(); ++j)
					(*this)(i,j) *= a(i,j);
		}else{
			throw runtime_error("The dimension of the two matrix doesn't match");
		}
	}catch (runtime_error err){
		cout << err.what() << endl;
	}
	return *this;
}	

template<typename T>
ostream& operator<< ( ostream &os, Matrix<T> &a){
	for(int i = 0; i != a.numrows(); ++i)
		for(int j = 0; j != a.numcols(); ++j)
			os << a(i,j);
	return os;
}


