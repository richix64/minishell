/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:52:16 by rpocater          #+#    #+#             */
/*   Updated: 2024/08/29 15:32:14 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	print_commands(t_com *com)
{
	t_com	*elem;
	int		i;

	elem = com;
	i = 0;
	while (elem != NULL)
	{
		ft_printf("Command %d: \n", i);
		print_content_com(elem, i);
		elem = elem->next;
		i++;
	}
	return ;
}

char	**con_with_i(t_token *list, int x)
{
	char	**ret;
	t_token	*elem;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (x + 1));
	if (ret == NULL)
	{
		return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
	}
	elem = list;
	i = 0;
	while (elem != NULL && i < x)
	{
		*(ret + i) = ft_strdup(elem->content);
		if (*(ret + i) == NULL)
			return (perror(MSG_MLC_F), exit(EXIT_FAILURE), NULL);
		elem = elem->next;
		i++;
	}
	*(ret + i) = NULL;
	return (ret);
}

void	ft_addredir(t_com *elem, int n_com, int *err)
{
	char	**new_com;
	t_redir	*red;
	int		i;
	int		tru;

	i = 0;
	tru = 0;
	red = NULL;
	new_com = generate_new_com(&n_com);
	while (elem->command[i] != NULL)
	{
		if (ft_metachr(elem->command[i][0]) == 2 && tru == 0)
			red = first_redir(elem, err, &tru, i);
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 1)
			second_redir(elem, red, i, &tru);
		else if (ft_metachr(elem->command[i][0]) != 2 && tru == 0)
			new_com[n_com++] = ft_protected_dup(elem->command[i]);
		i++;
	}
	free_dpchar(elem->command);
	if (new_com != NULL)
		new_com[n_com] = NULL;
	elem->command = new_com;
}

void	ft_countredir(t_com *list, int *err)
{
	t_com	*elem;
	int		i;
	int		n_com;

	elem = list;
	while (elem != NULL)
	{
		i = 0;
		n_com = 0;
		n_com = count_subcom(elem, i, n_com, err);
		if (n_com != -1)
		{
			ft_addredir(elem, n_com, err);
			elem = elem->next;
		}
		else
			return ;
	}
	return ;
}

t_com	*ft_lst_to_coms(t_token *list, int *err)
{
	t_com	*ret;
	t_token	*elem;
	int		i;

	i = 0;
	elem = list;
	ret = NULL;
	while (elem != NULL && elem->content[0] != '|')
	{
		elem = elem->next;
		i++;
	}
	if (i > 0)
	{
		ret = prepare_com(list, elem, i, err);
	}
	else if (elem != NULL && elem->content[0] == '|')
		return (*err = SE_PIPE * -1, perror(MSG_SE_PIPE), NULL);
	return (ret);
}
