extern int func_020227fc(void *buffer, int *result);

typedef struct {
    int words[9];
} Blob36;

int func_020229c8(Blob36 *ptr, int unused1, int unused2, int unused3)
{
    Blob36 local;
    int result;

    local = *ptr;
    if (func_020227fc(&local, &result) != 0) {
        *ptr = local;
        return result;
    }
    return -1;
}
