/*
 * circular_buffer.h
 *
 *  Created on: 25 Jun 2018
 *      Author: PeterGoddard
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

typedef struct
{
	uint8_t * p_buffer;
	uint8_t size;
	uint8_t in;
	uint8_t out;
	uint8_t count;
}
circular_buffer_t;

void initialise_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t * p_buffer, size_t size);
uint32_t put_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t value);
uint32_t get_circular_buffer(circular_buffer_t *p_circular_buffer, uint8_t * p_value);

#endif /* CIRCULAR_BUFFER_H_ */
