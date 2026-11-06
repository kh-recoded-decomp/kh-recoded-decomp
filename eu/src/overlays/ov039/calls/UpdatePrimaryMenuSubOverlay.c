extern int gMenuSubOverlayIndexStorage[];
extern char gPrimaryMenuRegistryTail[];

void UpdatePrimaryMenuSubOverlay(int arg0)
{
    int index = gMenuSubOverlayIndexStorage[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(gPrimaryMenuRegistryTail + index * 8) + 8))(arg0);
    }
}
