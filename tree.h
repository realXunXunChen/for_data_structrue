#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif
template<class Object>
struct BinaryNode;

template<class Object>
class BinaryTree;

template<class Object>
ostream& operator<<(ostream& os, BinaryNode<Object>* rhs);

template<class Object>
class BinaryTree{
	public:
		BinaryTree(BinaryNode<Object>* BN = NULL):
			root(BN){}
		BinaryTree(Object& ob) {root = new BinaryNode<Object>(ob);}
		BinaryTree(BinaryTree<Object>& lf, BinaryTree<Object>& rg, Object& elem){
			root = new BinaryNode<Object>(lf.get_root(), rg.get_root(), elem);}
		
		BinaryTree<Object>& operator=(const BinaryTree<Object>& rhs){
			root = rhs.get_root();
			return *this;
		}
		friend ostream& operator<<<Object>(ostream& os, BinaryNode<Object>* rhs);
//		~BinaryTree(){delete_(root);}
		void delete_(BinaryNode<Object>* &a){
			if(a != NULL){
				cout << "left\n";
				delete_(a->left);
				cout << "right\n";
				delete_(a->right);
				delete a;
			}
			a = NULL;
		}
		BinaryTree<Object>* merge(BinaryTree<Object>& a, BinaryTree<Object>& b);
		BinaryNode<Object>* get_root() const{return root;}
	private:
		BinaryNode<Object>* root;
};

template<class Object>
ostream& operator<<(ostream& os, BinaryNode<Object>* rhs){
	if(rhs-> left != NULL)
		operator<<(os, rhs-> left);
	os << rhs->element;
	if(rhs-> right != NULL)
	   operator<<(os, rhs-> right);
	return os;
}

template<class Object>
struct BinaryNode{
	BinaryNode():left(NULL),right(NULL),element(0){}
	BinaryNode(Object& ob):left(NULL),right(NULL),element(ob){}
	BinaryNode(BinaryNode<Object>* lf, BinaryNode<Object>* rg, Object& data):left(lf),right(rg),element(data){}
//	BinaryNode(Object& lf, Object& rg):left(lf),right(fg),el

	Object element;
	BinaryNode<Object>* left;
	BinaryNode<Object>* right;
//	BinaryNode<Object>* parent;
};

/*
template<class Object>
BinaryTree<Object>& BinaryTree::merge(BinaryTree<Object>& a, BinaryTree<Object>& b){
	this->root->left = a->get_root();
	this->root->right = b->get_root();
	return *this;
}
*/
