#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

using namespace std;
void ProcessList();
int main()
{
	ProcessList();
}
void ProcessList() {
	HANDLE hProcessShot;
	PROCESSENTRY32 ProcessInformation;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	ProcessInformation.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessShot, &ProcessInformation) && INVALID_HANDLE_VALUE!= hProcessShot) {
		do
		{
			printf("PROCESS NAME:  %ls  -  ", ProcessInformation.szExeFile );
			printf("PROCESS ID:  %i \n", ProcessInformation.th32ProcessID );
		}
		while (Process32Next(hProcessShot, &ProcessInformation));
	}
	else {

	}
	CloseHandle(hProcessShot);
}














