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
*/

Node *Solution::cloneGraph(Node *node)
{
  if (node == nullptr)
    return nullptr;
  /* for BFS to deal with cyclic graph */
  auto visited = unordered_set<Node *>();
  /* original -> cloned */
  auto created = unordered_map<Node *, Node *>();
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
    if (!created.count(visit))
      created[visit] = new Node(visit->id);
      
    auto cloned = created[visit];
    /* clone the neighbors */
    for (auto n : visit->neighbors)
    {
      if (!created.count(n))
        created[n] = new Node(n->id);
      cloned->neighbors.push_back(created[n]);
      q.push(n);
    }
  }

  return created[node];
}