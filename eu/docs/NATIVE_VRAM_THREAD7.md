# GX VRAM assignment fields and thread-info continuation (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

The GX assignment state comprises thirteen halfwords from LCDC through the main/sub extended palettes. Several native allocations span two neighboring fields. Renaming those allocations does not split, merge or replace the whole GXState view used by the SDK setters. The state masks record assignments; actual VRAM buffers and MMIO registers remain separate.

Thread-info similarly spans a separate first word and a twelve-byte continuation containing three pointer words. The original IRQ-switch assembly proves the pointer roles without changing the verified-library source that uses the descriptive base label.

## Inventory and evidence

### `main:02056f4a` → `gGXMainBgVramBank`

Previous label `data_02056f4a`; size **2 bytes**; source `eu/src/data/bss/Bss_main_02056f4a.c`.

2 BSS bytes at gGXState+2: the main BG VRAM bank mask.

GX_SetBankForBG stores the requested mask here, combines the old BG/LCDC masks to return released banks to LCDC, then programs the hardware bank controls. GX_DisableBankForBG passes this halfword to the common disable helper.

Limits: This is cached bank assignment state, not a BG tilemap buffer or the hardware register itself.

Pinned direct references:

- `eu/src/data/bss/Bss_main_02056f4a.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056f4c` → `gGXObjAndArm7VramBanks`

Previous label `data_02056f4c`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056f4c.c`.

4 BSS bytes at gGXState+4: main OBJ bank halfword followed by ARM7 bank halfword.

The GXVRamState native layout places obj and arm7 at offsets 4 and 6. GX_SetBankForOBJ writes obj and updates LCDC assignments; the complete GX state initializer clears all fields.

Limits: Two distinct halfwords share this native allocation. Keep both fields and their order; this rename changes no ownership or ARM7 access policy.

Pinned direct references:

- `eu/src/data/bss/Bss_main_02056f4c.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056f50` → `gGXTextureVramBank`

Previous label `data_02056f50`; size **2 bytes**; source `eu/src/data/bss/Bss_main_02056f50.c`.

2 BSS bytes at gGXState+8: texture VRAM bank mask.

GX_SetBankForTex stores the texture assignment, updates the LCDC mask and configures the requested texture banks; GX_DisableBankForTex passes this field to the shared bank-disable helper.

Limits: Keep the mask as a halfword and preserve the texture-enable side effects in the setter.

Pinned direct references:

- `eu/libs/nitro/gx/calls/GX_ResetBankForTex.c` → `src/arm9/object_factory/func_02008d24.c`; line(s) 3, 7.
- `eu/src/data/bss/Bss_main_02056f50.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056f52` → `gGXTexturePaletteAndClearImageBanks`

Previous label `data_02056f52`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056f52.c`.

4 BSS bytes at gGXState+0xa: texture-palette bank and clear-image bank halfwords.

GXVRamState and the native GX setter views place texPltt at +0xa and clearImage at +0xc. GX_SetBankForTexPltt updates the first halfword and its LCDC complement before programming banks E/F/G.

Limits: These are two independent assignments. The extended BG/OBJ palette states immediately afterward remain separate symbols and must not be folded into this four-byte object.

Pinned direct references:

- `eu/libs/nitro/gx/calls/GX_ResetBankForTexPltt.c` → `src/arm9/object_factory/func_02008d38.c`; line(s) 3, 7.
- `eu/src/data/bss/Bss_main_02056f52.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056f5a` → `gGXSubBgVramBank`

Previous label `data_02056f5a`; size **2 bytes**; source `eu/src/data/bss/Bss_main_02056f5a.c`.

2 BSS bytes at gGXState+0x12: sub-engine BG VRAM bank mask.

GX_SetBankForSubBG writes this field, updates the LCDC mask and configures the sub BG mapping. GX_DisableBankForSubBG passes the same halfword to the shared disable helper.

Limits: Main BG and sub BG masks are distinct fields; this does not describe a palette or a background resource handle.

Pinned direct references:

- `eu/src/data/bss/Bss_main_02056f5a.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056f5c` → `gGXSubObjVramBank`

Previous label `data_02056f5c`; size **2 bytes**; source `eu/src/data/bss/Bss_main_02056f5c.c`.

2 BSS bytes at gGXState+0x14: sub-engine OBJ VRAM bank mask.

GX_SetBankForSubOBJ stores this mask, updates LCDC assignment and programs the sub OBJ banks. GX_DisableBankForSubOBJ uses the same native state field.

Limits: Preserve the neighboring sub extended-palette fields and the halfword allocation size.

Pinned direct references:

- `eu/src/data/bss/Bss_main_02056f5c.c`; line(s) 3.

Base-view proof paths:

- `eu/src/calls/GX_InitGXState.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForTexPltt.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_SetBankForSubOBJ.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForTex.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubBG.c`.
- `eu/libs/nitro/gx/calls/GX_DisableBankForSubOBJ.c`.

### `main:02056b70` → `gThreadInfoPointerTail`

Previous label `data_02056b70`; size **12 bytes**; source `eu/src/data/bss/Bss_main_02056b6c.c`.

12 BSS bytes at OSi_ThreadInfo+4: current-thread pointer, thread-list pointer and thread-switch callback.

OS_LockMutex and OS_TryLockMutex read currentThread at +4. OSi_RescheduleThread reads switchCallback at +0xc. The original OS_IrqHandler_ThreadSwitch assembly traverses the list from +8, compares/updates the current pointer at +4 and calls +0xc with old/new threads.

Limits: The first native word of OSi_ThreadInfo contains two halfwords (reschedule request and IRQ depth) and remains separate. Preserve all three pointer words; no host scheduler or callback reentrancy contract is introduced.

Pinned direct references:

- `eu/src/data/bss/Bss_main_02056b6c.c`; line(s) 4.

Base-view proof paths:

- `eu/libs/nitro/os/calls/OS_LockMutex.c`.
- `eu/libs/nitro/os/calls/OS_TryLockMutex.c`.
- `eu/libs/nitro/os/calls/OSi_RescheduleThread.c`.
- `eu/src/asm_stubs/calls/OS_IrqHandler_ThreadSwitch.c`.


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
