#pragma once
#include <cstddef>
#include <stdexcept>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>

template<typename Node, typename Edge>
class Graph {
public:
    Graph();
    ~Graph();
    Graph(const Graph& graph);
    Graph(Graph&& graph);
    Graph& operator=(const Graph& graph);
    Graph& operator=(Graph&& graph);
    Edge* operator[](const Node& node);
    Edge* at(const Node& node);
    bool contains(const Node& node) const;
    bool empty() const;
    void insert(const Node& node);
    void insert_or_assign(const Node& node, const Edge* edges, const std::size_t count);
    void erase(const Node& node);
    Edge* find(const Node& node);
    class iterator;
    iterator begin() const;
    iterator end() const;
    std::reverse_iterator<iterator> rbegin() const;
    std::reverse_iterator<iterator> rend()   const;
    const Edge* get_edges(const Node& node, std::size_t &out_count) const;
    const Node* get_nodes(const Node& node, std::size_t &out_count) const;
    class DfsTraversal;
    DfsTraversal dfs(const Node& start) const;
    class BfsTraversal;
    BfsTraversal bfs(const Node& start) const;

private:
    struct NodeVertex {
        Node node;
        Edge* edges = nullptr;
        std::size_t edgeCount = 0;
        std::size_t edgeCapacity = 0;
    };
    NodeVertex* entries;
    std::size_t nodeCount;
    std::size_t nodeCapacity;
    void increase_node_capacity(std::size_t minCapacity);
    void increase_edge_capacity(NodeVertex &vertex, std::size_t minCapacity);
    NodeVertex* find_vertex(const Node& node) const;
};

template<typename Node, typename Edge>
Graph<Node, Edge>::Graph() : entries(nullptr), nodeCount(0), nodeCapacity(0) {}

template<typename Node, typename Edge>
Graph<Node, Edge>::~Graph() {
    for (std::size_t i = 0; i < nodeCount; i++)
        delete[] entries[i].edges;
    delete[] entries;
}

template<typename Node, typename Edge>
Graph<Node, Edge>::Graph(const Graph& graph) : entries(nullptr), nodeCount(0), nodeCapacity(0) {
    increase_node_capacity(graph.nodeCount);
    nodeCount = graph.nodeCount;
    for (std::size_t i = 0; i < nodeCount; i++) {
        entries[i].node = graph.entries[i].node;
        entries[i].edgeCapacity = graph.entries[i].edgeCount;
        entries[i].edgeCount = graph.entries[i].edgeCount;
        entries[i].edges = new Edge[entries[i].edgeCapacity];
        for (std::size_t j = 0; j < entries[i].edgeCount; ++j)
            entries[i].edges[j] = graph.entries[i].edges[j];
    }
}

template<typename Node, typename Edge>
Graph<Node, Edge>::Graph(Graph&& graph) : entries(graph.entries), nodeCount(graph.nodeCount), nodeCapacity(graph.nodeCapacity) {
    graph.entries = nullptr;
    graph.nodeCount = graph.nodeCapacity = 0;
}

template<typename Node, typename Edge>
Graph<Node, Edge>& Graph<Node, Edge>::operator=(const Graph& graph) {
    if (this != &graph) {
        this -> ~Graph();
        new (this) Graph(graph);
    }
    return *this;
}

template<typename Node, typename Edge>
Graph<Node, Edge>& Graph<Node, Edge>::operator=(Graph&& graph) {
    if (this != &graph) {
        this -> ~Graph();
        entries = graph.entries;
        nodeCount = graph.nodeCount;
        nodeCapacity = graph.nodeCapacity;
        graph.entries = nullptr;
        graph.nodeCount = graph.nodeCapacity = 0;
    }
    return *this;
}

template<typename Node, typename Edge>
void Graph<Node, Edge>::increase_node_capacity(std::size_t minCapacity) {
    if (nodeCapacity >= minCapacity) 
        return;
    std::size_t newCapacity;
    if (nodeCapacity == 0)
        newCapacity = 1;
    else
        newCapacity = nodeCapacity * 2;
    while (newCapacity < minCapacity) 
        newCapacity *= 2;
    NodeVertex* newArr = new NodeVertex[newCapacity];
    for (std::size_t i = 0; i < nodeCount; i++)
        newArr[i] = entries[i];
    delete[] entries;
    entries = newArr;
    nodeCapacity = newCapacity;
}

template<typename Node, typename Edge>
void Graph<Node, Edge>::increase_edge_capacity(NodeVertex &vertex, std::size_t minCapacity) {
    if (vertex.edgeCapacity >= minCapacity) 
        return;
    std::size_t newCapacity;
    if (nodeCapacity == 0)
        newCapacity = 1;
    else
        newCapacity = nodeCapacity * 2;
    while (newCapacity < minCapacity) 
        newCapacity *= 2;
    Edge* newArr = new Edge[newCapacity];
    for (std::size_t i = 0; i < vertex.edgeCount; i++)
        newArr[i] = vertex.edges[i];
    delete[] vertex.edges;
    vertex.edges = newArr;
    vertex.edgeCapacity = newCapacity;
}

template<typename Node, typename Edge>
typename Graph<Node,Edge>::NodeVertex* Graph<Node, Edge>::find_vertex(const Node& node) const {
    for (std::size_t i = 0; i < nodeCount; i++)
        if (entries[i].node == node)
            return &entries[i];
    return nullptr;
}

template<typename Node, typename Edge>
Edge* Graph<Node, Edge>::operator[](const Node& node) {
    auto* vertex = find_vertex(node);
    if (vertex)
        return vertex->edges;
    return nullptr;
}

template<typename Node, typename Edge>
Edge* Graph<Node, Edge>::at(const Node& node) {
    auto* vertex = find_vertex(node);
    if (vertex) 
        return vertex->edges;
    throw std::out_of_range("Node не найден");
}

template<typename Node, typename Edge>
bool Graph<Node, Edge>::contains(const Node& node) const {
    if(find_vertex(node))
        return true;
    return false;
}

template<typename Node, typename Edge>
bool Graph<Node, Edge>::empty() const {
    if(nodeCount == 0)
        return true;
    return false;
}

template<typename Node, typename Edge>
void Graph<Node, Edge>::insert(const Node& node) {
    if (contains(node)) 
        return;
    increase_node_capacity(nodeCount+1);
    entries[nodeCount++] = NodeVertex{node, nullptr, 0, 0};
}

template<typename Node, typename Edge>
void Graph<Node, Edge>::insert_or_assign(const Node& node, const Edge* edges,const std::size_t count) {
    auto* vertex = find_vertex(node);
    if (!vertex) {
        increase_node_capacity(nodeCount+1);
        entries[nodeCount++] = NodeVertex{node, nullptr, 0, 0};
        vertex = find_vertex(node);
    }
    increase_edge_capacity(*vertex, count);
    for (std::size_t i = 0; i < count; i++)
        vertex->edges[i] = edges[i];
    vertex->edgeCount = count;
}

template<typename Node, typename Edge>
void Graph<Node, Edge>::erase(const Node& node) {
    for (std::size_t i = 0; i < nodeCount; i++) {
        if (entries[i].node == node) {
            delete[] entries[i].edges;
            for (std::size_t j = i+1; j < nodeCount; j++) {
                entries[j-1] = entries[j];
            }
            nodeCount--;
            return;
        }
    }
}

template<typename Node, typename Edge>
Edge* Graph<Node, Edge>::find(const Node& node) {
    auto* vertex = find_vertex(node);
    if (vertex)
        return vertex->edges;
    return nullptr;
}

template<typename Node, typename Edge>
class Graph<Node, Edge>::iterator {
public:
    using value_type = Node;
    using difference_type = std::ptrdiff_t;
    using pointer = const Node*;
    using reference = const Node&;
    using iterator_category = std::bidirectional_iterator_tag;
    iterator(const NodeVertex* ivert): iVertex(ivert) {}
    reference operator*() const { return iVertex->node; }
    pointer operator->() const { return &iVertex->node; }
    iterator& operator++() { 
        ++iVertex; 
        return *this; 
    }
    iterator operator++(int) { 
        iterator ivert=*this;
        ++ivert; 
        return ivert; 
    }
    iterator& operator--() {
        --iVertex;
        return *this;
    }
    iterator operator--(int) {
        iterator tmp = *this;
        --iVertex;
        return tmp;
    }
    
    bool operator==(const iterator& ivert) const { return iVertex==ivert.iVertex; }
    bool operator!=(const iterator& ivert) const { return iVertex!=ivert.iVertex; }

private:
    const NodeVertex* iVertex;
};

template<typename Node, typename Edge>
auto Graph<Node, Edge>::begin() const -> iterator { return iterator(entries); }

template<typename Node, typename Edge>
auto Graph<Node, Edge>::end() const -> iterator { return iterator(entries + nodeCount); }

template<typename Node, typename Edge>
auto Graph<Node, Edge>::rbegin() const -> std::reverse_iterator<iterator> {
    return std::reverse_iterator<iterator>(end());
}

template<typename Node, typename Edge>
auto Graph<Node, Edge>::rend() const -> std::reverse_iterator<iterator> {
    return std::reverse_iterator<iterator>(begin());
}

template<typename Node, typename Edge>
const Edge* Graph<Node, Edge>::get_edges(const Node& node, std::size_t &out_count) const {
    auto* vertex = find_vertex(node);
    if (!vertex) 
        throw std::out_of_range("Node не найден");
    out_count = vertex->edgeCount;
    return vertex->edges;
}

template<typename Node, typename Edge>
const Node* Graph<Node, Edge>::get_nodes(const Node& node, std::size_t &out_count) const {
    auto* vertex = find_vertex(node);
    if (!vertex) 
        throw std::out_of_range("Node не найден");
    out_count = vertex->edgeCount;
    return reinterpret_cast<const Node*>(vertex->edges);
}

template<typename Node, typename Edge>
class Graph<Node, Edge>::DfsTraversal {
public:
    class Iterator {
    public:
        Iterator(): graph(nullptr), visited(nullptr), visitedCapacity(0), endFlag(true) {}
        Iterator(const Graph* graph, Node start) : graph(graph), visited(nullptr), visitedCapacity(0), endFlag(false) {
            visitedCapacity = graph->nodeCount;
            visited = new bool[visitedCapacity];
            for (std::size_t i = 0; i < visitedCapacity; ++i)
                visited[i] = false;
            stack.push(start);
            ++(*this);
        }
        ~Iterator(){ delete[] visited; }
        Node operator*() const { return current; }
        Iterator& operator++() {
            while (!stack.empty()) {
                auto node = stack.top(); 
                stack.pop();
                auto* vertex = graph->find_vertex(node);
                if (!vertex) 
                    continue;
                std::size_t index = 0;
                for (; index < graph->nodeCount; index++){
                    if (graph->entries[index].node == node) 
                        break;
                }
                if (!visited[index]) {
                    visited[index] = true;
                    current = node;
                    for (std::size_t i = 0; i < vertex->edgeCount; i++)
                        stack.push(vertex->edges[i]);
                    return *this;
                }
            }
            endFlag = true;
            return *this;
        }
        bool operator!=(const Iterator& itr) const { return endFlag != itr.endFlag; }
    private:
        const Graph* graph;
        std::stack<Node> stack;
        bool* visited;
        std::size_t visitedCapacity;
        Node current;
        bool endFlag;
    };

    DfsTraversal(const Graph* graph, Node start): graph(graph), start(start) {}
    Iterator begin() const { return Iterator(graph, start); }
    Iterator end() const { return Iterator(); }

private:
    const Graph* graph;
    Node start;
};

template<typename Node, typename Edge>
auto Graph<Node, Edge>::dfs(const Node& start) const -> DfsTraversal {
    return DfsTraversal(this, start);
}

template<typename Node, typename Edge>
class Graph<Node, Edge>::BfsTraversal {
public:
    class Iterator {
    public:
        Iterator(): graph(nullptr), visited(nullptr), visitedCapacity(0), endFlag(true) {}
        Iterator(const Graph* graph, Node start): graph(graph), visited(nullptr), visitedCapacity(0), endFlag(false) {
            visitedCapacity = graph->nodeCount;
            visited = new bool[visitedCapacity]();
            std::queue<Node> q; 
            queue = q; 
            queue.push(start);
            ++(*this);
        }
        ~Iterator(){ delete[] visited; }
        Node operator*() const { return current; }
        Iterator& operator++() {
            while (!queue.empty()) {
                auto node = queue.front(); 
                queue.pop();
                auto* vertex = graph->find_vertex(node);
                if (!vertex) 
                    continue;
                std::size_t index = 0;
                for (; index < graph->nodeCount; ++index)
                    if (graph->entries[index].node == node) 
                        break;
                if (!visited[index]) {
                    visited[index] = true;
                    current = node;
                    for (std::size_t i = 0; i < vertex->edgeCount; i++)
                        queue.push(vertex->edges[i]);
                    return *this;
                }
            }
            endFlag = true;
            return *this;
        }
        bool operator!=(const Iterator& o) const { return endFlag != o.endFlag; }
    private:
        const Graph* graph;
        std::queue<Node> queue;
        bool* visited;
        std::size_t visitedCapacity;
        Node current;
        bool endFlag;
    };

    BfsTraversal(const Graph* graph, Node start): graph(graph), start(start) {}
    Iterator begin() const { return Iterator(graph, start); }
    Iterator end() const { return Iterator(); }

private:
    const Graph* graph;
    Node start;
};

template<typename Node, typename Edge>
auto Graph<Node, Edge>::bfs(const Node& start) const -> BfsTraversal {
    return BfsTraversal(this, start);
}