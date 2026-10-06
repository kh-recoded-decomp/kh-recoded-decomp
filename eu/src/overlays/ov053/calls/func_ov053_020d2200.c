typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *func_ov053_020d2b40(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov053_020d2200(void)
{
    SetOverlayObjectFactory(func_ov053_020d2b40);
}
