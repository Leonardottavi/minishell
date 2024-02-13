/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lottavi <lottavi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:38:52 by lottavi           #+#    #+#             */
/*   Updated: 2024/02/13 13:19:37 by lottavi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

int getchartype(char c)
{
	switch(c)
	{
		case '\'':
			return CHAR_QOUTE;
			break;
		case '\"':
			return CHAR_DQUOTE;
			break;
		case '|':
			return CHAR_PIPE;
			break;
		case '&':
			return CHAR_AMPERSAND;
			break;
		case ' ':
			return CHAR_WHITESPACE;
			break;
		case ';':
			return CHAR_SEMICOLON;
			break;
		case '\\':
			return CHAR_ESCAPESEQUENCE;
			break;
		case '\t':
			return CHAR_TAB;
			break;
		case '\n':
			return CHAR_NEWLINE;
			break;
		case '>':
			return CHAR_GREATER;
			break;
		case '<':
			return CHAR_LESSER;
			break;
		case 0:
			return CHAR_NULL;
			break;
		default:
			return CHAR_GENERAL;
	};
	return CHAR_GENERAL;
}

int	lexar_build(char* input, int size)
{

}
