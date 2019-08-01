/* iface.h
 * Standard interfaces
 * 
 * Copyright 2015-2019 Akash Rawal
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

mdsl_rc_define(MmcResponder, mmc_responder);

static void mmc_responder_destroy(MmcResponder *responder)
{
	(*responder->destroy)(responder);
}

void mmc_responder_call(MmcResponder *responder, MmcMsg *msg)
{
	(*responder->call)(responder, msg);
}


mdsl_rc_define(MmcServant, mmc_servant);

static void mmc_servant_destroy(MmcServant *servant)
{
	(*servant->destroy)(servant);
}

void mmc_servant_call
	(MmcServant *servant, MmcMsg *msg, MmcResponder *responder)
{
	(*servant->call)(servant, msg, responder);
}
