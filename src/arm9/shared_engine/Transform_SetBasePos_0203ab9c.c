struct T { int a, b, c; };
struct S { int pad[18]; struct T t; };

void Transform_SetBasePos_0203ab9c(struct S *d, struct T *s)
{
    d->t = *s;
}
