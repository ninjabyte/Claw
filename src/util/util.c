#include <ctype.h>
#include <string.h>
#include "util.h"

int util_strncicmp(const char* a, const char* b, size_t n)
{
	int i;
	for (i = 0; i<n; i++)
		if (!a[i] || !b[i] || tolower((unsigned char) a[i]) != tolower((unsigned char) b[i]))
			return 0;
	return 1;
}
