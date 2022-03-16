#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

# define READ_END 0
# define WRITE_END 1
# define CYAN	"\033[1;36m"
# define NC		"\033[0m"

//extern t_list	*g_env;

typedef struct s_prog
{
	t_list	**env;
	int		l_cod;
}				t_prog;

extern t_prog	g_env;

typedef enum e_lex_states
{
	P_ERROR			= -1,
	P_NEUTRAL		= 0,
	P_D_QUOTE		= 1,
	P_S_QUOTE		= 2
}				t_lex_states;

typedef enum e_token_type
{
	T_ARGUMENT		= 0,
	T_IN_REDIR		= 1,
	T_D_IN_REDIR	= 2,
	T_OUT_REDIR		= 3,
	T_D_OUT_REDIR	= 4,
	T_PIPE			= 5
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
	int 			error;
	int 			l_error;
	t_token_type	type;
	t_lex_states	state;
}				t_pstatus;

typedef struct s_l_fd
{
	int	fd[2];
}				t_l_fd;

// parse_env_vars
char	*ft_get_env_var(char *token, int *num);
char	*ft_join_env_var(char *name, char *token, int i, int num);
void	ft_extend_vars(char **token);

// utils
void	ft_skip_spaces(t_pstatus *status);
char	**ft_resize_tokens(int num, char **tokens);

//frees.c
void	ft_free_split(char **s);
void	ft_free_tree(t_ast **tree);
void	ft_free_token(void *t);
void	ft_free_split(char **s);
void	ft_free_all(t_ast **tree, t_list **tokens);

//signas.c
void	my_signal(void);
void	sig_ignore(void);
void	sig_child(void);
void	sig_here_doc(void);

//env.c
char	*ft_getenv(char *name);

// parser_quotes.c
void	ft_parse_quotes(char **token);

// lexer
t_list	**ft_get_tokens(t_pstatus *status);

// ast
t_ast	*ft_astnew(t_node_type type, char *content);
void	ft_astadd_right(t_ast **tree, t_ast *new);
void	ft_astadd_left(t_ast **tree, t_ast *new);
t_ast	*ft_astget_last_r(t_ast *tree);
t_ast	*ft_astget_last_l(t_ast *tree);
void	ft_astappend_l(t_ast **tree, t_ast *new);
void	ft_astappend_r(t_ast **tree, t_ast *new);
int		ft_astsize_r(t_ast *node);

// parser.c
t_list	*ft_fill_simple_command(t_list *tokens, t_ast **tree);
t_ast	**ft_generate_ast(t_list **tokens);

// here_doc.c
int		ft_process_here_doc(t_ast **tree);


int	ft_exec_builtin(t_ast *tree, int pip, t_l_fd *r_fd, int fd[]);
int	ft_exec_cmd(t_ast *tree, t_l_fd *l_fd, t_l_fd *r_fd, int fd[]);
int	ft_getredir(t_ast *tree, int io);

//executor.c
t_l_fd		*ft_exec_tree(t_ast *tree, int pipe, int *l_pid, t_l_fd *l_fd);
char	**ft_envmatrix();

int		valid_builtins(t_ast *tree);

//binaries
//

int		ft_llen(char *s1, char *s2);
void	ft_use_builtins(t_ast *tree, int fd);
void	ft_pwd(int fd);
void	ft_cd(t_ast *path);
void	ft_echo(t_ast *tree, int fd);
void	ft_exit(void);
void    ft_env(int fd);
void	ft_unset(t_ast *tree);
void	ft_export(t_ast *tree, int fd);

#endif
