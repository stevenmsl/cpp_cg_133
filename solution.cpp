#include "solution.h"
#include "util.h"
#include <unordered_set>
#include <numeric>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>
#include <functional>
using namespace sol133;
using namespace std;

/*takeaways
  - use BFS hence a queue is required
  - a set to record nodes we have visited
  - a hash table to track which node has been created
    - a mapping from the original node to the created
      node
  - time complexity O(V+E)
*/

Node *Solution::cloneGraph(Node *node)
{
  if (node == nullptr)
    return nullptr;
  /* for BFS to deal with cyclic graph */
  auto visited = unordered_set<Node *>();
  /* original -> cloned */
  auto cloned = unordered_map<Node *, Node *>();
  auto q = queue<Node *>();
  q.push(node);

  while (!q.empty())
  {
    auto visit = q.front();
    q.pop();
    if (visited.count(visit))
      continue;
    visited.insert(visit);
    /* clone the node */
    if (!cloned.count(visit))
      cloned[visit] = new Node(visit->id);

    auto c = cloned[visit];
    /* clone the neighbors */
    for (auto n : visit->neighbors)
    {
      if (!cloned.count(n))
        cloned[n] = new Node(n->id);
      c->neighbors.push_back(cloned[n]);
      q.push(n);
    }
  }

  return cloned[node];
}