#include"System.h"
#include<iostream>

int main()
{
	System* sys = new System();

	bool result = sys->Initialize();
	if(result)
	{
		sys->Run();
	}

	sys->Release();

	return 0;
}
