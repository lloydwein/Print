#include "main.h"

/**
 * _memcpy - Copies n bytes from memory area src to
 *           the buffer contained in a buffer_t struct.
 * @dest: A buffer_t struct.
 * @source: A pointer to the memory area to copy.
 * @num_byte: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int _memcpy(buffer_t *dest, const char *source, unsigned int num_byte)
{
	unsigned int index;

	for (index = 0; index < num_byte; index++)
	{
		*(dest->buffer) = *(source + index);
		(dest->len)++;

		if (dest->len == 1024)
		{
			write(1, dest->start, dest->len);
			dest->buffer = dest->start;
			dest->len = 0;
		}

		else
			(dest->buffer)++;
	}

	return (num_byte);
}

/**
 * init_buffer - Initializes a variable of struct type buffer_t.
 *
 * Return: A pointer to the initialized buffer_t.
 */
buffer_t *init_buffer(void)
{
	buffer_t *dest;

	dest = malloc(sizeof(char) * 1024);
	if (dest == NULL)
		return (NULL);

	dest->buffer = malloc(sizeof(char) * 1024);
	if (dest->buffer == NULL)
	{
		free(dest);
		return (NULL);
	}

	dest->start = dest->buffer;
	dest->len = 0;

	return (dest);
}

/**
 * free_buffer - Frees a buffer_t struct.
 * @dest: The buffer_t struct to be freed.
 */
void free_buffer(buffer_t *dest)
{
	free(dest->start);
	free(dest);
}
