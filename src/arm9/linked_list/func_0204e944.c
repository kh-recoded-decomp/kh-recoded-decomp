/* Based on src/auto/func_02031e30.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
void func_0204e944(int **listHead, int **tailLink, int **newNode) {
    int *oldTail;
    newNode[1] = (int *)tailLink;
    oldTail = tailLink[0];
    newNode[0] = oldTail;
    if (oldTail == 0) {
        listHead[0] = (int *)newNode;
    } else {
        oldTail[1] = (int)newNode;
    }
    tailLink[0] = (int *)newNode;
}
