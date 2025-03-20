/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/20 11:59:27 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_cmd	*init_cmds(char **tokens)
{
	t_cmd	*cmds;
	size_t	start;
	size_t	i;

	cmds = NULL;
	start = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			add_cmd(&cmds, new_cmd(tokens, start, i));
			start = i + 1;
		}
		i++;
	}
	if (tokens[start])
		add_cmd(&cmds, new_cmd(tokens, start, i));
	if (cmds && cmds->next)
		cmds_has_pipes(cmds);
	return (cmds);
}

t_env	*init_envs(char **envp)
{
	t_env	*env;
	char	*name;
	size_t	i;
	char	path[1024];

	env = NULL;
	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '=')
			i++;
		name = ft_substr(*envp, 0, i);
		set_env(&env, name, ft_strdup(getenv(name)));
		free(name);
		envp++;
	}
	set_env(&env, "?", ft_strdup("0"));
	if (getcwd(path, 1024))
		set_env(&env, "PWD", ft_strdup(path));
	return (env);
}

char	*expand_variable_2(const char *input)
{
	size_t	len;
	char	*var_name;
	char	*value;
	char	*result;

	if (!input || strlen(input) < 4 || input[0] != '$' || input[1] != '('
		|| input[strlen(input) - 1] != ')')
		return (NULL);
	len = strlen(input) - 3;
	var_name = (char *)malloc(len + 1);
	if (!var_name)
		return (NULL);
	strncpy(var_name, input + 2, len);
	var_name[len] = '\0';
	value = getenv(var_name);
	free(var_name);
	if (value)
	{
		result = (char *)malloc(strlen(value) + 1);
		if (result)
			strcpy(result, value);
		return (result);
	}
	return (NULL);
}

void	funtion_perror(char *txt, char **buffer, int fd)
{
	perror(txt);
	free(*buffer);
	close(fd);
}

char	*read_hostname_file(int fd, char **buffer,
			ssize_t *buffer_size, ssize_t *total_read)
{
	ssize_t	bytes_read;
	char	*new_buffer;

	bytes_read = read(fd, *buffer + *total_read,
			*buffer_size - *total_read - 1);
	while (bytes_read > 0)
	{
		*total_read += bytes_read;
		if (*total_read >= *buffer_size - 1)
		{
			*buffer_size *= 2;
			new_buffer = (char *)realloc(*buffer, *buffer_size);
			if (!new_buffer)
				return (funtion_perror("Error al reasignar memoria",
						buffer, fd), NULL);
			*buffer = new_buffer;
		}
		bytes_read = read(fd, *buffer + *total_read,
				*buffer_size - *total_read - 1);
	}
	if (bytes_read < 0)
		return (funtion_perror("Error al leer /etc/hostname",
				buffer, fd), NULL);
	return (*buffer);
}
