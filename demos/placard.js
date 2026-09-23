// Gallery placard for the web demos: title, author, year, a short blurb, and
// the inputs the demo listens for, in the lower-left corner.
//
// States: closed (only a small circled-i box shows; the first-visit default),
// minimized (title and facts lines), and open (everything). The circled-i box
// or Tab opens the card as it was last shown; the x or Tab closes it; the
// minus and plus minimize and restore it; Shift+Tab steps open -> minimized ->
// closed -> open, so the card runs from the keyboard alone (no demo listens
// for Tab, so it is swallowed before SDL sees it). The last state set is kept
// for every demo in localStorage. URL switch: ?placard=off (or 0) shows no
// card on this page and leaves the stored state alone; ?placard=on (or 1)
// opens it and keeps it open.
//
// Each demo page names its demo, and the placard reads
// demos/<demo>/placard.json next to this file:
//   <script defer src="../../placard.js" data-demo="bounce"></script>
// The links (source, browse, timeline) follow from the demo name.
(function () {
    var SITE = "https://sgi-demos.org", REPO = "https://github.com/sgi-demos/sgi-demos";   // the site as in makefiles/platform.mk
    var me = document.currentScript;
    var demo = me && me.getAttribute("data-demo");
    if (!demo) return;
    var top = demo.split("/")[0];              // a variant (ep-1994/decomp) shares its demo's browse and timeline entries
    var q = new URLSearchParams(window.location.search).get("placard");
    if (q === "0" || q === "off") return;
    var state = null;                          // "open" | "min" | "closed"
    try { state = localStorage.getItem("placard"); } catch (e) {}
    function remember(v) { state = v; try { localStorage.setItem("placard", v); } catch (e) {} }
    if (q === "1" || q === "on") remember("open");
    var view = state === "open" ? "open" : "min";   // how the card shows when it opens

    fetch(me.src.replace(/placard\.js(\?.*)?$/, demo + "/placard.json")).then(function (r) { return r.ok ? r.json() : null; }).then(function (d) {
        if (!d) return;
        var style = document.createElement("style");
        style.textContent =
            "#canvas:focus{outline:none}" +   /* the tabindex below makes the canvas focusable; no focus ring on it */
            ".placard{position:fixed;left:20px;bottom:20px;z-index:10;box-sizing:border-box;width:max-content;max-width:calc(100vw - 40px);" +
            "padding:.8rem 1rem .9rem;border:1px solid rgba(255,255,255,.18);border-radius:6px;" +
            "background:rgba(26,42,74,.86);color:#fff;font:14px/1.45 -apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;" +
            "box-shadow:0 4px 18px rgba(0,0,0,.35);cursor:default}" +
            ".placard.min p,.placard.min .foot{display:none}.placard.min .who{display:block;margin:0}.placard.min .who .sep{display:none}.placard.min .who .fb,.placard.min .who .tech{display:block;margin-left:0}" +   /* minimized: framebuffer and machines each drop to their own line */
            ".placard.gone{display:none}" +
            ".placard-tab{position:fixed;left:20px;bottom:20px;z-index:10;padding:.1rem .4rem .15rem;border:1px solid rgba(255,255,255,.18);border-radius:4px;" +
            "background:rgba(26,42,74,.86);color:#a3b3c9;font:italic 600 11px -apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;cursor:pointer;user-select:none}" +
            ".placard-tab .i{font-style:normal;font-size:13px;vertical-align:-1px}" +
            ".placard-tab:hover{color:#fff}.placard-tab[hidden]{display:none}" +
            ".placard h1{margin:0 0 .15rem;padding-right:3.2rem;font-size:1.05rem;font-weight:600;font-style:italic}" +
            ".placard h1 a{color:#fff;text-decoration:none}.placard h1 a:hover{text-decoration:underline}" +
            ".placard .who{display:flex;flex-wrap:wrap;justify-content:space-between;gap:.2rem 1.5rem;margin:0 0 .5rem;color:#a3b3c9;font-size:.85rem}" +
            ".placard .who .tech{margin-left:auto;white-space:nowrap}" +
            ".placard .who a.yr{color:#8fc3ea;text-decoration:none}.placard .who a.yr:hover{text-decoration:underline}" +
            ".placard p{margin:0 0 .5rem}.placard p.port{color:#a3b3c9;font-size:.85rem;margin-top:-.2rem}" +
            ".placard .foot{display:flex;flex-wrap:wrap;align-items:center;justify-content:space-between;gap:.25rem 1rem}" +
            ".placard .in{display:flex;flex-wrap:wrap;align-items:center;gap:.25rem .8rem;color:#a3b3c9;font-size:.82rem}" +
            ".placard .in b{color:#fff;font-weight:600}" +
            ".placard .in .mouse{display:inline-flex;align-items:center;gap:.3rem}" +
            ".placard .in svg{display:block}" +
            ".placard .btns{position:absolute;right:.55rem;top:.35rem;display:flex;gap:.55rem;color:#a3b3c9;font-size:.95rem;line-height:1;user-select:none}" +
            ".placard .btns span{cursor:pointer;width:1em;text-align:center}.placard .btns span:hover{color:#fff}" +
            ".placard .more{margin-left:auto;font-size:.78rem;white-space:nowrap}.placard .more a{color:#8fc3ea;text-decoration:none;margin-left:.9rem}";
        document.head.appendChild(style);

        var el = document.createElement("div");
        el.className = "placard";
        el.setAttribute("role", "note");
        function esc(s) { return String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;"); }
        // after the year: API, then the framebuffer in one breath: colour mode, depth,
        // "Z" when it is z-buffered, and single or double buffer ("RGB, 24-bit, Z, double buffer");
        // right side of the same line: mid and high-end machines of the year
        var fb = [d.api || "IRIS GL", [d.color, d.depth, d.hidden, d.buffering].filter(Boolean).join(", ")].filter(Boolean).join(" \u00b7 ");
        // the year links to the demo's timeline entry
        var year = d.year ? "<a class='yr' href='" + SITE + "/timeline/#demo-" + esc(top) + "' title='timeline'>" + esc(d.year) + "</a>" : "";
        var who = [d.author ? esc(d.author) : "", year].filter(Boolean).join(", ") + "<span class='sep'> \u00b7 </span><span class='fb'>" + esc(fb) + "</span>";
        // A three-button mouse with the buttons the demo uses lit; "drag"
        // after it when the demo reads mouse motion.
        var mouseIds = 0;
        function mouseSvg(l, m, r) {
            // three buttons across the top, clipped to the rounded body so the
            // outer two follow its corners; a used button is lit white, an
            // unused one stays dim; the body outline is drawn last, on top
            var id = "placard-mouse-" + (mouseIds++);
            var body = "<rect x='1' y='1' width='24' height='30' rx='6'";
            function btn(x, on) {
                return "<rect x='" + x + "' y='1' width='8' height='12.5' fill='" + (on ? "#fff" : "rgba(255,255,255,.14)") + "' stroke='#1a2a4a' stroke-width='1'/>";
            }
            return "<svg width='26' height='32' viewBox='0 0 26 32' aria-hidden='true'>" +
                "<defs><clipPath id='" + id + "'>" + body + "/></clipPath></defs>" +
                body + " fill='rgba(255,255,255,.06)'/>" +
                "<g clip-path='url(#" + id + ")'>" + btn(1, l) + btn(9, m) + btn(17, r) + "</g>" +
                body + " fill='none' stroke='#a3b3c9' stroke-width='1.4'/></svg>";
        }
        // the mouse first (always drawn: unlit buttons say the demo doesn't
        // use it), then the demo's keys and devices, then tab, which runs this card
        function inputsHtml(items) {
            var mouse = items.filter(function (it) { return /^mouse:/.test(it); })[0] || "mouse:";
            var t = mouse.replace(/^mouse:\s*/, "").split(/\s+/);
            var l = t.indexOf("L") >= 0, m = t.indexOf("M") >= 0, r = t.indexOf("R") >= 0, drag = t.indexOf("drag") >= 0;
            var used = ["left", "middle", "right"].filter(function (n, i) { return [l, m, r][i]; });
            var title = used.length ? used.join(", ") + " mouse" + (drag ? ", drag" : "") : "no mouse input";
            var html = "<span class='mouse' title='" + esc(title) + "'>" + mouseSvg(l, m, r) + (drag ? "drag" : "") + "</span>";
            items.forEach(function (it) {
                if (!/^mouse:/.test(it)) html += "<span>" + esc(it.replace(/^keys:\s*/, "")) + "</span>";
            });
            return html + "<span title='Tab shows and hides this card'>tab</span>";
        }
        el.innerHTML =
            "<span class='btns'><span class='mn' title='minimize (Shift+Tab steps open, minimized, closed)'>&minus;</span><span class='mx' title='maximize'>+</span><span class='x' title='close (Tab brings it back)'>&times;</span></span>" +
            "<h1><a href='" + SITE + "/browse/#" + esc(top) + "' title='browse the demos'>" + esc(d.title || document.title) + "</a></h1>" +
            "<div class='who'><span>" + who + "</span>" + (d.machines ? "<span class='tech'>" + esc(d.machines) + "</span>" : "") + "</div>" +
            (d.blurb ? "<p>" + esc(d.blurb) + "</p>" : "") +
            (d.port ? "<p class='port'>This port: " + esc(d.port) + "</p>" : "") +
            "<div class='foot'>" +
            "<div class='in'>" + inputsHtml(d.inputs || d.inputs_detected || []) + "</div>" +
            "<div class='more'><a href='" + REPO + "/tree/main/demos/" + esc(demo) + "'>source</a></div>" +
            "</div>";
        document.body.appendChild(el);

        // Keyboard input goes to the canvas (SDL listens there), so keep the
        // focus on it: at load, and again after any click on the placard
        // itself. mousedown is cancelled so the placard never takes focus;
        // links and the x still get their click.
        function focusCanvas() {
            var c = document.getElementById("canvas");
            if (!c) return;
            if (!c.hasAttribute("tabindex")) c.tabIndex = -1;
            c.focus({ preventScroll: true });
        }
        el.addEventListener("mousedown", function (ev) { if (!ev.target.closest("a")) ev.preventDefault(); });
        el.addEventListener("click", function () { setTimeout(focusCanvas, 0); });
        focusCanvas();
        window.addEventListener("load", focusCanvas);

        // While the card is closed, the circled-i box in its corner brings it back.
        var tab = document.createElement("div");
        tab.className = "placard-tab";
        tab.innerHTML = "<span class='i'>&#x24D8;</span>";   // ⓘ
        tab.title = "press Tab to show the placard";
        document.body.appendChild(tab);

        // every state change is immediate, so open, minimize, and close all feel the same
        function set(s) {
            if (s !== "closed") view = s;
            el.classList.toggle("gone", s === "closed");
            el.classList.toggle("min", view === "min");
            el.querySelector(".mn").style.display = view === "min" ? "none" : "";
            el.querySelector(".mx").style.display = view === "min" ? "" : "none";
            tab.hidden = s !== "closed";
            remember(s);
        }
        function closed() { return el.classList.contains("gone"); }
        tab.addEventListener("click", function () { set(view); setTimeout(focusCanvas, 0); });
        el.querySelector(".x").addEventListener("click", function () { set("closed"); });
        el.querySelector(".mn").addEventListener("click", function () { set("min"); });
        el.querySelector(".mx").addEventListener("click", function () { set("open"); });
        set(state === "open" || state === "min" ? state : "closed");
        // Tab toggles the card; Shift+Tab steps open -> minimized -> closed ->
        // open. Captured at the window and stopped there, so neither SDL
        // (listening on the canvas) nor the browser's focus traversal gets it.
        window.addEventListener("keydown", function (ev) {
            if (ev.key !== "Tab" || ev.altKey || ev.ctrlKey || ev.metaKey) return;
            ev.preventDefault(); ev.stopImmediatePropagation();
            if (!ev.shiftKey) set(closed() ? view : "closed");
            else set(closed() ? "open" : view === "open" ? "min" : "closed");
        }, true);
    }).catch(function () {});
})();
