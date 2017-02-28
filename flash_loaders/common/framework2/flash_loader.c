//------------------------------------------------------------------------------
//
// Copyright (c) 2008-2015 IAR Systems
//
// Licensed under the Apache License, Version 2.0 (the "License")
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// $Revision: 39361 $
//
//------------------------------------------------------------------------------

// Wrapper for target-specific flash loader code

#include "flash_loader.h"
#include "flash_loader_extra.h"

#ifndef MAX_ARGS
#define MAX_ARGS 7
#endif

// Maximum combined size of arguments, including a trailing null for each argument.
#ifndef MAX_ARG_SIZE
#define MAX_ARG_SIZE 64
#endif

// Functions in this file, called from the assembly wrapper
void Fl2FlashInitEntry(void);
void Fl2FlashWriteEntry(void);
void Fl2FlashEraseWriteEntry(void);
void Fl2FlashChecksumEntry(void);
void Fl2FlashSignoffEntry(void);
void FlashBreak(void);

#if CODE_ADDR_AS_VOID_PTR
extern uint32_t FlashChecksum(void const *begin, uint32_t count);
#else
extern uint32_t FlashChecksum(uint32_t begin, uint32_t count);
#endif
extern uint32_t FlashSignoff();

uint16_t Crc16_helper(uint8_t const *p, uint32_t len, uint16_t sum);

// Flashloader framework version
__root const uint16_t frameworkVersion = 200;

__root __no_init FlashParamsHolder  theFlashParams;

__no_init int __argc;
__no_init char __argvbuf[MAX_ARG_SIZE];
#pragma required=__argvbuf
__no_init const char* __argv[MAX_ARGS];

#if CODE_ADDR_AS_VOID_PTR
#define CODE_REF void *
#else
#define CODE_REF uint32_t
#endif

void Fl2FlashInitEntry()
{
#if USE_ARGC_ARGV
  theFlashParams.count = FlashInit((CODE_REF)theFlashParams.base_ptr,
                                   theFlashParams.block_size,       // Image size
                                   theFlashParams.offset_into_block,// link adr
                                   theFlashParams.count,            // flags
                                   __argc,
                                   __argv);
#else
  theFlashParams.count = FlashInit((CODE_REF)theFlashParams.base_ptr,
                                   theFlashParams.block_size,       // Image size
                                   theFlashParams.offset_into_block,// link adr
                                   theFlashParams.count);           // flags
#endif
}

// The normal flash write function ----------------------------------------------
void Fl2FlashWriteEntry()
{
  theFlashParams.count = FlashWrite((CODE_REF)theFlashParams.base_ptr,
                                    theFlashParams.offset_into_block,
                                    theFlashParams.count,
                                    theFlashParams.buffer);
}

// The erase-first flash write function -----------------------------------------
void Fl2FlashEraseWriteEntry()
{
  uint32_t tmp = theFlashParams.block_size;
  if (tmp == 0)
  {
    FlashEraseData *p = (FlashEraseData*)theFlashParams.buffer;
    for (uint32_t i = 0; i < theFlashParams.count; ++i)
    {
      tmp = FlashErase((CODE_REF)p->start, p->length);
      if (tmp != 0) break;
      ++p;
    }
  }
  else
  {
    tmp = FlashErase((CODE_REF)theFlashParams.base_ptr,
                     theFlashParams.block_size);
    if (tmp == 0)
    {
      tmp = FlashWrite((CODE_REF)theFlashParams.base_ptr,
                       theFlashParams.offset_into_block,
                       theFlashParams.count,
                       theFlashParams.buffer);
    }
  }
  theFlashParams.count = tmp;
}


void Fl2FlashChecksumEntry()
{
  theFlashParams.count = FlashChecksum((CODE_REF)theFlashParams.base_ptr,
                                       theFlashParams.count);
}

void Fl2FlashSignoffEntry()
{
  theFlashParams.count = FlashSignoff();
}


uint16_t Crc16(uint8_t const *p, uint32_t len)
{
  uint8_t zero[2] = { 0, 0 };
  uint16_t sum = Crc16_helper(p, len, 0);
  return Crc16_helper(zero, 2, sum);
}

uint16_t Crc16_helper(uint8_t const *p, uint32_t len, uint16_t sum)
{
  while (len--)
  {
    int i;
    uint8_t byte = *p++;

    for (i = 0; i < 8; ++i)
    {
      uint32_t osum = sum;
      sum <<= 1;
      if (byte & 0x80)
        sum |= 1 ;
      if (osum & 0x8000)
        sum ^= 0x1021;
      byte <<= 1;
    }
  }
  return sum;
}

#pragma optimize=no_inline
__root void FlashBreak()
{
  while(1);
}
