extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_020b7df4[];
extern unsigned char data_020b7808[];

void *get_cached_movie_saturation_table_020aa9e8(void) {
    void *saturationTable;

    if (data_020b7df4[0] == 0) {
        if ((unsigned int)data_020b7df4[3] >= 0x300) {
            saturationTable = (void *)data_020b7df4[4];
            data_020b7df4[0] = (int)saturationTable;
            MIi_CpuCopyFast(data_020b7808, saturationTable, 0x300);
            data_020b7df4[4] += 0x300;
            data_020b7df4[3] -= 0x300;
        } else {
            return data_020b7808;
        }
    }
    return (void *)data_020b7df4[0];
}
