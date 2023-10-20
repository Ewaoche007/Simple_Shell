#include "shell.h"

/**
 **_strncpy - to copy a string
 *@dest: string destination to be copied
 *@src: source of the string
 *@n: for number of char to be copied
 *Return: string concentrated
 */
char *_strncpy(char *dest, char *src, int n)
{
	int l, k;
	char *s = dest;

	l = 0;
	while (src[l] != '\0' && l < n - 1)
	{
		dest[l] = src[l];
		l++;
	}
	if (l < n)
	{
		k = l;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - to focus on two strings
 *@dest: the initial string
 *@src: secondary string
 *@n: num of bytes to copy
 *Return: string concat
 */
char *_strncat(char *dest, char *src, int n)
{
	int l, k;
	char *s = dest;

	l = 0;
	k = 0;
	while (dest[l] != '\0')
		l++;
	while (src[k] != '\0' && k < n)
	{
		dest[l] = src[k];
		l++;
		k++;
	}
	if (k < n)
		dest[l] = '\0';
	return (s);
}

/**
 **_strchr - find char to the string
 *@s: string to pass
 *@c: char to find
 *Return: (s) the pointer that points to memory s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
