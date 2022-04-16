#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using namespace std;
void ProcessList();
void ThreadsInProsses(int ValPoint);
int main()
{
	ProcessList();
}
void ProcessList() {
	HANDLE hProcessShot;
	PROCESSENTRY32  Information;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Information.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessShot, &Information) && INVALID_HANDLE_VALUE != hProcessShot) {
		do
		{
				printf("PROSSES ID   = %i \n", Information.th32ProcessID);
				printf("PROSSES Name = %ls \n", Information.szExeFile);
				ThreadsInProsses(Information.th32ProcessID);
		} while (Process32Next(hProcessShot, &Information));
	}
	else {
		printf("Hata1");
	}
	CloseHandle(hProcessShot);
}

void ThreadsInProsses(int ValPoint) {
	HANDLE hProcessShot;
	THREADENTRY32  Information;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	Information.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hProcessShot, &Information) && INVALID_HANDLE_VALUE != hProcessShot) {
		do
		{
			if (Information.th32OwnerProcessID == ValPoint) {
				printf("     THREAD ID   = %i \n", Information.th32ThreadID);
			}
		} while (Thread32Next(hProcessShot, &Information));
	}
	else {
		printf("Hata");

	}
	CloseHandle(hProcessShot);
}

