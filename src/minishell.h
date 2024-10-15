/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:30:25 by jbober            #+#    #+#             */
/*   Updated: 2024/10/15 12:03:42 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <asm/termbits.h>
# include <sys/types.h>
# include <sys/wait.h> 

extern int	g_lastexit;

// #define BUFFER_SIZE 1024

typedef struct s_data	t_data;
typedef struct s_exe	t_exe;
typedef struct s_list	t_list;
typedef struct s_node	t_node;

typedef struct s_data
{
	char	*currinput;
	char	**currstr;
	char	**cstrl;
	t_list	*currmds;
	t_list	*lstart;
	pid_t	pid;
	char	**env;
	t_exe	*exe;
}	t_data;

typedef struct s_exe
{
	int		tube[2];
	int		pipehowmuch;
	char	*path;
	char	**paths;
	int		std_fd[2];
	int		endline;
}	t_exe;

typedef struct s_list
{
	t_node			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	char	**cmd;
	char	*infd;
	char	*outfd;
	int		status;
	int		oper;
}	t_node;

/*
	--- asd ---
*/

// envp

void	ms_cpy_env(t_data *data, char **arg);
void	ms_envp(t_data *data, char **envp);

// freerror

void	ms_error(t_data *data, char *str, int brexit);
void	ms_free(t_data *data, int modus);
void	ms_freevenmore(t_data *data);
void	ms_freelst(t_list *iamhere);

// minishell

void	ms_initialize(t_data *data, char **envp);
void	ms_prompt(t_data *data);
int		ms_read_input(t_data *data);

// signals

void	ms_strc(int sig);
char	*ms_expandlexit(t_data *data);

// ut1ls

char	**ms_split(t_data *data, char *str, char split);
int		*ms_countsplit(t_data *data, char *str, char split);
int		ms_sepcount(char *str, char split);
char	*ms_substr(t_data *data, char *str, int i, int j);
char	*ms_speciasplit(t_data *data, char *str);

// ut2ls

int		ms_strinlst(t_data *data, char *str);
int		ms_strncmp(char	*set, char *str, int len);
int		ms_strcontains(char *str, char *bigstr);
char	*ms_strdup(char *str);
char	*ms_strjoin(char *str1ng, char *str2ng);

// ut3ls

int		ms_strrchr(char *str, char find, int modus);
int		ms_strlen(char *str);
t_list	*ms_lstnew(t_data *data);
void	ms_lstadd_back(t_data *data, t_list **lst);
t_list	*ms_lstlast(t_list *lst);

// ut4ls

char	*ms_substrrev(char *str, int start, int len);
char	*ms_itoa(int n);
int		ms_findexpanse(t_data *data, char *str);
void	ms_ctrlitialize(t_data *data);
void	ms_ctrlfill(t_data *data, int k, char *str);
int		ms_cinset(char c, char *set, int modus);

// ut5ls

int	ms_check_qt(char c, int *weakqt, int *strongqt);

/*
	--- eidexe ---
*/

// cd

void	set_pwd(t_data *data, char *dir);
void	ms_cd(t_data *data, t_node *node);

// check_cmds

void	check_cmds(t_data *data);
void	check_cd(t_data *data, t_node *node);
void	check_echo(t_data *data, t_node *node);
void	check_pwd(t_data *data, t_node *node);
void	check_export(t_data *data, t_node *node);
void	check_unset(t_data *data, t_node *node);
void	check_env(t_data *data, t_node *node);

// control

void	find_cmd(t_data *data, t_node *node);
void	sort_in_out(t_data *data, t_node *node);
void	find_path(t_data *data, t_node *node);
void	sort_node(t_data *data, t_node *node);
void	get_pipes(t_data *data);
void	exe_control(t_data *data);

// echo

void	ms_echo(t_data *data, t_node *node);

//	env

void	ms_env(t_data *data, t_node *node);

// envp

void	env_free(char **env);
char	**rm_env(t_data *data, char **str);
char	**add_env(t_data *data, char **str);
void	ms_cpy_env(t_data *data, char **arg);
void	ms_envp(t_data *data, char **envp);

// exe

void	ms_executable(t_data *data, t_node *node);
void	do_command(t_data *data, t_node *node);

// expand

char	*expand_last_exit(t_data *data, char *rest);
char	*let_lose(t_data *data, char *str, int i);
void	ms_expand(t_data *data, t_node *content);

// export

void	fill_export(t_data *data, char **arg, char **str, int start);
void	ms_export(t_data *data, t_node *node);

// heredoc

char	*ms_heredoc(t_data *data);

// print

void	env_print(t_data *data);

// pwd

void	ms_pwd(t_data *data, t_node *node);

// unset

void	check_arg_u_e(t_data *data, char **arg, int start);
void	fill_arg(t_data *data, char **arg, char **str, int start);
int		ms_arglen(char **arg, int start);
void	ms_unset(t_data *data, t_node *node);

/*
	--- parse ---
*/

// parse

extern void	ms_parse_ctrl(t_data *data);

// parsefk1 + b

extern char	*ms_parsefk1_ctrl(t_data *data);
extern char	*ms_add_32(char *str, int i, int weakqt, int strongqt);

// parsefk2

extern char	*ms_parsefk2_ctrl(t_data *data);

// parsefk3

extern char	*ms_parsefk3_ctrl(t_data *data);

// parsefk4

extern char	*ms_parsefk4_ctrl(t_data *data);

#endif