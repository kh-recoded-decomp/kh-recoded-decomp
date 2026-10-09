    /* Absolute NitroSDK archive aliases supplied by the original linker. */
    .global fsi_default_dma_no
    .equ fsi_default_dma_no, 0x02057b1c

    .global fsi_arc_rom
    .equ fsi_arc_rom, 0x02057b24

    .global fsi_rom_archive_name
    .equ fsi_rom_archive_name, 0x02055c34

    .global fsi_rom_root_path
    .equ fsi_rom_root_path, 0x02055c38

    /* This build has no authenticated overlay digest rows. */
    .section .data
    .align 2

    .global SDK_OVERLAY_DIGEST
    .global SDK_OVERLAY_DIGEST_END
    .global sOverlayDigestPadding
SDK_OVERLAY_DIGEST:
SDK_OVERLAY_DIGEST_END:
sOverlayDigestPadding:
    .space 20
