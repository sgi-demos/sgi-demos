# Copyright, licensing, and fair use in sgi-demos

This document inventories every piece of third-party material in the sgi-demos repositories, states where each copy came from and under what terms, and assesses how the project's use of it stands under United States copyright law. It ends with the concrete changes needed to bring the repositories into a clean, defensible state.

Nothing here is legal advice. It is the project's own provenance record and reasoning, written so that a first-time reader, a rights holder, or a lawyer can see exactly what is in the repository and why the project believes each item is permitted.

Repositories covered: [sgi-demos](https://github.com/sgi-demos/sgi-demos) (this repo), [sgi-performer](https://github.com/sgi-demos/sgi-performer) (Performer Town), and the [sgi-demos.github.io](https://github.com/sgi-demos/sgi-demos.github.io) site that hosts the builds. All are public.

## 1. Summary

The project's position, in one paragraph: the demos are 1980s and 1990s Silicon Graphics marketing and sample programs whose source SGI itself shipped to every customer on the IRIS demo tape, in 4Dgifts, in the Developer Toolbox, and later on the free Linux Toolbox and oss.sgi.com. Several are under SGI's own permissive free-use license. The two that had no available source were reverse engineered from binaries. Everything that stands between that source and the screen (the IRIS GL implementation, the two rasterizers, the SDL layer, the Performer shim) is a fresh implementation or an Apache-licensed fork, and the project distributes no SGI library binaries and circumvents no technical protection. The project is noncommercial, attributes every author, and preserves every original notice.

Where the project is on firm ground:

- Four categories carry an express license or the author's permission: SGI's permissive notice (twilight, flight-1994, libgobj), SGI's Performer sample license, David Tristram's permission for Electropaint, and Apache 2.0 for the Alice 4 fork.
- Reimplementing the IRIS GL and Performer APIs is squarely within Sega v. Accolade, Sony v. Connectix, and Google v. Oracle.
- Reverse engineering gview and Electropaint from binaries produced original C, not copies of SGI object code.

Where the project is on thinner ground, roughly in descending order of exposure:

1. The full proprietary OpenGL Performer 3.0 Windows product, including core DLLs, debug symbols, the installer, and a FlexLM license file, was committed in sgi-performer. This was a complete commercial product redistributed verbatim, the one item that looked like the things Nintendo actually sues over. **Removed from the working tree on 2026-09-05** (still in git history until that is rewritten; see section 7).
2. SGI's manuals (65 MB of PDFs and 570 HTML files) were reproduced whole in this repo. Whole-work reproduction for reference is the weakest fair-use posture. **Moved to the separate sgi-docs repository on 2026-09-05**, so the code repository's standing no longer depends on them.
3. Two IRIX executables (gview for IRIX 3, flight 1.0 for the IRIS 1400) and the Ghidra databases built from them were committed. Decompilation projects that have survived Nintendo's attention never commit the original binary. **Removed on 2026-09-05**; hashes recorded in the demo READMEs.
4. The demo-tape sources (insect, jello, logo, ideas, arena, bounce, buttonfly, newave, libdemo) and the IRIS GL headers carry no license at all, or an "unpublished proprietary" notice. Their use rests on fair use, on SGI's own free distribution of them, and possibly on a pre-1989 notice defect, not on a grant. This is inherent to the project and is what section 5 is for.
5. The top-level Apache 2.0 LICENSE overclaimed. It can only cover the project's own work and the Alice 4 fork, but as written it read as covering SGI's and Tristram's code too. **Scoped on 2026-09-05** by a root NOTICE file and a License section in the README.
6. sgi-inventor carried 13 IRIX executables from the Inventor Games CD alongside their sources. Same situation as item 3; see section 4.4. **Removed on 2026-09-05.**

Items 1, 2, 3, 5, and 6 are done in the working tree and await commit. The removed files remain in git history; the decision on 2026-09-05 was not to rewrite history for now (section 7).

## 2. Who owns what

| Rights holder | What they own here | Notes |
|---|---|---|
| Hewlett Packard Enterprise (successor to Silicon Graphics, Inc.) | IRIS GL headers, all SGI-authored demos and libraries, the IRIS GL manuals, the IRIX binaries, OpenGL Performer, the Performer Town database, the SGI cube logo and the marks SGI, IRIS, IRIX, and OpenGL Performer | Silicon Graphics, Inc. entered Chapter 11 in 2009 and its assets went to Rackable Systems, which took the name Silicon Graphics International. HPE acquired that company in 2016. IRIX support ended in December 2013. HPE sells nothing that any of this material competes with. |
| David A. Tristram / Tristram Visual | Electropaint and the Panel Library, all versions | Electropaint is a registered US trademark of Tristram Visual. Tristram has granted permission for the decompilation, with conditions (see section 3.3). |
| Lawrence Kesteloot and the Alice 4 project | The original libgl software rasterizer and the test programs bench, colortest, gltest | Apache License 2.0. |
| Mark Laws (drvink), Brendan Shanks (bslabs) | The ElectroPortis decompilation tooling and non-Electropaint source files | MIT for their own files. The Electropaint-derived files carry Tristram's terms. |
| Khronos Group, ANGLE project authors (Google) | GLES2 and EGL headers, prebuilt ANGLE libraries in libs/libgles | MIT and Apache 2.0 headers, BSD-3-Clause binaries. |
| Adobe Systems and Digital Equipment Corporation | Helvetica Bold Oblique 14 BDF font | Permissive X11 font notice. |
| OpenSceneGraph authors | OSG, used by the Performer shim | OSGPL (LGPL-style with static-link exception). Not committed to the repo, cloned at build time. |
| sgi-demos contributors | The GLES2 rasterizer, the SDL event and framebuffer layers, the Performer-over-OSG shim, port harnesses, shims, tests, scripts, docs, thumbnails, and every modification to the above | Apache License 2.0. |

Two of the individual demo authors are noted because their names appear in the files: Paul Haeberli (cedit, sunflower, portlib, libdemo; 1984 to 1985) and Thant Tessman (insect, jello, logo; 1987). Both were SGI employees, so these are works made for hire owned by SGI's successor, but they are credited in the README and should stay credited.

## 3. Categories of material and the basis for using each

### 3.1 Expressly licensed by SGI

SGI released three bodies of code used here under written permissive terms.

The 1991 to 1994 permissive notice ("Permission to use, copy, modify, and distribute this software for any purpose and without fee is hereby granted, provided that the above copyright notice appear in all copies ...") is on twilight, on every file of flight-1994, and on libgobj. It is a plain MIT-style grant. Its only conditions are keeping the notice and not using SGI's name in advertising, and both are met.

The OpenGL Performer sample-code license (1993 to 1995, on perfly, libpfutil, libpfui, libpfdu, and the loaders) grants permission "to reproduce, distribute, and create derivative works" on three conditions: reproduce the notice, do not use SGI's name in publicity, and "the Source Code is not to be used, or ported or modified for use, except in conjunction with OpenGL Performer." The third condition is the sharpest license-text problem in the project, because the point of sgi-performer is to compile perfly against a reimplementation rather than against OpenGL Performer. Two things soften it. SGI put the same sources into its oss.sgi.com open-source Performer project, and the condition existed to stop the samples from being used to build a competing scene-graph product, which a preservation port of the samples is not. It is still a condition the project does not literally satisfy, and section 7 treats it as something to document rather than something to hide.

The IRIS GL headers deserve their own note. They carry SGI's 1984 "unpublished proprietary information ... may not be disclosed to third parties" legend, which SGI put on every file in /usr/include on every IRIX system it sold. The headers are declaring code: type definitions, constants, and function prototypes with no implementation. Google v. Oracle (2021) held that copying 11,500 lines of declaring code verbatim to reimplement an API on a new platform was fair use. That is exactly this use. The notice must still be retained, and it is.

### 3.2 Published by SGI without a license

Most of the demos came from the IRIS 4D demo tape, archived at bitsavers.org as sgidemos.tar.Z. SGI shipped this tape to customers with full source, with a menu system (buttonfly) for showing the demos on the showroom floor, and with .info slides explaining each one. The files carry no license and no copyright notice at all, with one exception: the flight sources carry the "unpublished proprietary" legend.

Nothing on the tape grants anyone permission to redistribute it. The project's basis for using it is fair use (section 5), reinforced by three facts specific to this material:

- SGI distributed it to the public, in source form, as marketing. It was never a trade secret in practice, whatever the flight legend says, and it has been mirrored on bitsavers for decades without objection.
- SGI later released the direct descendant of the most heavily protected item, flight, under its permissive license (flight-1994). The rights holder has already told the world it does not mind this code circulating.
- For the files with no notice at all, publication before 1 March 1989 without a copyright notice forfeited copyright under the 1976 Act unless the omission was cured within five years (17 U.S.C. §405). The demo tape was distributed to customers in the late 1980s and most of its files have no notice. Whether that distribution was a "publication" or a limited publication under license, and whether SGI ever registered these works, is unknown, so this is a possible defense and not something to rely on. It is worth a lawyer's look if the question ever becomes live.

cedit, sunflower, and portlib (Paul Haeberli, 1984 to 1985) are in the same position but are not on the tape. Their source location is not recorded in the repository and should be (section 7).

### 3.3 Author-permitted: Electropaint

Electropaint exists here in three generations, each with different terms.

The 1988 Panel Library v7 version was posted by Tristram to comp.sys.sgi and is also on the demo tape. Every file says "this software is in the public domain, it may not be resold or relicensed. Do not remove this notice." A public-domain dedication with conditions is legally a permissive license, not the public domain. The project keeps the notice and does not resell or relicense the files.

The 1989 Panel Library 9.6 version came from the IGL 0.1.8 distribution, whose author added a GPL v2-or-later header on top of Tristram's copyright line. The project's README already documents that the GPL header is IGL's addition. Because it says "or later," the file is GPL v3-compatible and can be built with the Apache 2.0 libgl without conflict. The Apache LICENSE cannot apply to it, though.

The 1994 OpenGL version was decompiled from the IRIX binary by Mark Laws with a custom decompiler, cleaned up by Brendan Shanks, and is distributed "with permission" of Tristram under the terms quoted in the file header: no selling, modifications should be shared with him, and this covers decompiled source too. The project meets the first condition (noncommercial) and should meet the second by sending Tristram Visual a link to the two ep-1994 ports and the ep-1989 script engine (section 7). The Electropaint name is used only to identify the work, which is nominative use of the trademark.

### 3.4 Reverse engineered from binaries

Two demos have no surviving source. gview was reconstructed from an IRIX 3 MIPS executable by disassembly, decompilation, and iterative rewriting into readable C; the resulting file is an original expression of the program's functionality, with the original binary and the intermediate Ghidra output kept as evidence. Electropaint 1994 was decompiled by a third party with the author's permission, as above.

Sega v. Accolade and Sony v. Connectix established that disassembling a copyrighted binary to understand how it works is fair use, and that the resulting independently written code is not infringing. Atari v. Nintendo adds a caveat that matters here: Atari lost its fair-use defense because it obtained Nintendo's source by lying to the Copyright Office. Provenance of the copy you reverse engineer matters. The gview binary came from an IRIX 3 installation tape and the flight 1.0 binary from a contributor's copy of the IRIS 1400 release, not from a leak, and the demo READMEs now say so.

The Performer core library is not reverse engineered. The sgi-performer README speculates that it could be, using the debug symbols in the Windows release. Section 7 recommends dropping that idea unless HPE agrees, because a distributable decompilation of a still-owned commercial library, without permission, is the one form of reverse engineering the case law does not protect.

### 3.5 Fresh implementations

Everything that makes the demos run on modern hardware is either project-authored or an Apache-licensed fork: the software rasterizer (Alice 4 fork), the GLES2 rasterizer, the SDL2 event and framebuffer layers, the headless Panel Library stub, the Electropaint script engine, the OpenGL-to-IRIS-GL wrapper for ep-1994, the Performer C API shim over OpenSceneGraph, all shim headers, all build files, tests, scripts, and thumbnails. None of it contains SGI implementation code. The project never had SGI's libgl or libpf source, so there is no clean-room question to answer beyond that.

### 3.6 Verbatim SGI artifacts that are not code

This is the category with the least justification per byte.

- The IRIS GL Programming Guide and Reference Manual as PDFs (65 MB) and as the HTML technical reference (570 files). SGI published these free on techpubs.sgi.com for years and they are mirrored at bitsavers and the Internet Archive. They are still copyrighted whole works, reproduced in full, for the same purpose they were written.
- The IRIX 3 gview executable, the flight 1.0 IRIS 1400 executable and its uuencoded form, and the Ghidra project databases that embed them.
- Data: the bounce object files, the gview GFO models, flight's model, terrain, texture, and sound files, the Performer Town database and textures, the .info slide files, and the SGI GFO Format PDF. Model and level data are copyrightable works (Micro Star v. FormGen, 1998). flight-1994's data is covered by the permissive license and the Town data by the Performer sample distribution; the rest is in the same fair-use position as the demo-tape source.
- The IRIS GL font 0 bitmap, dumped from a running IRIX 3 system. Bitmap typeface designs are not copyrightable in the United States (37 C.F.R. §202.1(e); the Copyright Office's 1988 policy decision on digitized typefaces), so this one is fine.

### 3.7 Third-party open source

Alice 4 (Apache 2.0), Khronos headers (MIT and Apache 2.0), ANGLE prebuilt binaries (BSD-3-Clause, which requires the license text to accompany binary redistribution and it is currently missing), the Adobe/DEC Helvetica BDF (permissive, notice retained in the BDF), and OpenSceneGraph (OSGPL, not committed). All compatible with Apache 2.0.

## 4. Inventory

Exposure ratings: none (own work or express license fully complied with), low (express license with a condition not literally met, or reverse engineered), medium (no license, relies on fair use), elevated (verbatim reproduction of a whole SGI work with a weak fair-use story).

### 4.1 Demos

| Demo | Author, year | Copy came from | Notice in files | What sgi-demos changed | Basis | Exposure |
|---|---|---|---|---|---|---|
| arena | SGI, c. 1988 | IRIS demo tape (bitsavers sgidemos.tar.Z, sgi/arena) | none | build fixes; network code excluded | fair use, §3.2 | medium |
| bench | Alice 4 project | Alice 4 triangle_benchmark, byte-identical | none (repo is Apache 2.0) | none | Apache 2.0 | none |
| bounce | SGI, c. 1988 | demo tape (sgi/bounce); Alice 4 and Developer Toolbox 4.0 copies kept in versions/ | none | build fixes | fair use, §3.2 | medium |
| buttonfly | Wade Olsen, SGI | demo tape (sgi/buttonfly); menus rewritten for the web build | none | menus, bison regeneration, build fixes | fair use, §3.2 | medium |
| cedit | Paul Haeberli, SGI, 1984 | not recorded | author line only | build fixes | fair use, §3.2 | medium |
| colortest | Alice 4 project | Alice 4, byte-identical | none | none | Apache 2.0 | none |
| ep-1988 | David Tristram, 1988 | comp.sys.sgi posting, 18 Aug 1988 (also demo tape sgi/panel) | "public domain, may not be resold or relicensed" | two preprocessor fixes, marked; headless panel stub added | author's notice, §3.3 | none |
| ep-1989 | David Tristram, 1989 | IGL 0.1.8, src/panel/D.app | Tristram copyright plus GPL v2+ header added by IGL | headless panel stub; script engine (epscript.c) built from the 1994 decompilation | author's notice, GPL, Tristram permission | low |
| ep-1994-ogl-decomp | Tristram 1994; decompiled by Laws, cleaned by Shanks | bslabs ElectroPortis fork, verbatim | Tristram permission header; MIT for non-ep files | none to ep.c; wrapper and harness added | author's permission, §3.3 | low |
| ep-1994-ogl-reversed | same | fork of the above | same | identifier renames only | author's permission, §3.3 | low |
| flight-1988 | Gary Tarolli, SGI, 1988 | demo tape (sgi/CLOVER1/flight) | "unpublished proprietary ... may not be disclosed" | 25 lines in 4 files, commented in place | fair use, §3.2; successor code released permissively | medium |
| flight-1994 | Rob Mace, SGI, 1984 to 1994 | SGI Linux Toolbox, March 2003; hills.grid and hills.t from Developer Toolbox 6.1 | SGI permissive license on every file | vintage-C fixes, loader bug fixes | express license; two data files from the proprietary-marked tree | none, low for the two data files |
| gltest | Alice 4 project | Alice 4, byte-identical | none | none | Apache 2.0 | none |
| gview | SGI, late 1980s | reconstructed from the IRIX 3 binary on an IRIX 3 installation tape; Barcelona and Sphere GFO data and .info from the same distribution | none | entire C file is new | reverse engineering, §3.4; data is fair use, §3.2 | low for code, medium for data |
| ideas | SGI, c. 1987 | demo tape (sgi/ideas) | none | build fixes | fair use, §3.2 | medium |
| insect | Thant Tessman, SGI, mid-1980s; David Ligon 1988 | demo tape (sgi/insect), restored against bitsavers in 2023 | author lines only | -fcommon workaround, build fixes | fair use, §3.2 | medium |
| jello | Thant Tessman, SGI, 1987 | demo tape (sgi/jello), restored 2023 | author line | build fixes | fair use, §3.2 | medium |
| logo | Thant Tessman, SGI, 1987 | demo tape (sgi/logo), restored 2023 | author line | build fixes | fair use, §3.2 | medium |
| newave | SGI, late 1980s | demo tape (sgi/newave) | none | build fixes | fair use, §3.2 | medium |
| sunflower | Paul Haeberli, SGI, 1984 | not recorded; not in the built DEMOS list | author line | build fixes | fair use, §3.2 | medium |
| twilight | Howard Look, SGI, 1991 | 4Dgifts-era sample | SGI permissive license | build fixes | express license | none |
| Performer Town (sgi-performer) | SGI, 1993 to 2002 | OpenGL Performer 3.0 Windows release (2002) and the oss.sgi.com CVS mirror | Performer sample license on all sources | perfly and samples compiled unmodified; pfosg shim is new | express license with the "in conjunction with OpenGL Performer" condition not literally met | low for sources and data; elevated for the win/ folder, see §4.3 |

### 4.2 Libraries, headers, and support material in this repo

| Item | Origin | Notice | Basis | Exposure |
|---|---|---|---|---|
| libs/libgl (gl.c, rasterizer.c, reference_rasterizer.c, vector.c) | Alice 4 fork, heavily extended | Alice 4 is Apache 2.0 | Apache 2.0 | none |
| libs/libgl (gles2_rasterizer.c, sdl_events.c, sdl_framebuffer.c, times.c, bdffont.c) | sgi-demos | none yet | own work | none |
| libs/libgl/irisfont0.c | IRIX 3 system font, dumped from a running machine | none | bitmap typefaces are not copyrightable | none |
| libs/libgl/helvBO14_bdf.c | X.org adobe-75dpi | Adobe/DEC permissive notice in the BDF | express license; notice should be carried into the .c | none |
| libs/libgles/include | Khronos, ANGLE | MIT, Apache 2.0, BSD | express licenses | none |
| libs/libgles/lib-* | prebuilt ANGLE binaries | LICENSE-ANGLE added 2026-09-05 | BSD-3-Clause | none |
| libs/libdemo | demo tape sgi/lib/libdemo (Haeberli, 1984) | author lines | fair use, §3.2 | medium |
| libs/portlib | demo tape libfont, librect, flyray/modlib (Haeberli, 1984 to 1985) plus others not recorded | author lines | fair use, §3.2 | medium |
| include/gl (gl.h, device.h) | SGI IRIX headers, release 2.3 | "unpublished proprietary" | declaring code, Google v. Oracle | low |
| include/demo_include | demo tape sgi/include (cv.h Kurt Akeley 1983, gobj.h SGI, port.h Haeberli) | gobj.h proprietary legend; others none | fair use, §3.2; declaring code | low to medium |
| include/shim | sgi-demos | none | own work | none |
| docs/irisgl-pdf-docs (5 PDFs, 65 MB) | SGI technical publications | SGI copyright inside | whole-work reproduction | moved to sgi-docs 2026-09-05 |
| docs/irisgl-html-docs (570 files) | SGI technical publications | SGI copyright inside | whole-work reproduction | moved to sgi-docs 2026-09-05 |
| docs/ARCHITECTURE.md, IRIS_GL_API.md, REPO.md | sgi-demos | none | own work | none |
| demos/gview/archive (IRIX 3 executable, Ghidra databases, disassembly and m2c output, man page, slides) | SGI executable and analysis derived from it | none | verbatim binary and mechanical transformations of it | whole directory moved to the sibling gview-archive repository 2026-09-05; SHA-256 of the executable in demos/gview/README.md |
| demos/gview/archive/SGI GFO Format.pdf | SGI document | unknown | whole-work reproduction | moved to sgi-docs 2026-09-05 |
| demos/flight-1988/versions/1.0-iris1400-motorola68k | SGI 1.0 executable, uuencoded, contributed via issue #4 | none | verbatim binary | removed 2026-09-05, SHA-256 in demos/flight-1988/README.md |
| bounce *.bin, gview *.gfo, flight-1994/defs, *.info slides | SGI data from the same distributions as the code | none | same basis as the code they belong to | medium (flight-1994: none) |
| media/*.png | screenshots taken by the project | none | own work depicting SGI works; identification | none |
| patches, tests, scripts, makefiles | sgi-demos | none | own work | none |

### 4.3 sgi-performer

| Item | Origin | Basis | Exposure |
|---|---|---|---|
| web/vendor/Performer (headers, samples, utility libs, loaders) | Performer 3.0 Windows release, verbatim | Performer sample license, condition (2) not literally met | low |
| web/data/town | Performer 3.0 sample data | shipped as open sample data; Performer FAQ confirms | low |
| web/src/pfosg, loaders, compat | sgi-demos | own work | none |
| oss.sgi.com | mirror of SGI's open-source Performer CVS | SGI published it as open source | none |
| win/OpenGLPerformer300 and the installer OpenGLPerformer300.exe (117 MB: libpf.dll, libpfdu-util.dll, debug builds and PDBs, all executables, license.dat) | complete proprietary product | none | removed from the working tree 2026-09-05; remains in git history. Nothing in the port depended on it. The README sentence about recovering core-library source from the debug symbols was replaced. |

### 4.4 sgi-inventor

Surveyed 2026-09-05. The repository is an archive of Open Inventor source trees plus the project's own SDL2/GLES2 port, and one SGI CD image.

| Item | Origin | Basis | Exposure |
|---|---|---|---|
| oss.sgi.com (SGI's Open Inventor 2.1 release, 2000) | archive.org mirror of the oss.sgi.com CVS | LGPL 2.1, released by SGI | none |
| oss.sgi.com/libFL/src/libFL_i386.a | prebuilt SGI font library binary, shipped by SGI inside that LGPL release | SGI's own distribution | none |
| aumuell/open-inventor | GitHub | LGPL 2.1 | none |
| mevislab (Inventor 2.6.6 extracted from the MeVisLab SDK) | MeVisLab SDK download | LGPL 2.1 (MeVis's fork of SGI's LGPL tree keeps the license; the SDK around it is proprietary but is not included) | none |
| coin3d/coin | GitHub | BSD-3-Clause (Kongsberg) | none |
| inventor-sdl2-gles2 (the port) | sgi-demos | LGPL 2.1, as a derivative of SGI's tree; build directories are untracked | none |
| inventor-games-cd/Sources (DROP, HOHOHO, MAZE, PBN, PUCK, SLOTCAR, SpaceCadet, linkatron; 7 MB) | SGI's published Inventor Games CD, 1994 | most files carry SGI's 1994 "UNPUBLISHED PROPRIETARY SOURCE CODE" legend, yet SGI put the sources on the CD it distributed. Same position as flight-1988: fair use, §3.2, reinforced by SGI's own distribution | medium |
| inventor-games-cd/Games (models, sounds, puzzles, help; 22 MB) | same CD | data shipped with the sources | medium |
| inventor-games-cd/Games, the 13 stripped IRIX MIPS executables (the eight games, PBNSOLVE, and four Movieola binaries) | same CD | verbatim SGI binaries, same situation as the gview and flight 1.0 executables | removed 2026-09-05, hashes in inventor-games-cd/README.md |
| inventor-games-cd/RUNME and the Showcase tour | same CD | trivial | low |

Done 2026-09-05: the 13 executables were removed (kept offline), inventor-games-cd/README.md records their hashes and states that the LGPL COPYING files elsewhere in the repository do not cover the Games CD. The files came from SGI's published Inventor Games CD. The games are the future Slotcars and Maze ports, and a port needs only the Sources tree.

## 5. Fair use analysis for the unlicensed material

17 U.S.C. §107 lists four factors. Applied to the demo-tape sources, the headers, and the data files:

**Purpose and character.** Noncommercial, educational, and preservationist. Nothing is sold and no advertising is served. The use is partly transformative: the demos are recontextualized as historical artifacts, wrapped in an emulation layer, documented, and made runnable on hardware that did not exist when they were written. After Andy Warhol Foundation v. Goldsmith (2023), courts ask whether the specific use shares the purpose of the original. SGI's purpose was to sell workstations by showing off their graphics; the project's purpose is to let people see and study what those workstations did. The audience and function are different even though the pixels are the same. This factor favors the project but not overwhelmingly, because running a demo is still running a demo.

**Nature of the work.** Computer programs are functional works and get thinner protection than novels or films (Computer Associates v. Altai; Sega). Demo programs written to exercise a graphics API are at the functional end of that range. Published, not unpublished, in the practical sense, whatever the legend on flight.c says. Favors the project.

**Amount used.** Entire programs, which usually cuts against fair use. The counterweight is that copying the whole is necessary for the purpose; you cannot preserve or run half a demo. Authors Guild v. Google (2015) and v. HathiTrust (2014) accepted whole-work copying where the purpose required it. Neutral to slightly against.

**Market effect.** There is no market. IRIX has been unsupported since 2013, the demos were never sold separately, HPE licenses none of this, and the source has been freely mirrored for decades. This is the factor that decides most software-preservation questions and it favors the project strongly. Hachette v. Internet Archive (2d Cir. 2024) is the caution: wholesale copying lost there because the books were in print and licensed. Nothing here is.

On balance the demo-tape material is a good fair-use case. The manuals and the IRIX binaries are a worse one because the third factor has no necessity argument (the project does not need them to run) and the first factor is weaker (the manuals are reproduced for exactly their original purpose).

## 6. US precedent, and the Nintendo acid test

### 6.1 The cases the project stands on

- **Sega Enterprises v. Accolade**, 977 F.2d 1510 (9th Cir. 1992). Disassembling Sega's code to learn the interface needed for compatibility was fair use, because functional requirements are not protected and disassembly was the only way to get at them.
- **Atari Games v. Nintendo**, 975 F.2d 832 (Fed. Cir. 1992). Reverse engineering can be fair use, but Atari lost because it got Nintendo's source from the Copyright Office under false pretenses. How you obtained the copy matters.
- **Sony Computer Entertainment v. Connectix**, 203 F.3d 596 (9th Cir. 2000). Copying the PlayStation BIOS repeatedly while building an emulator was fair use; the shipped emulator contained no Sony code. Emulators as such are legal.
- **Computer Associates v. Altai**, 982 F.2d 693 (2d Cir. 1992). The abstraction-filtration-comparison test strips out everything dictated by function, efficiency, external constraints, or the public domain before comparing. Reimplementations of an API survive this filter.
- **Lotus v. Borland**, 49 F.3d 807 (1st Cir. 1995), affirmed by an equally divided Supreme Court. A menu command hierarchy is an uncopyrightable method of operation. Function names and call sequences are on the same side of the line.
- **Google v. Oracle**, 593 U.S. 1 (2021). Verbatim copying of 11,500 lines of API declaring code to reimplement the platform elsewhere was fair use. This covers include/gl directly.
- **Campbell v. Acuff-Rose**, 510 U.S. 569 (1994) and **Andy Warhol Foundation v. Goldsmith**, 598 U.S. 508 (2023). Transformativeness is about the purpose of the specific use, and commerciality of that use counts against it. The project is noncommercial.
- **Authors Guild v. Google**, 804 F.3d 202 (2d Cir. 2015). Full-text copying of millions of in-copyright books for search was fair use. Whole-work copying is not fatal when the purpose needs it.
- **Micro Star v. FormGen**, 154 F.3d 1107 (9th Cir. 1998). Game level files are copyrightable and their unauthorized commercial distribution infringes. This is why the data files are treated as works in their own right above.
- **Hachette v. Internet Archive**, 115 F.4th 163 (2d Cir. 2024). Preservation framing does not rescue wholesale copying of works that have a live market. The distinction from this project is that nothing here has one.

The DMCA's anti-circumvention provision, 17 U.S.C. §1201, is where most modern emulation disputes are actually fought, and it does not apply here: IRIX demos, tapes, and CDs have no encryption or access control, so nothing is circumvented. The Librarian of Congress's triennial exemptions for video-game preservation (37 C.F.R. §201.40) exist because consoles do have such controls; the 2024 rulemaking renewed the exemption for libraries and archives but denied remote access, which shows how narrow the carve-out is and how fortunate it is not to need it.

Two non-defenses should be named so nobody relies on them. "Abandonware" has no legal meaning; the 1984 to 1994 SGI works are works made for hire with 95-year terms and stay in copyright until 2079 or later. And the absence of enforcement is not a license; it goes to practical risk and to the market-effect factor, not to permission.

### 6.2 What Nintendo has and has not gone after

Nintendo is the most aggressive rights holder in this space and its record is a useful acid test: projects it leaves alone for years have found the line, and projects it hits show where the line is.

Hit, and why:

- **ROM distribution sites.** LoveROMs and LoveRETRO (2018, consent judgment around 12 million dollars), RomUniverse (2021, 2.1 million dollars). Verbatim distribution of the copyrighted works themselves.
- **Yuzu** (Tropic Haze, settled March 2024 for 2.4 million dollars, project shut down) and **Ryujinx** (shut down October 2024 after Nintendo contact). The complaint was built on §1201: the emulator decrypts games with Nintendo's keys, and the project was tied to a leaked pre-release title. Nintendo then had thousands of Yuzu forks removed from GitHub. Emulation itself was not the claim; circumvention and facilitation were.
- **Dolphin on Steam** (2023). Valve asked Nintendo, Nintendo cited the Wii common key embedded in Dolphin, and Valve declined to list it. No lawsuit, and Dolphin itself continues. Again a key, not the emulator.
- **Portal 64** (January 2024). Valve asked the author to take it down because it depended on libultra, Nintendo's proprietary N64 SDK. The demake was original work; shipping the vendor's runtime library is what killed it.
- **Fan games and asset bundles.** AM2R, Pokémon Uranium, Super Mario 64 PC-port builds with the game's assets baked in, Garry's Mod workshop items (2024). Redistribution of Nintendo's own art, music, and models.
- **Palworld** (2024) is a patent suit, not copyright, and is mentioned only because it is often cited as if it were.

Left alone, for years, in public:

- **Matching decompilations**: sm64 (2019 to present), the Zelda Ocarina of Time and Majora's Mask decompilations, the pret Pokémon decompilations. They contain no assets, require the user's own ROM to build, refuse leaked source on principle, and produce original C.
- **Ports built on them**: Ship of Harkinian, 2Ship2Harkinian, sm64ex. Same rule: the user supplies the ROM, the project supplies only new code.
- **Emulators without keys**: Dolphin, mGBA, Cemu after it went open source, and the entire post-Connectix emulator ecosystem.
- **Engine reimplementations that need the original data**: ScummVM, OpenTTD, OpenRCT2, OpenMW. Fresh engine, user-supplied data.

The pattern is consistent. Nintendo acts on (1) distribution of its binaries and assets, (2) circumvention of its encryption, (3) inclusion of its proprietary SDK or runtime, and (4) commercial or leak-tainted projects. It does not act on original code that reimplements a platform or reconstructs a program, even when the reconstruction is exact.

### 6.3 How sgi-demos measures against that pattern

| Nintendo trigger | sgi-demos today |
|---|---|
| Distributing the vendor's binaries | Two obsolete IRIX executables and the full Performer 3.0 Windows product are committed. Nothing in any working demo depends on them. Removable. |
| Distributing the vendor's assets | Data files ship with the demos. Unlike a ROM, these were distributed by SGI in the clear with source, and flight-1994's and Town's are covered by license. The "bring your own data" model used by the decompilation projects is not available for demos whose whole point is the bundled scene, so this rests on fair use. |
| Circumventing encryption | None exists on any SGI medium used. Not applicable. |
| Including the vendor's proprietary SDK or runtime | The project does not ship SGI's libgl, libpf, or any IRIX library. Both are reimplemented. The only vendor SDK material is declaring code in headers, which Google v. Oracle covers. This is the exact point where Portal 64 failed and where sgi-demos is correctly positioned. |
| Commercial use | None. |
| Leaked or unreleased source | None. Every source came from media SGI sold or published, from the author, or from a public archive. |
| Vendor trademarks as branding | The organization is named sgi-demos and sibling repos display the SGI Performer and Open Inventor logos. Naming a preservation project after its subject is nominative use, but the logo images should be treated as identification, not branding, and a non-affiliation statement should be present. |

The one structural difference from the Nintendo world is that for source-distributed demos, the copyrighted work and the thing being preserved are the same file. A decompilation project can say "we ship none of Nintendo's expression"; sgi-demos cannot say that about insect.c, because insect.c is the exhibit. That is why the demo-tape material rests on fair use plus SGI's own free distribution of it, rather than on the clean separation the Nintendo projects use, and why keeping the rest of the repository clean matters: the fair-use argument for the demos should not be dragged down by manuals and binaries that no demo needs.

The other difference cuts the project's way. HPE is not Nintendo. It has no console, no game catalog, no key to protect, no product that competes with a 1988 flight simulator, and a documented history of releasing exactly this material (the Linux Toolbox in 2003, oss.sgi.com, the permissive notices) rather than defending it. Complete IRIX installation images have been on the Internet Archive and community mirrors for more than a decade without a takedown. That is not a license, but it is the best available evidence about the market-effect factor and about practical risk.

## 7. Modifications needed for a clean state

Ordered by exposure reduced per unit of work. None of these removes a working demo.

### P0: fix the license statement (documentation only)

1. **Done 2026-09-05. Scope the top-level LICENSE.** Keep Apache 2.0 for project-authored work and the Alice 4 fork, but add a NOTICE or COPYRIGHT file at the root stating that third-party material retains its own terms, listing each category from section 3 with a pointer to this document's inventory. Right now a reader of LICENSE would reasonably conclude that flight-1988 and ep-1994 are Apache-licensed, which the project has no power to grant.
2. **Add a per-demo license note.** Fifteen demo directories have no README (arena, bench, bounce, buttonfly, cedit, colortest, gltest, gview, ideas, insect, jello, logo, newave, sunflower, twilight). Each needs at minimum: author, year, where the copy came from (URL and archive filename), what notice the files carry, and what the project changed. The ep-*, flight-* READMEs already do this well and are the template.
3. **Partly done. Collect third-party license texts.** The ANGLE BSD-3-Clause license is now at libs/libgles/LICENSE-ANGLE (done 2026-09-05). Still to do: carry the Adobe/DEC font notice into helvBO14_bdf.c as a comment. Add the Alice 4 copyright line to the files forked from it.
4. **Mark modified files.** Apache 2.0 §4(b) and good practice both call for a notice in files that were changed. flight-1988 does this with "sgi-demos:" comments; extend the convention to the demo-tape files, or add a one-line MODIFICATIONS section to each demo README pointing at the git history.
5. **Done 2026-09-05 (in NOTICE and the README License section). Add a non-affiliation and takedown statement** to the top-level README: the project is not affiliated with or endorsed by HPE, SGI, or Tristram Visual; SGI, IRIS, IRIX, OpenGL Performer, and the cube logo are their owners' marks; and a contact address for rights holders. Every long-lived preservation project has one.

### P1: remove the whole-work SGI reproductions no demo needs

6. **Done 2026-09-05. Moved docs/irisgl-pdf-docs and docs/irisgl-html-docs to the separate sgi-docs repository** (73 MB, the single largest exposure in this repo), together with the GFO format PDF. docs/README.md now points there and to bitsavers and the Internet Archive. The project's own IRIS_GL_API.md stays; scripts/docs2md.sh regenerates it from a sibling sgi-docs checkout. Separating the manuals from the code means the code repository's fair-use posture no longer carries whole-work reproductions it does not need, while the manuals remain available under their own, weaker but distinct, preservation rationale. Still to decide: rewriting history to drop the blobs, since they are in every clone of sgi-demos.
7. **Done 2026-09-05.** The flight 1.0 executable was removed from demos/flight-1988/versions with its SHA-256 recorded in the README. The whole demos/gview/archive directory (executable, Ghidra databases, disassembly and m2c output, man page, slides) moved to the sibling gview-archive repository, so no binary or mechanical transformation of one remains in sgi-demos; the reconstructed gview.c stays and its README records the executable's hash. The gview binary came from an IRIX 3 installation tape (recorded in both READMEs).
8. **Done 2026-09-05. Moved the SGI GFO Format PDF** to sgi-docs; demos/gview/README.md links there.
9. **Done 2026-09-05. Removed win/ from sgi-performer** (the extracted product and the installer, 1,759 files), kept offline. The port never used it: everything it needs is in web/vendor/Performer and web/data/town. The README sentence about recovering the core library source from its debug symbols was replaced with a statement that the core libraries are not included and nothing is derived from them; a distributable decompilation of a still-owned commercial library without permission is what no case protects. Still in git history until rewritten.

### P1b: sgi-inventor

9b. **Done 2026-09-05. Removed the 13 Inventor Games CD executables** from sgi-inventor/inventor-games-cd/Games, kept the Sources tree and the data, recorded hashes and a license note in inventor-games-cd/README.md. Source: SGI's published Inventor Games CD, recorded in that README.

### P2: record provenance that is currently missing

10. **cedit and sunflower**: record where the source came from (4Dgifts, a Haeberli distribution, or the Alice 4 tree) and the archive URL.
11. **Done 2026-09-05. gview binary**: extracted from an IRIX 3 installation tape; recorded in demos/gview/README.md and gview-archive.
12. **portlib**: record the origin of the files that are not on the demo tape (ipc.c, parse.c, percent.c, redraw.c, subview.c; colormod.c, gamma.c, and getset.c duplicate the tape's libdemo).
13. **flight-1994 hills.grid and hills.t**: note in the README that these two files came from the Developer Toolbox 6.1 tree, whose sources carry the proprietary legend, while everything else is from the permissively licensed Linux Toolbox. Check whether the Linux Toolbox tarball on the Internet Archive actually lacks them; if a permissively licensed copy exists, swap it in.
14. **Add archive hashes.** For each imported tree, the demo README should state the archive filename, URL, and SHA-256 of the source archive, so anyone can verify "byte-identical to the archive" claims.

### P3: satisfy the conditions in the express licenses

15. **Electropaint**: send Tristram Visual (info@tristram.com) a link to ep-1988, ep-1989, and the two ep-1994 ports, which satisfies his "share the modified source with me" condition and is basic courtesy to a living author whose work is the project's most famous demo. Record the date sent in the ep-1994 README.
16. **Performer**: state plainly in the sgi-performer README that the sample sources are used with a reimplementation rather than with OpenGL Performer, that this does not literally meet condition (2) of SGI's sample license, and why the project believes it is within the spirit (SGI's own oss.sgi.com release, no competing product). Consider a short letter to HPE's open-source office asking for confirmation; HPE has relicensed SGI-era material before and a positive answer would settle the question for good.
17. **ep-1989 GPL**: note in the NOTICE file that ep-1989's ep.c is GPL v2-or-later per IGL and is not covered by the Apache license.

### What not to change

- Do not strip any SGI, Tristram, Alice 4, Khronos, or Adobe/DEC notice, including the "unpublished proprietary" legends. Retaining them is a condition of every license involved and of Apache 2.0 §4(c), and stripping notices would look like concealment.
- Do not replace include/gl with a rewritten header to escape the legend. The declaring-code position is strong and the rewrite would gain nothing.
- Git history is not being rewritten, by decision on 2026-09-05. The removed binaries, manuals, and the Performer product remain in the public history of sgi-demos, sgi-performer, and sgi-inventor; the working trees are clean but git still serves the old files on request. A history rewrite plus force push would withdraw them at the cost of invalidating every existing clone, and can be revisited if a rights holder ever asks.
- Do not remove the data files. They are what the demos display, they were distributed by SGI in the clear with the source, and the fair-use case for them is the same as for the code.

## 8. Sources consulted

- The demo tape: bitsavers.org/bits/SGI/iris/sgidemos.tar.Z (mirror at bitsavers.trailing-edge.com), inspected 2026-09-05. Contains arena, bounce, buttonfly, ideas, insect, jello, logo, newave, lib/libdemo, lib/libfont, lib/librect, panel/ep.c, and CLOVER1/flight. Only the flight files carry a copyright notice.
- SGI Linux Toolbox, March 2003, and Developer Toolbox 6.1, per the flight-1994 README and the version catalog it cites.
- IGL 0.1.8 and the ElectroPortis fork (LICENSE.md) in the sgi-demos org.
- OpenGL Performer 3.0 for Windows (2002-12-10) and the oss.sgi.com Performer CVS mirror, per the sgi-performer READMEs.
- Alice 4: github.com/lkesteloot/alice, LICENSE (Apache 2.0).
- Statutes and regulations: 17 U.S.C. §§105, 107, 108, 405, 1201; 37 C.F.R. §§201.40, 202.1.
- Cases as cited in section 6.
