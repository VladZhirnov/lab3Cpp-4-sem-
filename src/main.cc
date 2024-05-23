#include <iostream>
#include <map>
#include <vector>
#include <Graph/header.h>

int main()
{
	Graph<int, double> a;
	a.add_vertex(4);
	a.print();
	a.add_edge(4, 9, 0.5);
	a.print();
	a.remove_edge(4, 9);
	a.print();
}