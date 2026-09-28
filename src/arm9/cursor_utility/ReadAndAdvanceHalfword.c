unsigned short ReadAndAdvanceHalfword(unsigned short **cursor)
{
    unsigned short *valuePointer = *cursor;
    unsigned short value = *valuePointer++;
    *cursor = valuePointer;
    return value;
}
