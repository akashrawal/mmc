/* msg.c
 * Standard message format
 * 
 * Copyright 2015-2018 Akash Rawal
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

mdsl_rc_define(MmcMsg, mmc_msg);

static void mmc_msg_init(MmcMsg *msg, void *mem, size_t mem_len, 
	MmcFreeFn mem_free, size_t submsgs_len)
{
	int i;
	
	mdsl_rc_init(msg);
	
	msg->mem = mem;
	msg->mem_len = mem_len;
	msg->mem_free = mem_free;
	msg->submsgs_len = submsgs_len;
	
	for (i = 0; i < submsgs_len; i++)
	{
		msg->submsgs[i] = NULL;
	}
}

MmcMsg *mmc_msg_new
	(size_t mem_len, MmcFreeFn mem_free, void *mem, size_t submsgs_len)
{
	MmcMsg *msg;
	
	{
		size_t this_len 
			= sizeof(MmcMsg) + (sizeof(void *) * submsgs_len);
		msg = mdsl_alloc(this_len);
	}
	
	mmc_msg_init(msg, mem, mem_len, mem_free, submsgs_len);
	
	return msg;
}

MmcMsg *mmc_msg_newa(size_t mem_len, size_t submsgs_len)
{
	MmcMsg *msg;
	void *mem;
	
	{
		size_t this_len 
			= sizeof(MmcMsg) + (sizeof(void *) * submsgs_len);
		if (mem_len > 0)
			msg = mdsl_alloc2(this_len, mem_len, &mem);
		else
		{
			msg = mdsl_alloc(this_len);
			mem = NULL;
		}
	}
	
	mmc_msg_init(msg, mem, mem_len, NULL, submsgs_len);
	
	return msg;
}

MmcMsg *mmc_msg_try_new
	(size_t mem_len, MmcFreeFn mem_free, void *mem, size_t submsgs_len)
{
	MmcMsg *msg;
	
	{
		size_t this_len 
			= sizeof(MmcMsg) + (sizeof(void *) * submsgs_len);
		msg = mdsl_tryalloc(this_len);
		if (! msg)
			return NULL;
	}
	
	mmc_msg_init(msg, mem, mem_len, mem_free, submsgs_len);
	
	return msg;
}

MmcMsg *mmc_msg_try_newa(size_t mem_len, size_t submsgs_len)
{
	MmcMsg *msg;
	void *mem;
	
	{
		size_t this_len 
			= sizeof(MmcMsg) + (sizeof(void *) * submsgs_len);
		if (mem_len > 0)
			msg = mdsl_tryalloc2(this_len, mem_len, &mem);
		else
		{
			msg = mdsl_tryalloc(this_len);
			mem = NULL;
		}
		if (! msg)
			return NULL;
	}
	
	mmc_msg_init(msg, mem, mem_len, NULL, submsgs_len);
	
	return msg;
}

static void mmc_msg_destroy(MmcMsg *msg)
{
	int i;
	
	if (msg->mem_free)
		(* msg->mem_free) (msg->mem);
	
	for (i = 0; i < msg->submsgs_len; i++)
	{
		if (msg->submsgs[i])
			mmc_msg_unref(msg->submsgs[i]);
	}
	
	free(msg);
}

ssize_t mmc_msg_compare(MmcMsg *a, MmcMsg *b)
{
	ssize_t compres;
	size_t i;

	compres = a->mem_len - b->mem_len;
	if (compres != 0)
		return compres;
	compres = a->submsgs_len - b->submsgs_len;
	if (compres != 0)
		return compres;
	compres = memcmp(a->mem, b->mem, a->mem_len);
	if (compres != 0)
		return compres;
	for (i = 0; i < a->submsgs_len; i++)
	{
		compres = mmc_msg_compare(a->submsgs[i], b->submsgs[i]);
		if (compres != 0)
			return compres;
	}
	return 0;
}
