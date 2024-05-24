#include <iostream>
#include "graph.h"

int main() {
  
  Graph G = Graph(true);
  G.addNode(1);
  G.addNode(2);
  G.addNode(3);

  G.setEdge(1, 2);
  G.setEdge(1, 3);
  G.setEdge(2, 1);

  G.setName(1, "Root");

  G.printGraphData();
  G.printAllNodeEdges();
  
  return 0;
}
