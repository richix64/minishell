/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:02:56 by daortega          #+#    #+#             */
/*   Updated: 2024/07/27 12:57:43 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_heredoc(char *file, char *path)
{
	char	*line;
	int		fd;

	fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (perror(MSG_OPEN_F), exit(EXIT_FAILURE));
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, file) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
		line = readline("> ");
	}
	if (line != NULL)
		free(line);
}

void	check_heredoc(t_redir *redir)
{
	char	*path;
	int		i;
	char	*num;

	i = 0;
	while (redir != NULL)
	{
		if (redir->type == HERE_DOC)
		{
			num = ft_itoa(i);
			if (num == NULL)
				return (perror(MSG_MLC_F), exit(EXIT_FAILURE));
			path = ft_strjoin("/tmp/heredoc_minishell", num);
			free(num);
			if (path == NULL)
				return (perror(MSG_MLC_F), exit(EXIT_FAILURE));
			make_heredoc(redir->file, path);
			free(redir->file);
			redir->file = path;
			i++;
		}
		redir = redir->next;
	}
}

void	heredoc(t_com *command)
{
	while (command != NULL)
	{
		check_heredoc(command->redir);
		command = command->next;
	}
}
