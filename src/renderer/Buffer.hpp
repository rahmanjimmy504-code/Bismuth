#pragma once

#include "Geode/cocos/platform/win32/CCGL.h"
#include <common.hpp>
#include <vector>

#ifndef BISMUTH_GLES_BACKEND
#define GL_SHADER_STORAGE_BUFFER 0x90D2
#endif

class Buffer {
public:
    ~Buffer();

    inline usize getSize() const { return size; }
    inline u32 getId() const { return id; }

    void read(void* data, usize size, usize offset = 0);
    void write(void* data, usize size, usize offset = 0);

    inline void bindAs(GLenum binding) {
        glBindBuffer(binding, id);
    }

    inline void bindAsUniformBuffer(u32 binding) {
#ifdef BISMUTH_GLES_BACKEND
        (void)binding;
#else
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
#endif
    }

    inline void bindAsStorageBuffer(u32 binding) {
#ifdef BISMUTH_GLES_BACKEND
        (void)binding;
#else
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, id);
#endif
    }

    inline void* mapWriteOnly() {
#ifdef BISMUTH_GLES_BACKEND
        if (shadowData.empty())
            shadowData.resize(size);
        mapped = true;
        return shadowData.data();
#else
        bindAs(GL_ARRAY_BUFFER);
        return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#endif
    }

    inline void* mapReadWrite() {
#ifdef BISMUTH_GLES_BACKEND
        // mobile ES2 has no portable glGetBufferSubData equivalent. Buffers that
        // need CPU read/write mapping must opt into a shadow at creation time.
        if (shadowData.empty())
            shadowData.resize(size);
        mapped = true;
        return shadowData.data();
#else
        bindAs(GL_ARRAY_BUFFER);
        return glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
#endif
    }

    inline void unmap() {
#ifdef BISMUTH_GLES_BACKEND
        if (mapped) {
            uploadShadow();
            mapped = false;
        }
#else
        bindAs(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ARRAY_BUFFER);
#endif
    }

public:
    static Buffer* create(const char* name, usize size, GLenum usage, bool keepShadow = false);

    inline static void destroy(Buffer* buffer) {
        delete buffer;
    }

    inline static Buffer* createStaticDraw(const char* name, void* data, usize size) {
        auto ret = create(name, size, GL_STATIC_DRAW, false);
        if (!ret)
            return nullptr;
        ret->write(data, size);
        return ret;
    }

    inline static Buffer* createDynamicDraw(const char* name, usize size) {
        return create(name, size, GL_DYNAMIC_DRAW, false);
    }

    inline static Buffer* createDynamicCopy(const char* name, usize size) {
#ifdef BISMUTH_GLES_BACKEND
        return create(name, size, GL_DYNAMIC_DRAW, true);
#else
        return create(name, size, GL_DYNAMIC_COPY, false);
#endif
    }

#ifdef BISMUTH_GLES_BACKEND
    void uploadShadow();
#endif

private:
    usize size = 0;
    u32 id = 0;

#ifdef BISMUTH_GLES_BACKEND
    std::vector<u8> shadowData;
    bool mapped = false;
#endif
};