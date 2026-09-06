# Copyright, licensing, and fair use

## 1. Overview

These demos are 1980s-1990s Silicon Graphics marketing and sample programs whose source SGI itself shipped to every customer on IRIS demo tapes, in GL2 OS gifts, with IRIX OS releases 3-6, in Developer Toolbox releases, and at SGI's open source site at [oss.sgi.com](https://web.archive.org/web/20090525013351/http://oss.sgi.com/projects).

Everything between that source and the screen is a fresh implementation or an Apache-licensed fork: the IRIS GL API is reimplemented on the CPU and for modern GPUs, and the Performer core library on the open-source OpenSceneGraph library.

Core values of this project:
- Attribute everyone
- Keep every notice intact
- Ship no vendor binaries or runtimes
- Perform no circumvention
- Take no money: firmly non-commercial
- Maintain a written record of where each file came from

Third-party copyrighted work used by this project:
- Carries a permissive license or the author's permission, or
- Has a strong fair-use case, as SGI shipped it to its customers with their systems
- Is used in ways settled by legal precedent, in the case of APIs reimplemented and programs reconstructed from binaries
- Has no remaining commercial value: these are 25-45 year old software demos

This document provides a detailed justification of all third-party material used in these repos under https://github.com/sgi-demos:

| Repository | Contents |
|---|---|
| [sgi-demos](https://github.com/sgi-demos/sgi-demos) | This repo: the IRIS GL demos |
| [sgi-performer](https://github.com/sgi-demos/sgi-performer) | Performer Town |
| [sgi-inventor](https://github.com/sgi-demos/sgi-inventor) | Open Inventor trees and the Inventor Games CD |
| [sgi-docs](https://github.com/sgi-demos/sgi-docs) | SGI manuals |
| [sgi-demos.github.io](https://github.com/sgi-demos/sgi-demos.github.io) | The site that hosts live demos |


On an express grant:

- SGI's permissive notice: twilight, flight-1994, libgobj
- SGI's Performer sample license: the Performer sources and Town data.
- SGI's LGPL release: Open Inventor.
- David Tristram's notices and permission: the three Electropaint generations.
- Apache 2.0: the Alice 4 fork.
- Reimplementing the IRIS GL and Performer APIs, and reconstructing gview and Electropaint from binaries, rest on settled precedent (see section 6).

On fair use:

1. The demo-tape sources, the GL2 gifts-package files, the Inventor Games CD sources, the IRIS GL headers, and the data files that go with them carry no license or an "unpublished proprietary" legend. Their use rests on fair use (see section 5), on SGI's own distribution of them, and possibly on a pre-1989 notice defect.
2. The Performer sample license permits use only "in conjunction with OpenGL Performer," which a port over a reimplementation does not literally meet (see section 3).
3. The SGI manuals in sgi-docs repo are whole-work reproductions kept for historic preservation and reference.

## 2. Who owns what

| Rights holder | What they own here | Terms |
|---|---|---|
| Hewlett Packard Enterprise (HPE), successor to SGI via Rackable Systems (2009) and HPE's 2016 acquisition | IRIS GL headers, all SGI-authored demos, libraries, and data, the manuals in sgi-docs, Performer's headers, samples, and Town database, Open Inventor and the Inventor Games CD, the SGI cube logo and the marks SGI, IRIS, IRIX, OpenGL Performer, Open Inventor | See the notice table below. IRIX support ended in 2013; HPE sells nothing this material competes with. |
| Khronos Group, ANGLE project authors (Google) | GLES2 and EGL headers, prebuilt ANGLE libraries | MIT and Apache 2.0 headers, BSD-3-Clause binaries |
| Adobe Systems and Digital Equipment Corporation | Helvetica Bold Oblique 14 BDF font | Permissive X11 font notice |
| OpenSceneGraph authors | OSG, which the Performer shim is built on | OSGPL; not committed, cloned at build time |
| Brad Grantham and Lawrence Kesteloot (Alice 4 project) | The original libgl software rasterizer | Apache License 2.0 |
| Martin Aumüller | The aumuell Open Inventor tree, which sgi-inventor repo derives from | LGPL 2.1 |
| David A. Tristram / Tristram Visual | Electropaint and the Panel Library, all versions | Author's notices and permission, with conditions (see section 3). Electropaint is a registered trademark. |
| Mark Laws (drvink), Brendan Shanks (bslabs) | ElectroPortis decompilation tooling and non-Electropaint files | MIT; the Electropaint-derived files carry Tristram's terms |
| sgi-demos contributors | The GLES2 rasterizer, SDL layers, Performer OSG/SDL2/GLES2 port, Inventor SDL2/GLES2 port, harnesses, shims, tests, scripts, docs, thumbnails, and every modification to the above | Apache License 2.0 (the Inventor port: LGPL 2.1) |

SGI's material by the notice it carries:

| Notice | Files |
|---|---|
| SGI permissive license (1991-1994) | twilight, flight-1994, libgobj |
| Performer sample-code license (1993-1995) | Performer headers, samples, utility libraries, loaders, Town data |
| LGPL 2.1 (2000) | Open Inventor |
| "Unpublished proprietary" legend (1984-1994) | flight-1988, the IRIS GL headers, gobj.h, the gifts package's Notice file, most Inventor Games CD sources |
| No notice | the demo tape sources and data, the gifts package files, the GFO models, the IRIS GL font, the .info slides |

Wherever the individual programmers behind SGI demos can be identified, the [README](../README.md) and the demo READMEs credit them. Most were SGI employees, so their work and its copyright belongs to SGI's successor HPE; attribution is kept for historical record.

## 3. Categories of material and the basis for using each

| Category | Material | Notice or terms it carries | Basis for use | Conditions and status |
|---|---|---|---|---|
| SGI permissive license (1991-1994) | twilight, flight-1994, libgobj | "Permission to use, copy, modify, and distribute ... for any purpose and without fee" | express license | keep the notice, no use of SGI's name in advertising: met |
| SGI LGPL release (2000) | Open Inventor and the trees derived from it | LGPL 2.1 | express license | met |
| SGI Performer sample license (1993-1995) | Performer headers, samples, utility libraries, loaders, Town data | reproduce, distribute, derive, but only "in conjunction with OpenGL Performer" | express license | notice and no-advertising conditions met; the "in conjunction" condition not literally met, see note below |
| SGI demo tape (late 1980s) and GL2 gifts package (1989) | arena, bounce, buttonfly, ideas, insect, jello, logo, newave, libdemo, flight-1988; cedit, sunflower, portlib, port.h, rect.h | none on most files; "unpublished proprietary" legend on flight and on a Notice file in the gifts package | fair use (see section 5), reinforced by SGI having shipped the source to every customer | legends retained; see note below on pre-1989 notice |
| SGI IRIS GL headers | include/gl, gobj.h | "unpublished proprietary" legend | declaring code; Google v. Oracle | legend retained |
| SGI Inventor Games CD (1994) | the games' C++ sources and data | "unpublished proprietary source code" legend on most files | fair use, as for flight-1988; SGI put the sources on the CD it distributed | legends retained |
| Author-permitted: Electropaint | ep-1988 (Panel Library v7), ep-1989 (Panel Library 9.6 via IGL), ep-1994 (decompiled) | 1988: "public domain, may not be resold or relicensed"; 1989: Tristram copyright plus IGL's GPL v2-or-later header; 1994: distributed with Tristram's permission, no selling, share modifications | author's notices and permission | see note below |
| Reverse engineered | gview (reconstructed from the IRIX 3 binary); Electropaint 1994 (decompiled by drvink with permission) | none; original C | Sega, Connectix; provenance of the binaries recorded | binaries removed from the repositories, hashes in section 8 |
| Fresh implementations | libgl rasterizers, GLES2 rasterizer, SDL layers, panel stub, Electropaint script engine, ep-1994 GL wrapper, pfosg shim, Inventor bindings, shims, build files, tests, thumbnails | Apache 2.0 (Alice 4 fork and project work) | own work; contains no SGI implementation code | |
| SGI data | bounce models, GFO databases, flight terrain and sounds, Town database, Inventor game models, .info slides | none (flight-1994's and Town's are under their licenses) | copyrightable works (Micro Star v. FormGen) in the same fair-use position as the code they ship with | stay with the demos, which are nothing without them |
| SGI font | IRIS GL font 0 bitmap, dumped from a running IRIX 3 system | none | bitmap typefaces are not copyrightable in the US (37 C.F.R. §202.1(e)) | |
| X11 font | Helvetica Bold Oblique 14 (helvBO14_bdf.c, baked from the X.org adobe-75dpi BDF), used for the popup menus | Adobe Systems and Digital Equipment Corporation copyright with the permissive X11 font notice | express license | notice carried into the generated file by bake_bdf.py; no use of Adobe's or DEC's names in advertising: met |
| SGI manuals | Programming Guide, Reference Manual, Technical Reference, Porting Guide, GFO format description, in sgi-docs | SGI copyright | whole-work reproduction of freely published, widely mirrored, out-of-print manuals, for preservation | isolated in their own repository |
| Third-party open source | Alice 4, Khronos headers, ANGLE binaries, OpenSceneGraph, the aumuell Inventor tree | Apache 2.0, MIT, BSD-3-Clause, OSGPL, LGPL 2.1 | express licenses, all compatible | license texts and notices carried alongside |

Three points that need additional details:

- **The Performer condition.** sgi-performer compiles SGI's samples against the Performer API reimplemented on OpenSceneGraph, not against OpenGL Performer, which no longer runs on any current platform. The condition existed to stop the samples seeding a competing scene-graph product, SGI released the same sources through its oss.sgi.com open-source project, and this is a noncommercial port of SGI's own demos; the project believes that is within the license's spirit and says so in the sgi-performer README.
- **Tristram's terms.** The 1994 permission asks that the code not be sold and that modifications be shared with him. The project satisfies this: it's noncommercial, and the modified source is shared by being public. The 1989 file's GPL header is IGL's addition; because it says "or later" it is compatible with the Apache-licensed libgl, and NOTICE says the Apache license does not cover it.
- **The pre-1989 notice point.** Publication before 1 March 1989 without a copyright notice forfeited copyright under the 1976 Act unless cured within five years (17 U.S.C. §405). The demo tape and gifts package shipped to customers in the late 1980s and most of their files have no notice. Whether that shipment was a "publication" and whether SGI registered the works is unknown, so this is a possible defense, not one to rely on.

## 4. Inventory

### 4.1 sgi-demos: All demos

| Demo | Author, year | Copy came from | Notice | Changed | Basis |
|---|---|---|---|---|---|
| arena | SGI, c. 1988 | demo tape | none | ~230 lines, network fenced off | fair use; no license grant, SGI shipped the source |
| bounce | SGI, c. 1988 | demo tape (Alice 4 and Toolbox 4.0 copies in versions/) | none | ~170 lines, via Alice 4 | fair use; no license grant, SGI shipped the source |
| buttonfly | Wade Olsen, SGI | demo tape | none | ~60 lines, menus, bison | fair use; no license grant, SGI shipped the source |
| cedit | Paul Haeberli, SGI, 1984 | GL2-W3.6 gifts package | author line | 10 lines | fair use; no license grant, SGI installed the source on every IRIS |
| ep-1988 | David Tristram, 1988 | comp.sys.sgi posting (also demo tape) | public domain, not to be resold or relicensed | 2 preprocessor fixes; panel stub added | author's notice, conditions met |
| ep-1989 | David Tristram, 1989 | IGL 0.1.8 | Tristram copyright, IGL's GPL v2+ header | panel stub; script engine from the 1994 decompilation | author's notice and GPL; the script engine is under Tristram's 1994 permission |
| ep-1994-ogl-decomp | Tristram 1994; Laws, Shanks | bslabs ElectroPortis fork, verbatim | Tristram permission; MIT for non-ep files | none to ep.c; wrapper and harness added | author's permission, noncommercial and shared-source conditions met |
| ep-1994-ogl-reversed | same | fork of the above | same | identifier renames only | author's permission, as above |
| flight-1988 | Gary Tarolli, SGI, 1988 | demo tape | "unpublished proprietary" | 25 lines, commented in place | fair use; the legend is retained, SGI shipped the source, and SGI later released the successor code permissively |
| flight-1994 | Rob Mace, SGI, 1984-1994 | Linux Toolbox 2003; hills.grid and hills.t from Developer Toolbox 6.1 | SGI permissive license | vintage-C and loader fixes | express license; the two Toolbox data files carry no notice and rest on fair use |
| gview | SGI, late 1980s | reconstructed from the IRIX 3 binary; GFO data from the same distribution | none | entire file is new | reverse engineering, original C (Sega, Connectix); the GFO data is fair use like the tape data |
| ideas | SGI, c. 1987 | demo tape | none | ~28 lines | fair use; no license grant, SGI shipped the source |
| insect | Thant Tessman, SGI, mid-1980s; David Ligon 1988 | demo tape | author line (Ligon) | ~160 lines, extern split for wasm | fair use; no license grant, SGI shipped the source |
| jello | Thant Tessman, SGI, 1987 | demo tape | author line | 12 lines | fair use; no license grant, SGI shipped the source |
| logo | Thant Tessman, SGI, 1987 | demo tape | author line | 3 lines | fair use; no license grant, SGI shipped the source |
| newave | SGI, late 1980s | demo tape | none | 9 lines | fair use; no license grant, SGI shipped the source |
| sunflower | Paul Haeberli, SGI, 1984 | GL2-W3.6 gifts package; not built | author line | ~45 lines | fair use; no license grant, SGI installed the source on every IRIS |
| twilight | Howard Look, SGI, 1991 | SGI sample shipped with IRIX | SGI permissive license | build fixes | express license, conditions met |
| Performer Town (sgi-performer) | SGI, 1993-2002 | Performer 3.0 Windows release; oss.sgi.com | Performer sample license | samples compiled unmodified; pfosg shim new | express license; the "in conjunction with OpenGL Performer" condition not literally met (see section 3) |

### 4.2 sgi-demos: Libraries, headers, and support material

| Item | Origin | Notice | Basis |
|---|---|---|---|
| libs/libgl: gl.c, reference_rasterizer.c, vector.c, basic_types.h, rasterizer.h, vector.h | Alice 4 fork, extended | Alice 4 copyright and modification notice | Apache 2.0, conditions met |
| libs/libgl: gles2_rasterizer.c, sdl_events.c, sdl_framebuffer.c, times.c, bdffont.c | sgi-demos | | own work, Apache 2.0 |
| libs/libgl/irisfont0.c | IRIX 3 system font | | bitmap typeface, not copyrightable in the US |
| libs/libgl/helvBO14_bdf.c | X.org adobe-75dpi | Adobe/DEC notice, emitted by bake_bdf.py | express license, conditions met |
| libs/libgles | Khronos headers, prebuilt ANGLE | MIT, Apache 2.0, BSD-3-Clause (LICENSE-ANGLE) | express licenses, conditions met |
| libs/libdemo | demo tape lib/libdemo; getapixel.c from the gifts package | author lines | fair use; no license grant, SGI shipped the source |
| libs/portlib | GL2-W3.6 gifts package, byte-identical | author lines; SGI's Notice file kept | fair use; no license grant, SGI installed the source on every IRIS; not linked by any build |
| include/gl | SGI IRIX headers, release 2.3 | "unpublished proprietary" | declaring code copied to reimplement the API (Google v. Oracle); legend retained |
| include/demo_include | demo tape (cv.h, gobj.h) and gifts package (port.h, rect.h) | gobj.h legend; others none | declaring code, and fair use as for the tape source |
| include/shim, docs, patches, tests, scripts, makefiles, NOTICE, LICENSE | sgi-demos | Apache 2.0 | own work |
| bounce *.bin, gview *.gfo, flight-1994/defs, *.info slides | SGI data with the code | none | copyrightable works in the same fair-use position as the code they ship with; flight-1994's under its license |
| media/*.png | project screenshots | | own work depicting SGI works, for identification |

### 4.3 sgi-performer

| Item | Origin | Basis |
|---|---|---|
| web/vendor/Performer (headers, samples, utility libs, loaders) | Performer 3.0 Windows release, verbatim | sample license; the "in conjunction with OpenGL Performer" condition not literally met (see section 3) |
| web/data/town | Performer 3.0 sample data | shipped by SGI as open sample data under the same license |
| web/src/pfosg, loaders, compat | sgi-demos | own work: the Performer API over OSG and SDL2, Apache 2.0 |
| oss.sgi.com | mirror of SGI's open-source Performer CVS | published by SGI as open source |

### 4.4 sgi-inventor

| Item | Origin | Basis |
|---|---|---|
| oss.sgi.com (SGI's Open Inventor release, 2000), including the prebuilt libFL | archive.org mirror of the oss.sgi.com CVS | LGPL 2.1, released by SGI |
| aumuell/open-inventor | GitHub | LGPL 2.1; the tree the port derives from |
| inventor-sdl2-gles2 (the port) | sgi-demos, from the aumuell tree | LGPL 2.1, as a derivative of SGI's tree |
| inventor-games-cd/Sources | SGI's published Inventor Games CD, 1994 | fair use as for flight-1988: "unpublished proprietary" legend on most files, retained, yet SGI shipped the sources on the CD |
| inventor-games-cd/Games (models, sounds, puzzles, help) | same CD | data shipped with the sources, same basis; the 13 executables removed, hashes in its README |

### 4.5 sgi-docs

| Contents | Basis |
|---|---|
| Five IRIS GL manuals as PDFs, the HTML Technical Reference, the GFO format PDF, with hashes and archive links in its README | whole-work reproduction of freely published, widely mirrored, out-of-print SGI manuals, for historic preservation and reference |

## 5. Fair use analysis for the unlicensed material

17 U.S.C. §107, applied to the demo-tape, gifts-package, and Games CD sources, the headers, and the data:

| Factor | Here | Leans |
|---|---|---|
| Purpose and character | Noncommercial preservation and study; the demos are recontextualized as historical artifacts and made runnable on hardware that did not exist when they were written. SGI's purpose was selling workstations. | for the project |
| Nature of the work | Functional programs, thinly protected (Altai, Sega). Published in the practical sense, whatever the legends say; unpublished status no longer bars fair use by itself (Harper & Row, as answered by the 1992 amendment to §107). | for the project |
| Amount used | Entire programs and data, because a demo cannot be preserved or run in part (Authors Guild v. Google). | neutral to slightly against |
| Market effect | None. IRIX unsupported since 2013, the demos never sold separately, nothing licensed by HPE, the source mirrored freely for decades. | strongly for the project |


## 6. US precedent

### 6.1 The cases the project stands on

| Case | Holding | Where it applies here |
|---|---|---|
| Sega v. Accolade, 977 F.2d 1510 (9th Cir. 1992) | Disassembling a program to learn its functional requirements is fair use | the gview reconstruction and the Electropaint 1994 decompilation; the second fair-use factor for software |
| Atari v. Nintendo, 975 F.2d 832 (Fed. Cir. 1992) | Reverse engineering is fair use, but not when the copy was obtained by deception | why every README records where its copy came from: an IRIX 3 installation tape, a customer's IRIS 1400 release, SGI's shipped media, never a leak |
| Sony v. Connectix, 203 F.3d 596 (9th Cir. 2000) | Intermediate copying to build an emulator that ships none of the original's code is fair use | libgl, libgles, and the pfosg shim: the emulator layer, containing no SGI implementation |
| Computer Associates v. Altai, 982 F.2d 693 (2d Cir. 1992) | Functional elements are filtered out before comparing programs | the IRIS GL and Performer API surfaces libgl and pfosg reproduce; the second fair-use factor |
| Lotus v. Borland, 49 F.3d 807 (1st Cir. 1995), aff'd 4-4 | A command hierarchy is an uncopyrightable method of operation | the same API surfaces, and the demos' keyboard and mouse bindings |
| Harper & Row v. Nation, 471 U.S. 539 (1985), and the 1992 amendment to §107 | Unpublished status weighed heavily against fair use; Congress then provided it "shall not itself bar" fair use | the "unpublished proprietary" legends on flight-1988, the headers, gobj.h, and the Inventor games: SGI shipped the files, and the legend would not decide the question |
| Google v. Oracle, 593 U.S. 1 (2021) | Verbatim copying of API declaring code to reimplement the platform elsewhere is fair use, copyrightability assumed | include/gl and the vendored Performer headers |
| Campbell v. Acuff-Rose, 510 U.S. 569 (1994); Warhol v. Goldsmith, 598 U.S. 508 (2023) | Transformativeness turns on the purpose of the specific use; commerciality counts against | the first fair-use factor: preservation and study, no sales, no advertising, no donations |
| Authors Guild v. Google, 804 F.3d 202 (2d Cir. 2015) | Whole-work copying is not fatal when the purpose needs it | the third factor: a demo cannot run in part |
| Micro Star v. FormGen, 154 F.3d 1107 (9th Cir. 1998) | Game level data is a copyrightable work | why the data files are inventoried as works and share the code's analysis |
| Hachette v. Internet Archive, 115 F.4th 163 (2d Cir. 2024) | Preservation framing does not rescue wholesale copying of works with a live market | the fourth factor and its limit; nothing here has a market; the manuals are archived separately in sgi-docs repo |

- The DMCA's anti-circumvention provision (17 U.S.C. §1201), where most emulation disputes are fought, does not apply: no SGI medium used has encryption or access control.
- These works stay in copyright until 2079 or later and this project respects that.

### 6.2 The Nintendo Test

Nintendo is the most aggressive rights holder in this space and what it acts upon is a useful test: (1) distribution of its binaries and assets, (2) circumvention of its encryption, (3) inclusion of its proprietary SDK or runtime, and (4) commercial or leak-tainted projects. It does not act on original code that reimplements a platform or reconstructs a program, even when the reconstruction is exact.

### 6.3 How sgi-demos measures against that pattern

| Nintendo test | sgi-demos |
|---|---|
| Distributing the vendor's binaries | None in any code repository; only hashes are recorded, for provenance. |
| Distributing the vendor's assets | Data ships with the demos. SGI distributed it in the clear with source; flight-1994's and Town's are licensed; the rest is fair use, because a demo without its data is not a fully preserved artifact. |
| Circumventing encryption | None exists on any SGI medium used. |
| Including the vendor's SDK or runtime | No original SGI libgl, libpf, or IRIX library implementation ships; all APIs are reimplemented. The only vendor SDK material is declaring code in headers (Google v. Oracle). |
| Commercial use | None. Projects are purely volunteer efforts to preserve history.|
| Leaked or unreleased source | None. Every source came from media SGI sold or shipped, from the author, or from a public archive. |
| Vendor trademarks as branding | Nominative use of the SGI names and logos to identify the works preserved; NOTICE and the README carry a non-affiliation statement. |

Although there is much overlap between this project and work derived from Nintendo material, two major differences are noted here:
1. For source-distributed demos, the copyrighted file is the exhibit, so this project rests instead on fair use plus SGI's own distribution, with the code repositories kept to only what the demos need.
2. HPE has no products, keys, or catalog to protect in this area and does have a record of releasing this material (Linux Toolbox 2003, oss.sgi.com, the LGPL Inventor release, the permissive notices) rather than defending it.

## 7. What will always be preserved

This project preserves every existing copyright notice and essential data file:
- Preserve all SGI, Tristram, Alice 4, Khronos, or Adobe/DEC notices, including the "unpublished proprietary" legends. Retaining them is a condition of every license involved and of Apache 2.0 §4(c).
- Preserve all essential data files. They are required for historically accurate exercising of the demos, they were distributed by SGI in the clear with the source, and the fair-use case for them is the same as for the code.

## 8. Source archives

Source archive hashes are recorded for provenance. Individual demo READMEs name their source archive and point here.

| Archive | Supplies | Where | SHA-256 |
|---|---|---|---|
| IRIS 4D demo tape, sgidemos.tar.Z | arena, bounce, buttonfly, ideas, insect, jello, logo, newave, libdemo, flight-1988 (its panel/ep.c is an earlier Panel Library than ep-1988's v7) | [bitsavers](https://bitsavers.org/bits/SGI/iris/sgidemos.tar.Z) (mirror at bitsavers.trailing-edge.com) | be028995b697d885a5b8769ab49b664bc06c6876dba5eadd5d3044eeb76caad5 |
| GL2-W3.6 release tapes for the IRIS 2400/3000 (10 May 1989), gl2-w3.6+options.tar.gz: a raw dump of the Bootstrap System and Options tapes, each a series of cpio archives | the gifts package: cedit, sunflower, portlib, getapixel.c, port.h, rect.h | [bitsavers](https://bitsavers.org/bits/SGI/iris/gl2-w3.6+options.tar.gz) | 2bbd28466cae6aeeb95ad49bee813d8298e71e6df5405c8f98ae3fbc04ddf58b |
| The "Standard System (usr)" archive on that Bootstrap System tape: the fourth cpio file of the dump, named file.20020204.05:25:55.4 by the dumper's timestamp | the archive that actually contains usr/people/gifts; verify against this file | inside the tarball above | ff9499c0b34c50fa79f50ae00f08c3760c98207091d44e07c1c308bf984ed875 |
| gview, IRIX 3 MIPS ECOFF executable, 86,128 bytes | the binary gview.c was reconstructed from | IRIX 3 installation tape | 28c149f852d10e32e695b4455f1a93214135ad0153589d7caab16257aaf74018 |
| flight 1.0, IRIS 1400 68k executable, 176,660 bytes | reference for future reconstruction | contributed via [issue #4](https://github.com/sgi-demos/sgi-demos/issues/4) | a0c5d96d634d863f072213e120f3ea64e481fa114a723594c59e3912fb9a9c49 |
| flight 1.0, uuencoded form of the above | same | same | 9aa94505373a2ce5f00a4af8bdb26217f1b324ae430857d4cf9a0d3472d4fa82 |
| comp.sys.sgi, August 1988 mbox, 1988-August.txt.gz: David Tristram's six-part "panel" shar, Message-ID 8808182120.AA25292@orville.nas.nasa.gov, 18 Aug 1988 | ep-1988: Panel Library v7 ep.c, panel.h, colormod.c, fade.c, byte-identical (the mirror munges "@" to " at " in the notices; restored in the repo copies) | [nycbug Unix Usenet archive](https://mirrors.nycbug.org/pub/The_Unix_Archive/Unix_Usenet/comp.sys.sgi/1988-August.txt.gz) | 8f646cff51b73b8dd3f040485d99e22d4b9397190701fd6332b516361f94bfe6 |
| IGL 0.1.8, src/panel/D.app | ep-1989: Panel Library 9.6 ep.c, colormod.c, fade.c, panel.h with IGL's patches, byte-identical | [sgi-demos/igl](https://github.com/sgi-demos/igl) commit 9bff300, archived from [users.volja.net/wesley/igl.html](https://web.archive.org/web/20060506001910/http://users.volja.net/wesley/igl.html) | git commit, no tarball hash |
| ElectroPortis, Brendan Shanks's fork, src/ep.c | ep-1994: the decompiled ep.c, ep.h, ep_gluperspective.h, byte-identical | [sgi-demos/electroportis-bslabs-fork](https://github.com/sgi-demos/electroportis-bslabs-fork) commit 8a8d165f28dc267491fd0bac0d2c5fae54e8587c (2018-12-03), mirroring bslabs/electroportis | git commit, no tarball hash |
| OpenGL Performer 3.0 for Windows installer, OpenGLPerformer300.exe (2002-12-10) | the Performer headers, samples, utility libraries, loaders, and Town data vendored in sgi-performer | removed from sgi-performer, kept offline | 1f9c8310c92ed8d51b1bc902f8aeea9f50deb83d15cb4277933730d422da522f |
