typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *func_ov054_020d364c(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void func_ov054_020d2200(void)
{
    SetOverlayObjectFactory(func_ov054_020d364c);
}
