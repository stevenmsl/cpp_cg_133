#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol133;

/*
{"$id":"1","neighbors":[{"$id":"2","neighbors":[{"$ref":"1"},{"$id":"3","neighbors":
[{"$ref":"2"},{"$id":"4","neighbors":[{"$ref":"3"},{"$ref":"1"}],"val":4}],"val":3}],"val":2},
{"$ref":"4"}],"val":1}

Explanation:
Node 1's value is 1, and it has two neighbors: Node 2 and 4.
Node 2's value is 2, and it has two neighbors: Node 1 and 3.
Node 3's value is 3, and it has two neighbors: Node 2 and 4.
Node 4's value is 4, and it has two neighbors: Node 1 and 3.
*/

tuple<Node *>
testFixture1()
{
  auto g = new Node(1);
  g->neighbors.push_back(new Node(2));
  g->neighbors.push_back(new Node(4));

  auto node2 = g->neighbors[0];
  node2->neighbors.push_back(g); // Node 1
  node2->neighbors.push_back(new Node(3));
  auto node3 = node2->neighbors[1];
  auto node4 = g->neighbors[1];
  node3->neighbors.push_back(node2);
  node3->neighbors.push_back(node4);
  node4->neighbors.push_back(g);
  node4->neighbors.push_back(node3);

  return make_tuple(g);
}

void test1()
{
  auto f = testFixture1();
  Solution sol;
  auto g = sol.cloneGraph(get<0>(f));

  auto node1 = (g != nullptr) ? to_string(g->id) : "failed";

  cout << "Expect to see 1: " << node1 << endl;
  cout << "Node 1 has two neighbors: 2 and 4: " << endl;
  for (auto n : g->neighbors)
    cout << n->id << " ";
  cout << endl;
  cout << "Node 2 has two neighbors: 1 and 3: " << endl;
  for (auto n : g->neighbors[0]->neighbors)
    cout << n->id << " ";
  cout << endl;
}

main()
{
  test1();

  return 0;
}