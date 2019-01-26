/* incl.h
 * Includes
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

//TODO: Decide the includes in API headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

#include <mdsl/mdsl.h>

//Logging macros
#define mmc_error(...) mdsl_context_error("MMC", __VA_ARGS__)
#define mmc_warn(...) mdsl_context_warn("MMC", __VA_ARGS__)
#define mmc_debug(...) mdsl_context_debug("MMC", __VA_ARGS__)
#define mmc_assert(expr, ...) mdsl_context_assert("MMC", expr, __VA_ARGS__)

//Include all modules in dependency-based order
#include "msg.h"


