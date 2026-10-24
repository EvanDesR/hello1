// hello1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <strsafe.h>
int main()
{
	SYSTEM_INFO si; //declare structure
	::GetNativeSystemInfo(&si); //pass address of the structure, to the function

	printf("Processors: %u \n", si.dwNumberOfProcessors);
	printf("Page size: %u \n", si.dwPageSize);
	printf("Processor mask: %zX \n", si.dwActiveProcessorMask); //DWORD_PTR is a UINT that is guaranteed to be the exact size as a memory address on whatever target architecture (it can be compiled on 32 bit or 64 bit)
	printf("Min Process Address:%p \n", si.lpMinimumApplicationAddress);											//%z length modifier tells prinf that the argument is of size_t which will match architecture bitness
	printf("Max Process Address:%p \n", si.lpMaximumApplicationAddress);

	HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, 24824); //terminates notepad


	PROCESSENTRY32 currentProcInfo;
	PROCESSENTRY32 priorProcInfo;

	currentProcInfo.dwSize = sizeof(PROCESSENTRY32);
	priorProcInfo.dwSize = sizeof(PROCESSENTRY32);

	HANDLE SystemSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL); //take snpshot
	if (hProcess) {
		::TerminateProcess(hProcess, 0);
	}
	
	if (SystemSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("Error: %p \n", GetLastError());
		exit(1);
	}
	

	if (::Process32First(SystemSnapshot, &currentProcInfo) == TRUE)
	{
		printf("%lu \n",currentProcInfo.th32ProcessID);

		while (Process32Next(SystemSnapshot, &currentProcInfo) != FALSE)
		{

			if(currentProcInfo.th32ProcessID == 4 || currentProcInfo.th32ParentProcessID == 4)
			printf("%lu \n", currentProcInfo.th32ProcessID);

		}
	}
	else
	{
		printf("Error, the snapshot data was not written to procInfo struct buffer: %p \n", GetLastError());

	}
	

	//STRING STUFFFFFFF

	::MessageBox(nullptr,L"This is a LPCWSTR ")


}












// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
