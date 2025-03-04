#include "mini_shell.h"

bool	is_invalid_redirection(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space((unsigned char)line[i]))
		i++;
	if (line[i] == '<' || line[i] == '>')
	{
		while (line[i] == '<' || line[i] == '>')
			i++;
		while (line[i] && is_space((unsigned char)line[i]))
			i++;
		if (line[i] == '\0')
			return (true);
	}
	return (false);
}
