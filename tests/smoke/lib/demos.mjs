// The demo list, from the root Makefile (`make list`): every demo directory
// with a Makefile, minus draft ports. name is the path under demos/
// (ep-1994/decomp), id the same with "/" as "-" for file names, and placard
// the demo's placard.json.
import { execFileSync } from "node:child_process";
import { readFileSync } from "node:fs";
import { join } from "node:path";

export function listDemos(repo) {
  const out = execFileSync("make", ["--no-print-directory", "-s", "-C", repo, "list"], { encoding: "utf8" });
  return out.split("\n").filter(Boolean).map((name) => ({
    name,
    id: name.replace(/\//g, "-"),
    placard: JSON.parse(readFileSync(join(repo, "demos", name, "placard.json"), "utf8")),
  }));
}
