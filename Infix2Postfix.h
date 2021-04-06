#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif
#include "Stack.h"
#include "Queue.h"
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/chapter4/tree.h"

struct node{
	double num;
	char op;
	bool flag;
};
class calculator{
	public:
		void infix2postfix();
		double postfix_cal();
		double str2dbl(string str);
		void set_pri(){
			op_priority['+'] = op_priority['-'] = 1;
			op_priority['*'] = op_priority['/'] = 2;
		}
		double perform(){
			infix2postfix();
			return	postfix_cal();
		}
		BinaryTree<char> tree_ex();
	private:
		Stack<BinaryTree<char> > exst;
		string input;
		SeqQueue<node> postfix_ex;
		map<char,int> op_priority;
		Stack<node> op;
};

double calculator::str2dbl(string str){
	double temp = 0;
	double sum = 0;
	for(int i = 0; i < str.length(); ++i){
		temp = static_cast<double>(str[i] - '0');
		sum = temp + sum*10;
	}
	return sum;
}
		
//to transform a infix expression to postfix expression
void calculator::infix2postfix(){
	set_pri();
	cin >> input;
//	input = "1+2+3";
	node temp;
	for(string::iterator itr = input.begin();
			itr != input.end();){
		if(*itr >= '0' && *itr <= '9'){
			temp.flag = true;
			temp.num = *(itr++) - '0';
			while(itr != input.end() && *itr >= '0' && *itr <= '9'){
				temp.num = temp.num * 10 + (*itr - '0'); 
				++itr;
			}
			postfix_ex.EnQueue(temp);
		}else{
			temp.flag = false;
			temp.op = *itr;
			while(!op.empty() && op_priority[*itr] <= op_priority[op.top().op]){
				postfix_ex.EnQueue(op.top());
				op.pop();
			}
			op.push(temp);
			++itr;
		}
	}
	while(!op.empty()){
		node temp = op.top();
		op.pop();
		postfix_ex.EnQueue(temp);
	}
}
	
//to calculator the postfix expression
double calculator::postfix_cal(){
	node temp;
	int temp1,temp2;
	while(!postfix_ex.IsEmpty()){
		postfix_ex.DeQueue(temp);
		if(temp.flag == true){
			op.push(temp);
		}else{ 
			switch (temp.op){
				case '+':
					temp.flag = true;
					temp.num = op.pop().num + op.pop().num;
					op.push(temp);
					break;
				case '-':
					temp.flag = true;
					temp.num = 0 - op.pop().num + op.pop().num;
					op.push(temp);
					break;
				case '*':
					temp.flag = true;
					temp.num = op.pop().num * op.pop().num;
					op.push(temp);
					break;
				case '/':
					temp.flag = true;
					temp.num = 1 / op.pop().num * op.pop().num;
					op.push(temp);
					break;
			}
		}
	}
	return op.top().num;
}

BinaryTree<char> calculator::tree_ex(){
	SeqQueue<node> exp;
	node temp;
	char x;
	while(cin >> x){
		if (x == 'o')
			break;
		if(x >= '0' && x <= '9')
			temp.flag = true;
		else
			temp.flag = false;
		temp.op = x;
		exp.EnQueue(temp);
	}
	while(!exp.IsEmpty()){
		exp.DeQueue(temp);
		if(temp.flag == true){
			BinaryTree<string> temp_ex(temp.op);
			exst.push(temp_ex);
		}else{
			BinaryTree<string> temp1(exst.top());
			exst.pop();
			BinaryTree<string> temp2(exst.pop());
			BinaryTree<string> temp3(&temp2,&temp1,temp.op);
			exst.push(temp3);
		}
	}
	BinaryNode<string> ex(exst.top());
	BinaryTree<string> BT(&ex);
	return BT;
}
