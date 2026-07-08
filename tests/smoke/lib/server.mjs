// Minimal static file server for the smoke suite. No external deps.
// Serves files under `root`, with the MIME types Emscripten needs
// (notably application/wasm, and a permissive type for .data preloads).
import http from "node:http";
import { createReadStream } from "node:fs";
import { stat } from "node:fs/promises";
import { join, normalize, extname } from "node:path";

const MIME = {
  ".html": "text/html; charset=utf-8",
  ".js": "text/javascript; charset=utf-8",
  ".mjs": "text/javascript; charset=utf-8",
  ".wasm": "application/wasm",
  ".json": "application/json; charset=utf-8",
  ".data": "application/octet-stream",
  ".bin": "application/octet-stream",
  ".png": "image/png",
  ".ico": "image/x-icon",
  ".css": "text/css; charset=utf-8",
};

// Start a server rooted at `root`. Resolves to { url, close } where url has no
// trailing slash, e.g. http://127.0.0.1:53187
export function startServer(root) {
  const server = http.createServer(async (req, res) => {
    try {
      const urlPath = decodeURIComponent(new URL(req.url, "http://x").pathname);
      // Block path traversal: normalized path must stay under root.
      let filePath = normalize(join(root, urlPath));
      if (!filePath.startsWith(normalize(root))) {
        res.writeHead(403).end("forbidden");
        return;
      }
      let info = await stat(filePath).catch(() => null);
      // Directory index: a request for a directory (e.g. demos/x/web/) serves
      // its index.html, matching GitHub Pages. This is what lets the demos'
      // short web/ URL resolve to the fullwindow index.html page.
      if (info && info.isDirectory()) {
        filePath = join(filePath, "index.html");
        info = await stat(filePath).catch(() => null);
      }
      if (!info || !info.isFile()) {
        res.writeHead(404).end("not found");
        return;
      }
      const type = MIME[extname(filePath).toLowerCase()] || "application/octet-stream";
      res.writeHead(200, { "content-type": type });
      createReadStream(filePath).pipe(res);
    } catch (err) {
      res.writeHead(500).end(String(err));
    }
  });

  return new Promise((resolve) => {
    server.listen(0, "127.0.0.1", () => {
      const { port } = server.address();
      resolve({
        url: `http://127.0.0.1:${port}`,
        close: () => new Promise((r) => server.close(r)),
      });
    });
  });
}
