/*
 * Author: Landon Fuller <landonf@plausible.coop>
 *
 * Copyright (c) 2013 - 2015 Plausible Labs Cooperative, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PLCRASH_ASYNC_DYNAMICLOADER_C_COMPAT_H
#define PLCRASH_ASYNC_DYNAMICLOADER_C_COMPAT_H

#include <KSCrashTao/TBPLCrashMacros.h>
#include <KSCrashTao/TBPLCrashAsyncAllocator.h>
#include <KSCrashTao/TBPLCrashAsyncMachOImage.h>

/*
 * Provides a pure C interface to the C++ DynamicLoader.
 *
 * This exists solely to support the remaining C/Objective-C code; once the codebase migrates to C/C++/Objective-C++,
 * we can drop the C compatibility support used here.
 */

#ifdef __cplusplus
#include <KSCrashTao/TBDynamicLoader.hpp>
using kscrash_async_dynloader_t = kscrash::async::DynamicLoader;
using kscrash_async_image_list_t = kscrash::async::DynamicLoader::ImageList;
#else
typedef uintptr_t kscrash_async_dynloader_t;
typedef uintptr_t kscrash_async_image_list_t;
#endif


PLCR_C_BEGIN_DECLS


typedef struct kscrash_dynamic_loader_ctx {
    kscrash_async_allocator_t *writer_allocator;
    kscrash_async_allocator_t *_precrash_allocator;
    kscrash_async_dynloader_t *dynamic_loader;
} kscrash_dynamic_loader_ctx_t;

/** Init the async allocator
 */
void kscrash_init_dynamic_loader(void);
    
/** Get the shared async allocator, require `kscrash_init_async_allocator` called at app launch.
 */
kscrash_dynamic_loader_ctx_t *kscrash_get_shared_dynamic_loader(void);

kscrash_error_t kscrash_nasync_dynloader_new (kscrash_async_dynloader_t **loader, kscrash_async_allocator_t *allocator, task_t task);
kscrash_error_t kscrash_async_dynloader_read_image_list (kscrash_async_dynloader_t *loader, kscrash_async_allocator_t *allocator, kscrash_async_image_list_t **image_list);
void kscrash_async_dynloader_free (kscrash_async_dynloader_t *loader);


kscrash_error_t kscrash_nasync_image_list_new (kscrash_async_image_list_t **list, kscrash_async_allocator_t *allocator, task_t task);

kscrash_async_image_list_t *kscrash_async_image_list_new_empty (kscrash_async_allocator_t *allocator);

kscrash_async_macho_t *kscrash_async_image_list_get_image (kscrash_async_image_list_t *list, size_t index);
size_t kscrash_async_image_list_count (kscrash_async_image_list_t *list);
kscrash_async_macho_t *kscrash_async_image_containing_address (kscrash_async_image_list_t *list, pl_vm_address_t address);
void kscrash_async_image_list_free (kscrash_async_image_list_t *list);

PLCR_C_END_DECLS

#endif /* PLCRASH_ASYNC_DYNAMICLOADER_C_COMPAT_H */
