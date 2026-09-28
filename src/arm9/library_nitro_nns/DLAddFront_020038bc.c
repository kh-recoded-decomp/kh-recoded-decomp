struct DLNode {
    struct DLNode *prev;
    struct DLNode *next;
};

struct DLNode *DLAddFront_020038bc(struct DLNode *head, struct DLNode *node) {
    node->next = head;
    node->prev = 0;
    if (head != 0) {
        head->prev = node;
    }
    return node;
}
