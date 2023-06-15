#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lenofstr(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i += 1;
	}
	return i;
}


char* strcpy_blocks(char* newstr, const char* oldstr) {
	char* fir;
	char* sec;
	fir = oldstr;
	sec = newstr;
	
	int len = lenofstr(fir);
	int len1 = len / 8;


	for (int i = 0; i < len1; i++) {
		*(double*)sec = *(double*)fir;
		fir += 8;
		sec += 8;
	}
	for (int i = 0; i < (len - len1 * 8); i++) {
		*sec = *fir;
		fir++;
		sec++;
	}
}

int main() {

	char s[] = "isrjgrghoirhgohiohos rtyukl 234567890";
	const char* p1 = s;
	char* p2 = (char*)malloc(lenofstr(s));

	strcpy_blocks(p2, p1);
	printf("%s", "Old string: ");
	printf("%s\n", p1);
	printf("%s", "New string: ");
	printf("%s\n", p2);

	free(p2);
}