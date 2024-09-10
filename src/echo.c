/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:17:38 by daortega          #+#    #+#             */
/*   Updated: 2024/08/21 16:53:33 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(char **com, int print, int has_flag, int *status)
{
	while (com[print] != NULL)
	{
		if (com[print + 1] == NULL)
			ft_printf("%s", com[print]);
		else
			ft_printf("%s ", com[print]);
		print++;
	}
	if (!has_flag)
		ft_printf("\n");
	*status = EXIT_SUCCESS;
}

static int	check_flag(char *com)
{
	size_t	i;

	i = 2;
	if (com[0] != '-' || com[1] != 'n')
		return (0);
	while (i < ft_strlen(com))
	{
		if (com[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **command, int *status)
{
	int	i;
	int	flag;
	int	print;

	i = 1;
	flag = 0;
	print = 1;
	while (command[i] != NULL && check_flag(command[i]) == 1)
	{
		flag = 1;
		print = ++i;
	}
	print_echo(command, print, flag, status);
}
