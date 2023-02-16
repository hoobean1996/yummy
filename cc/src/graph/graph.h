#pragma once

#include <vector>
namespace Structures {

class Node {
public:
  Node();
  ~Node();

private:
  int id_;
};

class Edge {
public:
  Edge();
  ~Edge();
};

class Graph {
public:
  Graph() = delete;
  explicit Graph(int n);
  ~Graph();

private:
};
} // namespace Structures