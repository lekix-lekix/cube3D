/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:02:16 by lekix             #+#    #+#             */
/*   Updated: 2023/11/14 18:04:58 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	letter;

	letter = c;
	if (letter >= 'A' && letter <= 'Z')
		return (letter + 32);
	else
		return (letter);
}
