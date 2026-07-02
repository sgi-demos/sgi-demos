// "Non-blank" detection for a captured frame.
//
// We can't trust toDataURL() on a WebGL canvas, so the runner hands us a PNG
// buffer captured via the browser compositor. We decode it and measure how
// much of the image differs from its single most common color. A demo that
// failed to render tends to be a flat fill (all black, all one clear color);
// a demo that rendered has many colors and edges.
import { PNG } from "pngjs";

// Returns { content, dominantFraction, width, height }.
// `content` is the fraction of pixels (0..1) that are NOT the dominant
// quantized color. Higher = more stuff drawn.
export function analyzePng(buffer) {
  const png = PNG.sync.read(buffer);
  const { width, height, data } = png; // data is RGBA, 4 bytes/pixel
  const counts = new Map();
  const total = width * height;

  for (let i = 0; i < data.length; i += 4) {
    // Quantize to 4 bits per channel so anti-aliasing / dithering noise
    // doesn't shatter the histogram into thousands of near-identical bins.
    const r = data[i] >> 4;
    const g = data[i + 1] >> 4;
    const b = data[i + 2] >> 4;
    const key = (r << 8) | (g << 4) | b;
    counts.set(key, (counts.get(key) || 0) + 1);
  }

  let dominant = 0;
  for (const c of counts.values()) if (c > dominant) dominant = c;

  const dominantFraction = total ? dominant / total : 1;
  return {
    width,
    height,
    dominantFraction,
    content: 1 - dominantFraction,
  };
}
