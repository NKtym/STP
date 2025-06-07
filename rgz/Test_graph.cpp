#include <gtest/gtest.h>
#include "Graph.hpp"
#include <vector>
#include <algorithm>

class GraphIntTest : public ::testing::Test {
protected:
    Graph<int,int> graph;

    void SetUp() override {
        EXPECT_TRUE(graph.empty());
        EXPECT_FALSE(graph.contains(1));
        int tmp1[]{2,3};
        int tmp2[]{3};
        int tmp3[]{1};
        graph.insert(1);
        graph.insert_or_assign(2, tmp1, 2);
        graph.insert_or_assign(3, tmp2, 1);
        graph.insert_or_assign(4, tmp3, 1);
    }
};

TEST_F(GraphIntTest, CopyConstructor) {
    Graph<int,int> copy = graph;
    EXPECT_TRUE(copy.contains(1));
    std::size_t cnt; 
    copy.get_edges(2, cnt);
    EXPECT_EQ(cnt, 2);
    graph.erase(2);
    EXPECT_TRUE(copy.contains(2));
    EXPECT_FALSE(graph.contains(2));
}

TEST_F(GraphIntTest, MoveConstructor) {
    Graph<int,int> tmp = graph;
    Graph<int,int> mv = std::move(tmp);
    EXPECT_TRUE(mv.contains(3));
    EXPECT_TRUE(mv.contains(4));
    EXPECT_TRUE(tmp.empty());
}

TEST_F(GraphIntTest, CopyOp) {
    Graph<int,int> other;
    other.insert(5);
    EXPECT_TRUE(other.contains(5));
    other = graph;
    EXPECT_FALSE(other.contains(5));
    EXPECT_TRUE(other.contains(1));
    other.erase(1);
    EXPECT_FALSE(other.contains(1));
    EXPECT_TRUE(graph.contains(1));
}

TEST_F(GraphIntTest, MoveOp) {
    Graph<int,int> other;
    other.insert(5);
    EXPECT_TRUE(other.contains(5));
    other = std::move(graph);
    EXPECT_FALSE(other.contains(5));
    EXPECT_TRUE(other.contains(3));
    EXPECT_TRUE(other.contains(4));
    EXPECT_TRUE(graph.empty());
}


TEST_F(GraphIntTest, GetEdgesAndFind) {
    EXPECT_EQ(graph[5], nullptr);
    EXPECT_EQ(graph.find(5), nullptr);
    auto *e2 = graph[2];
    ASSERT_NE(e2, nullptr);
    std::size_t cnt;
    auto *edges2 = graph.get_edges(2, cnt);
    EXPECT_EQ(cnt, 2);
    EXPECT_EQ(e2[0], edges2[0]);
}

TEST_F(GraphIntTest, At) {
    EXPECT_THROW(graph.at(5), std::out_of_range);
    auto *e3 = graph.at(3);
    EXPECT_EQ(e3[0], 3);
}

TEST_F(GraphIntTest, Erase) {
    EXPECT_TRUE(graph.contains(4));
    graph.erase(4);
    EXPECT_FALSE(graph.contains(4));
}

TEST_F(GraphIntTest, EmptyAndContains) {
    EXPECT_FALSE(graph.empty());
    EXPECT_TRUE(graph.contains(2));
    EXPECT_TRUE(graph.contains(4));
    graph.erase(1);
    graph.erase(2); 
    graph.erase(3); 
    graph.erase(4);
    EXPECT_TRUE(graph.empty());
    EXPECT_FALSE(graph.contains(1));
    EXPECT_FALSE(graph.contains(3));
}

TEST_F(GraphIntTest, BeginEnd) {
    std::vector<int> vertexs;
    for (auto v = graph.begin(); v != graph.end(); ++v) {
        vertexs.push_back(*v);
    }
    EXPECT_EQ(vertexs.size(), 4);
    EXPECT_EQ(vertexs, std::vector<int>({1,2,3,4}));
}

TEST_F(GraphIntTest, RbeginRend) {
    std::vector<int> vertexs;
    for (auto it = graph.begin(); it != graph.end(); ++it) 
        vertexs.push_back(*it);
    std::vector<int> rev_vertexs;
    for (auto it = graph.rbegin(); it != graph.rend(); ++it) 
        rev_vertexs.push_back(*it);
    std::reverse(vertexs.begin(), vertexs.end());
    EXPECT_EQ(rev_vertexs, vertexs);
}

TEST_F(GraphIntTest, GetNodes) {
    std::size_t cnt;
    auto const* vertex = graph.get_nodes(2, cnt);
    EXPECT_EQ(cnt, 2);
    EXPECT_EQ(vertex[0], 2);
    EXPECT_EQ(vertex[1], 3);
}

TEST_F(GraphIntTest, DFSTraversal) {
    auto dfs = graph.dfs(2);
    std::vector<int> order;
    for (auto v: dfs) 
        order.push_back(v);
    ASSERT_FALSE(order.empty());
    EXPECT_EQ(order.front(), 2);
    EXPECT_EQ(order.size(), 2);
    EXPECT_EQ(order, std::vector<int>({2,3}));
}

TEST_F(GraphIntTest, BFSTraversal) {
    auto bfs = graph.bfs(2);
    std::vector<int> order;
    for (auto v: bfs) 
        order.push_back(v);
    ASSERT_FALSE(order.empty());
    EXPECT_EQ(order.front(), 2);
    EXPECT_EQ(order.size(), 2);
    EXPECT_EQ(order, std::vector<int>({2,3}));
}

TEST(MyGraph, MyTest){
    Graph<int,int> myGraph;
    myGraph.insert(1);
    int tmp1[]{3,4};
    int tmp2[]{4};
    int tmp3[]{1};
    myGraph.insert_or_assign(2, tmp1, 2);
    myGraph.insert_or_assign(3, tmp2, 1);
    myGraph.insert_or_assign(4, tmp3, 1);
    auto bfs = myGraph.bfs(2);
    auto dfs = myGraph.dfs(2);
    std::vector<int> order1;
    for (auto v: bfs) 
        order1.push_back(v);
    std::vector<int> order2;
    for (auto v: dfs) 
        order2.push_back(v);
    ASSERT_FALSE(order1.empty());
    EXPECT_EQ(order1.front(), 2);
    EXPECT_EQ(order1.size(), 4);
    EXPECT_EQ(order1, std::vector<int>({2,3,4,1}));
    ASSERT_FALSE(order2.empty());
    EXPECT_EQ(order2.front(), 2);
    EXPECT_EQ(order2.size(), 4);
    EXPECT_EQ(order2, std::vector<int>({2,4,1,3}));
}