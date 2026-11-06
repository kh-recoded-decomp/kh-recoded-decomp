# Canonical DATA aliases without new storage

Three numeric labels duplicated an already exported canonical identity at the
same native module/address. Only their duplicate configuration lines are
removed; no variable is added, renamed, resized or moved.

| Native identity | Existing C/ELF owner | Bytes |
|---|---|---:|
| main:02056ae0 | gTextTagColors | 8 |
| ov021:020b5620 | gActiveFieldButtonEntryIndex | 4 |
| ov021:020b56dc | gScriptHandlerTable | 128 |

The corresponding objects each export one allocation under the canonical name.
Native relocation targets and canonical sources already use those owners.
Source/ELF audits distinguish live undefined references from textual aliases:
twelve EU wrappers have the token data_ov021_020b5620 only on the left of a
macro that binds a shared-region symbol to gEffectResourceContainersLoaded.
Those macros refer to another EU address and remain unchanged. Equal spelling
in a shared source is not an owning-bank reference to EU 020b5620.

The remaining data_ov021_020b56c4 case is different. Its actual 12-byte BSS
allocation still uses the numeric name; gActiveFieldContext exists as a
LINKER_SYMBOL_SCAN facade and a configured alias. It still requires explicit
definition/reference normalization. This block does not bypass the renamer's
occupied-name guard or claim that fourth merge is finished.

## Active definitions

- [Text tag colors](../src/data/bss/Bss_main_02056ae0.c).
- [Field-button entry index](../src/overlays/ov021/data/bss/Bss_ov021_020b5620.c).
- [Script handler table](../src/overlays/ov021/data/bss/Bss_ov021_020b56d0.c).

The [retained-label ledger](EU_PENDING_DATA_LABELS.md) separates the 835
integrated naming assignments, these three canonical-alias closures and the
103 retained labels. Metadata aliases are not additional allocations.

## Validation

The combined naming block passes 14 official function checks, including the
canonical DATA consumers. All 21 complete production objects retain allocated
bytes/alignment, symbol offsets/sizes and relocation targets/types/addends.
The three BSS objects are included in that comparison. A fresh gate passes
108/108 native modules, with every hash unchanged. No comparator, compiler
selection, source type or storage declaration is changed by the three removals.
