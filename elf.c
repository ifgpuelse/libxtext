/* libelf - A portable C library for manage ELF files
    Copyright (C) <2022>  <Gabriel Correia>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#if defined(__unix__)
#define _GNU_SOURCE

#include <errno.h>

#endif

#include <libelf/elf.h>

elf_err_e elf_load_file(elf_ctx_t *elf_ctx, const char *elf_path_name)
{
    assert(elf_ctx != NULL);

    memset(elf_ctx, 0, sizeof(elf_ctx_t));

    if (elf_path_name == NULL)
        return LOAD_FILE_ERROR;
    
    elf_ctx->elf_name = strdup(elf_path_name);

    const FILE *local_file_ptr = elf_ctx->elf_file_ptr = fopen(elf_path_name, "rb");

    if (local_file_ptr == NULL)
    {
#if defined(__unix__)
        elf_ctx->error_record = strerror(errno);
#endif
        return LOAD_FILE_ERROR;
    }

    return ELF_OK;

}

elf_err_e elf_unload(elf_ctx_t *elf_ctx)
{
    assert(elf_ctx);

    FILE *local_file_ptr = elf_ctx->elf_file_ptr;

    if (local_file_ptr == NULL)
        return UNLOAD_FILE_ERROR;
    
    free((char*)elf_ctx->elf_name);
    
    fclose(local_file_ptr);

    memset(elf_ctx, 0, sizeof(elf_ctx_t));

    return ELF_OK;

}

