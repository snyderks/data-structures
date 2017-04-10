//
// Created by Kristian Snyder on 4/10/17.
//

#ifndef LAB11_DIRECTEDGRAPH_H
#define LAB11_DIRECTEDGRAPH_H

#include <cstdlib>
#include <unordered_map>


class DirectedGraph {
private:
    std::unordered_map<int, std::hash<int>> nodes;
};


#endif //LAB11_DIRECTEDGRAPH_H
