/* Microsoft Reference Implementation for TPM 2.0
 *
 *  The copyright in this software is being made available under the BSD License,
 *  included below. This software may be subject to other third party and
 *  contributor rights, including patent rights, and no such rights are granted
 *  under this license.
 *
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  BSD License
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this list
 *  of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or other
 *  materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ""AS IS""
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//** NV HOOKs allow for implementations of custom extensions
//   using standard NV read and writes

#ifndef    _NVHOOK_H_
#define    _NVHOOK_H_

#ifdef ENABLE_NV_HOOK

// Defines the base NV index that can have an associated hook defined.
// Each hook defined in NV_HOOK_TABLE is an offset from this index.
#define NV_HOOKBASE_INDEX (0x00008000)

// Max number of NV slots that can be associated with a hook callback.
#define NV_HOOK_MAX_SLOTS 255

// Write/Read callback definitions.
typedef TPM_RC(*NvHook)(
        uint32_t index,
        uint8_t* data,
        uint32_t size,
        uint32_t offset);

// Defines a Read/Write hook over a span of NV index
typedef struct {
    UINT16          nvIndexSpan;    // Number of indices this hook applies too.
    NvHook          nvWrite;        // Optional Write callback, executed on NVWrite to an index
                                    // in this span.
    NvHook          nvRead;         // Optional Read callback, , executed on NVRead to an index
                                    // in this span.
} NV_HOOK_ENTRY, *PNV_HOOK_ENTRY;

typedef struct {
    UINT16          nvIndexMax;    // Highest ordered index in this table. Base zero.
    UINT16          entryCount;    // Number of entries in this table.
    PNV_HOOK_ENTRY  entry;         // Flat array of entries. The first entry starts at NV_HOOKBASE_INDEX
} NV_HOOK_TABLE, *PNV_HOOK_TABLE;


#endif // ENABLE_NV_HOOK

#endif  // _NVHOOK_H_
