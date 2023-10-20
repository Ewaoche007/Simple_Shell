#include "shell.h"

/**
 * is_chain - to see if current char in delimeter is chain
 * @info: structure of the parameter
 * @buf: buffer of a char
 * @p: position location in buff
 *
 * Return: 1 if it is chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t u = *p;

	if (buf[u] == '|' && buf[u + 1] == '|')
	{
		buf[u] = 0;
		u++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[u] == '&' && buf[u + 1] == '&')
	{
		buf[u] = 0;
		u++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[u] == ';') /* found end of this command */
	{
		buf[u] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = u;
	return (1);
}

/**
 * check_chain - checks if chaining continues based on last status
 * @info: it is parameter struct
 * @buf: character buffer
 * @p: current position location in buff
 * @i: position to start in buff
 * @len: buffer length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t u = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			u = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			u = len;
		}
	}

	*p = u;
}

/**
 * replace_alias - maent replaces a aliases in the tokenized string
 * @info: struct of the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int l;
	list_t *node;
	char *p;

	for (l = 0; l < 10; l++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - to replace the tokenized strings vars
 * @info: struct of the parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int l = 0;
	list_t *node;

	for (l = 0; info->argv[l]; l++)
	{
		if (info->argv[l][0] != '$' || !info->argv[l][1])
			continue;

		if (!_strcmp(info->argv[l], "$?"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[l], "$$"))
		{
			replace_string(&(info->argv[l]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[l][1], '=');
		if (node)
		{
			replace_string(&(info->argv[l]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[l], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - string replacement
 * @old: old string location
 * @new: fresh string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
