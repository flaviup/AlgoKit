
#ifndef __BICONNECTEDCOMPONENTS_H__
#define __BICONNECTEDCOMPONENTS_H__

/*

The idea is to run a depth-first search while maintaining the following information:
	the depth of each vertex in the depth-first-search tree (once it gets visited), and
	for each vertex v, the lowest depth of neighbors of all descendants of v in the depth-first-search tree, called the lowpoint.

The depth is standard to maintain during a depth-first search. 
The lowpoint of v can be computed after visiting all descendants of v 
(i.e., just before v gets popped off the depth-first-search stack) as the minimum of the depth of v, 
the depth of all neighbors of v (other than the parent of v in the depth-first-search tree) 
and the lowpoint of all children of v in the depth-first-search tree.

The key fact is that a nonroot vertex v is a cut vertex (or articulation point) separating two biconnected components 
if and only if there is a child y of v such that lowpoint(y) = depth(v). This property can be tested once 
the depth-first search returned from every child of v (i.e., just before v gets popped off the depth-first-search stack), 
and if true, v separates the graph into different biconnected components. This can be represented by 
computing one biconnected component out of every such y (a component which contains y will contain the subtree of y, plus v), 
and then erasing the subtree of y from the tree.

The root vertex must be handled separately: it is a cut vertex if and only if it has at least two children. 
Thus, it suffices to simply build one component out of each child subtree of the root (including the root).

*/

#endif // __BICONNECTEDCOMPONENTS_H__
