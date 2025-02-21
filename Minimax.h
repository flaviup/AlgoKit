
#ifndef __MINIMAX_H__
#define __MINIMAX_H__

/*  max(a, b) = -min(-a, -b)
function integer minimax(node, depth)
    if node is a terminal node or depth <= 0:
        return the heuristic value of node
    alpha = -8
    for child in node:                       # evaluation is identical for both players 
        alpha = max(alpha, -minimax(child, depth-1))
    return alpha 
*/

#endif // __MINIMAX_H__
