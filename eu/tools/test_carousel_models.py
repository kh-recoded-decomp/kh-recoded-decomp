"""Replay the pending carousel initializer at explicit engine-call boundaries.

The initializer and projection helper execute ARM instructions. File allocation,
model initialization, animation binding and free are modeled calls: this tests
the caller's control flow, arguments, write footprint and resource lifetime, not
the implementations of those engine services or matching-C coverage.
"""
from pathlib import Path
import struct
import sys
import unittest

from project import EXTRACT_DIR, FUNC_INDEX, MWCC_DIR, ROOT
from arm_replay_link import compile_image

sys.path.insert(0, str(ROOT.parent / 'tools/mobiclip'))
from arm_exec import Cpu, Memory


SCENE = 0x01000000
STACK = SCENE + 0xfff0
SCENE_BYTES = 0x1000
TARGET = 'func_ov087_020c6ad0'
RECORD_IDS = (9, 15, 3, 11, 1, 13, 13, 7)
INFO_IDS = (8, 14, 2, 10, 0, 12, 12, 6)
PROJECTION = (0x800, 0xddb, 0x1555, 0x1000, 0x3e8000,
              0, 0, 0, 0, 0, 0x1c000, 0, 0x1000, 0)


def locator(resource):
    # A synthetic packed resource handle. The packer's internals are outside this test.
    return 0x81000000 | resource


class EngineBoundaryCpu(Cpu):
    def __init__(self, memory, addresses, count_changes):
        super().__init__(memory)
        self.addresses = addresses
        self.boundaries = {addresses[name]: name for name in (
            'BuildSlotImageParams', 'func_0202c4a0', 'InitSharedRecordAndDispatchAlt',
            'selectJointAnimationBlend', 'NNSi_FndFreeFromDefaultHeap')}
        self.events = []
        self.allocations = {}
        self.models = {}
        self.count_changes = count_changes
        self.free_count = 0

    def step(self):
        name = self.boundaries.get(self.r[15])
        if name is None:
            return super().step()
        a, b, c, d = self.r[:4]
        result = 0xbadc0de
        if name == 'BuildSlotImageParams':
            self.events.append(('pack', a, b))
            result = locator(b)
        elif name == 'func_0202c4a0':
            result = 0x01200000 + 0x40 * len(self.allocations)
            self.allocations[result] = a
            self.events.append(('load', a, b, result))
        elif name == 'InitSharedRecordAndDispatchAlt':
            if c not in self.allocations:
                raise AssertionError('initializer received an unknown allocation')
            self.models[c] = a
            self.events.append(('initialize', a, b, c, d))
        elif name == 'selectJointAnimationBlend':
            self.events.append(('bind', a, b, c, d))
        else:
            if a not in self.models:
                raise AssertionError('free did not follow initialization')
            scale = struct.unpack('<3i', self.mem.bytes(self.models[a] + 0xb0, 12))
            self.events.append(('free', a, scale))
            del self.models[a]
            if self.free_count in self.count_changes:
                self.mem.write(SCENE + 8, 4, self.count_changes[self.free_count])
            self.free_count += 1
        # Exercise the caller's ABI obligations, including ignored loader registers.
        self.r[0:4] = [result, 0xa1a1a1a1, 0xb2b2b2b2, 0xc3c3c3c3]
        self.r[12] = 0xcccccccc
        self.n, self.z, self.c, self.v = 1, 0, 1, 1
        self.r[15] = self.r[14]
        self.steps += 1


class CarouselModelTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest('requires the local EU ROM-derived function index')
        if not (MWCC_DIR / 'dsi/1.1/mwccarm.exe').is_file():
            raise unittest.SkipTest('requires CodeWarrior dsi/1.1')
        import verify_idx
        cls.index = verify_idx._index()
        cls.addresses = verify_idx.SYM_ADDR
        cls.entry = cls.addresses[TARGET]
        cls.original = bytes.fromhex(cls.index[TARGET]['hex'])
        overlay = EXTRACT_DIR / 'arm9_overlays/ov087.bin'
        if not overlay.is_file():
            raise unittest.SkipTest('requires the original extracted ov087')
        original_overlay = overlay.read_bytes()
        code_offset = cls.entry - 0x020c4280
        if original_overlay[code_offset:code_offset + len(cls.original)] != cls.original:
            raise AssertionError('overlay and function index do not describe the same original code')
        cls.resource_bytes = original_overlay[0x020c7d1c - 0x020c4280:0x020c7d5c - 0x020c4280]
        cls.candidate = cls.compile_candidate('dsi/1.1')

    @classmethod
    def compile_candidate(cls, compiler):
        return compile_image(ROOT / 'src/nonmatching/LoadCarouselModels.c',
                             'LoadCarouselModels', TARGET, compiler, cls.index, cls.addresses)

    def cpu(self, code, count, changes):
        memory = Memory()
        memory.map(self.entry, code)
        memory.map(self.addresses['data_ov087_020c7d1c'], self.resource_bytes)
        helper = self.index['LoadDefaultProjectionValues']
        self.assertEqual(helper['mode'], 'arm')
        self.assertEqual(helper['relocs'], [])
        memory.map(self.addresses['LoadDefaultProjectionValues'], bytes.fromhex(helper['hex']))
        memory.map(SCENE, bytes([0xa5]) * 0x10000)
        memory.write(SCENE + 8, 4, count)
        return EngineBoundaryCpu(memory, self.addresses, changes)

    @staticmethod
    def expected(count, locked_id, changes):
        memory = bytearray([0xa5] * SCENE_BYTES)
        struct.pack_into('<i', memory, 8, count)
        struct.pack_into('<14I', memory, 0x958, *PROJECTION)
        events = []
        ordinal = 0

        def initialize(model, info_id, record_id, scale):
            nonlocal count, ordinal
            token = 0x01200000 + 0x40 * ordinal
            events.extend((('pack', 2, info_id), ('load', locator(info_id), 14, token),
                           ('pack', 2, record_id),
                           ('initialize', SCENE + model, locator(record_id), token, 14)))
            events.extend(('bind', SCENE + model, track, SCENE + model + 0xd8, 0)
                          for track in range(5))
            struct.pack_into('<3i', memory, model + 0xb0, scale, scale, scale)
            events.append(('free', token, (scale, scale, scale)))
            if ordinal in changes:
                count = changes[ordinal]
                struct.pack_into('<i', memory, 8, count)
            ordinal += 1

        initialize(0x14, 4, 5, 0x2000)
        slot = 0
        while slot < count:
            resource = locked_id if locked_id != -1 and slot == count - 1 else slot
            struct.pack_into('<i', memory, 0x118 + slot * 0x108, resource)
            initialize(0x11c + slot * 0x108, INFO_IDS[resource], RECORD_IDS[resource], 0x800)
            slot += 1
        return bytes(memory), events

    def check_image(self, image):
        cases = [(count, locked_id, {}) for count in (-2, 0, *range(1, 9))
                 for locked_id in (-1, *range(8))]
        # Calls are external: preserve the ROM's reload of a mutable scene count.
        cases += [(8, 7, {1: 1}), (1, 7, {1: 3}), (0, -1, {0: 2})]
        for count, locked_id, changes in cases:
            with self.subTest(count=count, locked_id=locked_id, changes=changes):
                cpu = self.cpu(image, count, changes)
                saved = [0x44440000 + n for n in range(8)]
                cpu.r[4:12] = saved
                cpu.call(self.entry, [SCENE, locked_id], sp=STACK, limit=20000)
                expected, events = self.expected(count, locked_id, changes)
                self.assertEqual(cpu.mem.bytes(SCENE, SCENE_BYTES), expected)
                self.assertEqual(cpu.events, events)
                self.assertEqual(cpu.models, {})
                self.assertEqual(cpu.r[4:12], saved)
                self.assertEqual(cpu.r[13], STACK)

    def test_resource_tables_match_original_overlay(self):
        self.assertEqual(struct.unpack('<16I', self.resource_bytes), RECORD_IDS + INFO_IDS)

    def test_original_and_pending_c_control_flow_and_lifetime(self):
        self.check_image(self.original)
        self.check_image(self.candidate)

    def test_gcc_reconstruction(self):
        from _run_gcc import find_compiler
        try:
            find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.check_image(self.compile_candidate('gcc/12.2.1'))

    def test_clang_reconstruction(self):
        from _run_clang import find_compiler
        try:
            find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        self.check_image(self.compile_candidate('clang/22.1.3'))


if __name__ == '__main__':
    unittest.main()
