// -liphlpapi
#include <windows.h>
#include <iphlpapi.h>
#include <stdio.h>

int main() {         
    IP_ADAPTER_INFO *info = NULL, *pos;
    DWORD size = 0;

    GetAdaptersInfo(info, &size);

    info = (IP_ADAPTER_INFO *)malloc(size);

    GetAdaptersInfo(info, &size);

    for (pos=info; pos!=NULL; pos=pos->Next) {
        printf("\n%s\n\t", pos->Description);
        printf("%2.2x", pos->Address[0]);
        for (int i=1; i<pos->AddressLength; i++)
            printf(":%2.2x", pos->Address[i]);
    }

    free(info);
	getchar();
    return 0;
}