void *OSi_RemoveLinkFromQueue(void **queue) {
    char *head = (char *)queue[0];
    if (head != 0) {
        char *next = *(char **)(head + 0x80);
        queue[0] = next;
        if (next != 0) {
            *(void **)(next + 0x7c) = 0;
        } else {
            queue[1] = 0;
            *(void **)(head + 0x78) = 0;
        }
    }
    return head;
}
