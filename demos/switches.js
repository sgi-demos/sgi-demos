// URL switches for the web demos: each switch a page understands becomes the
// environment variable the C code reads, the same as setting it natively
// (?rast=ref is IRISGL_RAST=ref). Every demo page, and the site's
// buttonfly front page, loads this after defining Module and before the
// demo's .js:
//   <script src="../../switches.js"></script>
(function () {
    var SWITCHES = { rast: "IRISGL_RAST", par: "IRISGL_PAR" };
    var params = new URLSearchParams(window.location.search);
    Module.preRun = (Module.preRun || []).concat(function () {
        Object.keys(SWITCHES).forEach(function (k) {
            if (params.has(k)) ENV[SWITCHES[k]] = params.get(k);
        });
    });
})();
