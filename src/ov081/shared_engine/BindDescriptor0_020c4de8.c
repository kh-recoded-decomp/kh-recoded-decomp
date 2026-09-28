extern int Ov008_GetDescriptor0(void);
extern void Ov008_SetWord0And20(void *, int);
void BindDescriptor0_020c4de8(void *obj)
{
    Ov008_SetWord0And20(obj, Ov008_GetDescriptor0());
}
