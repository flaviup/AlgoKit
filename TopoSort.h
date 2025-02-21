
#ifndef __TOPOSORT_H__
#define __TOPOSORT_H__

/* Kahn (1962)
L <- Empty list that will contain the sorted elements
S <- Set of all nodes with no incoming edges
while S is non-empty do
    remove a node n from S
    insert n into L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S
if graph has edges then
    return error (graph has at least one cycle)
else 
    return L (a topologically sorted order)
*/

/* Tarjan (1976) - DFS based
L <- Empty list that will contain the sorted nodes
S <- Set of all nodes with no outgoing edges
for each node n in S do
    visit(n) 
function visit(node n)
    if n has not been visited yet then
        mark n as visited
        for each node m with an edge from m to n do
            visit(m)
        add n to L

*/

#endif // __TOPOSORT_H__
