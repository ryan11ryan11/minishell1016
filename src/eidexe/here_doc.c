/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:19:35 by rakropp           #+#    #+#             */
/*   Updated: 2024/08/21 14:46:28 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_heredoc(t_data *data)
{
	char	*ret;
	char	*tmp;
	char	*buf;

	ret = malloc(1 * sizeof(char));
	ret[0] = '\0';
	while (ret[ms_strlen(ret)] != EOF)
	{
		tmp = ret;
		buf = readline(" >	");
		add_history(buf);
		ret = ms_strjoin(tmp, buf);
		free (tmp);
		free (buf);
		if (!ret)
			ms_error(data, "eidexe/here_doc.c 32: failloc :(", ENOMEM);
	}
	return (ret);
}
