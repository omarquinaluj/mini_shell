/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension3_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/04/02 09:49:11 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*funtion_prompt(void)
{
	char	*userr;
	char	*hostnamee;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	userr = expand_variable_2("$(USER)");
	hostnamee = get_hostname();
	temp1 = concat_strings(userr, "@");
	temp2 = concat_strings(temp1, hostnamee);
	temp3 = concat_strings(temp2, ":~$ ");
	free(temp1);
	free(temp2);
	free(userr);
	free(hostnamee);
	return (temp3);
}

void	funtion_my_free(char *promptt, char *line)
{
	free(promptt);
	free(line);
}

char	*funtion_aux2(void)
{
	char	*aux;
	char	*temp4;
	char	*promptt;

	aux = funtion_prompt();
	temp4 = concat_strings(aux, "\001\033[1;35m\002");
	promptt = concat_strings("\001\033[1;32m\002", temp4);
	free(aux);
	free(temp4);
	return (promptt);
}

char	*ft_dup_line(const char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	while (*str == ' ')
		str++;
	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	ft_compared(char *line)
{
	int	i;

	i = 0;
	if (line && (line[0] == ' '))
	{
		while (line[i] != '\0')
		{
			if (line[i] == '<')
			{
				if (line[i++])
					return (1);
			}
			i++;
		}
	}
	return (0);
}
