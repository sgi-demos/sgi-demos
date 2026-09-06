# Copyright, licensing, and fair use

This document inventories every piece of third-party material in the sgi-demos repositories, states where each copy came from and under what terms, and assesses how the project's use of it stands under US copyright law.

Repositories covered, all under the [sgi-demos](https://github.com/sgi-demos) organization: [sgi-demos](https://github.com/sgi-demos/sgi-demos) (this repo, the IRIS GL demos), [sgi-performer](https://github.com/sgi-demos/sgi-performer) (Performer Town), [sgi-inventor](https://github.com/sgi-demos/sgi-inventor) (Open Inventor trees and the Inventor Games CD), [sgi-docs](https://github.com/sgi-demos/sgi-docs) (SGI manuals), and [sgi-demos.github.io](https://github.com/sgi-demos/sgi-demos.github.io) (the site that hosts the builds).

## 1. Summary

These demos are 1980s-1990s Silicon Graphics marketing and sample programs whose source SGI itself shipped to every customer on the IRIS demo tape, with IRIX releases 3 through 6, in Developer Toolbox releases, and later on oss.sgi.com. Several are under SGI's own permissive free-use license. Two were reverse engineered from binaries. Everything that stands between that source and the screen is a fresh implementation or an Apache-licensed fork: the IRIS GL API is reimplemented on two rasterizers and SDL2, and the Performer core library is reimplemented on the open-source OpenSceneGraph library. The code repositories contain no SGI library or product binaries, the project circumvents no technical protection, it is noncommercial, it attributes every author, and it preserves every original notice.

Where the project stands on an express grant:

- SGI's permissive notice covers twilight, flight-1994, and libgobj. SGI's Performer sample license covers the Performer sources and Town data. SGI's LGPL release covers Open Inventor. David Tristram's notices and permission cover the three Electropaint generations. Apache 2.0 covers the Alice 4 fork.
- Reimplementing the IRIS GL and Performer APIs is squarely within settled precedent (section 6.1): disassembling a copyrighted binary to learn how it works is fair use (Sega v. Accolade, Sony v. Connectix); the functional structure of an interface, its names, signatures, and call sequences, is filtered out of copyright protection altogether (Computer Associates v. Altai, Lotus v. Borland); and copying an API's declaring code verbatim to reimplement it on a new platform is fair use even on the assumption that the declarations are copyrightable (Google v. Oracle).
- Reverse engineering gview and Electropaint from binaries produced original C, not copies of SGI object code.

Where the project stands on fair use rather than a grant:

1. The demo-tape sources (arena, bounce, buttonfly, ideas, insect, jello, logo, newave, libdemo, flight-1988), the GL2 gifts-package files (cedit, sunflower, portlib), the Inventor Games CD sources, the IRIS GL headers, and the data files that go with them carry either no license or an "unpublished proprietary" legend. Their use rests on fair use (section 5), on SGI's own distribution of them, and possibly on a pre-1989 notice defect. This is inherent to the project.
2. The Performer sample license permits use only "in conjunction with OpenGL Performer," a condition a port over a reimplementation does not literally meet (section 3.1).
3. The SGI manuals in sgi-docs are whole-work reproductions kept for reference. They are outside the code repositories so that the demos' fair-use case does not carry them, and they stand on their own preservation rationale (section 3.6).

## 2. Who owns what

| Rights holder | What they own here | Notes |
|---|---|---|
| Hewlett Packard Enterprise (HPE) (successor to Silicon Graphics, Inc.) | IRIS GL headers, all SGI-authored demos, libraries, and data, the IRIS GL manuals in sgi-docs, OpenGL Performer's headers, samples, and Town database, Open Inventor and the Inventor Games CD, the SGI cube logo and the marks SGI, IRIS, IRIX, OpenGL Performer, and Open Inventor | Silicon Graphics, Inc. entered Chapter 11 in 2009 and its assets went to Rackable Systems, which took the name Silicon Graphics International. HPE acquired that company in 2016. IRIX support ended in December 2013. HPE sells nothing that any of this material competes with. |
| David A. Tristram / Tristram Visual | Electropaint and the Panel Library, all versions | Electropaint is a registered US trademark of Tristram Visual. Tristram has granted permission for the decompilation, with conditions (section 3.3). |
| Lawrence Kesteloot and Brad Grantham (Alice 4 project) | The original libgl software rasterizer | Apache License 2.0. |
| Mark Laws (drvink), Brendan Shanks (bslabs) | The ElectroPortis decompilation tooling and non-Electropaint source files | MIT for their own files. The Electropaint-derived files carry Tristram's terms. |
| Khronos Group, ANGLE project authors (Google) | GLES2 and EGL headers, prebuilt ANGLE libraries in libs/libgles | MIT and Apache 2.0 headers, BSD-3-Clause binaries. |
| Adobe Systems and Digital Equipment Corporation | Helvetica Bold Oblique 14 BDF font | Permissive X11 font notice. |
| OpenSceneGraph authors | OSG, which the Performer shim is built on | OSGPL (LGPL-style with a static-link exception). Not committed; cloned at build time. |
| MeVis Medical Solutions, Kongsberg, Martin Aumüller | The MeVisLab Inventor tree, Coin, and the aumuell Inventor tree in sgi-inventor | LGPL 2.1, BSD-3-Clause, LGPL 2.1. |
| sgi-demos contributors | The GLES2 rasterizer, the SDL event and framebuffer layers, the Performer-over-OSG shim, the Inventor SDL2/GLES2 port, port harnesses, shims, tests, scripts, docs, thumbnails, and every modification to the above | Apache License 2.0 (the Inventor port: LGPL 2.1, as a derivative of SGI's tree). |

Wherever individual programmers responsible for SGI demos can be identified, this project credits them in the [README](../README.md). Most were SGI employees writing SGI products, so under US law these are works made for hire whose copyright belonged to SGI and now to its successor, not to the authors; that is why the table names HPE rather than them. Attribution is kept regardless, both because it is right and because honest attribution strengthens a preservation project's fair-use posture. David Tristram is the one author who holds his own rights, because Electropaint was his own work before and apart from SGI.

## 3. Categories of material and the basis for using each

### 3.1 Expressly licensed by SGI

SGI released four bodies of code used here under written terms.

The 1991 to 1994 permissive notice ("Permission to use, copy, modify, and distribute this software for any purpose and without fee is hereby granted, provided that the above copyright notice appear in all copies ...") is on twilight, on every file of flight-1994, and on libgobj. It is a plain MIT-style grant. Its only conditions are keeping the notice and not using SGI's name in advertising, and both are met.

Open Inventor was released by SGI in 2000 under the LGPL 2.1, and every Inventor tree in sgi-inventor (SGI's own, aumuell's, MeVis's, and the project's port) carries that license. Coin, the independent reimplementation also archived there, is BSD-3-Clause.

The OpenGL Performer sample-code license (1993 to 1995, on perfly, libpfutil, libpfui, libpfdu, and the loaders) grants permission "to reproduce, distribute, and create derivative works" on three conditions: reproduce the notice, do not use SGI's name in publicity, and "the Source Code is not to be used, or ported or modified for use, except in conjunction with OpenGL Performer." The third condition is the sharpest license-text question in the project, because sgi-performer compiles perfly against the Performer API reimplemented on OpenSceneGraph rather than against OpenGL Performer itself. Two things soften it. SGI put the same sources into its oss.sgi.com open-source Performer project, and the condition existed to stop the samples from being used to build a competing scene-graph product, which a preservation port of the samples is not. It is still a condition the project does not literally satisfy, and the sgi-performer README says so in its License section, with the reasoning above.

The IRIS GL headers deserve their own note. They carry SGI's 1984 "unpublished proprietary information ... may not be disclosed to third parties" legend, which SGI put on every file in /usr/include on every IRIX system it sold. The headers are declaring code: type definitions, constants, and function prototypes with no implementation. Google v. Oracle (2021) held that copying 11,500 lines of declaring code verbatim to reimplement an API on a new platform was fair use. That is exactly this use. The notice must still be retained, and it is.

### 3.2 Published by SGI without a license

Most of the demos came from the IRIS 4D demo tape, archived at bitsavers as sgidemos.tar.Z. SGI shipped this tape to customers with full source, with a menu system (buttonfly) for showing the demos on the showroom floor, and with .info slides explaining each one. The files carry no license and no copyright notice at all, with one exception: the flight sources carry the "unpublished proprietary" legend.

Nothing on the tape grants anyone permission to redistribute it. The project's basis for using it is fair use (section 5), reinforced by three facts specific to this material:

- SGI distributed it to the public, in source form, as marketing. It was never a trade secret in practice, whatever the flight legend says, and it has been mirrored on bitsavers for decades without objection.
- SGI later released the direct descendant of the most heavily protected item, flight, under its permissive license (flight-1994). The rights holder has already told the world it does not mind this code circulating.
- For the files with no notice at all, publication before 1 March 1989 without a copyright notice forfeited copyright under the 1976 Act unless the omission was cured within five years (17 U.S.C. §405). The demo tape was distributed to customers in the late 1980s and most of its files have no notice. Whether that distribution was a "publication" or a limited publication under license, and whether SGI ever registered these works, is unknown, so this is a possible defense and not something to rely on. It is worth a lawyer's look if the question ever becomes live.

cedit, sunflower, portlib, and the port.h and rect.h headers (Paul Haeberli, 1984 to 1985) are in the same position by a different route. They are not on the demo tape; they are part of "gifts", the source package SGI installed on every IRIS 2400/3000 in /usr/people/gifts with its GL2-W3.x system releases, the direct ancestor of the 4Dgifts directory on IRIX. The project's copies were verified against the gifts package on the GL2-W3.6 release tape (May 1989) archived at bitsavers: portlib and getapixel.c are byte-identical, cedit and sunflower differ only by the port's build fixes, and the two headers by two lines each. The package's own README tells the customer to "look at all the source in this whole tree and try to figure out how it works." The individual files carry no notice; the mextools directory has a Notice file at its root with SGI's 1986 "unpublished proprietary" legend, the same legend as on flight and the headers, and it is retained in libs/portlib.

The Inventor Games CD (1994) in sgi-inventor is the same story a few years on: SGI put the C++ sources of its Inventor games on the CD it distributed, most of them under a 1994 "unpublished proprietary source code" legend. The legend is retained, the sources are kept, and the basis is the same as for flight-1988.

### 3.3 Author-permitted: Electropaint

Electropaint exists here in three generations, each with different terms.

The 1988 Panel Library v7 version was posted by Tristram to comp.sys.sgi and is also on the demo tape. Every file says "this software is in the public domain, it may not be resold or relicensed. Do not remove this notice." A public-domain dedication with conditions is legally a permissive license, not the public domain. The project keeps the notice and does not resell or relicense the files.

The 1989 Panel Library 9.6 version came from the IGL 0.1.8 distribution, whose author added a GPL v2-or-later header on top of Tristram's copyright line. The demo's README documents that the GPL header is IGL's addition. Because it says "or later," the file is GPL v3-compatible and can be built with the Apache 2.0 libgl without conflict. The Apache LICENSE does not apply to it, and NOTICE says so.

The 1994 OpenGL version was decompiled from the IRIX binary by Mark Laws with a custom decompiler, cleaned up by Brendan Shanks, and is distributed "with permission" of Tristram under the terms quoted in the file header: no selling, modifications should be shared with him, and this covers decompiled source too. The project meets both: it is noncommercial, and the modified source is shared in the open by virtue of being a public repository, which is what the condition asks for. Telling him directly is a courtesy the project intends to extend, not a term of the permission. The Electropaint name is used only to identify the work, which is nominative use of the trademark.

### 3.4 Reverse engineered from binaries

Two demos have no surviving source. gview was reconstructed from an IRIX 3 MIPS executable by disassembly, decompilation, and iterative rewriting into readable C; the resulting file is an original expression of the program's functionality. Electropaint 1994 was decompiled by a third party with the author's permission, as above.

Sega v. Accolade and Sony v. Connectix established that disassembling a copyrighted binary to understand how it works is fair use, and that the resulting independently written code is not infringing. Atari v. Nintendo adds a caveat that matters here: Atari lost its fair-use defense because it obtained Nintendo's source by lying to the Copyright Office. Provenance of the copy you reverse engineer matters. The gview binary came from an IRIX 3 installation tape and the flight 1.0 binary from a contributor's copy of the IRIS 1400 release, not from a leak, and the demo READMEs say so.

The Performer core library is reimplemented on the open-source OpenSceneGraph library: SGI's sample programs compile unmodified against the Performer API, and the pfosg shim maps that API onto OSG.

### 3.5 Fresh implementations

Everything that makes the demos run on modern hardware is either project-authored or an Apache-licensed fork: the software rasterizer (Alice 4 fork), the GLES2 rasterizer, the SDL2 event and framebuffer layers, the headless Panel Library stub, the Electropaint script engine, the OpenGL-to-IRIS-GL wrapper for ep-1994, the Performer C API shim over OpenSceneGraph, the Inventor SDL2/GLES2 bindings, all shim headers, all build files, tests, scripts, and thumbnails. None of it contains SGI implementation code. The project never had SGI's libgl or libpf source, so there is no clean-room question to answer beyond that.

### 3.6 Verbatim SGI artifacts that are not code

- Data: the bounce object files, the gview GFO models, flight's model, terrain, texture, and sound files, the Performer Town database and textures, the Inventor games' models and sounds, and the .info slide files. Model and level data are copyrightable works (Micro Star v. FormGen, 1998). flight-1994's data is covered by the permissive license and the Town data by the Performer sample distribution; the rest is in the same fair-use position as the source it ships with. The data stays with the demos because the demos are nothing without it.
- The IRIS GL font 0 bitmap, dumped from a running IRIX 3 system. Bitmap typeface designs are not copyrightable in the United States (37 C.F.R. §202.1(e); the Copyright Office's 1988 policy decision on digitized typefaces).
- The IRIS GL Programming Guide, Reference Manual, Technical Reference, Porting Guide, and the GFO format description, in sgi-docs. SGI published these free on techpubs.sgi.com for years and they are mirrored at bitsavers and the Internet Archive. They are still copyrighted whole works reproduced in full for the purpose they were written, which is the weakest fair-use posture in the project; keeping them in a repository of their own means the demos' case does not depend on them, and the sgi-docs README states their provenance and the rationale.
- No SGI executable or product binary is in any code repository.  SHA-256 hashes of executables are kept in their relevant READMEs for provenance as a historic preservation artifact.

### 3.7 Third-party open source

Alice 4 (Apache 2.0), Khronos headers (MIT and Apache 2.0), ANGLE prebuilt binaries (BSD-3-Clause, license text at libs/libgles/LICENSE-ANGLE), the Adobe/DEC Helvetica BDF (permissive, notice retained in the BDF), OpenSceneGraph (OSGPL, not committed), and in sgi-inventor the LGPL Inventor trees and BSD Coin. All compatible with the project's licenses.

## 4. Inventory

Exposure ratings: none (own work or express license fully complied with), low (express license with a condition not literally met, or reverse engineered), medium (no license, relies on fair use), elevated (verbatim reproduction of a whole SGI work with a weak fair-use story). Every demo directory has a README with the same information in more detail, including the archive URL and SHA-256 where the copy came from an archive.

### 4.1 Demos

| Demo | Author, year | Copy came from | Notice in files | What sgi-demos changed | Basis | Exposure |
|---|---|---|---|---|---|---|
| arena | SGI, c. 1988 | IRIS demo tape (bitsavers sgidemos.tar.Z, sgi/arena) | none | about 230 lines: network code fenced off, startup text, K&R macro fixes | fair use, §3.2 | medium |
| bounce | SGI, c. 1988 | demo tape (sgi/bounce); tape, Alice 4, and Developer Toolbox 4.0 copies kept in versions/ | none | about 170 lines, largely the Alice 4 adaptation | fair use, §3.2 | medium |
| buttonfly | Wade Olsen, SGI | demo tape (sgi/buttonfly) | none | about 60 lines; menus rewritten for the web build; bison-regenerated parser | fair use, §3.2 | medium |
| cedit | Paul Haeberli, SGI, 1984 | GL2-W3.6 gifts package (bitsavers gl2-w3.6+options.tar.gz, usr/people/gifts/mextools/tools) | author line only | 10 lines of build fixes | fair use, §3.2 | medium |
| ep-1988 | David Tristram, 1988 | comp.sys.sgi posting, 18 Aug 1988 (also demo tape sgi/panel) | "public domain, may not be resold or relicensed" | two preprocessor fixes, marked; headless panel stub added | author's notice, §3.3 | none |
| ep-1989 | David Tristram, 1989 | IGL 0.1.8, src/panel/D.app | Tristram copyright plus GPL v2+ header added by IGL | headless panel stub; script engine (epscript.c) built from the 1994 decompilation | author's notice, GPL, Tristram permission | low |
| ep-1994-ogl-decomp | Tristram 1994; decompiled by Laws, cleaned by Shanks | bslabs ElectroPortis fork, verbatim | Tristram permission header; MIT for non-ep files | none to ep.c; wrapper and harness added | author's permission, §3.3 | low |
| ep-1994-ogl-reversed | same | fork of the above | same | identifier renames only | author's permission, §3.3 | low |
| flight-1988 | Gary Tarolli, SGI, 1988 | demo tape (sgi/CLOVER1/flight) | "unpublished proprietary ... may not be disclosed" | 25 lines in 4 files, commented in place | fair use, §3.2; successor code released permissively | medium |
| flight-1994 | Rob Mace, SGI, 1984 to 1994 | SGI Linux Toolbox, March 2003; hills.grid and hills.t from Developer Toolbox 6.1 | SGI permissive license on every file | vintage-C fixes, loader bug fixes | express license; two data files from the proprietary-marked tree | none, low for the two data files |
| gview | SGI, late 1980s | reconstructed from the IRIX 3 executable on an IRIX 3 installation tape; Barcelona and Sphere GFO data and .info from the same distribution | none | entire C file is new | reverse engineering, §3.4; data is fair use, §3.2 | low for code, medium for data |
| ideas | SGI, c. 1987 | demo tape (sgi/ideas) | none | about 28 lines: K&R macro fixes | fair use, §3.2 | medium |
| insect | Thant Tessman, SGI, mid-1980s; David Ligon 1988 | demo tape (sgi/insect), restored against bitsavers in 2023 | author lines only | about 160 lines: globals split into extern declarations and definitions for the wasm linker | fair use, §3.2 | medium |
| jello | Thant Tessman, SGI, 1987 | demo tape (sgi/jello), restored 2023 | author line | 12 lines of build fixes | fair use, §3.2 | medium |
| logo | Thant Tessman, SGI, 1987 | demo tape (sgi/logo), restored 2023 | author line | 3 lines | fair use, §3.2 | medium |
| newave | SGI, late 1980s | demo tape (sgi/newave) | none | 9 lines, commented in place | fair use, §3.2 | medium |
| sunflower | Paul Haeberli, SGI, 1984 | GL2-W3.6 gifts package (bitsavers gl2-w3.6+options.tar.gz, usr/people/gifts/mextools/tools); not in the built DEMOS list | author line | about 45 lines of build fixes | fair use, §3.2 | medium |
| twilight | Howard Look, SGI, 1991 | SGI sample shipped with IRIX (exact release and archive not recorded) | SGI permissive license | build fixes | express license | none |
| Performer Town (sgi-performer) | SGI, 1993 to 2002 | OpenGL Performer 3.0 Windows release (2002) and the oss.sgi.com CVS mirror | Performer sample license on all sources | perfly and samples compiled unmodified; pfosg shim over OSG is new | express license with the "in conjunction with OpenGL Performer" condition not literally met | low |

### 4.2 Libraries, headers, and support material in this repo

| Item | Origin | Notice | Basis | Exposure |
|---|---|---|---|---|
| libs/libgl (gl.c, reference_rasterizer.c, vector.c, basic_types.h, rasterizer.h, vector.h) | Alice 4 fork, heavily extended | Alice 4 copyright and modification notice at the top of each | Apache 2.0 | none |
| libs/libgl (gles2_rasterizer.c, sdl_events.c, sdl_framebuffer.c, times.c, bdffont.c) | sgi-demos | none yet | own work | none |
| libs/libgl/irisfont0.c | IRIX 3 system font, dumped from a running machine | none | bitmap typefaces are not copyrightable | none |
| libs/libgl/helvBO14_bdf.c | X.org adobe-75dpi | Adobe/DEC permissive notice, carried from the BDF into the generated .c by bake_bdf.py | express license | none |
| libs/libgles/include | Khronos, ANGLE | MIT, Apache 2.0, BSD | express licenses | none |
| libs/libgles/lib-* | prebuilt ANGLE binaries | LICENSE-ANGLE alongside | BSD-3-Clause | none |
| libs/libdemo | demo tape sgi/lib/libdemo (Haeberli, 1984), plus getapixel.c from the GL2-W3.6 gifts package; see its README | author lines | fair use, §3.2 | medium |
| libs/portlib | GL2-W3.6 gifts package (bitsavers gl2-w3.6+options.tar.gz, usr/people/gifts/mextools/portlib), byte-identical; two files also on the demo tape (Haeberli, 1984 to 1985); see its README | author lines | fair use, §3.2 | medium |
| include/gl (gl.h, device.h) | SGI IRIX headers, release 2.3 | "unpublished proprietary" | declaring code, Google v. Oracle | low |
| include/demo_include | demo tape (cv.h Kurt Akeley 1983, gobj.h SGI) and the GL2-W3.6 gifts package (port.h, rect.h, Haeberli) | gobj.h proprietary legend; others none | fair use, §3.2; declaring code | low to medium |
| include/shim | sgi-demos | none | own work | none |
| docs/ARCHITECTURE.md, IRIS_GL_API.md, REPO.md, COPYRIGHT.md | sgi-demos (IRIS_GL_API.md is generated from the Technical Reference in sgi-docs) | none | own work | none |
| bounce *.bin, gview *.gfo, flight-1994/defs, *.info slides | SGI data from the same distributions as the code | none | same basis as the code they belong to | medium (flight-1994: none) |
| media/*.png | screenshots taken by the project | none | own work depicting SGI works; identification | none |
| NOTICE, LICENSE, patches, tests, scripts, makefiles | sgi-demos | Apache 2.0 | own work | none |

### 4.3 sgi-performer

| Item | Origin | Basis | Exposure |
|---|---|---|---|
| web/vendor/Performer (headers, samples, utility libs, loaders) | Performer 3.0 Windows release, verbatim | Performer sample license, condition (2) not literally met | low |
| web/data/town | Performer 3.0 sample data | shipped as open sample data; the Performer FAQ confirms the Town databases were unencrypted sample data from 1.2 on | low |
| web/src/pfosg, loaders, compat | sgi-demos | own work: the Performer API over OpenSceneGraph and SDL2 | none |
| oss.sgi.com | mirror of SGI's open-source Performer CVS | SGI published it as open source | none |

### 4.4 sgi-inventor

| Item | Origin | Basis | Exposure |
|---|---|---|---|
| oss.sgi.com (SGI's Open Inventor 2.1 release, 2000) | archive.org mirror of the oss.sgi.com CVS | LGPL 2.1, released by SGI | none |
| oss.sgi.com/libFL/src/libFL_i386.a | prebuilt SGI font library, shipped by SGI inside that LGPL release | SGI's own distribution | none |
| aumuell/open-inventor | GitHub | LGPL 2.1 | none |
| mevislab (Inventor 2.6.6 extracted from the MeVisLab SDK) | MeVisLab SDK download | LGPL 2.1 (MeVis's fork of SGI's LGPL tree keeps the license; the proprietary SDK around it is not included) | none |
| coin3d/coin | GitHub | BSD-3-Clause (Kongsberg) | none |
| inventor-sdl2-gles2 (the port) | sgi-demos | LGPL 2.1, as a derivative of SGI's tree; build directories are untracked | none |
| inventor-games-cd/Sources (DROP, HOHOHO, MAZE, PBN, PUCK, SLOTCAR, SpaceCadet, linkatron; 7 MB) | SGI's published Inventor Games CD, 1994 | most files carry SGI's 1994 "unpublished proprietary source code" legend, yet SGI put the sources on the CD it distributed; fair use, §3.2, as for flight-1988 | medium |
| inventor-games-cd/Games (models, sounds, puzzles, help; 22 MB) | same CD | data shipped with the sources | medium |
| inventor-games-cd/RUNME and the Showcase tour | same CD | trivial | low |

inventor-games-cd/README.md records the hashes of the 13 executables that were removed and states that the LGPL COPYING files elsewhere in the repository do not cover the Games CD.

### 4.5 sgi-docs

| Repository | Contents | Basis | Exposure |
|---|---|---|---|
| sgi-docs (public) | Five SGI IRIS GL manuals as PDFs (65 MB), the HTML Technical Reference (570 files), the GFO format PDF; README with hashes and archive links | whole-work reproduction of freely published, widely mirrored, out-of-print SGI manuals, for preservation and reference | elevated, and deliberately isolated from the code |

## 5. Fair use analysis for the unlicensed material

17 U.S.C. §107 lists four factors. Applied to the demo-tape and gifts-package sources, the Games CD sources, the headers, and the data files:

**Purpose and character.** Noncommercial, educational, and preservationist. Nothing is sold and no advertising is served. The use is partly transformative: the demos are recontextualized as historical artifacts, wrapped in an emulation layer, documented, and made runnable on hardware that did not exist when they were written. After Andy Warhol Foundation v. Goldsmith (2023), courts ask whether the specific use shares the purpose of the original. SGI's purpose was to sell workstations by showing off their graphics; the project's purpose is to let people see and study what those workstations did. The audience and function are different even though the pixels are the same. This factor favors the project but not overwhelmingly, because running a demo is still running a demo.

**Nature of the work.** Computer programs are functional works and get thinner protection than novels or films (Computer Associates v. Altai; Sega). Demo programs written to exercise a graphics API are at the functional end of that range. Published, not unpublished, in the practical sense, whatever the legend on flight.c says: SGI shipped the files to customers. Even if the legend were taken at face value, unpublished status no longer bars fair use by itself (Harper & Row, as answered by the 1992 amendment to §107). Favors the project.

**Amount used.** Entire programs, which usually cuts against fair use. The counterweight is that copying the whole is necessary for the purpose; you cannot preserve or run half a demo. Authors Guild v. Google (2015) and v. HathiTrust (2014) accepted whole-work copying where the purpose required it. Neutral to slightly against.

**Market effect.** There is no market. IRIX has been unsupported since 2013, the demos were never sold separately, HPE licenses none of this, and the source has been freely mirrored for decades. This is the factor that decides most software-preservation questions and it favors the project strongly. Hachette v. Internet Archive (2d Cir. 2024) is the caution: wholesale copying lost there because the books were in print and licensed. Nothing here is.

On balance the demo material is a good fair-use case. The manuals in sgi-docs are a weaker one, because the third factor has no necessity argument (nothing needs them to run) and the first factor is weaker (they are reproduced for exactly their original purpose); that is why they are in a repository of their own.

## 6. US precedent, and the Nintendo acid test

### 6.1 The cases the project stands on

Each case is followed by the part of this project it bears on.

- **Sega Enterprises v. Accolade**, 977 F.2d 1510 (9th Cir. 1992). Disassembling Sega's code to learn the interface needed for compatibility was fair use, because functional requirements are not protected and disassembly was the only way to get at them. Here: the gview reconstruction (§3.4), which disassembled and decompiled an SGI executable to recover a program whose source no longer exists, and the drvink decompilation that produced Electropaint 1994. Sega is also the source of the second fair-use factor's treatment of software (§5): programs are functional works that get thinner protection than expressive ones, which applies to every SGI file used here.
- **Atari Games v. Nintendo**, 975 F.2d 832 (Fed. Cir. 1992). Reverse engineering can be fair use, but Atari lost because it got Nintendo's source from the Copyright Office under false pretenses. How you obtained the copy matters. Here: the provenance rules the project follows for everything it reverse engineers or imports, and the reason every README records where its copy came from (an IRIX 3 installation tape for gview, a customer's IRIS 1400 release for flight 1.0, public archives of media SGI shipped for the rest, never a leak).
- **Sony Computer Entertainment v. Connectix**, 203 F.3d 596 (9th Cir. 2000). Copying the PlayStation BIOS repeatedly while building an emulator was fair use; the shipped emulator contained no Sony code. Emulators as such are legal. Here: libgl and libgles, the IRIS GL implementation that plays the role of the emulator, and the pfosg shim for Performer; like Connectix's product, what ships contains none of SGI's implementation.
- **Computer Associates v. Altai**, 982 F.2d 693 (2d Cir. 1992). The abstraction-filtration-comparison test strips out everything dictated by function, efficiency, external constraints, or the public domain before comparing. Reimplementations of an API survive this filter. Here: the IRIS GL function names, argument conventions, device and event model, and colormap semantics that libgl reproduces, and the Performer C API that pfosg reproduces; all of it is filtered out as functional before any comparison with SGI's code would begin. Altai's view of programs as largely functional also underlies the second fair-use factor for the demo sources themselves (§5).
- **Lotus v. Borland**, 49 F.3d 807 (1st Cir. 1995), affirmed by an equally divided Supreme Court. A menu command hierarchy is an uncopyrightable method of operation. Function names and call sequences are on the same side of the line. Here: the same API surface as above, and the demos' own keyboard and mouse bindings, which the ports reproduce exactly so that the demos behave as they did.
- **Harper & Row v. Nation Enterprises**, 471 U.S. 539 (1985), and the 1992 amendment to 17 U.S.C. §107. Harper & Row held that a work's unpublished status weighs heavily against fair use under the second factor; Congress then added to §107 that unpublished status "shall not itself bar a finding of fair use." Here: the "unpublished proprietary" legends on flight-1988, the IRIS GL headers, gobj.h, and the Inventor games. The legend is SGI's assertion, not a fact about distribution: SGI put these files on tapes and CDs it shipped to customers, so they are published in the practical sense the second factor cares about, and even if a court took the legend at face value the 1992 amendment means it would not decide the question.
- **Google v. Oracle**, 593 U.S. 1 (2021). Verbatim copying of 11,500 lines of API declaring code to reimplement the platform elsewhere was fair use. Here: include/gl, SGI's own gl.h and device.h carried verbatim under their proprietary legend, and the Performer headers vendored in sgi-performer; declaring code copied so that unmodified SGI programs compile against a new implementation, which is the Android fact pattern.
- **Campbell v. Acuff-Rose**, 510 U.S. 569 (1994) and **Andy Warhol Foundation v. Goldsmith**, 598 U.S. 508 (2023). Transformativeness is about the purpose of the specific use, and commerciality of that use counts against it. Here: the first fair-use factor for the demo-tape sources and data (§5): the project's purpose is historical preservation and study rather than SGI's purpose of selling workstations, and nothing is sold, no advertising is served, and no donations are taken.
- **Authors Guild v. Google**, 804 F.3d 202 (2d Cir. 2015). Full-text copying of millions of in-copyright books for search was fair use. Whole-work copying is not fatal when the purpose needs it. Here: the third fair-use factor for the demos; a demo cannot be preserved or run in part, so the whole of each source file and its data is used.
- **Micro Star v. FormGen**, 154 F.3d 1107 (9th Cir. 1998). Game level files are copyrightable and their unauthorized commercial distribution infringes. Here: the reason the data files (bounce's models, the GFO databases, flight's terrain and sounds, the Performer Town database, the Inventor games' models) are inventoried as works in their own right (§3.6) rather than treated as incidental to the code, and why they share the code's fair-use analysis rather than escaping it.
- **Hachette v. Internet Archive**, 115 F.4th 163 (2d Cir. 2024). Preservation framing does not rescue wholesale copying of works that have a live market. Here: the fourth fair-use factor, and the limit on it. The distinction from Hachette is that nothing here is in print, licensed, or for sale, and HPE has no product these demos compete with. The case is also why the SGI manuals were moved out of the code repositories into sgi-docs: they are the material most like the books in Hachette, whole works reproduced for their original purpose, and the demos' case should not depend on them.

The DMCA's anti-circumvention provision, 17 U.S.C. §1201, is where most modern emulation disputes are actually fought, and it does not apply here: IRIX demos, tapes, and CDs have no encryption or access control, so nothing is circumvented. The Librarian of Congress's triennial exemptions for video-game preservation (37 C.F.R. §201.40) exist because consoles do have such controls; the 2024 rulemaking renewed the exemption for libraries and archives but denied remote access, which shows how narrow the carve-out is and how fortunate it is not to need it.

Two non-defenses should be named so nobody relies on them. "Abandonware" has no legal meaning; the 1984 to 1994 SGI works are works made for hire with 95-year terms and stay in copyright until 2079 or later. And the absence of enforcement is not a license; it goes to practical risk and to the market-effect factor, not to permission.

### 6.2 What Nintendo has and has not gone after

Nintendo is the most aggressive rights holder in this space and its record is a useful acid test. The pattern is consistent. Nintendo acts on (1) distribution of its binaries and assets, (2) circumvention of its encryption, (3) inclusion of its proprietary SDK or runtime, and (4) commercial or leak-tainted projects. It does not act on original code that reimplements a platform or reconstructs a program, even when the reconstruction is exact.

### 6.3 How sgi-demos measures against that pattern

| Nintendo trigger | sgi-demos |
|---|---|
| Distributing the vendor's binaries | None in any code repository. SGI executable hashes only are recorded for historical provenance. |
| Distributing the vendor's assets | Data files ship with the demos. Unlike a ROM, these were distributed by SGI in the clear with source, and flight-1994's and Town's are covered by license. The "bring your own data" model used by the decompilation projects is not available for demos whose whole point is the bundled scene, so this rests on fair use. |
| Circumventing encryption | None exists on any SGI medium used. Not applicable. |
| Including the vendor's proprietary SDK or runtime | The project ships no SGI libgl, libpf, or IRIX library. The IRIS GL API is reimplemented on the project's rasterizers and the Performer API on OpenSceneGraph. The only vendor SDK material is declaring code in headers, which Google v. Oracle covers. This is the exact point where Portal 64 failed and where sgi-demos is correctly positioned. |
| Commercial use | None. |
| Leaked or unreleased source | None. Every source came from media SGI sold or published, from the author, or from a public archive. |
| Vendor trademarks as branding | The organization is named sgi-demos and sibling repos display the SGI Performer and Open Inventor logos. Naming a preservation project after its subject is nominative use; NOTICE and the README carry a non-affiliation statement and identify the marks' owners. |

The one structural difference from the Nintendo world is that for source-distributed demos, the copyrighted work and the thing being preserved are the same file. A decompilation project can say "we ship none of Nintendo's expression"; sgi-demos cannot say that about insect.c, because insect.c is the exhibit. That is why the demo-tape material rests on fair use plus SGI's own free distribution of it, rather than on the clean separation the Nintendo projects use, and why the code repositories are kept to what the demos need: the fair-use argument for the demos is not asked to carry manuals or binaries.

The other difference cuts the project's way. HPE is not Nintendo. It has no console, no game catalog, no key to protect, no product that competes with a 1988 flight simulator, and a documented history of releasing exactly this material (the Linux Toolbox in 2003, oss.sgi.com, the LGPL Inventor release, the permissive notices) rather than defending it. Complete IRIX installation images have been on the Internet Archive and community mirrors for more than a decade without a takedown. That is not a license, but it is the best available evidence about the market-effect factor and about practical risk.

## 7. What not to change

- Do not strip any SGI, Tristram, Alice 4, Khronos, or Adobe/DEC notice, including the "unpublished proprietary" legends. Retaining them is a condition of every license involved and of Apache 2.0 §4(c), and stripping notices would look like concealment.
- Do not replace include/gl with a rewritten header to escape the legend. The declaring-code position is strong and the rewrite would gain nothing.
- Do not remove the data files. They are what the demos display, they were distributed by SGI in the clear with the source, and the fair-use case for them is the same as for the code.

## 8. Source archives

The one place hashes are recorded. The READMEs name their source and point here.

| Archive | Supplies | Where | SHA-256 |
|---|---|---|---|
| IRIS 4D demo tape, sgidemos.tar.Z | arena, bounce, buttonfly, ideas, insect, jello, logo, newave, libdemo, flight-1988, ep-1988's Panel Library v7 | [bitsavers](https://bitsavers.org/bits/SGI/iris/sgidemos.tar.Z) (mirror at bitsavers.trailing-edge.com) | be028995b697d885a5b8769ab49b664bc06c6876dba5eadd5d3044eeb76caad5 |
| GL2-W3.6 release tapes for the IRIS 2400/3000 (10 May 1989), gl2-w3.6+options.tar.gz: a raw dump of the Bootstrap System and Options tapes, each a series of cpio archives | the gifts package: cedit, sunflower, portlib, getapixel.c, port.h, rect.h | [bitsavers](https://bitsavers.org/bits/SGI/iris/gl2-w3.6+options.tar.gz) | 2bbd28466cae6aeeb95ad49bee813d8298e71e6df5405c8f98ae3fbc04ddf58b |
| The "Standard System (usr)" archive on that Bootstrap System tape: the fourth cpio file of the dump, named file.20020204.05:25:55.4 by the dumper's timestamp | the archive that actually contains usr/people/gifts; verify against this file | inside the tarball above | ff9499c0b34c50fa79f50ae00f08c3760c98207091d44e07c1c308bf984ed875 |
| gview, IRIX 3 MIPS ECOFF executable, 86,128 bytes | the binary gview.c was reconstructed from | an IRIX 3 installation tape | 28c149f852d10e32e695b4455f1a93214135ad0153589d7caab16257aaf74018 |
| flight 1.0, IRIS 1400 68k executable, 176,660 bytes | reference for a future reconstruction | contributed via issue #4 | a0c5d96d634d863f072213e120f3ea64e481fa114a723594c59e3912fb9a9c49 |
| flight 1.0, uuencoded form of the above | same | same | 9aa94505373a2ce5f00a4af8bdb26217f1b324ae430857d4cf9a0d3472d4fa82 |
| OpenGL Performer 3.0 for Windows installer, OpenGLPerformer300.exe (2002-12-10) | the Performer headers, samples, utility libraries, loaders, and Town data vendored in sgi-performer | previous free SGI download, offline | 1f9c8310c92ed8d51b1bc902f8aeea9f50deb83d15cb4277933730d422da522f |

Other sources consulted, without archive hashes yet (see docs/COPYRIGHT_TODO.md):

- SGI Linux Toolbox, March 2003, and Developer Toolbox 6.1, per the flight-1994 README.
- IGL 0.1.8 and the ElectroPortis fork (LICENSE.md) in the sgi-demos org.
- The oss.sgi.com Performer CVS mirror, per the sgi-performer READMEs.
- SGI's Open Inventor release (oss.sgi.com CVS, LGPL 2.1), the aumuell and MeVisLab trees, Coin, and the Inventor Games CD, per the sgi-inventor READMEs.
- Alice 4: github.com/lkesteloot/alice, LICENSE (Apache 2.0).
- Statutes and regulations: 17 U.S.C. §§105, 107, 108, 405, 1201; 37 C.F.R. §§201.40, 202.1.
- Cases as cited in section 6.
