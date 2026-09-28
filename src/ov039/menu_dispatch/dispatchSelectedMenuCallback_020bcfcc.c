typedef int (*MenuHandlerCallback)(int event);

typedef struct {
    void *callbackObject;
    int padding;
} MenuHandlerEntry;

extern int data_020bea84[];
extern MenuHandlerEntry data_020be8d0[];

int dispatchSelectedMenuCallback_020bcfcc(int event)
{
    int handled = 1;
    int selectedIndex = data_020bea84[1];

    if (selectedIndex != -1) {
        handled = (*(MenuHandlerCallback *)data_020be8d0[selectedIndex].callbackObject)(event);
    }

    return handled;
}
