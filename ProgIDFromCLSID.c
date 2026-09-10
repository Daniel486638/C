#include <stdio.h>
#include <windows.h>
// #include <combaseapi.h>
// -lole32

#define LENGTH 39

int main() {
	char cs[LENGTH];
	printf("Please write CLSID.\n");
	fgets(cs, LENGTH, stdin);
	printf("%s\n", cs);

	GUID c;
	int Error = CLSIDFromString((LPCOLESTR)cs, &c);
	printf("%i, %i\n", __LINE__, Error);

	OLECHAR **inP2;
	ProgIDFromCLSID((REFCLSID)&c, inP2);

	printf("%i", inP2);
	printf("%i", *inP2);
	printf("%i", **inP2);
	fgets(cs, 1, stdin);


	return 0;
};