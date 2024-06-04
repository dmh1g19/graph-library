#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include "node.h"

class Graph {
private:
  std::unordered_map<int, Node*> nodes;
  bool isDirect;

public:
  Graph(bool isDirect) : isDirect(isDirect)  {}

  void addNode(int nodeId) {
    nodes[nodeId] = new Node(nodeId);
  }

  void setEdge(int a, int b) {
    nodes[a]->addEdge(b);
  }

  void setName(int nodeId, std::string name) {
    for(const auto& pair : nodes) {
      if(pair.first == nodeId) {
        pair.second->addName(name);
      }
    }
  }

  void printGraphData() const {
    std::stringstream ss;

    ss << "Is directional: " << isDirect << std::endl;
    ss << "Node list: ";

    std::string sep = "";
    for(const auto& pair : nodes) {
      ss << sep << pair.first;
      sep = ", ";
    }
    std::cout << ss.str() << std::endl;
  }

  void printAllNodeEdges() const {
    std::stringstream ss;

    std::string sep = "";
    for(const auto& pair : nodes) {

      ss << sep << pair.first << "-{";
      std::string sep2 = "";

      const std::vector<int> &edges = pair.second->getEdges();
      for(int i=0;i<edges.size();i++) {
        ss << sep2 << pair.second->getEdges()[i];
        sep2 = ",";
      }
      
      ss << "} ";
      sep = ", ";
    }
    std::cout << ss.str() << std::endl;
  }

  std::unordered_map<int, Node*> get_graph() {
    return nodes;
  }

  void scale_free_graph(int total_nodes) {


  }
};

