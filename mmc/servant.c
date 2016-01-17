/* servant.c
 * Interface for servants
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


#include "servant.h"

//Abstract class MPContext:

MmcMPContext *mmc_mp_context_create
	(size_t struct_size, MmcMPContextReplyFn reply_fn)
{
	MmcMPContext *ctx;
	
	if (struct_size < sizeof(MmcMPContext))
		mmc_error("struct_size should be atleast sizeof(MmcMPContext)");
	
	ctx = (MmcMPContext *) mmc_alloc(struct_size);
	
	ctx->reply_fn = reply_fn;
	ctx->create_reply_fn = NULL;
	
	return ctx;
}

//Virtual function to send reply back
void mmc_mp_context_reply_msg
	(MmcMPContext *ctx, MmcMsg *reply_msg)
{
	(*ctx->reply_fn)(ctx, reply_msg);
	free(ctx);
}


//Abstract class Servant:

//Reference counting
mmc_rc_define(MmcServant, mmc_servant)

//Base class constructor
MmcServant *mmc_servant_create
	(size_t struct_size, 
	MmcServantDispatchFn dispatch, MmcServantDestroyFn destroy)
{
	MmcServant *servant;
	
	if (struct_size < sizeof(MmcServant))
		mmc_error("struct_size should be atleast MmcServant");
	
	servant = (MmcServant *) mmc_alloc(struct_size);
	
	mmc_rc_init(servant);
	servant->dispatch = dispatch;
	servant->destroy = destroy;
	
	return servant;
}
	
//Virtual function to deliver message to servant
int mmc_servant_dispatch
	(MmcServant *servant, MmcMsg *args_msg, MmcMPContext *ctx)
{
	return (*servant->dispatch) (servant, args_msg, ctx);
}

//Destructor
void mmc_servant_destroy(MmcServant *servant)
{
	(* servant->destroy)(servant);
	
	free(servant);
}

//Managed serialization
void mmc_mp_context_reply
	(MmcMPContext *ctx, void *out_args)
{
	MmcMsg *reply_msg;
	
	reply_msg = (*ctx->create_reply_fn) (out_args);
	mmc_mp_context_reply_msg(ctx, reply_msg);
	mmc_msg_unref(reply_msg);
}

