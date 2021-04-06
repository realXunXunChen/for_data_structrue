#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif

template <typename Comparable>
class BinarySearchTree{
	struct BinaryNode{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode( const Comparable& theElement, BinaryNode* lt, BinaryNode* rt):
			element(theElement), left(lt), right(rt){}
	};
	public:
		BinarySearchTree(){root = NULL;}
		BinarySearchTree( const BinarySearchTree & rhs){root = clone(rhs.get_root());}
		~BinarySearchTree(){makeEmpty();}

		const Comparable& findMin() const{return findMin(root);}
		const Comparable& findMax() const{return findMax(root);}
		bool contains(const Comparable& x) const{contains(x,root);}
		bool isEmpty() const{return root == NULL;}
		virtual void printTree() const{printTree(root);}

		void makeEmpty(){makeEmpty(root);}
		virtual	void insert(const Comparable& x){insert(x, root);}
		void remove(const Comparable& x){remove(x,root);}
		BinaryNode* get_root()const {return root;}

		const BinarySearchTree& operator=(const BinarySearchTree& rhs){
			if(this != &rhs){
				makeEmpty();
				root = clone(rhs.get_root());
			}
			return *this;
		}

	private:
		BinaryNode* root;
		virtual void insert(const Comparable& x, BinaryNode*& t) const{
			if(t == NULL)
				t = new BinaryNode(x, NULL, NULL);
			else if(x < t-> element)
				insert(x, t->left);
			else if(x > t-> element)
				insert(x, t->right);
			else
			return;
		}

		void remove(const Comparable& x, BinaryNode*& t) const{
			if(t == NULL)
				return;
			if(x < t->element)
				remove(x, t->left);
			else if(x > t->element)
				remove(x, t->right);
			else if(t->left != NULL && t->right != NULL){//two children
				t->element = findMin(t->right)->element;
				remove(t->element,t->right);
			}else{
				BinaryNode* oldNode = t;
				t = (t->left != NULL) ? t->left : t->right;
				delete oldNode;
			}
		}

		BinaryNode* findMin(BinaryNode* t) const{
			if(t == NULL)
				return NULL;
			if(t -> left == NULL)
				return t;
			return findMin(t->left);
		}

		BinaryNode* findMax(BinaryNode* t) const{
			if(t == NULL)
				return NULL;
			while(t -> right != NULL)
				t = t->right;
			return t;	
		}

		bool contains(const Comparable& x, BinaryNode* t) const{
			if(t == NULL)
				return false;
			else if( x < t->element)
				return contains(x, t-> left);
			else if( x > t-> element)
				return contains(x, t->right);
			else
				return true;//Match
		}

		void makeEmpty(BinaryNode*& t){
			if(t != NULL){
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
			t = NULL;
		}

		void printTree(BinaryNode* t)const{
			if(t == NULL)
				return;
			cout << t->element << endl;
			printTree(t->left);
			printTree(t->right);
		}

		BinaryNode* clone(BinaryNode* t) const{
			if(t == NULL)
				return NULL;
			return new BinaryNode(t->element, clone(t->left), clone(t->right));
		}
};

