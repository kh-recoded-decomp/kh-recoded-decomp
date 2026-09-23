/* Unlinks an object from its parent child list and clears parent links from its children.
 * Evidence: Parent/first-child/next-sibling offsets and unlink operations in source.
 * Uncertainty: Object type is generic engine tree node.
 * Source: src/auto/func_0202a6d8.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

void detach_object_tree_node_0202ee1c(int node) {
    int child, previousChild;
    if (*(int *)(node + 0xbc) != 0) {
        previousChild = 0;
        child = *(int *)(*(int *)(node + 0xbc) + 0xc0);
        while (child != 0) {
            if (child == node) {
                if (previousChild != 0) {
                    *(int *)(previousChild + 0xc4) = *(int *)(child + 0xc4);
                } else {
                    *(int *)(*(int *)(node + 0xbc) + 0xc0) = *(int *)(child + 0xc4);
                }
            }
            previousChild = child;
            child = *(int *)(child + 0xc4);
        }
        *(int *)(node + 0xbc) = 0;
    }
    {
        int childCursor = *(int *)(node + 0xc0);
        if (childCursor != 0) {
            while (childCursor != 0) {
                *(int *)(childCursor + 0xbc) = 0;
                childCursor = *(int *)(childCursor + 0xc4);
            }
            *(int *)(node + 0xc0) = 0;
        }
    }
}
