#include "shell.h"

/**
 * **strtow - separates a string into words. delimeters repeated are ignored
 * @str: the input string
 * @d: the string delimeter
 * Return: a pointer that points an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, u, h, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, u = 0; u < numwords; u++)
	{
		while (is_delim(str[l], d))
			i++;
		h = 0;
		while (!is_delim(str[l + h], d) && str[l + h])
			h++;
		s[u] = malloc((h + 1) * sizeof(char));
		if (!s[u])
		{
			for (h = 0; h < u; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < h; b++)
			s[u][b] = str[l++];
		s[u][b] = 0;
	}
	s[u] = NULL;
	return (s);
}

/**
 * **strtow2 - separates a string into words
 * @str: the string input 
 * @d: the delimeter
 * Return: a pointer that points to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int l, u, h, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
				    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (l = 0, u = 0; u < numwords; u++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		h = 0;
		while (str[l + h] != d && str[l + h] && str[l + h] != d)
			h++;
		s[u] = malloc((h + 1) * sizeof(char));
		if (!s[h])
		{
			for (h = 0; h < u; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < h; b++)
			s[u][b] = str[l++];
		s[u][b] = 0;
	}
	s[u] = NULL;
	return (s);
}
