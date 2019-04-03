#include <iostream>

#define MAX_NODES 128
#define MAX_VALUE 2000000000

using namespace std;

int V, E, a[MAX_NODES][MAX_NODES], parent[MAX_NODES], dist[MAX_NODES], from, to, x, y, z;
bool visited[MAX_NODES];

void Dijkstra(int node)
{
	int min_dist, i;
	for(i = 1; i <= V; i++)
	{
		dist[i] = MAX_VALUE;
		visited[i] = 0;
	}
	dist[node] = 0;

	for(;;)
	{
		min_dist = -1;
		for(i = 1; i <= V; i++)
		if(dist[i] > min_dist && !visited[i])
		{
			node = i;
			min_dist = dist[i];
		}
		if(min_dist == -1)
			return;
		visited[node] = 1;

		for(i = 1; i <= V; i++)
			if(a[node][i] && (dist[i] < min(dist[node], a[node][i]))){
				dist[i] = dist[node] + a[node][i];
				parent[i] = node;
			}
	}

}

void printWay(int node)
{
	if(parent[node] != from)
		printWay(parent[node]);
	cout << parent[node] << " ";
}

int main()
{
	cin >> V >> E;
	cin >> from >> to;
	for(int i = 1; i <= E; i++)
	{
		cin >> x >> y >> z;
		a[x][y] = z;
	}

	Dijkstra(from);

	if(dist[to] == MAX_VALUE)
		cout << "No way exists from node " << from << " to node " << to << "!\n";
	else
	{
		cout << dist[to] << endl;
		printWay(to);
		cout << to << endl;
	}

	return 0;
}