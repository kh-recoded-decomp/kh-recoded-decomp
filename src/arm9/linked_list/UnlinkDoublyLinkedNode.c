/* Based on src/auto/func_02028740.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
void UnlinkDoublyLinkedNode(int **listHead, int *removedNode) {
    if (removedNode[0] != 0) {
        *(int *)(removedNode[0] + 4) = removedNode[1];
    }
    if (removedNode[1] != 0) {
        *(int *)removedNode[1] = removedNode[0];
    }
    if (removedNode == *listHead) {
        *listHead = (int *)removedNode[0];
    }
    removedNode[1] = 0;
    removedNode[0] = 0;
}
