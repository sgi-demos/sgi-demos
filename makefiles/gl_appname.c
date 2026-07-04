//
// Stamped into every demo by make_demo.mk with -DGL_APPNAME="<APPNAME>".
// One demo per program (museum piece): winopen() in libgl ignores the
// title the demo passes and uses this instead — on web, emscripten's
// argv[0] is "this.program", so the passed title is useless there.
//
const char *gl_appname = GL_APPNAME;
