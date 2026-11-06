# Native exception-handler DATA views (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Verified native callback boundary

These names describe the borrowed exception-handler argument and function pointer read by OSi_DisplayExContext. The native exception-state view spans existing separate BSS symbols; neither partial pointer view permits shrinking its symbol. The source belongs to a verified-library receipt. Integration must keep the instructions, literals and semantic checks intact and renew source evidence through the existing unchanged strict verifier; a manual hash edit is not validation.

## Inventory and evidence

### `main:02056df4` → `gOsExceptionHandlerArgumentStorage`

Previous label `data_02056df4`; existing ELF size **8 bytes**. Source: `eu/src/data/bss/Bss_main_02056df0.c`.

8-byte native BSS symbol: handler argument pointer at+0 and reserved word at+4.

OSi_DisplayExContext loads the first word here into callback argument register r1; the first argument r0 is OSi_ExContext. The adjacent global exception-state view places handlerArg at+4 from OSi_ExceptionState, which is this address.

Limits: Preserve all eight bytes and the cross-symbol state view. The handler argument is borrowed and may be NULL. This symbol is not an allocated exception-context buffer.

Pinned references:

- `eu/libs/nitro/os/asm_stubs/calls/OSi_DisplayExContext.c` → `src/arm9/library_nitro_os/OSi_DisplayExContext_02003e28.c`; reference line(s) 13, 32.
- `eu/src/data/bss/Bss_main_02056df0.c`; reference line(s) 5.

### `main:02056dfc` → `gOsExceptionHandlerPointerStorage`

Previous label `data_02056dfc`; existing ELF size **36 bytes**. Source: `eu/src/data/bss/Bss_main_02056df0.c`.

36-byte native BSS symbol: exception-handler function word at+0; trailing 32 bytes remain outside the demonstrated pointer contract.

OSi_DisplayExContext checks the handler through its OSi_ExceptionState view, loads this same function word and calls it with (OSi_ExContext,handlerArg) while switching/restoring the native processor state around the callback.

Limits: Do not shrink this symbol to a four-byte pointer or assign its trailing 32 bytes an unsupported role. Renaming touches a verified-library native source and requires regenerated source evidence through the unchanged strict verifier; source/receipt edits are not included in this research proposal.

Pinned references:

- `eu/libs/nitro/os/asm_stubs/calls/OSi_DisplayExContext.c` → `src/arm9/library_nitro_os/OSi_DisplayExContext_02003e28.c`; reference line(s) 14, 34.
- `eu/src/data/bss/Bss_main_02056df0.c`; reference line(s) 4.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
280/282 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 348 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
