/* Removes a node from the object registry list and hash bucket chain.
 * Evidence: List pointers and key-based hash bucket operations in source.
 * Uncertainty: Registry key identity is inferred from 16-bit field at +0x10.
 * Source: src/calls/func_02023890.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */


extern int data_020603c8[];
extern int data_020603d8[];

void unlink_object_registry_node_0202a3a8(int node)
{
    unsigned int nodeKey;
    int nextNode;
    int bucketHead;

    nodeKey = *(unsigned short *)(node + 0x10);
    if (data_020603c8[3] == node) {
        data_020603c8[3] = *(int *)(node + 0xc);
    }
    bucketHead = data_020603d8[nodeKey];
    if (bucketHead == node) {
        nextNode = *(int *)(node + 0xc);
        if (nextNode != 0 && *(unsigned short *)(nextNode + 0x10) == nodeKey) {
            data_020603d8[nodeKey] = nextNode;
        } else {
            data_020603d8[nodeKey] = 0;
        }
    }
    if (*(int *)(node + 0xc) != 0) {
        *(int *)(*(int *)(node + 0xc) + 8) = *(int *)(node + 8);
    }
    if (*(int *)(node + 8) != 0) {
        *(int *)(*(int *)(node + 8) + 0xc) = *(int *)(node + 0xc);
    }
}
