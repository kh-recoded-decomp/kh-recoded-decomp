/* Based on src/auto/func_0202872c.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
void LinkNodeAtListHead(int *listHead, int *newNode)
{
    newNode[1] = 0;
    newNode[0] = *listHead;
    if (*listHead != 0)
        *(int *)(*listHead + 4) = (int)newNode;
    *listHead = (int)newNode;
}
