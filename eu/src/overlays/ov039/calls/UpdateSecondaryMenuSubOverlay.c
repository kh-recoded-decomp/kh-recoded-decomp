extern int gMenuSubOverlayIndexStorage[];
extern char gSecondaryMenuRegistryTail[];

void UpdateSecondaryMenuSubOverlay(int arg0)
{
    int index = gMenuSubOverlayIndexStorage[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(gSecondaryMenuRegistryTail + index * 8) + 8))(arg0);
    }
}
