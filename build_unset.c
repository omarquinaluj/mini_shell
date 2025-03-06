#include "mini_shell.h"

int	builtin_unset(t_cmd *cmd, t_env **envs)
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!remove_env(envs, cmd->args[i]))
			return (0);
		i++;
	}
	return (EXIT_SUCCESS);
}
