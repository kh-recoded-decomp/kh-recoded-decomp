typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern void func_ov075_020c8ba0(void *menu, int messageId, int dialogType, int position, int cancelable, va_list args);

void ShowDialogMessage_020c8ce4(void *menu, int messageId, int dialogType, int cancelable, ...)
{
    va_list args;

    va_start(args, cancelable);
    func_ov075_020c8ba0(menu, messageId, dialogType, -1, cancelable, args);
}
