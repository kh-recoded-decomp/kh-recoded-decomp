extern int func_02001908(int obj, int index, int unused);
extern void func_02001804(int obj, int x, int y, int z, int index, int *outIndex);
extern int func_020019f4(int obj);

void func_ov039_020be574(int obj, int x, int y, int z, int startIndex)
{
    int index = startIndex;
    int advance;

    do {
        advance = func_02001908(obj, index, 0);
        func_02001804(obj, x - (advance >> 1), y, z, index, &index);
        advance = func_020019f4(obj);
        y = y + advance;
    } while (index != 0);
}
