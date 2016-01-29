/* utils.c
 * Internal utilities
 * 
 * Copyright 2015 Akash Rawal
 * This file is part of Modular Middleware.
 * 
 * Modular Middleware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Modular Middleware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Modular Middleware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "incl.h"

//If you want to break at an error or warning break at this function.
void mmc_warn_break(int to_abort)
{
	if (to_abort)
		abort();
}

//Memory allocation functions
void *mmc_alloc(size_t size)
{
	void *mem = mmc_tryalloc(size);
	if (! mem)
	{
		mmc_error("Cannot allocate memory of %d bytes", (int) size);
	}
	return mem;
}

void *mmc_realloc(void *old_mem, size_t size)
{
	void *mem = mmc_tryrealloc(old_mem, size);
	if (! mem)
	{
		mmc_error("Cannot allocate memory of %d bytes", (int) size);
	}
	return mem;
}

void *mmc_alloc2(size_t size1, size_t size2, void **mem2_return)
{
	void *mem1;
	
	//mem2 must be aligned to size of two pointers.
	//Adjust size1 for that.
	size1 = mmc_offset_align(size1);
	
	//Now allocate
	mem1 = mmc_tryalloc(size1 + size2);
	if (! mem1)
	{
		mmc_error("Cannot allocate memory of %d bytes", (int) (size1 + size2));
	}
	
	*mem2_return = MMC_PTR_ADD(mem1, size1);
	return mem1;
}

void *mmc_tryalloc2(size_t size1, size_t size2, void **mem2_return)
{
	void *mem1;
	
	//mem2 must be aligned to size of two pointers.
	//Adjust size1 for that.
	size1 = mmc_offset_align(size1);
	
	//Now allocate
	mem1 = mmc_tryalloc(size1 + size2);
	if (! mem1)
	{
		return NULL;
	}
	
	*mem2_return = MMC_PTR_ADD(mem1, size1);
	return mem1;
}

char *mmc_strdup(const char *str)
{
	char *res = strdup(str);
	if (!res)
	{
		mmc_error("Memory allocation failed.");
	}
	return res;
}

void *mmc_memdup(const void *mem, size_t len)
{
	void *res = mmc_alloc(len);
	memcpy(res, mem, len);
	return res;
}
