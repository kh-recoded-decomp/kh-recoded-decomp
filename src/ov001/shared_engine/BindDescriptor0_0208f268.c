extern int Ov008_GetDescriptor0(void);
extern void Ov008_SetWord0And20(void *, int);
void BindDescriptor0_0208f268(void *obj)
{
    Ov008_SetWord0And20(obj, Ov008_GetDescriptor0());
}
