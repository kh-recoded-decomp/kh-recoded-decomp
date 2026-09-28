extern void Node_UnlinkAndClearRefs(int);

void QuadTree_RemoveObject_02033c60(int *param_1, int param_2) {
    if (param_1[0x27] == 0) {
        return;
    }
    Node_UnlinkAndClearRefs(param_2);
}
