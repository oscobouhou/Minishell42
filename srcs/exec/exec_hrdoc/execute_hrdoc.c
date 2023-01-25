/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hrdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:39:41 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/25 12:55:42 by oboutarf         ###   ########.fr       */
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
    pid_t   pid;
    int     fd;

    pid = fork();
    if (pid == -1)
        return (dprintf(2, "couldn't fork process for hrdoc!"), 0);
    if (pid == 0)
    {
        fd = open("/tmp/tmp_file.txt", O_CREAT | O_WRONLY, 777);
        if (!fd)
            return (dprintf(2, "couldn't open hrdoc file!"), 0);
        while (1)
        {
            usr_input = readline("> ");
            if (!ft_strcmp(usr_input, mshell->tkn->tkn))
            {
                close(fd);
				if (usr_input)
					free(usr_input);
                exit(0);
            }
            write(fd, usr_input, ft_strlen(usr_input));
			write(fd, "\n", 1);
            free(usr_input);
        }
    }
	waitpid(pid, NULL, 0);
    fd = -42;
    usr_input = recover_heredoc_content(fd);
    gather_usr_input(usr_input, mshell);
    unlink("/tmp/tmp_file.txt");
    return (1);
}
