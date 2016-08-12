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


#include "incl.h"

//Abstract class MPContext:

MmcMPContext *mmc_mp_context_create
    (size_t struct_size, MmcMPContextReplyFn reply_fn)
{
    MmcMPContext *ctx;
    
    if (struct_size < sizeof(MmcMPContext))
        mmc_error("struct_size should be atleast sizeof(MmcMPContext)");
    
    ctx = (MmcMPContext *) mmc_alloc(struct_size);
    
    ctx->reply_fn = reply_fn;
    
    return ctx;
}

//Virtual function to send reply back
void mmc_mp_context_reply
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
    MmcServantHandleMsgFn handle_msg, MmcServantDestroyFn destroy)
{
    MmcServant *servant;
    
    if (struct_size < sizeof(MmcServant))
        mmc_error("struct_size should be atleast MmcServant");
    
    servant = (MmcServant *) mmc_alloc(struct_size);
    
    mmc_rc_init(servant);
    servant->handle_msg = handle_msg;
    servant->destroy = destroy;
    
    return servant;
}
    
//Virtual function to deliver message to servant
void mmc_servant_handle_msg
    (MmcServant *servant, MmcMsg *msg, MmcMPContext *ctx)
{
    (*servant->handle_msg) (servant, msg, ctx);
}

//Destructor
void mmc_servant_destroy(MmcServant *servant)
{
    (* servant->destroy)(servant);
    
    free(servant);
}



