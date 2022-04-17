#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

void ProcessList();
void ThreadsInProsses();
void ThreadAndProcessWrite();
template<class T>
class List
{
public:
    T GetIndex(unsigned int i) {
        return (i >= _Lengh) ? 0 : *StartPoint[i];
    }
    void Read() {
        for (int i = 0; i < _Lengh; i++) {
            cout << *StartPoint[i] << endl;
        }
    }
    int Lengh() {
        return _Lengh;
    }
    void Add(T value)
    {
        MemoryPointCreate(&value);
    }
    void Remove(unsigned int index) {
        _RemoveIndex(&index);
    }
    int CountVal(T Value) {
        int j = 0;
        for (int i = 0; i < _Lengh; i++) {
            j = (*StartPoint[i] == Value) ? ++j : j;
        }
        return j;
    }
    int FindIndex(T Value) {
        int j = 0;
        for (int i = 0; Lengh(); i++) {
            if (*StartPoint[i] == Value) {
                j = i;
                break;
            }
        }
        return j;
    }
private:
    int _Lengh = 0;
    T** StartPoint;
    T* _FirstValue = new T[1];

    void _RemoveIndex(int* Rindex) {
        T** NewStartPoint = StartPoint;
        StartPoint = new T * [_Lengh - 1];
        for (int i = 0, j = 0; i < _Lengh; i++) {
            if (i != *Rindex - 1) {
                StartPoint[j] = NewStartPoint[i];
                j++;
            }
        }
        free(NewStartPoint);
        _Lengh--;
    }
    void MemoryPointCreate(T* value, int Type = 0) {
        T* NPoint = new T[1];
        *NPoint = *value;
        MemoryExpansion(NPoint);
    }
    void MemoryExpansion(T* NValue) {
        if (_Lengh > 0) {
            _Lengh++;
            T** NewStartPoint = StartPoint;
            StartPoint = new T * [_Lengh];
            for (int i = 0; i < _Lengh - 1; i++)
            {
                StartPoint[i] = NewStartPoint[i];
            }
            StartPoint[_Lengh - 1] = NValue;
            free(NewStartPoint);
        }
        else {
            _Lengh++;
            StartPoint = new T * [_Lengh];
            StartPoint[0] = NValue;
        }
    }
};

List<int> ProcessesID;
List<WCHAR*> ProcessesName;
List<int> ThreadsID;

void ProcessList() {
	HANDLE hProcessShot;
	PROCESSENTRY32  Information;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Information.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessShot, &Information) && INVALID_HANDLE_VALUE != hProcessShot) {
		do
		{
            ProcessesID.Add(Information.th32ProcessID);
            ProcessesName.Add(Information.szExeFile);
		} 
        while (Process32Next(hProcessShot, &Information));
	}
	else {
		printf("Error");
	}
	CloseHandle(hProcessShot);
}
void ThreadsInProsses() {
	HANDLE hProcessShot;
	THREADENTRY32  Information;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	Information.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hProcessShot, &Information) && INVALID_HANDLE_VALUE != hProcessShot) {
		do
		{
            ThreadsID.Add(Information.th32ThreadID);
            ThreadsID.Add(Information.th32OwnerProcessID);
		} while (Thread32Next(hProcessShot, &Information));
	}
	else {
		printf("Error");

	}
	CloseHandle(hProcessShot);
}
void ThreadAndProcessWrite() {
    for (int i = 0; i < ProcessesID.Lengh();i++) {
        cout <<"PROCESS ID : "<< ProcessesID.GetIndex(i) << endl;
        cout <<"PROCESS NAME : " << ProcessesName.GetIndex(i) << endl;
        for (int j = 1; j < ThreadsID.CountVal(ProcessesID.GetIndex(i));j+=2) {
            cout <<"THREAD ID : " << ThreadsID.GetIndex(ThreadsID.FindIndex(ProcessesID.GetIndex(i)) + j)<<endl;
        }
    }
}
int main()
{
    ProcessList();
    ThreadsInProsses();
    ThreadAndProcessWrite();
}

