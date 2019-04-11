#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;
class undirected_graph;
class Node
{
public:
	Node();
	void nextVertex(int _vertex);
	friend class undirected_graph;
private:
	Node* link;
	int vertex;
};
Node::Node()
{
	link = NULL;
	vertex = -1;
}
void Node::nextVertex(int _vertex)
{
	link = new Node;
	link->vertex = _vertex;
}
class undirected_graph
{
public:
	undirected_graph();
	~undirected_graph();
	void setNE(int _n, int _e);
	void generate();
	void print();
	void DFS(int **DFS_tree);
	void BFS(int **BFS_tree);
private:
	int **matrix;
	Node *list;
	int n, e;
};
undirected_graph::undirected_graph()
{
	matrix = NULL;
	list = NULL;
	n = 0;
	e = 0;
}
undirected_graph::~undirected_graph()
{
	if (list)
	{
		delete[] list;
		list = NULL;
		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = NULL;
	}
}
void undirected_graph::setNE(int _n, int _e)
{
	n = _n;
	e = _e;
	if (list)
	{
		delete[] list;
		list = NULL;
		for (int i = 0; i < n; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = NULL;
	}
	matrix = new int*[n];
	list = new Node[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}
	}
	generate();
}
void undirected_graph::generate()
{
	for (int i = 0; i < e; i++)
	{
		int x, y;
		x = rand() % (n - 1);
		y = rand() % (n - x - 1) + x + 1;
		if (matrix[x][y])
		{
			i--;
			continue;
		}
		matrix[x][y] = 1;
		matrix[y][x] = 1;
	}

	for (int i = 0; i < n; i++)
	{
		Node *current = &list[i];
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j])
			{
				current->nextVertex(j);
				current = current->link;
			}
		}
	}
}
void undirected_graph::print()
{
	ofstream oup;
	oup.open("randomGraph.csv");
	for (int i = 0; i < n; i++)
	{
		oup << "," << i;
	}
	oup << endl;
	for (int i = 0; i < n; i++)
	{
		oup << i;
		for (int j = 0; j < n; j++)
		{
			cout << matrix[i][j] << " ";
			oup << "," << matrix[i][j];
		}
		oup << endl;
		cout << endl;
	}
	oup.close();
	for (int i = 0; i < n; i++)
	{
		Node *current = list[i].link;
		cout << i << "->";
		while (current)
		{
			cout << current->vertex << "->";
			current = current->link;
		}
		cout << "NULL" << endl;
	}
}
void undirected_graph::DFS(int **DFS_tree)
{
	stack<int> s;
	char color[n];
	if (DFS_tree)
	{
		for (int i = 0; i < n; i++)
		{
			color[i] = 'w';
			for (int j = 0; j < n; j++)
			{
				DFS_tree[i][j] = 0;
			}
		}
		for(int i = 0; i < n; i++)
		{
			if(color[i] != 'w')
			{
				continue;
			}
			s.push(i);
			color[i] = 'g';
			cout << i;
			while (!s.empty())
			{
				int curr= s.top();
				for (int j = 0; j < n; j++)
				{
					if (matrix[curr][j])
					{
						if (color[j] == 'w')
						{
							cout << "->" << j;
							color[j] = 'g';
							s.push(j);
							DFS_tree[curr][j] = 1;
							DFS_tree[j][curr] = 1;
							break;
						}	
					}
					if(j == n - 1)
					{
						s.pop();
					}
				}
			}
			cout << " ";
		}
	}
	cout << endl << "DFS_tree:" << endl;
	ofstream oup;
	oup.open("DFS_tree.csv");
	for (int i = 0; i < n; i++)
	{
		oup << "," << i;
	}
	oup << endl;
	for (int i = 0; i < n; i++)
	{
		oup << i;
		for (int j = 0; j < n; j++)
		{
			cout << DFS_tree[i][j] << " ";
			oup << "," << DFS_tree[i][j];
		}
		oup << endl;
		cout << endl;
	}
	oup.close();
}
void undirected_graph::BFS(int **BFS_tree)
{
	queue<int> q;
	char color[n];
	if (BFS_tree)
	{
		for (int i = 0; i < n; i++)
		{
			color[i] = 'w';
			for (int j = 0; j < n; j++)
			{
				BFS_tree[i][j] = 0;
			}
		}
		for(int i = 0; i < n; i++)
		{
			if(color[i] != 'w')
			{
				continue;
			}
			q.push(i);
			color[i] = 'g';
			cout << i;
			while (!q.empty())
			{
				int curr = q.front();
				q.pop();
				for (int j = 0; j < n; j++)
				{
					if (matrix[curr][j])
					{
						if (color[j] == 'w')
						{
							cout << "->" << j;
							color[j] = 'g';
							q.push(j);
							BFS_tree[curr][j] = 1;
							BFS_tree[j][curr] = 1;
						}
					}
				}
				color[i] = 'b';
			}
			cout << " ";
		}
	}
	cout << endl << "BFS_tree:" << endl;
	ofstream oup;
	oup.open("BFS_tree.csv");
	for (int i = 0; i < n; i++)
	{
		oup << "," << i;
	}
	oup << endl;
	for (int i = 0; i < n; i++)
	{
		oup << i;
		for (int j = 0; j < n; j++)
		{
			cout << BFS_tree[i][j] << " ";
			oup << "," << BFS_tree[i][j];
		}
		oup << endl;
		cout << endl;
	}
	oup.close();
}
int main()
{
	int n, e;
	srand(unsigned(time(NULL)));
	undirected_graph graph1;
	cout << "Please enter number of vertex : ";
	cin >> n;
	system("CLS");
	while (true)
	{
		cout << "Please enter number of edge : ";
		cin >> e;
		if (e <= n * (n - 1) / 2)
		{
			system("CLS");
			break;
		}
	}
	int **Traversal = new int*[n];
	for (int i = 0; i < n; i++)
	{
		Traversal[i] = new int[n];
	}
	graph1.setNE(n, e);
	graph1.print();
	graph1.DFS(Traversal);
	cout << endl;
	
	graph1.BFS(Traversal);
	cout << endl;
	
	for (int i = 0; i < n; i++)
	{
		delete[] Traversal[i];
	}
	delete[] Traversal;
	system("PAUSE");
}
