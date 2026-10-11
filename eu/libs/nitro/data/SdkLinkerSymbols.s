    /* Interior views of the reconstructed FX12 sine table at 0x02053580.
     * These aliases do not allocate storage or duplicate the table. */
    .global data_02053640
    .equ data_02053640, 0x02053640
    .global data_020536c0
    .equ data_020536c0, 0x020536c0
    .global data_02053740
    .equ data_02053740, 0x02053740
    .global data_02053780
    .equ data_02053780, 0x02053780
    .global data_02053800
    .equ data_02053800, 0x02053800
    .global data_02053900
    .equ data_02053900, 0x02053900
    .global data_02053980
    .equ data_02053980, 0x02053980
    .global data_020539c0
    .equ data_020539c0, 0x020539c0
    .global data_02053ac0
    .equ data_02053ac0, 0x02053ac0
    .global data_02053b40
    .equ data_02053b40, 0x02053b40
    .global data_02053b80
    .equ data_02053b80, 0x02053b80
    .global data_02053d80
    .equ data_02053d80, 0x02053d80

    /* Existing field views of sTexStartAddrTable[0]. */
    .global data_0205291a
    .equ data_0205291a, 0x0205291a
    .global data_0205291c
    .equ data_0205291c, 0x0205291c

    /* The standalone DMA view aliases CARDRomState.dmaReadInfo (+0x10). */
    .global sCardDmaReadInfo
    .equ sCardDmaReadInfo, 0x02057630

    /* Existing field views within typed SDK/game storage. */
    .global OSi_IsThreadInitialized
    .equ OSi_IsThreadInitialized, 0x02056b5c
    .global sTouchPanelCalibration
    .equ sTouchPanelCalibration, 0x020597a0
    .global gCameraDefaultProjection
    .equ gCameraDefaultProjection, 0x0205fe4c

    /* Zero-byte view used by SHA-1 finalization. */
    .global sSha1PaddingZeros
    .equ sSha1PaddingZeros, 0x02052af5

    /* Ambiguous overlay-address anchors within gListPortraitLayouts. They are
     * existing DSD metadata views, not separately allocated portrait storage. */
    .global data_ov101_020c2360
    .equ data_ov101_020c2360, 0x020c2360
    .global data_ov101_020c2368
    .equ data_ov101_020c2368, 0x020c2368
    .global data_ov101_020c2380
    .equ data_ov101_020c2380, 0x020c2380
    .global data_ov101_020c2b18
    .equ data_ov101_020c2b18, 0x020c2b18
    .global data_ov101_020c2cc5
    .equ data_ov101_020c2cc5, 0x020c2cc5
    .global data_ov101_020c2d41
    .equ data_ov101_020c2d41, 0x020c2d41
    .global data_ov101_020c322d
    .equ data_ov101_020c322d, 0x020c322d
    .global data_ov101_020c3275
    .equ data_ov101_020c3275, 0x020c3275
    .global data_ov101_020c3500
    .equ data_ov101_020c3500, 0x020c3500
    .global data_ov101_020c4014
    .equ data_ov101_020c4014, 0x020c4014
    .global data_ov101_020c4160
    .equ data_ov101_020c4160, 0x020c4160
    .global data_ov101_020c4c60
    .equ data_ov101_020c4c60, 0x020c4c60
    .global data_ov101_020c4fe0
    .equ data_ov101_020c4fe0, 0x020c4fe0

    /* Ambiguous DSD anchors inside the list-slot template arrays. */
    .global data_ov101_020c1bc8
    .equ data_ov101_020c1bc8, 0x020c1bc8
    .global data_ov101_020c1e61
    .equ data_ov101_020c1e61, 0x020c1e61
    .global data_ov101_020c1ea0
    .equ data_ov101_020c1ea0, 0x020c1ea0

    /* Absolute NitroSDK archive aliases supplied by the original linker. */
    /* Interior anchors in the wireless board's fixed-stride tables. */
    /* Ambiguous DSD anchors within the 1 KB wireless scan buffer. */
    /* Interior byte anchor in entry 231 of the group table. */
    .global data_ov001_020a0101
    .equ data_ov001_020a0101, 0x020a0101

    .global data_ov015_0207f0f9
    .equ data_ov015_0207f0f9, 0x0207f0f9
    .global data_ov015_0207f151
    .equ data_ov015_0207f151, 0x0207f151
    .global data_ov015_0207f211
    .equ data_ov015_0207f211, 0x0207f211
    .global data_ov015_0207f235
    .equ data_ov015_0207f235, 0x0207f235
    .global data_ov015_0207f26d
    .equ data_ov015_0207f26d, 0x0207f26d

    .global gWirelessThemes
    .equ gWirelessThemes, 0x0207a312
    .global data_ov015_0207a313
    .equ data_ov015_0207a313, 0x0207a313
    .global data_ov015_0207a40f
    .equ data_ov015_0207a40f, 0x0207a40f

    .global data_ov101_020c1c60
    .equ data_ov101_020c1c60, 0x020c1c60

    .global fsi_default_dma_no
    .equ fsi_default_dma_no, 0x02057b1c

    .global fsi_arc_rom
    .equ fsi_arc_rom, 0x02057b24

    .global fsi_rom_archive_name
    .equ fsi_rom_archive_name, 0x02055c34

    .global fsi_rom_root_path
    .equ fsi_rom_root_path, 0x02055c38

    /* Interior field labels in the stage heap configuration records. */
    .global data_ov001_020a0378
    .equ data_ov001_020a0378, 0x020a0378
    .global data_ov001_020a037c
    .equ data_ov001_020a037c, 0x020a037c

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
