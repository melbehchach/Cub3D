/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:24:07 by mel-behc          #+#    #+#             */
/*   Updated: 2021/12/08 15:41:18 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (c == 0)
		return (&str[i]);
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lnd;
	size_t	lns;

	i = 0;
	j = 0;
	lnd = ft_strlen(dst);
	lns = ft_strlen(src);
	if (lnd > dstsize)
		return (dstsize + lns);
	while (dst[i])
		i++;
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (lnd + lns);
}

char	*ft_strjoin(char **s1, char **s2)
{
	char	*ptr;
	size_t	tlen;
	size_t	i;

	i = 0;
	if (!*s1 || !*s2)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	tlen = (ft_strlen(*s1) + ft_strlen(*s2));
	ptr = malloc(sizeof(char) * (tlen + 1));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	i = ft_strlcat(ptr, *s1, tlen + 1);
	ft_strlcat(&ptr[i], *s2, tlen - i + 1);
	free(*s1);
	free(*s2);
	*s1 = NULL;
	*s2 = NULL;
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
