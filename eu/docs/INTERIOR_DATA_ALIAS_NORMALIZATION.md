# Interior DATA aliases represented by canonical bases and addends

Ten redundant numeric interior labels are retired through their existing
physical owners. Eighteen existing load references in five configuration files
now express the same native addresses as canonical base plus explicit addend.
The operation changes neither the allocation nor the effective address. It
assigns no new semantic name to an unproved interior field.

## Retired aliases and physical owners

| Former label | Native module/address | Existing owner and offset | Owner bytes |
|---|---|---|---:|
| `data_02053109` | main:02053109 | `pivotUtil_` + 0x1 | 36 |
| `data_0205310a` | main:0205310a | `pivotUtil_` + 0x2 | 36 |
| `data_0205310b` | main:0205310b | `pivotUtil_` + 0x3 | 36 |
| `data_ov001_0209edf4` | ov001:0209edf4 | `gHudGaugeTable` + 0x8 | 40 |
| `data_ov001_0209edf8` | ov001:0209edf8 | `gHudGaugeTable` + 0xc | 40 |
| `data_ov001_020a0303` | ov001:020a0303 | `sOv001_TraTg_020a02fc` + 0x7 | 8 |
| `data_ov001_020a0505` | ov001:020a0505 | `gModelDictionaryNameScratch` + 0x1 | 16 |
| `data_ov076_020cd404` | ov076:020cd404 | `gSlotMenuSharedState` + 0x4 | 12 |
| `data_ov077_020ca3a4` | ov077:020ca3a4 | `gItemScreenSharedState` + 0x4 | 12 |
| `data_ov104_020d3744` | ov104:020d3744 | `DSProt_BSS` + 0x4 | 32 |

`DSProt_BSS +4` has no configured relocation references and needs no relocation
adjustment. Its interior field's operational meaning remains unproved; the
metadata retirement does not name that field or allocate another object.

## Equivalent native references

For every changed record:

`old target + old addend = canonical base + new addend = original ROM word`

The new addend equals the previous addend plus the interior offset. All old
addends in this set were zero. Every full four-byte ROM word was compared
without masking or Thumb-bit normalization. Relocation origin, kind and module
selection remain unchanged; no record is added, deleted, moved or retyped.
Every unlisted record stays unchanged.

| Source configuration / from | Unchanged target module | Canonical owner + addend | Original native word |
|---|---|---|---|
| `config/arm9/relocs.txt` / `0x0201b168` | `main` | `pivotUtil_` + 0x1 | `0x02053109` |
| `config/arm9/relocs.txt` / `0x0201b16c` | `main` | `pivotUtil_` + 0x2 | `0x0205310a` |
| `config/arm9/relocs.txt` / `0x0201b170` | `main` | `pivotUtil_` + 0x3 | `0x0205310b` |
| `config/arm9/relocs.txt` / `0x0201c354` | `main` | `pivotUtil_` + 0x1 | `0x02053109` |
| `config/arm9/relocs.txt` / `0x0201c35c` | `main` | `pivotUtil_` + 0x2 | `0x0205310a` |
| `config/arm9/relocs.txt` / `0x0201c360` | `main` | `pivotUtil_` + 0x3 | `0x0205310b` |
| `config/arm9/overlays/ov001/relocs.txt` / `0x02074214` | `overlay(1)` | `gHudGaugeTable` + 0xc | `0x0209edf8` |
| `config/arm9/overlays/ov001/relocs.txt` / `0x020749b0` | `overlay(1)` | `gHudGaugeTable` + 0xc | `0x0209edf8` |
| `config/arm9/overlays/ov001/relocs.txt` / `0x02074b74` | `overlay(1)` | `gHudGaugeTable` + 0x8 | `0x0209edf4` |
| `config/arm9/overlays/ov001/relocs.txt` / `0x02074b78` | `overlay(1)` | `gHudGaugeTable` + 0xc | `0x0209edf8` |
| `config/arm9/overlays/ov001/relocs.txt` / `0x02075240` | `overlay(1)` | `gHudGaugeTable` + 0xc | `0x0209edf8` |
| `config/arm9/overlays/ov034/relocs.txt` / `0x020bfb8c` | `overlay(1)` | `sOv001_TraTg_020a02fc` + 0x7 | `0x020a0303` |
| `config/arm9/overlays/ov034/relocs.txt` / `0x020c01cc` | `overlay(1)` | `sOv001_TraTg_020a02fc` + 0x7 | `0x020a0303` |
| `config/arm9/overlays/ov034/relocs.txt` / `0x020c021c` | `overlay(1)` | `gModelDictionaryNameScratch` + 0x1 | `0x020a0505` |
| `config/arm9/overlays/ov034/relocs.txt` / `0x020c05dc` | `overlay(1)` | `sOv001_TraTg_020a02fc` + 0x7 | `0x020a0303` |
| `config/arm9/overlays/ov034/relocs.txt` / `0x020c08d4` | `overlay(1)` | `sOv001_TraTg_020a02fc` + 0x7 | `0x020a0303` |
| `config/arm9/overlays/ov076/relocs.txt` / `0x020c8298` | `overlay(76)` | `gSlotMenuSharedState` + 0x4 | `0x020cd404` |
| `config/arm9/overlays/ov077/relocs.txt` / `0x020c5a68` | `overlay(77)` | `gItemScreenSharedState` + 0x4 | `0x020ca3a4` |

The main pivot utility references use base 0x02053108 with addends 1, 2 or 3.
The HUD-gauge references use base 0x0209edec with addends 8 or 0x0c. The tra_tg
and model-name scratch references use their existing base plus 7 and 1.
The slot/item menu color pointers use their 12-byte parent state plus 4.
Pointer values and complete owner layouts remain unchanged.

## Retained ov004 ambiguity

`data_ov004_02064575` remains in the ov004 configuration with its original
`ambiguous` qualifier. It is physically offset 0x11 inside the 20-byte
`sOv004_SfSffont8Nftr_02064564` string object. Three native references retain
these exact targets and module lists:

- ov022:0x020a7244 → 0x02064575, `module:overlays(1,4)`.
- ov036:0x020ba83c → 0x02064575, `module:overlays(1,4)`.
- ov036:0x020ba910 → 0x02064575, `module:overlays(1,4)`.

The same odd value can encode the ov001 Thumb entry `ReadSessionPackedBits | 1`.
The string's physical containment does not prove that these three words select
ov004. No invocation or loader-lifetime evidence resolves the bank. Converting
them to a string base/addend would erase that unresolved interpretation.

After the 18 supported normalizations, dsd configure still required this label;
it was restored. Thus ten aliases are retired, not eleven. All three ambiguous
relocation records remain unchanged. The earlier 21-reference proposal is
superseded and is not part of the accepted change.

## Sources and validation

- [Pivot utility owner](../libs/nns/g3d/data/g3d_nsbca_pivot_table.c).
- [HUD gauge owner](../src/overlays/ov001/data/tables/gHudGaugeTable.c).
- [tra_tg string owner](../src/overlays/ov001/data/strings/Strings_ov001_020a02fc.c).
- [Model dictionary-name scratch owner](../src/overlays/ov001/data/bss/Bss_ov001_020a0500.c).
- [Slot menu state](../src/overlays/ov076/calls/SlotMenu_DrawHintText.c).
- [Item menu state](../src/overlays/ov077/calls/ItemScreen_DrawHintText.c).
- [DSProt owner](../src/overlays/ov104/DSProt-Extra.c).
- [Ambiguous ov004 string owner](../src/overlays/ov004/data/strings/Strings_ov004_02064564.c).

The combined accepted block includes the existing [active-context backing-storage name](CANONICAL_DATA_ALIAS_NORMALIZATION.md#active-field-context-storage-and-view).
All 87 affected official checks pass. All 94 complete production objects retain
allocated bytes/alignment, symbol offsets/sizes and relocation target
values/types/addends. The fresh 108-module linked gate retains every native
hash. The official verifier, compiler selection and native relocation values
are unchanged. The [92-label ledger](EU_PENDING_DATA_LABELS.md) preserves the
remaining evidence boundaries and the old identity anchors for these closures.
