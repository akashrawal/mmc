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

//TODO: Documentation

typedef struct _MmcResponder MmcResponder;
struct _MmcResponder
{
	MdslRC parent;	

	void (*destroy)();
	void (*call)(MmcResponder *responder, MmcMsg *msg);
};

mdsl_rc_declare(MmcResponder, mmc_responder);

void mmc_responder_call(MmcResponder *responder, MmcMsg *msg);


typedef struct _MmcServant MmcServant;
struct _MmcServant
{
	MdslRC parent;	

	void (*destroy)();
	void (*call)
		(MmcServant *servant, MmcMsg *msg, MmcResponder *responder);
};

mdsl_rc_declare(MmcServant, mmc_servant);

void mmc_servant_call
	(MmcServant *servant, MmcMsg *msg, MmcResponder *responder);


