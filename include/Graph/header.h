#define INF 1e9

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric> 

template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex _to;
		Vertex _from;
		Distance _distance;
	};
private:
	std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;
public:
    bool has_vertex(const Vertex& v) const {
        if (std::find(_vertices.begin(), _vertices.end(), v) == _vertices.end()) return false;
        return true;
    }
    void add_vertex(const Vertex& v) {
        _vertices.push_back(v);
        _edges[v] = {};
    }
    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) return false;
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        _vertices.erase(it);
        _edges.erase(v);
        for (auto& vertex : _vertices) {
            auto& edges = _edges.at(vertex);
            edges.erase(std::remove_if(edges.begin(), edges.end(), [v](const Edge& edge) {return edge._to == v; }), edges.end());
        }
        return true;
    }
    std::vector<Vertex> vertices() const {
        return _vertices;
    }
    void print() const {
        for (const auto& v : _vertices) {
            std::cout << v << " : ";
            for (const auto& e : _edges.at(v)) {
                std::cout << "(" << e._from << ", " << e._to << ", " << e._distance << ") ";
            }
            std::cout << std::endl;
        }
    }
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        _edges[from].push_back({ to, from, d });
    }
    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_edge(from, to)) return false;
        auto& edges = _edges.at(from);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [to](const Edge& edge) {return edge._to == to; }), edges.end());
        return true;
    }
    bool remove_edge(const Edge& e) {
        if (!has_edge(e)) return false;
        auto& edges = _edges.at(e._from);
        edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge) {return edge._to == e._to && edge._distance == e._distance; }), edges.end());
        return true;
    }
    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (std::find(_vertices.begin(), _vertices.end(), from) == _vertices.end()) return false;
        for (auto& edge : _edges.at(from)) {
            if (edge._to == to) return true;
        }
        return false;
    }
    bool has_edge(const Edge& e) const {
        if (std::find(_vertices.begin(), _vertices.end(), e._from) == _vertices.end()) return false;
        for (auto& edge : _edges.at(e._from)) {
            if (edge._to == e._to && edge._distance == e._distance) return true;
        }
        return false;
    }
    std::vector<Edge> edges(const Vertex& vertex) {
        return _edges[vertex];
    }
    size_t order() const{
        return _vertices.size();
    }
    size_t degree(const Vertex& v) const {
        size_t count = 0;
        for (auto& edge : _edges.at(v)) {
            if (edge._to == v) count += 2;
            else count++;
        }
        return count;
    }
    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to))
            return {};

        for (const Vertex& vertex : _vertices) {
            for (const Edge& edge : _edges.at(vertex)) {
                if (edge._distance < 0) {
                    throw std::runtime_error("The graph contains negative weights");
                }
                if (edge._to == vertex) {
                    throw std::runtime_error("There are cycles in the graph");
                }
            }
        }

        std::unordered_map<Vertex, Distance> distances;
        std::unordered_map<Vertex, Vertex> prev;

        for (const auto& vertex : _vertices)
            distances[vertex] = INF;
        distances[from] = 0;

        std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<std::pair<Distance, Vertex>>> pq;
        pq.push({ 0, from });

        while (!pq.empty()) {
            Vertex u = pq.top().second;
            pq.pop();

            if (u == to) {
                std::vector<Edge> path;
                Vertex current = to;
                while (current != from) {
                    for (const auto& edge : _edges.at(prev[current])) {
                        if (edge._to == current) {
                            path.push_back(edge);
                            break;
                        }
                    }
                    current = prev[current];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            if (distances[u] < INF) {
                for (const auto& edge : _edges.at(u)) {
                    Distance alt = distances[u] + edge._distance;
                    if (alt < distances[edge._to]) {
                        distances[edge._to] = alt;
                        prev[edge._to] = u;
                        pq.push({ alt, edge._to });
                    }
                }
            }
        }
        return {};
    }
    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        if (!has_vertex(start_vertex)) return {};
        std::vector<Vertex> traversal_order;
        std::queue<Vertex> to_explore;
        std::unordered_set<Vertex> visited;

        to_explore.push(start_vertex);
        visited.insert(start_vertex);

        while (!to_explore.empty()) {
            Vertex current = to_explore.front();
            to_explore.pop();

            traversal_order.push_back(current);

            // Исследуем все смежные вершины
            for (const auto& edge : _edges.at(current)) {
                // Если смежная вершина ещё не посещена
                if (visited.find(edge._to) == visited.end()) {
                    visited.insert(edge._to);
                    to_explore.push(edge._to);
                }
            }
        }
        return traversal_order;
    }
    Vertex find_farthest_vertex() const {
        Vertex farthest_vertex;
        Distance max_avg_distance = -1;

        for (const auto& vertex : _vertices) {
            if (_edges.at(vertex).empty()) continue;

            Distance total_distance = std::accumulate(_edges.at(vertex).begin(), _edges.at(vertex).end(), 0.0,
                [](Distance sum, const Edge& edge) {
                    return sum + edge._distance;
                });

            Distance avg_distance = total_distance / _edges.at(vertex).size();

            if (avg_distance > max_avg_distance) {
                max_avg_distance = avg_distance;
                farthest_vertex = vertex;
            }
        }
        return farthest_vertex;
    }
};