#include "mini_shell.h"

int	ft_error(char *msg, char *bin)
{
	ft_putstr_fd("minishell: \0", 2);
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putchar_fd(':', 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}