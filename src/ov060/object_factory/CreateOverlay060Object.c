/* The shared initializer clears all 0x230 bytes and records variant 1 and
 * selection index 0. See analysis/types/overlay_loading.h for observed fields.
 * No specific enemy, screen or game mode is inferred from these constants. */
typedef struct OverlayObject OverlayObject;
extern void *func_0202a178(unsigned int size);
extern void InitializeOverlayObject(OverlayObject *object, int variant, int selectionIndex);
OverlayObject *CreateOverlay060Object(void)
{
    OverlayObject *object = func_0202a178(0x230);
    InitializeOverlayObject(object, 1, 0);
    return object;
}
