/*
 * circular_buffer.c
 *
 *  Created on: 25 Jun 2018
 *      Author: PeterGoddard
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "circular_buffer.h"

static uint32_t is_full(circular_buffer_t *p_circular_buffer);
static uint32_t is_empty(circular_buffer_t *p_circular_buffer);

/* Public APIs */

void initialise_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t * p_buffer, size_t size)
{
	assert(p_circular_buffer);
	assert(p_buffer);

	for(uint8_t loop=0;loop<size;loop++)
	{
		p_buffer[loop] = 0;
	}

	p_circular_buffer->p_buffer = p_buffer;
	p_circular_buffer->size = size;
	p_circular_buffer->in = 0;
	p_circular_buffer->out = 0;
	p_circular_buffer->count = 0;
}

uint32_t put_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t value)
{
	uint32_t put_error_flag = 0;

	assert(p_circular_buffer);
	assert(p_circular_buffer->p_buffer);

	if( is_full(p_circular_buffer) )
	{
		put_error_flag = 1;
	}
	else
	{
		p_circular_buffer->p_buffer[p_circular_buffer->in] = value;
		p_circular_buffer->in = (p_circular_buffer->in + 1) % p_circular_buffer->size;
		p_circular_buffer->count++;
		put_error_flag = 0;
	}

	return put_error_flag;
}

uint32_t get_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t * p_value)
{
	uint32_t get_error_flag = 0;

	assert(p_circular_buffer);
	assert(p_circular_buffer->p_buffer);

	if( is_empty(p_circular_buffer) )
	{
		get_error_flag = 1;
	}
	else
	{
		*p_value = p_circular_buffer->p_buffer[p_circular_buffer->out];
		p_circular_buffer->out = (p_circular_buffer->out + 1) % p_circular_buffer->size;
		p_circular_buffer->count--;

		get_error_flag = 0;
	}

	return get_error_flag;
}

/* Private APIs */
static uint32_t is_full(circular_buffer_t *p_circular_buffer)
{
	uint32_t full_flag = 0;

	if( p_circular_buffer->count >= p_circular_buffer->size)
	{
		full_flag = 1;
	}

	return full_flag;
}

static uint32_t is_empty(circular_buffer_t *p_circular_buffer)
{
	uint32_t empty_flag = 0;

    if(p_circular_buffer->in == p_circular_buffer->out)
    {
        empty_flag = 1;
    }

    return(empty_flag);
}
