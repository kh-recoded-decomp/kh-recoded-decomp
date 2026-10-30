"""Replay state 5 of the EU scene callback and its real upload helper.

Texture-size/key helpers and StepTextureUpload execute their ROM instructions.
Container lookup, VRAM allocation, VBlank waits and graphics transfers are
explicit boundaries. This tests the caller protocol, not DS rendering hardware.
"""
import itertools
import struct
import sys
import unittest

from project import EXTRACT_DIR, FUNC_INDEX, MWCC_DIR, ROOT
from thumb_replay_link import compile_thumb_image

sys.path.insert(0, str(ROOT.parent / 'tools/mobiclip'))
from arm_exec import Cpu, Memory

TARGET = 'RunSceneLoadStep'
SCENE, TEXTURE = 0x01000000, 0x01100000
FILE = SCENE + 0x8000
STACK = SCENE + 0xfff0
UPLOAD = 0x1a08
SCENE_SIZE = 0x1a40
TEX_ALLOC, PLTT_ALLOC = 0x01200000, 0x01200100
KEYS = (0x12001234, 0x34004567, 0x5600789a)
# These compiler helpers belong to other callback states. Give them explicit
# trap boundaries rather than pretending their ABI matches a ROM division call.
RUNTIME_TRAPS = {name: 0x01201000 + index * 0x100 for index, name in enumerate(
    ('__divsi3', '__modsi3', '__udivsi3', '__umodsi3'))}
REAL_HELPERS = ('NNS_G3dTexGetRequiredSize', 'NNS_G3dTex4x4GetRequiredSize',
                'NNS_G3dPlttGetRequiredSize', 'NNS_G3dTexSetTexKey', 'Obj_SetWord2C',
                'StepTextureUpload')
GRAPHICS = ('OS_WaitVBlankIntr', 'GX_BeginLoadTex', 'GX_LoadTex', 'GX_EndLoadTex',
            'GX_BeginLoadTexPltt', 'GX_LoadTexPltt', 'GX_EndLoadTexPltt')


def read(buffer, offset, size=4):
    return int.from_bytes(buffer[offset:offset + size], 'little')


def write(buffer, offset, value, size=4):
    buffer[offset:offset + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, 'little')


class TextureBoundaryCpu(Cpu):
    def __init__(self, memory, addresses, fail):
        super().__init__(memory)
        self.boundaries = {addresses[name]: name for name in GRAPHICS + ('NNS_G3dGetTex',)}
        self.boundaries.update({TEX_ALLOC: 'allocate_texture', PLTT_ALLOC: 'allocate_palette'})
        self.fail = fail
        self.events = []

    def step(self):
        if self.r[15] in RUNTIME_TRAPS.values():
            raise AssertionError('compiler arithmetic helper is outside the tested texture state')
        name = self.boundaries.get(self.r[15])
        if name is None:
            return super().step()
        if self.thumb:
            raise AssertionError('texture backend boundary must be entered in ARM state')
        a, b, c = self.r[:3]
        result = 0xbadc0de
        if name == 'NNS_G3dGetTex':
            self.events.append((name, a))
            result = TEXTURE
        elif name.startswith('allocate_'):
            self.events.append((name, a, b, c))
            result = 0 if self.fail else KEYS[2 if name == 'allocate_palette' else 1 if b else 0]
        elif name in ('GX_LoadTex', 'GX_LoadTexPltt'):
            self.events.append((name, a, b, c, self.mem.bytes(a, c)))
        else:
            self.events.append((name,))
        self.r[:4] = [result, 0xa1a1a1a1, 0xb2b2b2b2, 0xc3c3c3c3]
        self.r[12] = 0xcccccccc
        self.n, self.z, self.c, self.v = 1, 0, 1, 1
        self.thumb = bool(self.r[14] & 1)
        self.r[15] = self.r[14] & ~1
        self.steps += 1


class SceneTextureLoadTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest('requires the local EU ROM-derived function index')
        if not (MWCC_DIR / 'dsi/1.3p1/mwccarm.exe').is_file():
            raise unittest.SkipTest('requires CodeWarrior dsi/1.3p1')
        import verify_idx
        cls.index, cls.addresses = verify_idx._index(), verify_idx.SYM_ADDR
        cls.entry = cls.addresses[TARGET]
        original = bytes.fromhex(cls.index[TARGET]['hex'])
        overlay = EXTRACT_DIR / 'arm9_overlays/ov045.bin'
        if not overlay.is_file():
            raise unittest.SkipTest('requires the extracted original ov045')
        blob = overlay.read_bytes()
        offset = cls.entry - 0x020be600
        if blob[offset:offset + len(original)] != original:
            raise AssertionError('overlay and index do not describe the same original callback')
        cls.original = (cls.entry | 1, [(cls.entry, original)])
        # Current EU names for the same original relocation targets.
        aliases = {'func_02029254': 'AddRecordItem',
                   'func_ov027_020b7d78': 'InitBackgroundContainer',
                   'func_ov045_020bf3f0': 'RunResultTallyStep'}
        manifest, thumb = {}, set()
        for _, name in cls.index[TARGET]['relocs']:
            source_name = aliases.get(name, name)
            address = cls.addresses.get(source_name, verify_idx._symbol_address(name))
            if address is None:
                raise AssertionError('unresolved original reference: ' + name)
            mode = cls.index.get(source_name, cls.index.get(name, {})).get('mode')
            if mode == 'thumb':
                address |= 1
                thumb.add(source_name)
            manifest[source_name] = address
        cls.manifest, cls.thumb_functions = manifest, thumb
        cls.candidate = cls.compile_candidate('dsi/1.3p1')

    @classmethod
    def compile_candidate(cls, compiler):
        manifest = dict(cls.manifest)
        if compiler.startswith(('gcc/', 'clang/')):
            del manifest['_s32_div_f']
            runtime = RUNTIME_TRAPS if compiler.startswith('gcc/') else {
                '__udivsi3': RUNTIME_TRAPS['__udivsi3']}
            manifest.update(runtime)
        return compile_thumb_image(
            ROOT / 'src/overlays/ov045/calls/RunSceneLoadStep.c', TARGET,
            compiler, cls.entry, manifest, thumb_functions=cls.thumb_functions)

    def cpu(self, image, state, sizes, flag, fail, remaining):
        memory = Memory()
        for address, code in image[1]:
            memory.map(address, code)
        for name in REAL_HELPERS:
            memory.map(self.addresses[name], bytes.fromhex(self.index[name]['hex']))
        memory.map(SCENE, bytes([0xa5]) * 0x10000)
        texture = memory.map(TEXTURE, bytes((i * 7 + 3) & 255 for i in range(0x10000)))
        memory.map(self.addresses['data_ov045_020c08a0'], struct.pack('<I', SCENE))
        memory.map(self.addresses['sDefaultAllocTexVramFunc'], struct.pack('<III', TEX_ALLOC, 0, PLTT_ALLOC))
        memory.write(SCENE + 0x10, 2, 5)
        memory.write(SCENE + UPLOAD + 0xc, 4, TEXTURE)
        memory.write(SCENE + UPLOAD + 0x10, 4, remaining)
        memory.write(SCENE + UPLOAD + 0x14, 4, 0x888)
        memory.write(SCENE + UPLOAD + 0x18, 4, TEXTURE + 0x1000)
        memory.write(SCENE + UPLOAD + 0x20, 2, state)
        memory.write(SCENE + UPLOAD + 0x24, 4, FILE)
        for offset, size in zip((0xc, 0x1c, 0x30), sizes):
            write(texture, offset, size, 2)
        for offset, value in ((8, 0x71000111), (0x18, 0x72000222), (0x2c, 0x73000333),
                              (0x14, 0x1000), (0x24, 0x3000), (0x28, 0x5000), (0x38, 0x6000)):
            write(texture, offset, value)
        for offset, value in ((0x10, 0x40), (0x20, flag | 0x40), (0x32, 0x40)):
            write(texture, offset, value, 2)
        return TextureBoundaryCpu(memory, self.addresses, fail)

    @staticmethod
    def expected(scene_before, texture_before, fail):
        scene, texture = bytearray(scene_before), bytearray(texture_before)
        events = []

        def get(offset, size=4):
            return read(scene, UPLOAD + offset, size)

        def put(offset, value, size=4):
            write(scene, UPLOAD + offset, value, size)

        def allocate(name, size, flag, key):
            if not size:
                return 0
            events.append((name, size, flag, 0))
            return 0 if fail else key

        def upload_chunk():
            amount = min(get(0x10), 0x400)
            source, destination = get(0x18), get(0x14)
            events.extend((('OS_WaitVBlankIntr',), ('GX_BeginLoadTex',),
                           ('GX_LoadTex', source, destination, amount,
                            bytes(texture[source - TEXTURE:source - TEXTURE + amount])),
                           ('GX_EndLoadTex',)))
            put(0x14, destination + amount)
            put(0x18, source + amount)
            put(0x10, get(0x10) - amount)
            return get(0x10) == 0

        if get(0x20, 2) == 0:
            events.append(('NNS_G3dGetTex', FILE))
            normal = allocate('allocate_texture', read(texture, 0xc, 2) * 8, 0, KEYS[0])
            compressed = allocate('allocate_texture', read(texture, 0x1c, 2) * 8, 1, KEYS[1])
            palette = allocate('allocate_palette', read(texture, 0x30, 2) * 8,
                               read(texture, 0x20, 2) & 0x8000, KEYS[2])
            if normal:
                write(texture, 8, normal)
            if compressed:
                write(texture, 0x18, compressed)
            write(texture, 0x2c, palette)
            put(0x10, read(texture, 0xc, 2) * 8)
            if get(0x10):
                put(0x18, TEXTURE + read(texture, 0x14))
                put(0x14, read(texture, 8, 2) * 8)
                put(0x1c, 0)
                put(0x20, 1, 2)
            else:
                put(0x20, 2, 2)
            put(0xc, TEXTURE)
        if get(0x20, 2) == 1 and upload_chunk():
            put(0x20, 2, 2)
            write(texture, 0x10, read(texture, 0x10, 2) | 1, 2)
        if get(0x20, 2) == 2:
            put(0x10, read(texture, 0x1c, 2) * 8)
            if get(0x10):
                put(0x18, TEXTURE + read(texture, 0x24))
                put(0x14, read(texture, 0x18, 2) * 8)
                put(0x1c, 0)
            else:
                put(0x20, 5, 2)
        if get(0x20, 2) == 3 and upload_chunk():
            put(0x18, TEXTURE + read(texture, 0x28))
            address = read(texture, 0x18, 2) * 8
            put(0x14, ((address & 0x1ffff) >> 1) + 0x20000 + ((address & 0x40000) >> 2))
            put(0x10, read(texture, 0x1c, 2) * 4)
            put(0x1c, 0)
            put(0x20, 4, 2)
        if get(0x20, 2) == 4 and upload_chunk():
            put(0x20, 5, 2)
            write(texture, 0x20, read(texture, 0x20, 2) | 1, 2)
        if get(0x20, 2) == 5:
            put(0x10, read(texture, 0x30, 2) * 8)
            put(0x18, TEXTURE + read(texture, 0x38))
            put(0x14, read(texture, 0x2c, 2) * 8)
            put(0x1c, 1)
            put(0x20, 6, 2)
        if get(0x20, 2) == 6:
            source, destination, amount = get(0x18), get(0x14), get(0x10)
            events.extend((('OS_WaitVBlankIntr',), ('GX_BeginLoadTexPltt',),
                           ('GX_LoadTexPltt', source, destination, amount,
                            bytes(texture[source - TEXTURE:source - TEXTURE + amount])),
                           ('GX_EndLoadTexPltt',), ('OS_WaitVBlankIntr',)))
            put(0x20, 100, 2)
            write(texture, 0x32, read(texture, 0x32, 2) | 1, 2)
        if get(0x20, 2) == 100:
            write(scene, 0x12, 0, 2)
            write(scene, 0x10, 6, 2)
        return bytes(scene), bytes(texture), events

    def check_case(self, image, state, sizes, flag, fail, remaining):
        cpu = self.cpu(image, state, sizes, flag, fail, remaining)
        scene = cpu.mem.bytes(SCENE, SCENE_SIZE)
        texture = cpu.mem.bytes(TEXTURE, 0x10000)
        expected_scene, expected_texture, events = self.expected(scene, texture, fail)
        saved = [0x44440000 + n for n in range(8)]
        cpu.r[4:12] = saved
        # The callback has no input arguments. Vary the ignored incoming words.
        cpu.r[:4] = [0xdead0000 | state, sizes[0], flag, 0xffffffff if fail else 0]
        result = cpu.call(image[0], [], sp=STACK, limit=10000)
        self.assertEqual(result, 0)
        self.assertEqual(cpu.mem.bytes(SCENE, SCENE_SIZE), expected_scene)
        self.assertEqual(cpu.mem.bytes(TEXTURE, 0x10000), expected_texture)
        self.assertEqual(cpu.events, events)
        self.assertEqual(cpu.r[4:12], saved)
        self.assertEqual(cpu.r[13], STACK)

    def check_image(self, image):
        for sizes, flag, fail in itertools.product(
                itertools.product((0, 1, 128, 129, 256), (0, 1, 128, 129), (0, 1, 3)),
                (0, 0x8000), (False, True)):
            with self.subTest(state=0, sizes=sizes, flag=flag, fail=fail):
                self.check_case(image, 0, sizes, flag, fail, 1032)
        for state, remaining, compressed, palette in itertools.product(
                (1, 2, 3, 4, 5, 6, 100, 99), (0, 8, 1024, 1032, 2048),
                (0, 1, 128, 129), (0, 1, 3)):
            with self.subTest(state=state, remaining=remaining, compressed=compressed, palette=palette):
                self.check_case(image, state, (129, compressed, palette), 0x8000, False, remaining)

    def test_rom_and_matching_c_texture_allocation_and_upload_states(self):
        self.check_image(self.original)
        self.check_image(self.candidate)

    def test_matching_image_is_identical_to_the_rom(self):
        # This also checks the replay linker's branch state, addends and data
        # addresses against the already-linked ROM.
        self.assertEqual(self.candidate[1][0][0], self.entry)
        self.assertEqual(self.candidate[1][0][1], self.original[1][0][1])

    def test_gcc_texture_state(self):
        self.check_image(self.compile_candidate('gcc/12.2.1'))

    def test_clang_texture_state(self):
        self.check_image(self.compile_candidate('clang/22.1.3'))


if __name__ == '__main__':
    unittest.main()
