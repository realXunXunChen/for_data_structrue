#ifndef HEAD_H
#define HEAD_H
#include "/Users/apple/study/2020postgraduate/major/DataStructureAndAlgorithm/DataStructure/head.h"
#endif
// this the basic of graph
template<class T, class E>
class Graphlist; 

template<class T, class E>
istream& operator>>(istream& in, Graphlist<T,E>& G);

template<class T, class E>
ostream& operator<<(ostream& os, Graphlist<T,E>& G);

const int DefaultVertices = 30;
template<class T, class E>
class Graph{
	public:
		Graph(int sz = DefaultVertices):maxVertices(sz), numEdges(0), numVertices(0){}
		~Graph(){};
		bool GraphEmpty() const {
			if(numEdges == 0) 
				return true;
		}

		bool UndirectedGraphFull() const{
			if(numVertices == maxVertices && numEdges == maxVertices * (maxVertices - 1) / 2)
				return true;
			else 
				return false;
		}

		int NumberOfVertices() { return numVertices;}
		int NumberOfEdges(){ return numEdges;}
		virtual T getValue(int i) = 0;
		virtual E getWeight(int v1, int v2) = 0;
		virtual int getFirstNeighbor(int v) = 0;
		virtual int getNextNeighbor(int v, int w) = 0;
		virtual bool insertVertex(const T& vertex) = 0;
		virtual bool insertEdge(int v1, int v2, E cost) = 0;
		virtual bool removeVertex(int v) = 0;
		virtual bool removeEdge(int v1, int v2) = 0;
		virtual int getVertexPos(T vertex) = 0;
		const E maxWeight = 100000000;
	protected:
		int maxVertices;
		int numEdges;
		int numVertices;
};

//This is completed by adjacency list

template<class T, class E>
class Graphlist: public Graph<T,E>{
	private:
		struct Edge{
			int dest;
			E cost;
			Edge* link;
			Edge(){}
			Edge(int num, E weight):dest (num), cost(weight), link(NULL){}
			bool operator!=(Edge& rhs)const{
				return dest == rhs.dest ? true : false;
			}
		};

		struct Vertex{
			T data;
			Edge* adj;
			Vertex(){}
			Vertex(T v): data(v), adj(NULL){}
		};
	public:
		Graphlist(int sz = DefaultVertices):Graph<T,E>(sz){
			//No you cannot initialize base class members from initializer list directly. 
			//This is because order of initialization proceeds in this way
			NodeTable = new Vertex[this->maxVertices];//if the Base class is a template, we must add a "this->" or "Base::"
			// before using member in base class
			if(NodeTable == NULL){
				cerr << "memory allocating error!" << endl;
				exit(1);
			}
		}
		
		~Graphlist(){
			for(int i = 0; i < this->numVertices; ++i){
				Edge* tmp;// = NodeTable[i].adj;
				while(NodeTable[i].adj != NULL){
					tmp = NodeTable[i].adj;
					NodeTable[i].adj = tmp->link;
					delete tmp;
				}
			}
			delete [] NodeTable;
		}

		T getValue(int i){
			cout << "getVAlue";
			return i > -1 ? NodeTable[i].data : 0;
		}

		E getWeight(int v1, int v2);
		bool insertVertex(const T& vertex);
		bool insertEdge(int v1, int v2, E cost);
		bool removeVertex(int v);
		bool removeEdge(int v1, int v2);
		int getFirstNeighbor(int v);
		int getNextNeighbor(int v, int w);

		void create(){
			srand((unsigned)time(NULL));
			char x = 'a';
			for(int i = 0;i != 10; ++i){
				insertVertex(x);
				++x;
			}
			
			for(int j = 0; j != 40; ++j){
				int i = rand()%10;
				int k = rand()%10;
				//cout << i << "," << k << "\n";
				if(i != k)
					insertEdge(i,k,j);
			}
		}

		int getVertexPos(T vertex){
			for (int i = 0; i < Graph<T,E>::numVertices; ++i)
				if(NodeTable[i].data == vertex)
					return i;
			return -1;
		}
		friend istream& operator>> <T,E>(istream& in, Graphlist<T,E>& G);
		friend ostream& operator<< <T,E>(ostream& os, Graphlist<T,E>& G);

	private:
		Vertex* NodeTable;
};

template<class T, class E>
E Graphlist<T,E>::getWeight(int v1, int v2){
	if(v1 != -1 && v2 != -1){
		Edge* p = NodeTable[v1].adj;
		while(p != NULL && p->dest != v2)
			p = p->link;
		if(p != NULL)
			return p->cost;
	}
	return this->maxWeight;
}
		

template<class T, class E>
int Graphlist<T,E>::getFirstNeighbor(int v){
	if(v != -1){
		Edge *p = NodeTable[v].adj;
		if(p != NULL)
			return p->dest;
	}
	return -1;
}

template<class T, class E>
int Graphlist<T,E>::getNextNeighbor(int v, int w){
	if(v != -1 && w != -1){
		Edge* p = NodeTable[v].adj;
		while(p != NULL && p->dest != w)
			p = p -> link;
		if(p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}

template<class T, class E>
bool Graphlist<T,E>::insertVertex(const T& vertex){
	if(this->numVertices == this->maxVertices)
		return false;
	NodeTable[this->numVertices++].data = vertex;
	return true;
}

template<class T, class E>
bool Graphlist<T,E>::removeVertex(int v){
	if(this->numVertices == 1 || v < 0 || v >= this->numVertices) 
		return false;
	Edge *p, *s, *t;
	int i, k;
	while(NodeTable[v].adj != NULL){
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;
		t = NULL;
		while( s != NULL && s->dest != v){
			t = s;
			s = s->link;
		}
		if(s != NULL){
			if( t == NULL)
				NodeTable[k].adj = s->link;
			else
				t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		--this->numEdges;
	}
	--this->numVertices;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while(p != NULL){
		s = NodeTable[p->dest].adj;
		while(s != NULL){
			if(s->dest == this->numVertices){
				s->dest = v;
				break;
			}else{
				s = s->link;
			}
		}
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlist<T,E>::insertEdge(int v1, int v2, E weight){
	if(v1 > -1 && v2 > -1 && v1 < this->numVertices && v2 < this->numVertices){
		Edge *q, *p = NodeTable[v1].adj;
		while(p != NULL && p->dest != v2)
			p = p->link;
		if(p != NULL) return false;
		p = new Edge;
		q = new Edge;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		++this->numEdges;
		return true;
	}
	return false;
}

template<class T, class E>
bool Graphlist<T,E>::removeEdge(int v1, int v2){
	if(v1 != -1 && v2 != -1){
		Edge *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while(p != NULL && p->dest != v2){
			q = p;
			p = p->link;
		}
		if(p != NULL){
			if(p == s)
				NodeTable[v1].adj = p->link;
			else
				q->link = p->link;
			delete p;
		}else{
			return false;
		}
		p = NodeTable[v2].adj;
		q = NULL,s = p;
		while(p != NULL && p->dest != v1){
		   q = p;
		   p = p->link;
		}
		if(p != NULL){
			if(p == s)
				NodeTable[v2].adj = p->link;
			else
				q->link = p->link;
			delete p;
			return true;
		}else{
			return false;
		}
	}
	return false;
}

template<class T, class E>
istream& operator>>(istream& in, Graphlist<T,E>& G){
	int i, j, k, m, n;
	T e1, e2;
	E weight;
	in >>n >>m;
	for(i = 0; i < n; ++i){
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while(i < m){
		in >> e1 >> e2 >>weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if(j == -1 || k == -1)
			cout << "error input message" << endl;
		else{
			G.insertEdge(j,k,weight);
			++i;
		}
	}
	return in;
}

template<class T, class E>
ostream& operator<<(ostream& os, Graphlist<T,E>& G){
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	os << n << "," << m << endl;
	for(i = 0; i < n; ++i)
		for(j = i+1; j < n; ++j){
			//cout << i << "," << j << endl;
			w = G.getWeight(i,j);
			if(w > 0 && w < G.maxWeight){
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				os << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return os;
}

// The following is completed by matrix
template<class T, class E>
class GraphMatrix:public Graph<T, E>{
	friend istream& operator>> <T,E>(istream& in, Graphlist<T,E>& G);
	friend ostream& operator<< <T,E>(ostream& os, Graphlist<T,E>& G);
	public:
		GraphMatrix(int sz = DefaultVertices):Graph<T,E>(sz){
			int i,j;
			VerticesList = new T[this->maxVertices];
			edge = new T*[this->maxVertices];
			for(i = 0; i < this->maxVertices; ++i)
				edge[i] = new T[this->maxVertices];
			for(i = 0; i < this->maxVertices; ++i)
				for(j = 0; j <this->maxVertices; ++i)
					edge[i][j] = (i == j)?0:this->maxWeight;
		}
		~GraphMatrix(){
			delete [] VerticesList;
			delete [] edge;
		}

		T getValue(int i){ return i > -1 && i < this->numVertices ? VerticesList[i] : NULL;}

		E getWeight(int v1, int v2){
			if(v1 > -1 && v2 > -1 && v1 < this->numVertices && v2 < this->numVertices)
				return edge[v1][v2];
			else
				return NULL;
		}

		int getFirstNeighbor(int v1){
			if(v1 != -1){
				for(int i = 0; i < this->numVertices; ++i)
					if(edge[v1][i] != 0 && edge[v1][i] != this->maxWeight)
						return i;
			}
			return -1;
		}

		int getNextNeighbor(int v1, int v2){
			if(v1 != -1 && v2 != -1)
				for(int i = v2 + 1; v2 < this->numVertices; ++i)
					if(edge[v1][i] > 0 && edge[v1][i] < this->maxWeight)
						return i;
			return -1;
		}

		bool insertVertex(const T& vertex){
			if(this->numVertices == this->maxVertices)
				return false;
			VerticesList[this->numVertices++] = vertex;
			return true;
		}

		bool removeVertex(int v){
			if(v<0 && v>=this->numVertices) 
				return false;
			if(this->numVertices == 0)
				return false;
			VerticesList[v] = VerticesList[--this->numVertices];
			for(int i = 0; i < this->numVertices+1; ++i)
				if(edge[v][i] > 0 && edge[v][i] < this->maxWeight)
					--this->numEdges;
			for(int i = 0; i != this->numVertices+1; ++i)
				edge[v][i] = edge[this->numVertices][i];
			for(int i = 0; i != this->numVertices+1; ++i)
				edge[i][v] = edge[i][this->numVertices];
			return true;
		}

		bool insertEdge(int v1, int v2, E cost){
			if(v1 > -1 && v2 >-1 && v1 <this->numVertices && v2 < this->numVertices && edge[v1][v2] == this->maxWeight){
				edge[v1][v2] = edge[v2][v1] = cost;
				++this->numEdges;
				return true;
			}
			else
				return false;
		}

		bool removeEdge(int v1, int v2){
			if(v1 > -1 && v2 > -1 && v1 < this->numVertices && v2 < this->numVertices && edge[v1][v2] > 0 && edge[v1][v2]
					< this->maxWeight){
				edge[v1][v2] = edge[v2][v1] = this->maxWeight;
				--this->numEdges;
				return true;
			}else
				return false;
		};

		void create(){
			cout << "start\n";
			srand((unsigned)time(NULL));
			char x = 'a';
			for(int i = 0;i != 10; ++i){
				insertVertex(x);
				++x;
			}
			
			for(int j = 0; j != 20; ++j){
				int i = rand()%10;
				int k = rand()%10;
				if(i != k)
					insertEdge(i,k,j);
			}
		}


				



	private:
		T* VerticesList;
		E** edge;
		int getVertexPos(T vertex){
			for(int i = 0; i < this->numVertices; ++i){
				if(VerticesList[i] == vertex)
					return i;
			}
			return -1;
		}
};


template<class T, class E>
istream& operator>>(istream& in, GraphMatrix<T,E>& G){
	int i, j, k, m, n;
	T e1, e2;
	E weight;
	in >>n >>m;
	for(i = 0; i < n; ++i){
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while(i < m){
		in >> e1 >> e2 >>weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if(j == -1 || k == -1)
			cout << "error input message" << endl;
		else{
			G.insertEdge(j,k,weight);
			++i;
		}
	}
	return in;
}

template<class T, class E>
ostream& operator<<(ostream& os, GraphMatrix<T,E>& G){
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	os << n << "," << m << endl;
	for(i = 0; i < n; ++i)
		for(j = i+1; j < n; ++j){
			w = G.getWeight(i,j);
			if(w > 0 && w < G.maxWeight){
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				os << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return os;
}
	
