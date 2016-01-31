/* utils.h
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

/**
 * \addtogroup mmc_utils
 * \{
 * 
 * This section documents a collection of important utility functions.
 */
 
//Failable operations
typedef enum
{
	MMC_SUCCESS = 0,
	MMC_FAILURE = -1
} MmcStatus;

//Adds integer to pointer
#define MMC_PTR_ADD(ptr, bytes) ((void *) (((int8_t *) (ptr)) + (bytes)))

#define mmc_encl_struct(ptr, type, member) \
	((type *) (MMC_PTR_ADD((ptr), -(offsetof(type, member)))))

//Pointer casting macros
#define MMC_UINT_TO_PTR(v) MMC_INT_TO_PTR(v))
#define MMC_UINT16_TO_PTR(v) MMC_INT16_TO_PTR(v)
#define MMC_UINT32_TO_PTR(v) MMC_INT32_TO_PTR(v)

#define MMC_PTR_TO_UINT(v) ((unsigned int) MMC_PTR_TO_INT(v))
#define MMC_PTR_TO_UINT16(v) ((uint16_t) MMC_PTR_TO_INT16(v))
#define MMC_PTR_TO_UINT32(v) ((uint32_t) MMC_PTR_TO_INT32(v))

#define MMC_VAR_ARRAY_SIZE 2

//Errors
#ifdef __GNUC__

#define mmc_context_error(context, ...) \
	do { \
		fprintf(stderr, context ": %s: %s:%d: ERROR:", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		mmc_warn_break(1); \
	} while (0)

#define mmc_context_warn(context, ...) \
	do { \
		fprintf(stderr, context ": %s: %s:%d: WARNING:", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		mmc_warn_break(0); \
	} while (0)

#else

#define mmc_context_error(context, ...) \
	do { \
		fprintf(stderr, context ": %s:%d: ERROR:", __FILE__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		mmc_warn_break(1); \
	} while (0)

#define mmc_context_warn(context, ...) \
	do { \
		fprintf(stderr, context ": %s:%d: WARNING:", __FILE__, __LINE__); \
		fprintf(stderr, __VA_ARGS__); \
		fprintf(stderr, "\n"); \
		mmc_warn_break(0); \
	} while (0)

#endif	

#define mmc_error(...) mmc_context_error("MMC", __VA_ARGS__)
#define mmc_warn(...) mmc_context_error("MMC", __VA_ARGS__)

/**If you want to break at an error or warning from Modular Middleware
 * use debugger to break at this function.
 * 
 * \param to_abort In case of error its value is 1, else it is 0.
 */
void mmc_warn_break(int to_abort);

//Allocation
#define mmc_tryalloc malloc
#define mmc_tryrealloc realloc

/**Allocates memory of size bytes. 
 * If memory allocation fails the program is aborted.
 * 
 * This function uses malloc() internally.
 * \param size Number of bytes to allocate
 * \return Newly allocated memory, free with free()
 */
void *mmc_alloc(size_t size);

/**Reallocates memory old_mem to size bytes. 
 * If memory allocation fails program is aborted.
 * 
 * This function uses realloc() internally.
 * \param old_mem Original memory to resize
 * \param size Number of bytes to allocate
 * \return Newly allocated memory, free with free()
 */
void *mmc_realloc(void *old_mem, size_t size);

/**Allocates two memory blocks of size1 and size2 bytes. 
 * If memory allocation fails the program is aborted.
 * 
 * \param size1 Number of bytes to allocate for first memory block
 * \param size2 Number of bytes to allocate for second memory block
 * \param mem2_return Return location for second memory block
 * \return First memory block, free with free() to free both memory blocks.
 */
void *mmc_alloc2(size_t size1, size_t size2, void **mem2_return);

/**Allocates two memory blocks of size1 and size2 bytes. 
 * If memory allocation fails NULL is returned and mem2_return 
 * argument is unmodified.
 * \param size1 Number of bytes to allocate for first memory block
 * \param size2 Number of bytes to allocate for second memory block
 * \param mem2_return Return location for second memory block
 * \return First memory block, free with free() to free both memory blocks.
 */
void *mmc_tryalloc2(size_t size1, size_t size2, void **mem2_return);

#define mmc_new(type) ((type *) mmc_alloc(sizeof(type)))

//LATER: Check if this is correct
#define mmc_alloc_boundary (2 * sizeof(void *))

#define mmc_offset_align(offset) \
	(((offset) + mmc_alloc_boundary - 1) \
	- (((offset) + mmc_alloc_boundary - 1) % mmc_alloc_boundary))

/**Allocates a new memory and copies the given string into it.
 * If memory allocation fails the program is aborted.
 * 
 * \param str the string to copy
 * \return Newly allocated string. free with free().
 */
char *mmc_strdup(const char *str);

/**Allocates a new memory, copies the contents of _mem_ and returns it.
 * If memory allocation fails the program is aborted.
 * 
 * \param mem The memory to be copied
 * \param len The number of bytes to be copied
 * \return newly allocated memory containing the data from _mem_,
 *         free with free().
 */
void *mmc_memdup(const void *mem, size_t len);

//Template code for reference counting
typedef struct 
{
	int refcount;
} MmcRC;

#define mmc_rc_declare(TypeName, type_name) \
	void type_name ## _ref(TypeName *object); \
	void type_name ## _unref(TypeName *object); \
	int type_name ## _get_refcount(TypeName *object);

#define mmc_rc_define(TypeName, type_name) \
	static void type_name ## _destroy(TypeName *object); \
	void type_name ## _ref(TypeName *object) \
	{ \
		MmcRC *x = (MmcRC *) object; \
		 \
		x->refcount++; \
	} \
	void type_name ## _unref(TypeName *object) \
	{ \
		MmcRC *x = (MmcRC *) object; \
		 \
		x->refcount--; \
		if (x->refcount <= 0) \
		{ \
			type_name ## _destroy(object); \
		} \
	} \
	int type_name ## _get_refcount(TypeName *object) \
	{ \
		MmcRC *x = (MmcRC *) object; \
		 \
		return x->refcount; \
	}

#define mmc_rc_init(object) \
	do { \
		MmcRC *x = (MmcRC *) object; \
		x->refcount = 1; \
	} while (0)

/**
 * \}
 */
