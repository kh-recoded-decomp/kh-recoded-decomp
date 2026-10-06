typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *func_ov057_020d42ac(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov057_020d3f40(void)
{
    SetOverlayObjectFactory(func_ov057_020d42ac);
}
