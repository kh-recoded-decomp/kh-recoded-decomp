typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *func_ov055_020d3dd4(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov055_020d3740(void)
{
    SetOverlayObjectFactory(func_ov055_020d3dd4);
}
