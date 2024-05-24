#include <vector>
#include <iostream>
#include <string>

class Node {
private:
  int id;
  std::string name = "";
  std::vector<int> edges;

public:
  Node(const int &id) : id(id) {}

  void addName(const std::string &newName) {
    name = newName;
  }

  void addEdge(const int &nodeId) {
    edges.push_back(nodeId);
  }

  const std::vector<int> &getEdges() const {
    return edges;
  }

  const std::string &getName() const {
    return name;
  }
};
