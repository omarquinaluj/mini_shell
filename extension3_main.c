/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension3_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:41:04 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/20 11:59:45 by alexander        ###   ########.fr       */
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
	temp4 = concat_strings(aux, "\033[1;35m");
	promptt = concat_strings("\033[1;32m", temp4);
	free(aux);
	free(temp4);
	return (promptt);
}
