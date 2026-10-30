# DS Protect runtime

Hand-written ARM routines from the DS Protect anti-piracy library in overlay 104:
the dispatch trampolines in front of each encrypted check, the five static
initializers that unscramble the library at start-up, the shared dispatcher and
the table decoder. Like the NitroSDK pages, each section is checked by
`tools/sdklib/verify_sdklib.py`, which runs the ROM's own instructions against the
Python model in `tools/sdklib/families/dsprot.py`; see
[PROGRESS_POLICY.md](../PROGRESS_POLICY.md).

A port does not need any of this: the checks it protects (flash cart, emulator
and ROM integrity tests) pass on genuine hardware and have no gameplay effect, so
a host build can call the decrypted C functions directly or skip them. This page
exists so that the protection can be understood and removed safely.

## Layout and life cycle

Every guarded function `F` has a 36-byte trampoline followed by a 0x18-byte
context, `DSProtWrapperContext`:

| Offset | Field | Meaning |
|---|---|---|
| `0x00` | `returnAddress` | The caller's `lr` while `F` runs; afterwards a stack address. |
| `0x04` | `encodedKey` | Current key of `F`'s encrypted body. |
| `0x08` | `function` | `F`'s address + 0x1000, then `DSProt_BSS` + 0x1000 + its byte size. |
| `0x10` | `savedR10` | The caller's `r10` while `F` runs. |
| `0x14` | `encodedDispatcher` | `Encryptor_DecryptionWrapperFragment` + 0x1000. |

The trampolines, the encryptor and the RC4 routines are themselves stored
scrambled. `FS_StartOverlay` runs the overlay's `.ctor` list,
`gDSProtInitializers`, whose five entries each hand the table that follows them
to `Encryptor_DecodeFunctionTable`. After that the trampolines are plain ARM, and
each guarded function stays RC4-encrypted except while it runs.

The tests replace the routines' callees with small ARM stubs that log their
arguments, and record the cache-maintenance `mcr`s without emulating a cache; the
Hardware bullets say what those operations do on the ARM946E-S.

## Trampolines

All seventeen trampolines are the same nine instructions; they differ only in the
context that follows them, and so in the function they reach. They are called
like the guarded function, with its arguments in `r0`-`r3` and on the stack, and
return whatever it returns. Each reads its own address from `pc`, loads the
context's `encodedDispatcher`, subtracts 0x1000 and jumps there with `ip` = the
context; the target is pushed and popped through `pc`, so `sp`, `lr` and `r0`-`r3`
reach the dispatcher unchanged.

### `__DSProt_DetectFlashcart`

- **Interface:** as `DetectFlashcart` (0x8c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectFlashcartContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectFlashcartContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `__DSProt_DetectNotFlashcart`

- **Interface:** as `DetectNotFlashcart` (0x8c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectNotFlashcartContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectNotFlashcartContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `__DSProt_DetectEmulator`

- **Interface:** as `DetectEmulator` (0x8c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectEmulatorContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectEmulatorContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `__DSProt_DetectNotEmulator`

- **Interface:** as `DetectNotEmulator` (0x8c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectNotEmulatorContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectNotEmulatorContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `__DSProt_DetectDummy`

- **Interface:** as `DetectDummy` (0x80 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectDummyContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectDummyContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `__DSProt_DetectNotDummy`

- **Interface:** as `DetectNotDummy` (0x80 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDetectNotDummyContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDetectNotDummyContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Integrity_MACOwner_IsBad`

- **Interface:** as `Integrity_MACOwner_IsBad` (0x110 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtIntegrityMACOwnerIsBadContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtIntegrityMACOwnerIsBadContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Integrity_MACOwner_IsGood`

- **Interface:** as `Integrity_MACOwner_IsGood` (0x110 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtIntegrityMACOwnerIsGoodContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtIntegrityMACOwnerIsGoodContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Integrity_ROMTest_IsBad`

- **Interface:** as `Integrity_ROMTest_IsBad` (0x110 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtIntegrityROMTestIsBadContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtIntegrityROMTestIsBadContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Integrity_ROMTest_IsGood`

- **Interface:** as `Integrity_ROMTest_IsGood` (0x110 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtIntegrityROMTestIsGoodContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtIntegrityROMTestIsGoodContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_MACOwner_IsBad`

- **Interface:** as `MACOwner_IsBad` (0xac encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtMACOwnerIsBadContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtMACOwnerIsBadContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_MACOwner_IsGood`

- **Interface:** as `MACOwner_IsGood` (0xac encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtMACOwnerIsGoodContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtMACOwnerIsGoodContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_ROMUtil_CRC32`

- **Interface:** as `ROMUtil_CRC32` (0x90 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtROMUtilCRC32Context.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtROMUtilCRC32Context`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_ROMTest_IsBad`

- **Interface:** as `ROMTest_IsBad` (0x23c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtROMTestIsBadContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtROMTestIsBadContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_ROMTest_IsGood`

- **Interface:** as `ROMTest_IsGood` (0x23c encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtROMTestIsGoodContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtROMTestIsGoodContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Dummy_IsBad`

- **Interface:** as `Dummy_IsBad` (0x8 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDummyIsBadContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDummyIsBadContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

### `RunEncrypted_Dummy_IsGood`

- **Interface:** as `Dummy_IsGood` (0x8 encrypted bytes); `ip` and the flags are
  clobbered, every other register reaches the dispatcher unchanged.
- **Behavior:** jumps to `gDSProtDummyIsGoodContext.encodedDispatcher - 0x1000`, which is
  `Encryptor_DecryptionWrapperFragment`, with `ip` = `&gDSProtDummyIsGoodContext`.
- **Hardware:** none; plain ARM code that only reads the context after itself.

## Static initializers

Each initializer is `orr r0, pc, #0`, `adds r0, r0, #4` and a conditional branch
that is always taken, because the address is never zero: a tail call of
`Encryptor_DecodeFunctionTable` with the table that starts right after its code.

### `__sinit_ov104_020d2028`

- **Interface:** no arguments or result; `r0` and the flags are clobbered, and
  `r1`-`r3`, `sp` and `lr` reach the decoder unchanged, so the decoder returns to
  the caller.
- **Behavior:** calls `Encryptor_DecodeFunctionTable(&gDSProtDetectionFunctions)`, the table 12
  bytes after its own entry, which unscrambles the six `__DSProt_Detect*` trampolines.
- **Hardware:** none of its own; see the decoder.

### `__sinit_ov104_020d25d0`

- **Interface:** no arguments or result; `r0` and the flags are clobbered, and
  `r1`-`r3`, `sp` and `lr` reach the decoder unchanged, so the decoder returns to
  the caller.
- **Behavior:** calls `Encryptor_DecodeFunctionTable(&gDSProtIntegrityFunctions)`, the table 12
  bytes after its own entry, which unscrambles the four `RunEncrypted_Integrity_*` trampolines.
- **Hardware:** none of its own; see the decoder.

### `__sinit_ov104_020d2958`

- **Interface:** no arguments or result; `r0` and the flags are clobbered, and
  `r1`-`r3`, `sp` and `lr` reach the decoder unchanged, so the decoder returns to
  the caller.
- **Behavior:** calls `Encryptor_DecodeFunctionTable(&gDSProtEncryptionFunctions)`, the table 12
  bytes after its own entry, which unscrambles `Encryptor_EncryptFunction`, `Encryptor_DecryptFunction` and `Encryptor_DecryptionWrapperFragment`.
- **Hardware:** none of its own; see the decoder.

### `__sinit_ov104_020d31fc`

- **Interface:** no arguments or result; `r0` and the flags are clobbered, and
  `r1`-`r3`, `sp` and `lr` reach the decoder unchanged, so the decoder returns to
  the caller.
- **Behavior:** calls `Encryptor_DecodeFunctionTable(&gDSProtRuntimeFunctions)`, the table 12
  bytes after its own entry, which unscrambles the seven `RunEncrypted_ROMTest_*`, `RunEncrypted_MACOwner_*`, `RunEncrypted_ROMUtil_CRC32` and `RunEncrypted_Dummy_*` trampolines.
- **Hardware:** none of its own; see the decoder.

### `__sinit_ov104_020d36b4`

- **Interface:** no arguments or result; `r0` and the flags are clobbered, and
  `r1`-`r3`, `sp` and `lr` reach the decoder unchanged, so the decoder returns to
  the caller.
- **Behavior:** calls `Encryptor_DecodeFunctionTable(&gDSProtCipherFunctions)`, the table 12
  bytes after its own entry, which unscrambles the seven `RC4_*` routines.
- **Hardware:** none of its own; see the decoder.

## Dispatcher and decoder

### `Encryptor_DecryptionWrapperFragment`

- **Interface:** entered from a trampoline with `ip` = the context, `lr` = the
  original caller and the guarded function's arguments in `r0`-`r3`. Returns the
  guarded function's `r0` and restores `r4`-`r11`, `sp` and `lr`; `r1`-`r3`, `ip`
  and the flags hold whatever the callees left.
- **Behavior:** pushes `r0`-`r3`, saves `r10` in `savedR10` and `lr` in
  `returnAddress`, then calls `Encryptor_DecryptFunction` with `encodedKey` and the
  two `function` words; it returns the decrypted entry. The fragment restores the
  arguments, calls that entry and keeps its result in `r4`, calls
  `Encryptor_EncryptFunction` with the same three context words and stores the key
  it returns in `encodedKey`. Finally it reloads `lr` from `returnAddress`,
  overwrites that field with the current `sp`, restores `r10` and returns the
  result. A guarded function that re-entered itself would share the context, so
  re-entrant calls are not supported.
- **Hardware:** none here; the decrypt and encrypt routines flush the caches.

### `Encryptor_DecodeFunctionTable`

- **Interface:** `r0` = a table of `DSProtFunctionInfo` entries (address + 0x1000,
  `DSProt_BSS` + 0x1000 + byte size), ended by an entry whose address is 0. No
  result; `r4`-`r11` and `sp` are preserved.
- **Behavior:** clears the three words before the table, then walks each entry's
  range a word at a time with a running key that starts at 0xF0B9A2EA. A `B` or
  `BLX` immediate (`Encryptor_CategorizeInstruction` 3 or 1) gets bit 24 flipped
  and 0x402 subtracted from its 24-bit offset, and the key absorbs the new top
  byte. Every other word, a `BL` after its bit 24 is flipped, is XORed with the
  key, which then absorbs the word and the word shifted right by 8, keeping 24
  bits. Size bits below a whole word are ignored. After each range it clears the
  entry and flushes the caches, and it stops at the first entry whose address is 0.
- **Hardware:** after every range it cleans and invalidates all 4 x 32 lines of
  the 4-way ARM946E-S data cache by set and index (`mcr p15, 0, rN, c7, c14, 2`,
  each preceded by a write-buffer drain), invalidates the instruction cache
  (`c7, c5, 0`) and drains the write buffer again, so the decoded instructions are
  fetched from memory.
