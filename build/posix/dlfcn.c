#include "dlfcn.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//#include <skynet.h>
//#include <skynet_handle.h>
//#include <skynet_server.h>
//#include <stdint.h>


#define SKYNET_LLE_FLAGS 0

//static void pusherror() {
//	uint32_t handle = skynet_current_handle();
//	struct skynet_context *context = skynet_handle_grab(handle);
//	int error = GetLastError();
//	char buffer[128];
//	if (FormatMessageA(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, error, 0, buffer, sizeof(buffer) / sizeof(char), NULL)) {
//		skynet_error(context, buffer);
//	} else
//		skynet_error(context, "system error %d\n", error);
//	skynet_context_release(context);
//}

void *dlopen(const char *filename, int flag) {
	(void)flag;
	return LoadLibraryExA(filename, NULL, SKYNET_LLE_FLAGS);
}

char *dlerror(void) {
	DWORD err = GetLastError();
	HLOCAL LocalAddress = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err, 0, (PTSTR)&LocalAddress, 0, NULL);
	return (LPSTR)LocalAddress;

	/*int error = GetLastError();
	char buffer[128];
	if (FormatMessageA(FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error, 0, buffer, sizeof(buffer) / sizeof(char), NULL)) {
		return buffer;
	} else
		return printf("system error %d\n", error);*/
}

void *dlsym(void *handle, const char *symbol) {
	return GetProcAddress((HMODULE)handle, symbol);
}

int dlclose(void *handle) {
	return FreeLibrary((HMODULE)handle);
}