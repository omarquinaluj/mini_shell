#include "mini_shell.h"

void	error_write(char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": write error: ", STDERR_FILENO);
	ft_putstr_fd("No space left on device\n", STDERR_FILENO);
}
