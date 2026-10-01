typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern void func_ov075_020c8ba0(void *menu, int messageId, int dialogType, int position, int cancelable, va_list args);

void ShowDialogMessageAt_020c8d0c(void *menu, int messageId, int dialogType, int position, int cancelable, ...)
{
    va_list args;

    va_start(args, cancelable);
    func_ov075_020c8ba0(menu, messageId, dialogType, position, cancelable, args);
}
