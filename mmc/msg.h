/* msg.h
 * Standard message format
 * 
 * Copyright 2015-2020 Akash Rawal
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

//TODO: Documentation

typedef struct _MmcMsg MmcMsg;

typedef void (*MmcFreeFn)(void *mem);

struct _MmcMsg
{
	MdslRC parent;
	size_t mem_len;
	MmcFreeFn mem_free;
	void *mem;
	size_t submsgs_len;
	MmcMsg *submsgs[];
};

mdsl_rc_declare(MmcMsg, mmc_msg);

MmcMsg *mmc_msg_new
	(size_t mem_len, MmcFreeFn mem_free, void *mem, size_t submsgs_len);

MmcMsg *mmc_msg_newa(size_t mem_len, size_t submsgs_len);

MmcMsg *mmc_msg_try_new
	(size_t mem_len, MmcFreeFn mem_free, void *mem, size_t submsgs_len);

MmcMsg *mmc_msg_try_newa(size_t mem_len, size_t submsgs_len);

ssize_t mmc_msg_compare(MmcMsg *a, MmcMsg *b);
