#include "shell.h"

/**
 * interactive -to return true if a shell is in its interactive mode
 * @info: for the struct address
 *
 * Return: 1 if it is in its interactive mode, 0 for otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - to check if a char is a delimeter
 * @w: the char that is to be checked
 * @delim: a delimeter of the string
 * Return: 1 if is true, 0 if it is false
 */
int is_delim(char w, char *delim)
{
	while (*delim)
		if (*delim++ == w)
			return (1);
	return (0);
}

/**
 * _isalpha - is to check for the alphabetic char
 * @k: The char to input
 * Return: 1 for if c is alphabetic, 0 otherwise
 */

int _isalpha(int k)
{
	if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - it is to convert a string to integer
 * @s: a string that is to be converted
 * Return: 0 if no num in the string, convert the num otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
