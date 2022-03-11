#include <minishell.h>

char	*get_name(int i)
{
	char	*num;
	char	*name;
	char	*tmp;

	num = ft_itoa(i);
	tmp = ft_strjoin(num, ".tmp");
	name = ft_strjoin(".", tmp);
	free(num);
	free(tmp);
	return (name);
}

char	*ft_open_tmp(int	*fd)
{
	int		i;
	char	*name;

	i = 0;
	while (i++ < 1000)
	{
		name = get_name(i);
		if (access(name, F_OK) == 0)
		{
			free(name);
			continue ;
		}
		*fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (*fd != -1)
			break ;
		else
		{
			free(name);
			return (NULL);
		}
	}
	return (name);
}

void	ft_write_here_doc(t_ast *node)
{
	char	*line;
	int		*fd;
	char	*name;

	fd = ft_calloc(sizeof(int), 1);
	name = ft_open_tmp(fd);
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) == ft_strlen(node->data) 
				&& ft_strncmp(line, node->data, ft_strlen(line)) == 0)
			break ;
		ft_putendl_fd(line, *fd);
		free(line);
	}
	close(*fd);
	node->data = name;
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
