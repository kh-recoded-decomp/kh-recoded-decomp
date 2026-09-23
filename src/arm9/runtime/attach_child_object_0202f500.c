/* Detaches the destination from its old parent if needed, copies initialization data from the source, and links the destination into the source object tree.
 * Evidence: Parent/child/sibling pointer updates, initialization block copy, and source/destination offsets in function body.
 * Uncertainty: The short value stored at destination +0xc8 comes from an opaque resource lookup.
 * Source: src/calls/func_0202af3c.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);
extern void func_0202ee1c(void *child);
extern void func_02021e60(void *dst, void *src);
extern int func_0201aafc(void *resourceEntry, void *searchKey);

extern char data_02060770[];

void attach_child_object_0202f500(void *child, void *parent, void *initializationData) {
    int resourceIndex;
    void *resourceEntry;

    if (((void **)child)[0xbc / 4] != (void *)0) {
        func_0202ee1c(child);
    }
    if (parent == (void *)0) return;

    INITi_CpuClear32_0x01ff86fc(0, data_02060770, 0x10);
    func_02021e60(data_02060770, initializationData);

    resourceEntry = ((void **)parent)[0x24 / 4];
    resourceEntry = resourceEntry ? (void *)((char *)resourceEntry + 0x40) : (void *)0;
    if (resourceEntry == (void *)0) {
        resourceIndex = -1;
    } else {
        resourceIndex = func_0201aafc(resourceEntry, data_02060770);
    }
    *(unsigned short *)((char *)child + 0xc8) = (unsigned short)resourceIndex;

    {
        void *previousFirstChild = ((void **)parent)[0xc0 / 4];
        if (previousFirstChild != (void *)0) ((void **)child)[0xc4 / 4] = previousFirstChild;
    }
    ((void **)parent)[0xc0 / 4] = child;
    ((void **)child)[0xbc / 4] = parent;
}
