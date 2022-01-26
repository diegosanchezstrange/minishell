#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_lex_states
{
	P_NEUTRAL	= 0,
	P_D_QUOTE	= 1,
	P_S_QUOTE	= 2
}				t_lex_states;

typedef enum e_token_type
{
	T_ARGUMENT	= 0,
	T_IN_REDIR	= 1,
	T_OUT_REDIR	= 2,
	T_PIPE		= 3
}				t_token_type;

typedef enum e_node_type
{
	T_COMMAND_NODE		= 0,
	T_ARGUMENT_NODE		= 1,
	T_REDIR_NODE		= 2,
	T_IN_NODE			= 3,
	T_DOUBLE_IN_NODE	= 4,
	T_OUT_NODE			= 5,
	T_DOUBLE_OUT_NODE	= 6,
	T_PIPE_NODE			= 7
}				t_node_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}				t_token;

typedef struct s_ast
{
	char			*data;
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_pstatus
{
	char			*data;
	int				curr;
	t_lex_states	state;
}				t_pstatus;

// parse_env_vars
char	*ft_get_env_var(char *token, int *num);
char	*ft_join_env_var(char *name, char *token, int i, int num);
void	ft_extend_vars(char **token);

// utils
void	ft_skip_spaces(t_pstatus *status);
char	**ft_resize_tokens(int num, char **tokens);

// parser_quotes.c
void	ft_parse_quotes(char **token);

// lexer
t_list	**ft_get_tokens(t_pstatus *status);

// ast
t_ast	*ft_astnew(t_node_type type, char *content);
void	ft_astadd_right(t_ast **tree, t_ast *new);
void	ft_astadd_left(t_ast **tree, t_ast *new);

// parser.c
t_list	*ft_fill_simple_command(t_list *tokens, t_ast **tree);
t_ast	**ft_generate_ast(t_list **tokens);

#endif
