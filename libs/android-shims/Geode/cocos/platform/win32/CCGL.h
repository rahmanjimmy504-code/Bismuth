#pragma once

// Bismuth's shared sources historically include this desktop path directly.
// Android Geometry Dash runs with OpenGL ES; route the old include to Geode's
// Android GLES2 compatibility header instead of defining desktop GL entrypoints.
#include <Geode/cocos/platform/android/CCGL.h>

#ifndef GL_VERTEX_ARRAY_BINDING
#define GL_VERTEX_ARRAY_BINDING GL_VERTEX_ARRAY_BINDING_OES
#endif

#ifndef GL_DOUBLE
#define GL_DOUBLE 0x140A
#endif

// GLES2 exposes float attributes only. The mobile renderer stores its index-like
// metadata as floats, so these wrappers intentionally use the GLES2 API.
static inline void bismuth_glVertexAttribIPointer(
    GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer
) {
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}
#define glVertexAttribIPointer bismuth_glVertexAttribIPointer

static inline void bismuth_glVertexAttribLPointer(
    GLuint index, GLint size, GLenum, GLsizei stride, const GLvoid* pointer
) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}
#define glVertexAttribLPointer bismuth_glVertexAttribLPointer
