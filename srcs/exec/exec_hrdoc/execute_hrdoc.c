/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hrdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:39:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/27 18:26:18 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	content_size_file(int fd, char *buf, int *i)
{
	fd = open("/tmp/tmp_file.txt", O_RDONLY, 777);
    if (fd < 0)
    {
        return (0);
    }
    while (read(fd, buf, 1))
	{
        i[0]++;
	}
	close(fd);
	return (1);
}

int	gather_usr_input(char *content, t_mshell *mshell)
{
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = content;
	return (1);
}

char *recover_heredoc_content(int fd)
{
	char	*content;
    char    buf[1];
    int     i[2];

    i[0] = 0;
	i[1] = 0;
	buf[i[1]] = 0;
	content_size_file(fd, buf, i);
    content = malloc(sizeof(char) * (i[0] + 1));
	if (!content)
		return (NULL);
    fd = open("/tmp/tmp_file.txt", O_RDONLY, 777);
    if (fd < 0)
    {
        return (0);
    }
	i[0] = 0;
	while (read(fd, buf, 1))
	{
		content[i[0]] = buf[i[1]];
		i[0]++;
	}
	content[i[0]] = '\0';
	close(fd);
    return (content);
}

int execute_hrdoc(t_mshell *mshell)
{
    char    *usr_input;
    int     line;

    line = 0;
    pipe(mshell->pipe_fd);
    while (1)
    {
        usr_input = readline("> ");
        if (!check_eof(usr_input))
        {
            close(mshell->pipe_fd[1]);
			return (dprintf(STDERR_FILENO, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line, mshell->tkn->tkn), 1);
        }
        if (!ft_strcmp(usr_input, mshell->tkn->tkn))
        {
            if (usr_input)
                free(usr_input);
            close(mshell->pipe_fd[1]);
            break ;
        }
        write(mshell->pipe_fd[1], usr_input, ft_strlen(usr_input));
        write(mshell->pipe_fd[1], "\n", 1);
        line++;
        free(usr_input);
    }
    return (1);
}
