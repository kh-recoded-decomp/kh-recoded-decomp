/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/auto/OSi_EnqueueTail.c. */
void OSi_EnqueueTail(void **list, void **node)
{
    void **tail = list[0x8c / 4];

    if (tail == 0) {
        list[0x88 / 4] = node;
    } else {
        tail[0x10 / 4] = node;
    }

    node[0x14 / 4] = tail;
    node[0x10 / 4] = 0;
    list[0x8c / 4] = node;
}
