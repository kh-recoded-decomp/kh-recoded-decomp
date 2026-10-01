extern void Ov002_BlitNibbleRun(int a, int b, int width, int height,
                                int flags, int style, void *row);

typedef struct {
    unsigned char bytes[5];
} Ov002ShortRow;

extern Ov002ShortRow data_0209de06[];

void DrawShortLayoutRow_02073824(int a, int b, int row) {
    Ov002_BlitNibbleRun(a, b, 5, 110, 0, 1, &data_0209de06[row]);
}
