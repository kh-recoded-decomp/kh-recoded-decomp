/* Compares up to the requested number of bytes in two strings, stopping at a difference or null terminator and returning the unsigned-byte difference.
 * Uncertainty: This identifies a shared library operation; the particular scene, asset or gameplay caller using it is not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/msl/c/calls/strncmp.c.
 * Original routine: strncmp. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
int String_CompareBounded_020220bc(const unsigned char *s1, const unsigned char *s2, unsigned int n) {
    if (n != 0) {
        do {
            unsigned char b = *s2++;
            unsigned char a = *s1++;
            if (a != b) return (int)a - (int)b;
            if (a == 0) break;
        } while (--n != 0);
    }
    return 0;
}
