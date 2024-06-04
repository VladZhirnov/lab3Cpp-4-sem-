#include <iostream>
#include <map>
#include <vector>
#include <Graph/header.h>

int main()
{
    Graph<int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(4, 2, 1);
    graph.add_edge(3, 5, 4);
    graph.add_edge(1, 3, 4);
    graph.add_edge(5, 4, 5);

    graph.print();
    std::vector<int> bfs_order = graph.walk(1);

    //Порядок обхода в ширину
    std::cout << "\n BFS:\n";
    for (int vertex : bfs_order) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    double distance = 0.0;
    for (const auto& edge : graph.shortest_path(1, 4)) {
        std::cout << "From " << edge._from << " to " << edge._to << " distance = " << edge._distance << std::endl;
        distance += edge._distance;
    }
    std::cout << "Distance from 1 to 4 =  " << distance << std::endl;

    // Вершина с наибольшей средней длиной ребер
    int farthest_vertex = graph.find_farthest_vertex();
    std::cout << "\n vertex with max avg distance: " << farthest_vertex << std::endl;
}