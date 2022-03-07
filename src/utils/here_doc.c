#include <minishell.h>

char	*ft_open_tmp(int	*fd)
{
	int		i;
	char	*num;
	char	*name;

	i = 0;
	while (i++ < 1000)
	{
		num = ft_itoa(i);
		name = ft_strjoin(num, ".tmp");
		if (access(name, F_OK) == 0)
			continue ;
		*fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (*fd != -1)
			break ;
		else
		{
			free(name);
			free(num);
			return (NULL);
		}
	}
	free(num);
	return (name);
}

void	ft_write_here_doc(t_ast *node)
{
	char	*line;
	size_t	l;
	int		*fd;
	char	*name;

	fd = ft_calloc(sizeof(int), 1);
	name = ft_open_tmp(fd);
	while (1)
	{
		line = get_next_line(0);
		l = ft_strlen(line);
		if (l)
			line[l - 1] = 0;
		if (l < ft_strlen(node->data))
			l = ft_strlen(node->data);
		if (ft_strncmp(line, node->data, l) == 0)
			break ;
		write(*fd, line, ft_strlen(line));
		free(line);
	}
	close(*fd);
	node->data = name;
	node->type = T_IN_NODE;
	free(line);
	free(fd);
}

void	ft_process_here_doc(t_ast **tree)
{
	t_ast	*curr;

	if ((*tree)->type == T_PIPE_NODE)
	{
		ft_process_here_doc(&((*tree)->left));
		ft_process_here_doc(&((*tree)->right));
	}
	else
	{
		curr = (*tree)->right->left;
		while (curr)
		{
			if (curr->type == T_DOUBLE_IN_NODE)
				ft_write_here_doc(curr);
			curr = curr->left;
		}
	}
}
