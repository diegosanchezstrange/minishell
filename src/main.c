/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:18 by dsanchez          #+#    #+#             */
/*   Updated: 2022/02/02 20:52:17 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

t_pstatus status;
extern char	**environ;

char	*ft_get_path(char *arg)
{
	char	*env;
	char	**path;
	char	*command;

	if (access(arg, F_OK) == 0)
		return (arg);
	env = getenv("PATH");
	if (!env)
		return ("");
	path = ft_split(env, ':');
	while (*path)
	{
		command = ft_strjoin(*path, ft_strjoin("/", arg));
		if (access(command, F_OK) == 0)
			return (command);
		path++;
	}
	return ("");
}

int	ft_execute(char **tokens)
{
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		execve(ft_get_path(tokens[0]), tokens, environ);
		perror(tokens[0]);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("minish");
		return (0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (1);
	}
}

void	ft_print_tokens(char **tokens)
{
	if (!tokens)
		return ;
	printf("------------------- TOKENS -------------------\n");
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
	printf("------------------- TOKENS -------------------\n");
}

void	ft_print_tokens_list(t_list **tokens)
{
	t_list	**pointer;

	if (!tokens)
		return ;
	pointer = malloc(sizeof(void *));
	if (!pointer)
		return ;
	*pointer = *tokens;
	printf("------------------- TOKENS -------------------\n");
	while (*pointer)
	{
		printf("data: %s , type: %d\n", ((t_token *)((*pointer)->content))->data, ((t_token *)((*pointer)->content))->type);
		*pointer = (*pointer)->next;
	}
	printf("------------------- TOKENS -------------------\n");
	free(pointer);
}

void	ft_free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	free(token->data);
	free(token);
}

/*void	my_prompt(int n)
{
	n = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void my_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_prompt);
}*/
void	ft_use_builtins(t_ast *tree)
{
	if (ft_strncmp(tree->data, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tree->data, "echo", 4) == 0)
		ft_echo(tree);
	else if (ft_strncmp(tree->data, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(tree->data, "env", 3) == 0)
		ft_env();
}

void	ft_tree_travel(t_ast **tree)
{
	char	*cmd;

	while (*tree && (*tree)->data)
	{
		cmd = (*tree)->data;
		if (!ft_strnstr(cmd, "pwdechoexitunsetenvexport", ft_strlen(cmd)))
			ft_use_builtins(*tree);
		else
			printf("ARG -- data : %s, type : %d\n", (*tree)->data, (*tree)->type);
		(*tree) = (*tree)->right;
	}
}
int	main(void)
{
	t_list		**tokens;
	t_ast		**tree;
	int			state;

	state = 1;
	while (state)
	{
		//my_signal();
		status.data = readline(CYAN"$"NC" ");
		if (status.data == NULL)
		{
			write(1, "exit", 5);
			exit(0);
		}
		if (status.data)
			add_history(status.data);
		status.curr = 0;
		status.error = 0;
		tokens = ft_get_tokens(&status);
		//ft_print_tokens_list(tokens);
		if (tokens)
		{
			tree = ft_generate_ast(tokens);
			if (*tree)
			{
/*				printf("HEAD -- data : %s, type : %d\n", (*tree)->data, (*tree)->type);
				(*tree) = (*tree)->right;
				while ((*tree))
				{
					printf("ARG -- data : %s, type : %d\n", (*tree)->data, (*tree)->type);
					(*tree) = (*tree)->right;
				}*/
			ft_tree_travel(tree);
			}
			else
				printf("NULL\n");
		}
		ft_lstclear(tokens, ft_free_token);
		free(tokens);
	}
	return (0);
}
