#include <iostream>
#include <map>
#include <vector>
#include <Graph/header.h>

int main()
{
	Graph<int, double> a;
	a.add_vertex(4);
	a.add_vertex(6);
	a.print();
}