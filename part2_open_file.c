/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2_open_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:58:57 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/14 18:58:59 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_validate_directory(char *path, t_shell *shell)
{
    struct stat sb;

    if (stat(path, &sb) == -1)
    {
        if (errno == ENOENT)
        {
            perror(path);
        }
		shell->exit_status = 1;
		return (-1);
	}
    return (0);
}
