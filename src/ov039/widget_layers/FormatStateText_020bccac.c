typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern int data_ov039_020bea00;
extern int func_ov027_020ba31c(int arg0, int arg1, int arg2, int arg3, int arg4);

int FormatStateText_020bccac(int id, int buffer, int format, ...)
{
    va_list args;

    va_start(args, format);
    func_ov027_020ba31c(data_ov039_020bea00 + 0xcac4, id, buffer, format, (int)args);
    return buffer;
}
