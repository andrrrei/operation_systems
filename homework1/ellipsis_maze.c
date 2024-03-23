#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find the length of a string
int lenofstr(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i += 1;
	}
	return i;
}

// Function to copy blocks of memory from one location to another
char* strcpy_blocks(char* newstr, const char* oldstr) {
	char* fir;
	char* sec;
	fir = oldstr;
	sec = newstr;
	
	int len = lenofstr(fir);
	int len1 = len / 8;

	// Copying blocks of size 8 bytes
	for (int i = 0; i < len1; i++) {
		*(double*)sec = *(double*)fir;
		fir += 8;
		sec += 8;
	}
	// Copying the remaining characters individually
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

	// Copying blocks of memory from the input string to the new string
	strcpy_blocks(p2, p1);
	
	// Printing the original string
	printf("%s", "Old string: ");
	printf("%s\n", p1);
	// Printing the new string
	printf("%s", "New string: ");
	printf("%s\n", p2);

	free(p2);
}
