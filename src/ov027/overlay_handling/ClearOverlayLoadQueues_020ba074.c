extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0202c438(void);
extern void func_020ba1e0(int *load_node, int nFlag);

extern int overlay_load_queues;

void ClearOverlayLoadQueues_020ba074(void)
{
    int *load_node;
    int *load_queue;
    int *next_node;

    load_queue = *(int **)&overlay_load_queues;
    load_node = (int *)NNS_FndGetNextListObject(load_queue, 0);
    while (load_node != 0) {
        next_node = (int *)NNS_FndGetNextListObject(load_queue, load_node);
        if (load_node[0] == 1) {
            func_0202c438();
            if (load_node[2] != 0) {
                NNSi_FndFreeFromDefaultHeap((void *)load_node[2]);
            }
        }
        NNS_FndRemoveListObject(load_queue, load_node);
        if ((load_node[1] & 0x80000000) != 0) {
            load_node[1] = 0;
        } else if (load_node[1] != 0) {
            NNSi_FndFreeFromDefaultHeap((void *)load_node[1]);
        }
        if (load_node != 0) {
            NNSi_FndFreeFromDefaultHeap(load_node);
        }
        load_node = next_node;
    }

    load_node = (int *)NNS_FndGetNextListObject(load_queue + 3, 0);
    while (load_node != 0) {
        next_node = (int *)NNS_FndGetNextListObject(load_queue + 3, load_node);
        func_020ba1e0(load_node, 1);
        load_node = next_node;
    }
}
