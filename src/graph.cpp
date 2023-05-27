#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include "graph.h"

struct Node {
    int m_state;
    std::vector<int> m_path;

    Node(int s, const std::vector<int> & p){
        m_state = s;
        m_path = p;
    }
};

Graph::Graph(const std::vector<std::vector<int>> & adj) {
    m_adj = adj;
}

std::vector<std::vector<int>> Graph::BFS(const int &s, const int &g) const {
    std::vector<bool> explored(m_adj.size());
    std::queue<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.front();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        for (int adjacent : m_adj.at(curr.m_state)) {
            if (!explored.at(adjacent)) {
                std::vector<int> n = curr.m_path;
                n.push_back(adjacent);
                frontier.push(Node(adjacent, n));
            }    
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::DFS(const int &s, const int &g) const {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.top();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        for (int adjacent : m_adj.at(curr.m_state)) {
            if (!explored.at(adjacent)) {
                std::vector<int> n = curr.m_path;
                n.push_back(adjacent);
                frontier.push(Node(adjacent, n));
            }    
        }
    }
    return {};
}


std::vector<std::vector<int>> Graph::DLS(const int &s, const int &g, const int &depth) const {
    std::vector<bool> explored(m_adj.size());
    std::stack<Node> frontier; 
    std::vector<int> explore_order;
    frontier.push(Node(s,{}));
    while (!frontier.empty()) {
        Node curr = frontier.top();
        if(std::find(explore_order.begin(), explore_order.end(), curr.m_state) == explore_order.end())
            explore_order.push_back(curr.m_state);
        frontier.pop();
        explored.at(curr.m_state) = true;
        if(curr.m_state == g)
            return {curr.m_path, explore_order};
        if(curr.m_path.size() < depth) {
            for (int adjacent : m_adj.at(curr.m_state)) {
                if (!explored.at(adjacent)) {
                    std::vector<int> n = curr.m_path;
                    n.push_back(adjacent);
                    frontier.push(Node(adjacent, n));
                }    
            }
        }
    }
    return {};
}

std::vector<std::vector<int>> Graph::IDS(const int &s, const int &g) const {
    for(int depth = 0; depth < 100000; depth++) {
        std::vector<std::vector<int>> result = DLS(s, g, depth);
        if(result.size() > 0)
            return result;
    }
    return {};
}



