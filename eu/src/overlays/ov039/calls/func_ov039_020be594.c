extern int func_0200191c(int obj, int index, int unused);
extern void DrawDirectional(int obj, int x, int y, int z, int index, int *outIndex);
extern int GetNestedModeByte(int obj);

void func_ov039_020be594(int obj, int x, int y, int z, int startIndex)
{
    int index = startIndex;
    int advance;

    do {
        advance = func_0200191c(obj, index, 0);
        DrawDirectional(obj, x - (advance >> 1), y, z, index, &index);
        advance = GetNestedModeByte(obj);
        y = y + advance;
    } while (index != 0);
}
