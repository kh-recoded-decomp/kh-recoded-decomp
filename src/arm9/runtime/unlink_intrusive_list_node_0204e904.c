/* Removes a doubly linked node from a list, updating its neighbors and head when needed, then clears the node links.
 * Evidence: Pointer rewiring operations in source.
 * Uncertainty: The two-word node layout and head pointer are directly visible.
 * Source: src/auto/func_02031df0.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
void unlink_intrusive_list_node_0204e904(int *listHead, int *node) {
    if (node == (int *)*listHead) *listHead = node[1];
    if ((int *)node[1] != (int *)0) *(int *)node[1] = *node;
    if (*node != 0) *(int *)(*node + 4) = node[1];
    *node = 0;
    node[1] = 0;
}
