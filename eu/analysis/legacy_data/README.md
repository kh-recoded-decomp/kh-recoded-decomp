# Superseded DATA sources

This directory preserves historical generated copies that have been replaced
by active typed DATA sources. Files here are outside the compiled source tree.
Use the current module's `config/arm9/**/delinks.txt` to identify its compiled
translation unit and storage range.

| Preserved file | Active replacement | EU storage |
|---|---|---|
| [ov014/Rodata_ov014_0206f7fc.c](ov014/Rodata_ov014_0206f7fc.c) | [PanelCategoryTables.c](../../src/overlays/ov014/data/tables/PanelCategoryTables.c) | ov014 .rodata 0x0206f7fc..0x0206f860 |

The archived file is byte-for-byte unchanged. It has no EU delink entry and
was absent from the active Ninja input graph when archived. The replacement
already owns the full native span. The root-level US/shared source and its
match manifest retain their existing paths.

Further files belong here only after checking active configuration and
include dependencies, identifying their canonical replacement, and passing
the complete linked-module gate. An old object in `build/` alone does not
establish that its source still participates in the build.
