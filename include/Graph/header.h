#include <iostream>
#include <unordered_map>

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
        if (std::find(_vertices.cbegin(), _vertices.cend(), v) == _vertices.cend()) return false;
        return true;
    }
    void add_vertex(const Vertex& v) {
        _vertices.push_back(v);
        _edges[v] = {};
    }
    bool remove_vertex(const Vertex& v) {
        if (has_vertex(v) == false) return false;
        auto it = std::find(_vertices.cbegin(), _vertices.cend(), v);
        _vertices.erase(it);
        _edges.erase(v);
        return true;
    }
    std::vector<Vertex> vertices() const {
        return _vertices;
    }
    void print() const {
        for (const auto& v : _vertices) {
            std::cout << v << " : ";
            for (const auto& e : _edges.at(v)) {
                std::cout << "(" << e._to << ", " << e._distance << "),  ";
            }
            std::cout << std::endl;
        }
    }

};