extern void QuadTree_RemoveObject_02033c60(int *tree, int node);
extern void func_02033c3c(int *tree, int node);

/* Re-inserts a node if its moved flag is set */
void QuadTree_ReinsertNodeIfFlagSet_02033f10(int *tree, int node) {
    if ((*(unsigned char *)(node + 0xc) & 1) == 0) {
        return;
    }
    QuadTree_RemoveObject_02033c60(tree, node);
    func_02033c3c(tree, node);
    *(unsigned char *)(node + 0xc) &= ~1;
}
