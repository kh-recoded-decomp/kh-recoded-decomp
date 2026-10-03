"""ROM-free checks for module identity and the reviewed gameplay knowledge."""
import json
import re
import sys
import unittest
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
import ghidra_project as gp
import compile_match as cm

class GhidraMetadataTests(unittest.TestCase):
    def test_overlay_identity_and_ambiguity_are_preserved(self):
        self.assertEqual(gp.module_targets('main'),['arm9'])
        self.assertEqual(gp.module_targets('overlay(5)'),['ov005'])
        self.assertEqual(gp.module_targets('overlays(1,4)'),['ov001','ov004'])
        with self.assertRaises(RuntimeError):gp.module_targets('overlay(unknown)')

    def test_all_reference_binaries_have_fingerprints(self):
        pins=json.loads((ROOT/'profiles/bk9e-reference-binaries.json').read_text())
        expected={'arm9/arm9.bin','arm9/itcm.bin','arm9/dtcm.bin','arm7/arm7.bin'}
        expected.update(f'arm9_overlays/ov{i:03}.bin' for i in range(105))
        self.assertEqual(set(pins),expected)
        for pin in pins.values():
            self.assertRegex(pin['sha256'],r'^[0-9a-f]{64}$')
            self.assertGreater(pin['size'],0)

    def test_knowledge_addresses_refer_to_imported_functions(self):
        seen=set()
        importer=(ROOT/'tools/ghidra/ImportBK9E.java').read_text()
        configured=re.search(r'new String\[\]\{([^}]+)\}',importer)
        self.assertIsNotNone(configured,'ImportBK9E knowledge file list is missing')
        knowledge_files=re.findall(r'"(analysis/[^\"]+\.json)"',configured.group(1))
        self.assertTrue(knowledge_files,'ImportBK9E has no reviewed knowledge files')
        exporter=(ROOT/'tools/ghidra/ExportBK9E.java').read_text()
        exported=re.search(r'new String\[\]\{([^}]+)\}',exporter)
        self.assertIsNotNone(exported,'ExportBK9E knowledge file list is missing')
        self.assertEqual(knowledge_files,re.findall(r'"(analysis/[^\"]+\.json)"',exported.group(1)))
        for relative in knowledge_files:
            path=ROOT/relative
            if not path.exists():
                continue
            knowledge=json.loads(path.read_text())
            types_path=ROOT/knowledge['types']
            self.assertTrue(types_path.is_file(),f'missing types header for {relative}: {types_path}')
            for function in knowledge['functions']:
                module=function['module'];address=int(function['address'],0)
                folder=gp.CONFIG if module=='arm9' else gp.CONFIG/module if module in ('itcm','dtcm') else gp.CONFIG/'overlays'/module
                addresses={int(m[4],16) for line in (folder/'symbols.txt').read_text().splitlines() if (m:=gp.FUNCTION.match(line))}
                self.assertIn(address,addresses)
                self.assertNotIn((module,address),seen,f'duplicate knowledge target in {relative}: {module}:{address:#x}');seen.add((module,address))
                self.assertTrue(function['evidence']);self.assertTrue(function['uncertainty'])
                self.assertIn(function['name']+'(',function['prototype'])

    def test_registered_sources_remain_self_contained_c(self):
        entries=json.loads((ROOT/'matches.json').read_text())['matches']
        for entry in entries:
            self.assertNotIn('build',entry)
            self.assertIn(entry['compiler'],cm.compiler_config()['variants'])
            cm.validate_c_source(ROOT/entry['source'])
            self.assertIn(entry['understanding'],('gameplay','subsystem','unknown'))

    def test_registered_data_sources_remain_self_contained_c(self):
        path=ROOT/'data_matches.json'
        entries=json.loads(path.read_text())['data'] if path.exists() else []
        for entry in entries:
            self.assertIn(entry['section'],('.rodata','.data','.bss'))
            self.assertIn(entry['compiler'],cm.compiler_config()['variants'])
            self.assertLess(int(entry['start'],16),int(entry['end'],16))
            cm.validate_c_source(ROOT/entry['source'])

if __name__=='__main__':unittest.main()
