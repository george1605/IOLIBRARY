#pragma once
#include "core.h"
#include "file.h"

namespace io
{
#define TTF_MAGIC 0x5F0F3CF5
	typedef struct _ttfHeader
	{
           uint32_t version;
           uint32_t fontRevision;
           uint32_t checkSum;
           uint32_t magic;
           uint16_t flags;
	} ttf_header;

	typedef struct _ttftable
	{

	} ttf_table;
}
