/* Computes an inner/outer padded keyed hash through a caller-supplied hash-operation table.
 * Target conditional branches compare lengths as unsigned throughout the key shortening and pad loops.
 * Adapted CC0 C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, src/calls/func_0200bb80.c. */


typedef struct {
    unsigned int digestSize;   
    unsigned int blockSize;    
    void *self;       
    void *digestBuf;  
    void (*reset)(void *self);
    void (*update)(void *self, const void *data, unsigned int len);
    void (*finish)(void *self, void *out);
} HashOps;

void ComputeKeyedHash_0200da88(void *out, const void *msg, unsigned int msgLen, const void *key, unsigned int keyLen, HashOps *ops) {
    unsigned char keyBuf[0x40];
    unsigned char ipad[0x40];
    unsigned char opad[0x40];
    unsigned int i;

    if (out && msg && msgLen && key && keyLen && ops) {
        const unsigned char *kp = key;
        unsigned int klen = keyLen;

        if (keyLen > ops->blockSize) {
            ops->reset(ops->self);
            ops->update(ops->self, key, keyLen);
            ops->finish(ops->self, keyBuf);
            kp = keyBuf;
            klen = ops->digestSize;
        }

        for (i = 0; i < klen; i++) {
            ipad[i] = kp[i] ^ 0x36;
        }
        for (; i < ops->blockSize; i++) {
            ipad[i] = 0x36;
        }

        ops->reset(ops->self);
        ops->update(ops->self, ipad, ops->blockSize);
        ops->update(ops->self, msg, msgLen);
        ops->finish(ops->self, ops->digestBuf);

        for (i = 0; i < klen; i++) {
            opad[i] = kp[i] ^ 0x5c;
        }
        for (; i < ops->blockSize; i++) {
            opad[i] = 0x5c;
        }

        ops->reset(ops->self);
        ops->update(ops->self, opad, ops->blockSize);
        ops->update(ops->self, ops->digestBuf, ops->digestSize);
        ops->finish(ops->self, out);
    }
}
