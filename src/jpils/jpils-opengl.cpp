/* This file is public domain */
#ifdef _WIN32
 #include <windows.h>
#endif

#include "jpils-opengl.h"

#ifdef _WIN32
 #include <gl/gl.h>
 #include <gl/glu.h>
#elif defined (LINUX)
 #include <GL/gl.h>
 #include <GL/glut.h>
 #undef KeyPress
#else
 #include <GLUT/glut.h>
#endif

BEGIN_JUCE_NAMESPACE

void OpenGL::gl__Accum(unsigned int op, float value) {
    ::glAccum(op, value);
}

void OpenGL::gl__AlphaFunc(unsigned int func, float ref) {
    ::glAlphaFunc(func, ref);
}

void OpenGL::gl__ArrayElement(int i) {
    ::glArrayElement(i);
}

void OpenGL::gl__Begin(unsigned int mode) {
    ::glBegin(mode);
}

void OpenGL::gl__BindTexture(unsigned int target, unsigned int texture) {
    ::glBindTexture(target, texture);
}

void OpenGL::gl__BlendFunc(unsigned int sfactor, unsigned int dfactor) {
    ::glBlendFunc(sfactor, dfactor);
}

void OpenGL::gl__CallList(unsigned int list) {
    ::glCallList(list);
}

void OpenGL::gl__CallLists(int n, unsigned int type, const void * lists) {
    ::glCallLists(n, type, lists);
}

void OpenGL::gl__Clear(unsigned int mask) {
    ::glClear(mask);
}

void OpenGL::gl__ClearAccum(float red, float green, float blue, float alpha) {
    ::glClearAccum(red, green, blue, alpha);
}

void OpenGL::gl__ClearColor(float red, float green, float blue, float alpha) {
    ::glClearColor(red, green, blue, alpha);
}

void OpenGL::gl__ClearDepth(double depth) {
    ::glClearDepth(depth);
}

void OpenGL::gl__ClearIndex(float c) {
    ::glClearIndex(c);
}

void OpenGL::gl__ClearStencil(int s) {
    ::glClearStencil(s);
}

void OpenGL::gl__Color__3d(double red, double green, double blue) {
    ::glColor3d(red, green, blue);
}

void OpenGL::gl__Color__4d(double red, double green, double blue, double alpha) {
    ::glColor4d(red, green, blue, alpha);
}

void OpenGL::gl__ColorMask(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    ::glColorMask(red, green, blue, alpha);
}

void OpenGL::gl__ColorMaterial(unsigned int face, unsigned int mode) {
    ::glColorMaterial(face, mode);
}

void OpenGL::gl__ColorPointer(int size, unsigned int type, int stride, const void * pointer) {
    ::glColorPointer(size, type, stride, pointer);
}

void OpenGL::gl__CopyPixels(int x, int y, int width, int height, unsigned int type) {
    ::glCopyPixels(x, y, width, height, type);
}

void OpenGL::gl__CopyTexImage1D(unsigned int target, int level, unsigned int internalFormat, int x, int y, int width, int border) {
    ::glCopyTexImage1D(target, level, internalFormat, x, y, width, border);
}

void OpenGL::gl__CopyTexImage2D(unsigned int target, int level, unsigned int internalFormat, int x, int y, int width, int height, int border) {
    ::glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border);
}

void OpenGL::gl__CopyTexSubImage1D(unsigned int target, int level, int xoffset, int x, int y, int width) {
    ::glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void OpenGL::gl__CopyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) {
    ::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void OpenGL::gl__CullFace(unsigned int mode) {
    ::glCullFace(mode);
}

void OpenGL::gl__DeleteLists(unsigned int list, int range) {
    ::glDeleteLists(list, range);
}

void OpenGL::gl__DepthFunc(unsigned int func) {
    ::glDepthFunc(func);
}

void OpenGL::gl__DepthMask(unsigned char flag) {
    ::glDepthMask(flag);
}

void OpenGL::gl__DepthRange(double zNear, double zFar) {
    ::glDepthRange(zNear, zFar);
}

void OpenGL::gl__Disable(unsigned int cap) {
    ::glDisable(cap);
}

void OpenGL::gl__DisableClientState(unsigned int array) {
    ::glDisableClientState(array);
}

void OpenGL::gl__DrawArrays(unsigned int mode, int first, int count) {
    ::glDrawArrays(mode, first, count);
}

void OpenGL::gl__DrawBuffer(unsigned int mode) {
    ::glDrawBuffer(mode);
}

void OpenGL::gl__DrawElements(unsigned int mode, int count, unsigned int type, const void * indices) {
    ::glDrawElements(mode, count, type, indices);
}

void OpenGL::gl__DrawPixels(int width, int height, unsigned int format, unsigned int type, const void * pixels) {
    ::glDrawPixels(width, height, format, type, pixels);
}

void OpenGL::gl__EdgeFlag(unsigned char flag) {
    ::glEdgeFlag(flag);
}

void OpenGL::gl__EdgeFlagPointer(int stride, const void * pointer) {
    ::glEdgeFlagPointer(stride, pointer);
}

void OpenGL::gl__EdgeFlagv(const unsigned char * flag) {
    ::glEdgeFlagv(flag);
}

void OpenGL::gl__Enable(unsigned int cap) {
    ::glEnable(cap);
}

void OpenGL::gl__EnableClientState(unsigned int array) {
    ::glEnableClientState(array);
}

void OpenGL::gl__End() {
    ::glEnd();
}

void OpenGL::gl__EndList() {
    ::glEndList();
}

void OpenGL::gl__EvalCoord__1d(double u) {
    ::glEvalCoord1d(u);
}

void OpenGL::gl__EvalCoord__2d(double u, double v) {
    ::glEvalCoord2d(u, v);
}

void OpenGL::gl__EvalMesh__1(unsigned int mode, int i1, int i2) {
    ::glEvalMesh1(mode, i1, i2);
}

void OpenGL::gl__EvalMesh__2(unsigned int mode, int i1, int i2, int j1, int j2) {
    ::glEvalMesh2(mode, i1, i2, j1, j2);
}

void OpenGL::gl__EvalPoint__1(int i) {
    ::glEvalPoint1(i);
}

void OpenGL::gl__EvalPoint__2(int i, int j) {
    ::glEvalPoint2(i, j);
}

void OpenGL::gl__Finish() {
    ::glFinish();
}

void OpenGL::gl__Flush() {
    ::glFlush();
}

void OpenGL::gl__Fog__f(unsigned int pname, float param) {
    ::glFogf(pname, param);
}

void OpenGL::gl__FrontFace(unsigned int mode) {
    ::glFrontFace(mode);
}

void OpenGL::gl__Frustum(double left, double right, double bottom, double top, double zNear, double zFar) {
    ::glFrustum(left, right, bottom, top, zNear, zFar);
}

unsigned int OpenGL::gl__GenLists(int range) {
    return ::glGenLists(range);
}

unsigned int OpenGL::gl__GetError() {
    return ::glGetError();
}

const unsigned char * OpenGL::gl__GetString(unsigned int name) {
    return ::glGetString(name);
}

void OpenGL::gl__GetTexImage(unsigned int target, int level, unsigned int format, unsigned int type, void * pixels) {
    ::glGetTexImage(target, level, format, type, pixels);
}

void OpenGL::gl__Hint(unsigned int target, unsigned int mode) {
    ::glHint(target, mode);
}

void OpenGL::gl__IndexMask(unsigned int mask) {
    ::glIndexMask(mask);
}

void OpenGL::gl__IndexPointer(unsigned int type, int stride, const void * pointer) {
    ::glIndexPointer(type, stride, pointer);
}

void OpenGL::gl__Index__d(double c) {
    ::glIndexd(c);
}

void OpenGL::gl__InitNames() {
    ::glInitNames();
}

void OpenGL::gl__InterleavedArrays(unsigned int format, int stride, const void * pointer) {
    ::glInterleavedArrays(format, stride, pointer);
}

bool OpenGL::gl__IsEnabled(unsigned int cap) {
    return ::glIsEnabled(cap) != 0;
}

bool OpenGL::gl__IsList(unsigned int list) {
    return ::glIsList(list) != 0;
}

bool OpenGL::gl__IsTexture(unsigned int texture) {
    return ::glIsTexture(texture) != 0;
}

void OpenGL::gl__LightModel__f(unsigned int pname, float param) {
    ::glLightModelf(pname, param);
}

void OpenGL::gl__Light__f(unsigned int light, unsigned int pname, float param) {
    ::glLightf(light, pname, param);
}

void OpenGL::gl__LineWidth(float width) {
    ::glLineWidth(width);
}

void OpenGL::gl__ListBase(unsigned int base) {
    ::glListBase(base);
}

void OpenGL::gl__LoadIdentity() {
    ::glLoadIdentity();
}

void OpenGL::gl__LoadName(unsigned int name) {
    ::glLoadName(name);
}

void OpenGL::gl__LogicOp(unsigned int opcode) {
    ::glLogicOp(opcode);
}

void OpenGL::gl__MapGrid__1d(int un, double u1, double u2) {
    ::glMapGrid1d(un, u1, u2);
}

void OpenGL::gl__MapGrid__2d(int un, double u1, double u2, int vn, double v1, double v2) {
    ::glMapGrid2d(un, u1, u2, vn, v1, v2);
}

void OpenGL::gl__Material__f(unsigned int face, unsigned int pname, float param) {
    ::glMaterialf(face, pname, param);
}

void OpenGL::gl__MatrixMode(unsigned int mode) {
    ::glMatrixMode(mode);
}

void OpenGL::gl__NewList(unsigned int list, unsigned int mode) {
    ::glNewList(list, mode);
}

void OpenGL::gl__Normal__3d(double nx, double ny, double nz) {
    ::glNormal3d(nx, ny, nz);
}

void OpenGL::gl__NormalPointer(unsigned int type, int stride, const void * pointer) {
    ::glNormalPointer(type, stride, pointer);
}

void OpenGL::gl__Ortho(double left, double right, double bottom, double top, double zNear, double zFar) {
    ::glOrtho(left, right, bottom, top, zNear, zFar);
}

void OpenGL::gl__PassThrough(float token) {
    ::glPassThrough(token);
}

void OpenGL::gl__PixelStore__f(unsigned int pname, float param) {
    ::glPixelStoref(pname, param);
}

void OpenGL::gl__PixelTransfer__f(unsigned int pname, float param) {
    ::glPixelTransferf(pname, param);
}

void OpenGL::gl__PixelZoom(float xfactor, float yfactor) {
    ::glPixelZoom(xfactor, yfactor);
}

void OpenGL::gl__PointSize(float size) {
    ::glPointSize(size);
}

void OpenGL::gl__PolygonMode(unsigned int face, unsigned int mode) {
    ::glPolygonMode(face, mode);
}

void OpenGL::gl__PolygonOffset(float factor, float units) {
    ::glPolygonOffset(factor, units);
}

void OpenGL::gl__PolygonStipple(const unsigned char * mask) {
    ::glPolygonStipple(mask);
}

void OpenGL::gl__PopAttrib() {
    ::glPopAttrib();
}

void OpenGL::gl__PopClientAttrib() {
    ::glPopClientAttrib();
}

void OpenGL::gl__PopMatrix() {
    ::glPopMatrix();
}

void OpenGL::gl__PopName() {
    ::glPopName();
}

void OpenGL::gl__PushAttrib(unsigned int mask) {
    ::glPushAttrib(mask);
}

void OpenGL::gl__PushClientAttrib(unsigned int mask) {
    ::glPushClientAttrib(mask);
}

void OpenGL::gl__PushMatrix() {
    ::glPushMatrix();
}

void OpenGL::gl__PushName(unsigned int name) {
    ::glPushName(name);
}

void OpenGL::gl__RasterPos__2d(double x, double y) {
    ::glRasterPos2d(x, y);
}

void OpenGL::gl__RasterPos__3d(double x, double y, double z) {
    ::glRasterPos3d(x, y, z);
}

void OpenGL::gl__RasterPos__4d(double x, double y, double z, double w) {
    ::glRasterPos4d(x, y, z, w);
}

void OpenGL::gl__ReadBuffer(unsigned int mode) {
    ::glReadBuffer(mode);
}

void OpenGL::gl__ReadPixels(int x, int y, int width, int height, unsigned int format, unsigned int type, void * pixels) {
    ::glReadPixels(x, y, width, height, format, type, pixels);
}

void OpenGL::gl__Rect__d(double x1, double y1, double x2, double y2) {
    ::glRectd(x1, y1, x2, y2);
}

int OpenGL::gl__RenderMode(unsigned int mode) {
    return ::glRenderMode(mode);
}

void OpenGL::gl__Rotate__d(double angle, double x, double y, double z) {
    ::glRotated(angle, x, y, z);
}

void OpenGL::gl__Scale__d(double x, double y, double z) {
    ::glScaled(x, y, z);
}

void OpenGL::gl__Scissor(int x, int y, int width, int height) {
    ::glScissor(x, y, width, height);
}

void OpenGL::gl__ShadeModel(unsigned int mode) {
    ::glShadeModel(mode);
}

void OpenGL::gl__StencilFunc(unsigned int func, int ref, unsigned int mask) {
    ::glStencilFunc(func, ref, mask);
}

void OpenGL::gl__StencilMask(unsigned int mask) {
    ::glStencilMask(mask);
}

void OpenGL::gl__StencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass) {
    ::glStencilOp(fail, zfail, zpass);
}

void OpenGL::gl__TexCoord__1d(double s) {
    ::glTexCoord1d(s);
}

void OpenGL::gl__TexCoord__2d(double s, double t) {
    ::glTexCoord2d(s, t);
}

void OpenGL::gl__TexCoord__3d(double s, double t, double r) {
    ::glTexCoord3d(s, t, r);
}

void OpenGL::gl__TexCoord__4d(double s, double t, double r, double q) {
    ::glTexCoord4d(s, t, r, q);
}

void OpenGL::gl__TexCoordPointer(int size, unsigned int type, int stride, const void * pointer) {
    ::glTexCoordPointer(size, type, stride, pointer);
}

void OpenGL::gl__TexEnvf(unsigned int target, unsigned int pname, float param) {
    ::glTexEnvf(target, pname, param);
}

void OpenGL::gl__TexGen__d(unsigned int coord, unsigned int pname, double param) {
    ::glTexGend(coord, pname, param);
}

void OpenGL::gl__TexImage1D(unsigned int target, int level, int internalformat, int width, int border, unsigned int format, unsigned int type, const void * pixels) {
    ::glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

void OpenGL::gl__TexImage2D(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void * pixels) {
    ::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void OpenGL::gl__TexParameter__f(unsigned int target, unsigned int pname, float param) {
    ::glTexParameterf(target, pname, param);
}

void OpenGL::gl__TexSubImage1D(unsigned int target, int level, int xoffset, int width, unsigned int format, unsigned int type, const void * pixels) {
    ::glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void OpenGL::gl__TexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void * pixels) {
    ::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void OpenGL::gl__Translate__d(double x, double y, double z) {
    ::glTranslated(x, y, z);
}

void OpenGL::gl__Vertex__2d(double x, double y) {
    ::glVertex2d(x, y);
}

void OpenGL::gl__Vertex__3d(double x, double y, double z) {
    ::glVertex3d(x, y, z);
}

void OpenGL::gl__Vertex__4d(double x, double y, double z, double w) {
    ::glVertex4d(x, y, z, w);
}

void OpenGL::gl__VertexPointer(int size, unsigned int type, int stride, const void * pointer) {
    ::glVertexPointer(size, type, stride, pointer);
}

void OpenGL::gl__Viewport(int x, int y, int width, int height) {
    ::glViewport(x, y, width, height);
}

END_JUCE_NAMESPACE
