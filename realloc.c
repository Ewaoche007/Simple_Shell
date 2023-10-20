#include "shell.h"

/**
 * _memset - fits a constant byte in memory
 * @s: points to the memory area
 * @b: a byte to fill *s with
 * @n: an amount of bytes to fill
 * Return: (s) a pointer to s memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int l;

	for (l = 0; l < n; l++)
		s[l] = b;
	return (s);
}

/**
 * ffree - free up a string of strings
 * @pp: string of the strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - to reallocate the block of memory
 * @ptr: points to previous malloc'ated block
 * @old_size: a byte size of previous block
 * @new_size: a byte size of new block
 *
 * Return: pointer of da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
