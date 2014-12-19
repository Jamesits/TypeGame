int fredraw()
{
	{
		mvaddstr(1, COL1, "'Normal' white-on-black");
#if(CHTYPE_LONG >= 2)       /* "non-standard" 64-bit chtypes     */
		attron(A_DIM);
		mvaddstr(2, COL1, "Dimmed text");
		attroff(A_DIM);
#endif
#ifdef PDC_WIDE
		mvaddwstr(3, COL1, L"'Normal' text,  but wide");
#endif
		attron(A_BLINK);
		mvaddstr(6, 40, "Blinking");
		attron(A_BOLD);
		mvaddstr(8, 40, "BlinkBold");
		attron(A_ITALIC);
		mvaddstr(0, COL2, "BlinkBoldItalic");
		attrset(COLOR_PAIR(3));
		attron(A_UNDERLINE);
#ifdef PDC_WIDE
		mvaddstr(1, COL2, "Underlined");
		addwstr(L"WideUnder");
#endif
		attrset(COLOR_PAIR(1));
		attron(A_UNDERLINE | A_ITALIC);
		mvaddstr(2, COL2, "UnderlinedItalic");
		attrset(COLOR_PAIR(2));
		attron(A_BLINK);
		mvaddstr(4, COL1, "Black-on-yellow blinking");

		attrset(COLOR_PAIR(1));
		move(4, COL2);
		text_in_a_box("Text in a box");

		attrset(COLOR_PAIR(6));
		attron(A_STRIKEOUT);
		mvaddstr(10, 40, "Strikeout");
		attrset(COLOR_PAIR(1));

		for (i = 0; i < 128; i++)
		{                 /* Show extended characters: */
#ifdef PDC_WIDE
			wchar_t buff[5];

			_snwprintf(buff, 5, L"%2x ",
				(unsigned)(i + unicode_offset) & 0xff);
			mvaddwstr(5 + i % 16, (i / 16) * 5, buff);
			addch((chtype)(i + unicode_offset));
#else
			char buff[5];

			sprintf(buff, "%2x %c", i + 128, (char)(i + 128));
			mvaddstr(5 + i % 16, (i / 16) * 5, buff);
#endif
		}

#if(CHTYPE_LONG >= 2)       /* "non-standard" 64-bit chtypes     */
		for (i = 0; i < 3; i++)
		{                 /* Demonstrate full RGB color control: */
			int j;
			const char *output_text[3] = {
				"Red on green to white on black   | (you can get full RGB colors when desired,",
				"Blue on yellow to black on red | with palette coloring still being available)",
				"White on red to green on blue,  underlined and italic" };
			const int len = strlen(output_text[i]);

			move(21 + i, 1);
			for (j = 0; j < len; j++)
			{
				attr_t output_color;
				const int oval = j * 31 / len;
				const int reverse = 31 - oval;

				if (!i)
					output_color = A_RGB(31, oval, oval, 0, reverse, 0);
				else if (i == 1)
					output_color = A_RGB(0, 0, reverse, 31, reverse, 0);
				else
				{
					output_color = A_RGB(reverse, 31, reverse,
						reverse, 0, oval);
					output_color |= A_UNDERLINE | A_ITALIC;
				}
				attrset(output_color);
				addch(output_text[i][j]);
			}
		}
#endif         /* #if(CHTYPE_LONG >= 2) */
		return 0;
}