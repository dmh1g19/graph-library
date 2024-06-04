#include <vector>
#include <iostream>
#include <string>

class Node {
private:
  int id;
  std::string name = "";
  std::vector<int> edges;

public:
  Node(int id) : id(id) {}

  void addName(std::string newName) {
    name = newName;
  }

  void addEdge(int nodeId) {
    edges.push_back(nodeId);
  }

  const std::vector<int> &getEdges() const {
    return edges;
  }

  std::string getName() const {
    return name;
  }
};
