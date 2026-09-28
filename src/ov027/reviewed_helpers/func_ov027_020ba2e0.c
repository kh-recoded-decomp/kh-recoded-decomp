/* Forwards a variable argument list to another helper and returns the caller-provided output buffer.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_020898cc.c. */

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern int func_020ba31c(int a, unsigned b, unsigned short *c, unsigned d, void *va);

unsigned short *func_ov027_020ba2e0(int a, unsigned b, unsigned short *c, unsigned d, ...) {
    va_list ap;

    va_start(ap, d);
    func_020ba31c(a, b, c, d, ap);
    return c;
}
