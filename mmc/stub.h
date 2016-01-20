/* stub.h
 * Convenience interface for stubs and skeletons
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

//Interface for client side stubs (prefered, not mandatory to follow)
typedef MmcMsg * (*MmcStubCreateMsg) (void *args);
typedef int (*MmcStubReadReply) (MmcMsg *reply_msg, void *out_args);

typedef struct
{
	MmcStubCreateMsg create_msg;
	MmcStubReadReply read_reply;
} MmcStubSpec;

//Interface for object side reply function 
//(prefered but not mandatory to follow)
typedef MmcMsg * (*MmcCreateReplyFn) (void *out_args);

