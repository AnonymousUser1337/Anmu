


inline int strlen_Const(const char * s)
{	int length = 0;
	for (length = 0;*s != '\0'; ++s)
	{	length++;
	}
	return length;
}

inline int strlen(char * s)
{	int length = 0;
	for (length = 0;*s != '\0'; ++s)
	{	
		length++;
	}
	return length;
}
