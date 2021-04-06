#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/chapter3/Stack.h"
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/chapter3/Queue.h"
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/chapter4/tree.h"

struct node{
	string operand;
	string op;
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
		BinaryTree<string> tree_ex();
	private:
		Stack<BinaryTree<string> > exst;
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
//	cin >> input;
	input = "1+2+3";
	node temp;
	for(string::iterator itr = input.begin();
			itr != input.end();){
		if(*itr >= '0' && *itr <= '9'){
			temp.flag = true;
			while(itr != input.end() && *itr >= '0' && *itr <= '9'){
				temp.operand += *(itr++);
			}
			postfix_ex.EnQueue(temp);
		}else{
			temp.operand = "";
			temp.flag = false;
			temp.op = *itr;
			while(!op.empty() && op_priority[*itr] <= op_priority[op.top().op[0]]){
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
/*	
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
					temp.operand = op.pop().num + op.pop().num;
					op.push(temp);
					break;
				case '-':
					temp.flag = true;
					temp.operand = 0 - op.pop().num + op.pop().num;
					op.push(temp);
					break;
				case '*':
					temp.flag = true;
					temp.operand = op.pop().num * op.pop().num;
					op.push(temp);
					break;
				case '/':
					temp.flag = true;
					temp.operand = 1 / op.pop().num * op.pop().num;
					op.push(temp);
					break;
			}
		}
	}
	return op.top().operand;
}

*/
BinaryTree<string> calculator::tree_ex(){
	SeqQueue<node> exp = postfix_ex;
	node temp;
	while(!exp.IsEmpty()){
		exp.DeQueue(temp);
		if(temp.flag == true){
			cout << temp.operand << endl;
			BinaryTree<string> temp_ex(temp.operand);
			exst.push(temp_ex);
		}else{
			cout << temp.op << endl;
			BinaryTree<string> temp1 = exst.pop();
			BinaryTree<string> temp2 = exst.pop();
			BinaryTree<string> temp3(temp2,temp1,temp.op);
			cout << "test of temp3:\n";
			if(temp3.get_root()->left-> left  == NULL)
				cout << "left is NULL \n";
			else
				cout << "left is wrong\n";
			if(temp3.get_root()->right->right == NULL)
				cout << "right is NULL \n";
			else
				cout << "right is wrong\n";
			exst.push(temp3);
		}
	}
	BinaryTree<string> BT = exst.top();
	return BT;
}
