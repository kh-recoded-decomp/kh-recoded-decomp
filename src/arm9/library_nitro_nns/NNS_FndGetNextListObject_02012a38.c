void *NNS_FndGetNextListObject_02012a38(void *list, void *obj) {
    if (obj == 0) {
        return *(void **)list;
    }
    return *(void **)((char *)obj + *(unsigned short *)((char *)list + 0xa) + 4);
}
