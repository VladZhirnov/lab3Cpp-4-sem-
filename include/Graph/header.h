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

};