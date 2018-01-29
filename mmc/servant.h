/* servant.h
 * Interface for servants
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

//Forward declarations
typedef struct _MmcMPContext MmcMPContext;
typedef struct _MmcServant MmcServant;

//Abstract class MPContext:
	//Base class for contextual information for current message passing
	//operation. 
	//Inherited in network module code
	//to provide add-on information like sender's identity.
	typedef void (*MmcMPContextReplyFn)
		(MmcMPContext *ctx, MmcMsg *reply_msg);
	struct _MmcMPContext
	{
		MmcMPContextReplyFn reply_fn;
	};

	//Base class constructor
	MmcMPContext *mmc_mp_context_create
		(size_t struct_size, MmcMPContextReplyFn reply_fn);

	//Virtual function to send reply back
	void mmc_mp_context_reply
		(MmcMPContext *ctx, MmcMsg *reply_msg);


//Abstract class Servant:
	//Base class for the servant. Compulsory. 
	//Inherited in serialization and then user code to provide message passing 
	//interface abstraction to network module
	typedef void (* MmcServantHandleMsgFn) 
		(MmcServant *servant, MmcMsg *msg, MmcMPContext *ctx);
	typedef void (*MmcServantDestroyFn) (MmcServant *servant);
	struct _MmcServant
	{
		MmcRC parent;
		//Does whatever should happen message has been received.
		MmcServantHandleMsgFn handle_msg;
		//Destructor
		MmcServantDestroyFn destroy;
	};

	//Base class constructor
	MmcServant *mmc_servant_create
		(size_t struct_size, 
		MmcServantHandleMsgFn handle_msg, MmcServantDestroyFn destroy);
		
	//Virtual function to deliver message to servant
	void mmc_servant_handle_msg
		(MmcServant *servant, MmcMsg *msg, MmcMPContext *ctx);
	
	mmc_rc_declare(MmcServant, mmc_servant);

