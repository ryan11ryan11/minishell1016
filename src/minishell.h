/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:30:25 by jbober            #+#    #+#             */
/*   Updated: 2024/10/15 14:44:49 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
//# include <asm/termbits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <dirent.h>

extern int	g_lastexit;

// #define BUFFER_SIZE 1024

typedef struct s_data	t_data;
typedef struct s_exe	t_exe;
typedef struct s_list	t_list;
typedef struct s_node	t_node;

typedef struct s_data
{
	char	**currstr;
	char	**cstrl;
	t_list	*lstart;
	t_exe	*exe;
	t_list	*currmds;
	char	*currinput;
	int		num_envp;
	char	**env;
	int		errcode;
	int		env_set;
	int		num_pipe;
	char	**patharr;
	int		num_ndata;
	int		**pipe;
	char	**new_envp;
	struct s_envlist	*envlist;
	pid_t	*pid;
}	t_data;

typedef struct s_exe
{
	int		tube[2];
	int		pipehowmuch;
	char	*path;
	char	**paths;
	int		std_fd[2];
	int		endline;
	int		test;
}	t_exe;

typedef struct s_list
{
	t_node			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	char	**cmd;
	char	*path;
	char	*infd;
	char	*outfd;
	int		status;
	int		oper;
	int		appnd;
}	t_node;

typedef struct s_envlist
{
	char				*value;
	struct s_envlist	*next;
}	t_envlist;


/*
	--- asd ---
*/

// envp

void	ms_cpy_env(t_data *data, char **arg);
void	ms_envp(t_data *data, char **envp);

// freerror

void	ms_error(t_data *data, char *str, int brexit);
//void	ms_free(t_data *data, int modus);
// void	ms_freevenmore(t_data *data);
// void	ms_freelst(t_list *iamhere);

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

// void	find_cmd(t_data *data, t_node *node);
// void	sort_in_out(t_data *data, t_node *node);
// void	find_path(t_data *data, t_node *node);
// void	sort_node(t_data *data, t_node *node);
// void	get_pipes(t_data *data);
// void	exe_control(t_data *data);

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
int		ms_count32(char *str);

// parsefk2

extern char	*ms_parsefk2_ctrl(t_data *data);

// parsefk3

extern char	*ms_parsefk3_ctrl(t_data *data);

// parsefk4

extern char	*ms_parsefk4_ctrl(t_data *data);


/*
	--- NEW ---
*/

// builtin_control
int	count_arg(t_data *data);
int	builtin(t_data *data);
int	ft_strcmp2(const char *s1, const char *s2);
int	builtin_exception2(char *arr);
int	builtin_exception(t_data *data);

//envlistclear
void	envlistclear(t_envlist *envlist);

//envp_list_maker
t_envlist	*ft_envlast(t_envlist *lst);
void	envlist_addback(t_envlist **lst, t_envlist *new);
t_envlist	*envlist_new(void *content);
int		env_size_checker(char *env[]);
int		envlistmaker(t_data *data, char *env[]);

//ft_cd
int		no_argument(t_node *content);
int		slash_up(t_node *argvt, char *input);
int		ft_cd(t_data *data);

//ft_echo
char	**argv_maker(char *line);
int		ft_strcmp3(const char *s1, const char *s2, int size);
int		all_n(char *txt, int len);
int		filenum_count(void);
char	**filearr_maker(int file_num);
char	**filename_arr_maker(DIR *dir);
int		print_directory();
int		print_argv(t_node *argvt, int i);
int		ft_echo(t_data *data);

//ft_env
int		ft_env(t_data *data);

//ft_export
char	*remove_quo(char *arr);
void	fix_arr(char **arr);
int		add_to_list(char **arr, t_data *data);
int		ft_export(t_data *data, char *line);

//ft_export2
int	is_duplicate(char *name, t_envlist *envlist, char *arr, t_data *data);
char	*quo_add(char *arr);
void	print_all(t_envlist *envlist);
int		underbar_alphabet(char *msg, t_data *data);
int		is_empty(char *msg, t_data *data);

//ft_export3
int		name_check(char *arr, t_envlist *envlist, t_data *data);
void	ft_envlist_back(t_envlist **lst, t_envlist *new);
int		add_newblock(t_envlist **envlist, char *content, t_data *data);
int		add_truespace(char *line, int *i, int *num_truespace);
int		newarr_counter(char *line);

//ft_export4
char	**new_arr_init(char *line);
char	*make_arr(char *line, int i, int j);
int		quo_jump(int *i, int *j, char *line);
void	new_add(int *i, int *j, char *line, char **new_arr);
char	**new_arr_maker(char *line);

//ft_export5
int		is_alphabet(char *name, t_data *data);
int		add_arr(char **arr, char *new);

//ft_pwd
int		ft_pwd(void);

//ft_unset
void	delete_node(t_envlist **head, t_envlist *node_to_delete);
t_envlist	*find_value_envlist(t_envlist *envlist, char *arr);
int		ft_unset(t_data *data);

//herdoc_signal
void	heredoc_ctrl_c(int signum);
void	heredoc_signal(void);

//pipe
void	init_pipe(t_data *data);
void	pipe_all_close(t_data *data);
void	exec_pipe(t_data *data, int i);
void	free_pipe(t_data *info);

//pipe2
int		count_pipe(t_data *data);
int		**assign_pipe(int num_pipe);

//signal
void	set_terminal_print_on(void);
void	set_terminal_print_off(void);
void	ctrl_c(int signum);
void	ft_signal(void);

//util
int		ft_strlcmp_limited(const char *s1, const char *s2);
char	*ft_strcat(char *s1, char *s2);

//pipe_utils4
int		all_component_check(t_data *data);
void	all_pipe_close(t_data *data);
char	*new_path_maker(char *input);
void	error_exit(char *msg, int error_number);
void	builtin_situation(t_data *data);

//pipe_utils3
void	case_outfile(t_node *argvt);
char	*get_last_word(char *buffer, int index);
void	case_heredoc(t_data *data);
int		case_infile(t_data *data);
void	child_process(t_data *data, int i);
void	parent_process(t_data *data);
int		exec_command_errcheck(t_data *data);
int		parent_process_exec(t_data *data);
int		is_pipe(t_list *currmds, t_data *data);
void	exec_command(t_data *data);

//pipe_utils2
pid_t	*assign_pid(int num_args);
char	*absolute_path(t_data *data);
char	*pathfinder(char *command, t_data *data);
void	count_currmds(t_data *data);
void	doublearr_free(char ***arr);
char	*ft_get_env(t_data *data);
void	data_setting(t_data *data);

//pipe_utils
int		count_envplist(t_data *data);
int		envp_setting(t_data *data);
void	envp_maker(t_data *data);
char	*slashadd(char *path);
char	*commandadd(char *slashadded, char *command);

//ft_lib
char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(const char *s, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int ch);

//ft_lib2
char	*ft_strncpy(char *dest, const char *src, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

//utils
char	*without_data(char *str);
void	print_current_path();

#endif