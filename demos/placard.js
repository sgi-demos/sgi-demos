// Gallery placard for the web demos: title, author, year, a short blurb, and
// the inputs the demo listens for, shown in the lower-left corner when the
// page loads, minimized to the title and author lines until the plus opens
// it. The x closes it; the minus shrinks it to the title and author
// line, the plus restores it; Tab hides and shows it, and Shift+Tab steps
// through open, minimized, closed, and back to open, so the card can be run
// from the keyboard alone (no demo listens for Tab, so it is swallowed before
// SDL sees it). Every state change is immediate. Whichever state was last set
// (open, minimized, closed) is kept for every demo from then on, in
// localStorage. URL switches: ?placard=0 starts this page without the card
// and leaves the stored state alone, ?placard=1 reopens it and keeps it open,
// ?placard=25 closes it by itself after 25 seconds (HOLD_MS is the default,
// 0 = stay). Each demo page includes this with
//   <script defer src="../../placard.js"></script>
// and it reads ../placard.json (demos/<name>/placard.json, next to the source).
// A page elsewhere (the site's buttonfly front page) names the demo instead:
//   <script defer src="https://sgi-demos.org/sgi-demos/demos/placard.js" data-demo="buttonfly"></script>
(function () {
    var me = document.currentScript;
    var demo = me && me.getAttribute("data-demo");
    var url = demo ? me.src.replace(/placard\.js(\?.*)?$/, demo + "/placard.json") : "../placard.json";
    var q = new URLSearchParams(window.location.search).get("placard");
    if (q === "0" || q === "off") return;
    var state = null;                          // "open" | "min" | "closed", kept across demos and visits
    try { state = localStorage.getItem("placard"); } catch (e) {}
    function remember(v) { state = v; try { localStorage.setItem("placard", v); } catch (e) {} }
    if (q === "1" || q === "on") remember("open");   // reopen, and stay open from here on
    var view = "min";                           // the last visible mode, so Tab reopens as it was; minimized on a first visit
    try { view = localStorage.getItem("placard-view") || "min"; } catch (e) {}
    if (state === "min" || state === "open") view = state;
    var HOLD_MS = 0;                          // 0: stays until closed; ?placard=<seconds> closes it after that long
    var LAYOUT = "fit";                      // "fit": as wide as its longest line; "wide": a strip across the bottom; "corner": the earlier 420px card
    if (q && /^\d+$/.test(q)) HOLD_MS = (q | 0) * 1000;

    fetch(url).then(function (r) { return r.ok ? r.json() : null; }).then(function (d) {
        if (!d) return;
        var style = document.createElement("style");
        style.textContent =
            "#canvas:focus{outline:none}" +   /* the tabindex below makes the canvas focusable; no focus ring on it */
            ".placard{position:fixed;left:20px;bottom:20px;z-index:10;box-sizing:border-box;" +
            "padding:.8rem 1rem .9rem;border:1px solid rgba(255,255,255,.18);border-radius:6px;" +
            "background:rgba(26,42,74,.86);color:#fff;font:14px/1.45 -apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;" +
            "box-shadow:0 4px 18px rgba(0,0,0,.35);cursor:default}" +
            ".placard.fit{width:max-content;max-width:calc(100vw - 40px)}" +
            ".placard.corner{max-width:min(420px,calc(100vw - 40px))}" +
            ".placard.wide{right:20px}" +
            ".placard.min{width:max-content}.placard.min p,.placard.min .foot{display:none}.placard.min .who{display:block;margin:0}.placard.min .who .sep{display:none}.placard.min .who .fb,.placard.min .who .tech{display:block;margin-left:0}" +   /* minimized: framebuffer and machines each drop to their own line */
            ".placard.gone{display:none}" +
            ".placard-tab{position:fixed;left:20px;bottom:20px;z-index:10;padding:.15rem .5rem .2rem;border:1px solid rgba(255,255,255,.18);border-radius:4px;" +
            "background:rgba(26,42,74,.86);color:#a3b3c9;font:italic 600 12px -apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;cursor:pointer;user-select:none}" +
            ".placard-tab:hover{color:#fff}.placard-tab[hidden]{display:none}" +
            ".placard h1{margin:0 0 .15rem;padding-right:3.2rem;font-size:1.05rem;font-weight:600;font-style:italic}" +
            ".placard h1 a{color:#fff;text-decoration:none}.placard h1 a:hover{text-decoration:underline}" +
            ".placard .who{display:flex;flex-wrap:wrap;justify-content:space-between;gap:.2rem 1.5rem;margin:0 0 .5rem;color:#a3b3c9;font-size:.85rem}" +
            ".placard .who .tech{margin-left:auto;white-space:nowrap}" +
            ".placard .who a.yr{color:#8fc3ea;text-decoration:none}.placard .who a.yr:hover{text-decoration:underline}" +
            ".placard p{margin:0 0 .5rem}" +
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
        el.className = "placard " + LAYOUT;
        el.setAttribute("role", "note");
        function esc(s) { return String(s).replace(/&/g, "&amp;").replace(/</g, "&lt;"); }
        // after the year: colour mode and framebuffer depth; right side of the same line: mid and high-end machines of the year
        var fb = [d.color, d.depth].filter(Boolean).join(", ");
        // the year links to the demo's timeline entry
        var year = d.year ? (d.more ? "<a class='yr' href='" + esc(d.more) + "' title='timeline'>" + esc(d.year) + "</a>" : esc(d.year)) : "";
        var who = [d.author ? esc(d.author) : "", year].filter(Boolean).join(", ") + (fb ? "<span class='sep'> \u00b7 </span><span class='fb'>" + esc(fb) + "</span>" : "");
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
        function inputsHtml(items) {
            var html = "";
            items.forEach(function (it) {
                var mm = /^mouse:\s*(.*)$/.exec(it);
                if (mm) {
                    var t = mm[1].split(/\s+/);
                    var l = t.indexOf("L") >= 0, m = t.indexOf("M") >= 0, r = t.indexOf("R") >= 0, drag = t.indexOf("drag") >= 0;
                    var title = ["left", "middle", "right"].filter(function (n, i) { return [l, m, r][i]; }).join(", ") + " mouse" + (drag ? ", drag" : "");
                    html += "<span class='mouse' title='" + esc(title) + "'>" + mouseSvg(l, m, r) + (drag ? "drag" : "") + "</span>";
                } else {
                    html += "<span>" + esc(it.replace(/^keys:\s*/, "")) + "</span>";
                }
            });
            return html;
        }
        var inputs = d.inputs || d.inputs_detected || [];
        el.innerHTML =
            "<span class='btns'><span class='mn' title='minimize (Shift+Tab steps open, minimized, closed)'>&minus;</span><span class='mx' title='maximize'>+</span><span class='x' title='close (Tab brings it back)'>&times;</span></span>" +
            "<h1>" + (d.browse ? "<a href='" + esc(d.browse) + "' title='browse the demos'>" + esc(d.title || document.title) + "</a>" : esc(d.title || document.title)) + "</h1>" +
            (who || d.machines ? "<div class='who'><span>" + who + "</span>" + (d.machines ? "<span class='tech'>" + esc(d.machines) + "</span>" : "") + "</div>" : "") +
            (d.blurb ? "<p>" + esc(d.blurb) + "</p>" : "") +
            "<div class='foot'>" +
            (inputs.length ? "<div class='in'>" + inputsHtml(inputs) + "</div>" : "<span></span>") +
            (d.source ? "<div class='more'>" +
                (d.source ? "<a href='" + esc(d.source) + "'>source</a>" : "") + "</div>" : "") +
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

        var timer = null, hovering = false;
        function arm() { clearTimeout(timer); if (HOLD_MS > 0) timer = setTimeout(function () { if (!hovering) hide(); }, HOLD_MS); }
        el.addEventListener("mouseenter", function () { hovering = true; });
        el.addEventListener("mouseleave", function () { hovering = false; arm(); });
        function setMin(on) {
            el.classList.toggle("min", on);
            el.querySelector(".mn").style.display = on ? "none" : "";
            el.querySelector(".mx").style.display = on ? "" : "none";
            view = on ? "min" : "open";
            try { localStorage.setItem("placard-view", view); } catch (e) {}
        }
        // While the card is closed, a small "tab" in its corner says how to get it back.
        var tab = document.createElement("div");
        tab.className = "placard-tab";
        tab.textContent = "tab for info";
        tab.title = "press Tab to show the placard";
        tab.hidden = true;
        document.body.appendChild(tab);
        // every state change is immediate, so open, minimize, and close all feel the same
        function hide() { el.classList.add("gone"); tab.hidden = false; remember("closed"); }
        function show() { el.classList.remove("gone"); tab.hidden = true; setMin(view === "min"); remember(view); }
        tab.addEventListener("click", function () { show(); setTimeout(focusCanvas, 0); });
        el.querySelector(".x").addEventListener("click", hide);
        el.querySelector(".mn").addEventListener("click", function () { setMin(true); remember("min"); });
        el.querySelector(".mx").addEventListener("click", function () { setMin(false); remember("open"); });
        setMin(view === "min");
        if (state === "closed") { el.classList.add("gone"); tab.hidden = false; }
        // Tab toggles the card; Shift+Tab steps open -> minimized -> closed ->
        // open. Captured at the window and stopped there, so neither SDL
        // (listening on the canvas) nor the browser's focus traversal gets it.
        window.addEventListener("keydown", function (ev) {
            if (ev.key !== "Tab" || ev.altKey || ev.ctrlKey || ev.metaKey) return;
            ev.preventDefault(); ev.stopImmediatePropagation();
            var closed = el.classList.contains("gone");
            if (!ev.shiftKey) { if (closed) show(); else hide(); return; }
            if (closed) { view = "open"; show(); }
            else if (!el.classList.contains("min")) { setMin(true); remember("min"); }
            else hide();
        }, true);
        arm();
    }).catch(function () {});
})();
