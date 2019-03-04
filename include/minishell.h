/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:43:02 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/04 15:27:24 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "lexer.h"
# include "builtin.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

void					minishell();
int						parser(t_lexer *lexer, char ***env);
int						fill_lexer(char *str, t_lexer *lexer, char **env);
void					free_lexer(t_lexer *lexer);
void					free_tab(char **tab);
char					*str_pathfile(const char *s1, const char *s2);
int						error_exec(int no, char *prog, char *display);
int						test_access(char *path);
int						execute(int argc, char **argv, char ***env);
char					**copy_env(char **env, int add_variable);
int						true_variable(char *env, char *arg);
void					set_token_env(t_token *token, char **env);
void					create_variable(int argc, char **argv, char ***env);

#endif
