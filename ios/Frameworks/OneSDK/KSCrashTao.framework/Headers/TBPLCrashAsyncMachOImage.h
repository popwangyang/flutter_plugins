/*
 * Author: Landon Fuller <landonf@plausible.coop>
 *
 * Copyright (c) 2011-2013 Plausible Labs Cooperative, Inc.
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

#ifndef PLCRASH_ASYNC_MACHO_IMAGE_H
#define PLCRASH_ASYNC_MACHO_IMAGE_H

#include <stdint.h>
#include <mach/mach.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include <KSCrashTao/TBPLCrashAsyncMObject.h>
#include <KSCrashTao/TBPLCrashAsyncAllocator.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @internal
 * @ingroup kscrash_async_image
 * @{
 */

/**
 * @internal
 *
 * A Mach-O image instance.
 */
typedef struct kscrash_async_macho {
    /** A borrowed reference to our backing allocator instance. */
    kscrash_async_allocator_t *_allocator;

    /** The Mach task in which the Mach-O image can be found */
    mach_port_t task;

    /** The binary image's header address. */
    pl_vm_address_t header_addr;
    
    /** The binary's dyld-reported reported vmaddr slide. */
    pl_vm_off_t vmaddr_slide;

    /** The binary image's name/path, allocated from _allocator. */
    char *name;

    /** The Mach-O header. For our purposes, the 32-bit and 64-bit headers are identical. Note that the header
     * values may require byte-swapping for the local process' use. */
    struct mach_header header;
    
    /** Total size, in bytes, of the in-memory Mach-O header. This may differ from the header field above,
     * as the above field does not include the full mach_header_64 extensions to the mach_header. */
    pl_vm_size_t header_size;

    /** Number of load commands */
    uint32_t ncmds;

    /** Mapped Mach-O load commands */
    kscrash_async_mobject_t load_cmds;

    /** The Mach-O image's __TEXT segment, as defined by the LC_SEGMENT/LC_SEGMENT_64 load command. */
    pl_vm_address_t text_vmaddr;

    /** Total size, in bytes, of the Mach-O image's __TEXT segment, as defined by the LC_SEGMENT/LC_SEGMENT_64 load command. */
    pl_vm_size_t text_size;
    
    /** If true, the image is 64-bit Mach-O. If false, it is a 32-bit Mach-O image. */
    bool m64;

    /** The byte order functions to use for this image */
    const kscrash_async_byteorder_t *byteorder;
} kscrash_async_macho_t;

/**
 * @internal
 *
 * A mapped Mach-O segment.
 */
typedef struct kscrash_async_macho_mapped_segment_t {
    /** The segment's mapped memory object */
    kscrash_async_mobject_t mobj;

    /* File offset of this segment. */
    uint64_t	fileoff;
    
    /* File size of the segment. */
	uint64_t	filesize;
} pl_async_macho_mapped_segment_t;

/**
 * @internal
 *
 * A 32-bit/64-bit neutral symbol table entry. The values will be returned in host byte order.
 */
typedef struct kscrash_async_macho_symtab_entry {
    /* Index into the string table */
    uint32_t n_strx;

    /** Symbol type. */
    uint8_t n_type;

    /** Section number. */
    uint8_t n_sect;

    /** Description (see <mach-o/stab.h>). */
    uint16_t n_desc;

    /** Symbol value */
    pl_vm_address_t n_value;

    /**
     * The normalized symbol address. This will include any required bit flags -- such as the ARM thumb high-order
     * bit -- which are not included in the symbol table by default.
     */
    pl_vm_address_t normalized_value;
} kscrash_async_macho_symtab_entry_t;

/**
 * @internal
 *
 * A Mach-O symtab reader. Provides support for iterating the contents of a Mach-O symbol table.
 */
typedef struct kscrash_async_macho_symtab_reader {
    /** The image from which the symbol table has been mapped. */
    kscrash_async_macho_t *image;

    /** The mapped LINKEDIT segment. */
    pl_async_macho_mapped_segment_t linkedit;

    /** Pointer to the symtab table within the mapped linkedit segment. The validity of this pointer (and the length of
     * data available) is gauranteed. */
    void *symtab;
    
    /** Total number of elements in the symtab. */
    uint32_t nsyms;
    
    /** Pointer to the global symbol table, if available. May be NULL. The validity of this pointer (and the length of
     * data available) is gauranteed. If non-NULL, symtab_local must also be non-NULL. */
    void *symtab_global;

    /** Total number of elements in the global symtab. */
    uint32_t nsyms_global;

    /** Pointer to the local symbol table, if available. May be NULL. The validity of this pointer (and the length of
     * data available) is gauranteed. If non-NULL, symtab_global must also be non-NULL. */
    void *symtab_local;

    /** Total number of elements in the local symtab. */
    uint32_t nsyms_local;

    /** The mapped string table. The validity of this pointer (and the length of
     * data available) is gauranteed. */
    char *string_table;

    /** The string table's size, in bytes. */
    size_t string_table_size;
} kscrash_async_macho_symtab_reader_t;

/**
 * Prototype of a callback function used to execute user code with async-safely fetched symbol.
 *
 * @param address The symbol address.
 * @param name The symbol name. The callback is responsible for copying this value, as its backing storage is not gauranteed to exist
 * after the callback returns.
 * @param ctx The API client's supplied context value.
 */
typedef void (*pl_async_macho_found_symbol_cb)(pl_vm_address_t address, const char *name, void *ctx);

kscrash_error_t kscrash_async_macho_init (kscrash_async_macho_t *image, kscrash_async_allocator_t *allocator, mach_port_t task, const char *name, pl_vm_address_t header);

const kscrash_async_byteorder_t *kscrash_async_macho_byteorder (kscrash_async_macho_t *image);
const struct mach_header *kscrash_async_macho_header (kscrash_async_macho_t *image);
pl_vm_size_t kscrash_async_macho_header_size (kscrash_async_macho_t *image);
    
bool kscrash_async_macho_contains_address (kscrash_async_macho_t *image, pl_vm_address_t address);

cpu_type_t kscrash_async_macho_cpu_type (kscrash_async_macho_t *image);
cpu_subtype_t kscrash_async_macho_cpu_subtype (kscrash_async_macho_t *image);

void *kscrash_async_macho_next_command (kscrash_async_macho_t *image, void *previous);
void *kscrash_async_macho_next_command_type (kscrash_async_macho_t *image, void *previous, uint32_t expectedCommand);
void *kscrash_async_macho_find_command (kscrash_async_macho_t *image, uint32_t cmd);
void *kscrash_async_macho_find_segment_cmd (kscrash_async_macho_t *image, const char *segname);

kscrash_error_t kscrash_async_macho_map_segment (kscrash_async_macho_t *image, const char *segname, pl_async_macho_mapped_segment_t *seg);
kscrash_error_t kscrash_async_macho_map_section (kscrash_async_macho_t *image, const char *segname, const char *sectname, kscrash_async_mobject_t *mobj);

kscrash_error_t kscrash_async_macho_find_symbol_by_pc (kscrash_async_macho_t *image, pl_vm_address_t pc, pl_async_macho_found_symbol_cb symbol_cb, void *context);
kscrash_error_t kscrash_async_macho_find_symbol_by_name (kscrash_async_macho_t *image, const char *symbol, pl_vm_address_t *pc);

kscrash_error_t kscrash_async_macho_symtab_reader_init (kscrash_async_macho_symtab_reader_t *reader, kscrash_async_macho_t *image);
kscrash_async_macho_symtab_entry_t kscrash_async_macho_symtab_reader_read (kscrash_async_macho_symtab_reader_t *reader, void *symtab, uint32_t index);
const char *kscrash_async_macho_symtab_reader_symbol_name (kscrash_async_macho_symtab_reader_t *reader, uint32_t n_strx);
void kscrash_async_macho_symtab_reader_free (kscrash_async_macho_symtab_reader_t *reader);

void kscrash_async_macho_mapped_segment_free (pl_async_macho_mapped_segment_t *segment);

void kscrash_async_macho_free (kscrash_async_macho_t *image);

/**
 * @}
 */
    
#ifdef __cplusplus
}
#endif

#endif /* PLCRASH_ASYNC_MACHO_IMAGE_H */
