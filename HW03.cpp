#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
using namespace std;

class MaxFlow
{
public:
	MaxFlow();
	MaxFlow(char file_name[]);
	void DFS();
	bool reduce();
	void Ford_Fulkerson();
	void print();
	int get_max_flow()const;
private:
	int **residual;
	int *path;
	int size;
	int max_flow;
};
MaxFlow::MaxFlow()
{
	residual = NULL;
	path = NULL;
	size = 0;
	max_flow = 0;
}
MaxFlow::MaxFlow(char file_name[])
{
	ifstream inp;
	inp.open(file_name);
	int tmp, count = 0;
	while(!inp.eof())
	{
		inp >> tmp;
		count++;
	}
	size = sqrt(count);
	inp.close();
	inp.open(file_name);
	residual = new int*[size];
	for(int i = 0; i < size; i++)
	{
		residual[i] = new int[size];
		for(int j = 0; j < size; j++)
		{
			inp >> residual[i][j];
		}
	}
	path = new int[size];
	for(int i = 0; i < size; i++)
	{
		path[i] = -1;
	}
	max_flow = 0;
}
void MaxFlow::DFS()
{
	stack<int> s;
	char color[size];
	bool foundT = false;
	for(int i = 0; i < size; i++)//initial
	{
		color[i] = 'w';
	}
	s.push(0);
	color[0] = 'g';
	while(!s.empty() && !foundT)
	{
		int curr = s.top();
		for(int i = 0; i < size; i++)
		{
			if(residual[curr][i])
			{
				if(color[i] == 'w')
				{
					color[i] = 'g';
					s.push(i);
					if(i == size - 1)
					{
						foundT = true;
					} 
					break;
				}
			}
			if(i == size -1)
			{
				s.pop();
			}
		}
	}
	for(int i = 0; i < size; i++)//initial
	{
		path[i] = -1;
	}
	int i = s.size() - 1;
	while(!s.empty())//save path
	{
		path[i--] = s.top();
		//cout << s.top() << " ";
		s.pop();
	}
}
bool MaxFlow::reduce()
{
	int min;
	if(path[0] != -1)
	{
		min = residual[ path[0] ][ path[1] ];
	}
	else
	{
		return false;
	}
	for(int i = 1; i < size - 1 && path[i] != size - 1; i++)
	{
		if(residual[ path[i] ][ path[i+1] ] < min)
		{
			min = residual[ path[i] ][ path[i+1] ];
		}
	}
	max_flow += min;
	for(int i = 0; i < size - 1 && path[i] != size - 1; i++)
	{
		residual[ path[i] ][ path[i+1] ] -= min;
	}
	return true;
}
void MaxFlow::Ford_Fulkerson()
{
	while(true)
	{
		DFS();
		if(!reduce())
		{
			print();
			break;
		}
		print();
	}
}
void MaxFlow::print()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cout << residual[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for(int i = 0; i < size; i++)
	{
		cout << path[i] << " ";
	}
	cout << endl << endl;
}
int MaxFlow::get_max_flow()const
{
	return max_flow;
}

int main()
{
	char file_name[] = "file.txt";
	MaxFlow graph1;
	graph1 = MaxFlow(file_name);
	
	graph1.print();
	graph1.Ford_Fulkerson();
	cout << "MaxFlow = " << graph1.get_max_flow() << endl;
	return 0;
}
