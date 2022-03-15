#include <windows.h>
#include <gdiplus.h>
#include <iostream>

//use gdiplus library when compiling
#pragma comment( lib, "gdiplus" )

using namespace Gdiplus;

VOID GetPointCountExample()
{
	// Create a path that has one ellipse and one line.
	GraphicsPath path;
	path.AddLine(0, 0, 0, 1);

	// Find out how many data points are stored in the path.
	int count = path.GetPointCount();
	std::cout << count << std::endl;

	//std::cout << path.GetLastStatus() << std::endl;
}

int main()
{
	//Must call GdiplusStartup before making any GDI+ calls
	//https://docs.microsoft.com/en-us/windows/win32/api/Gdiplusinit/nf-gdiplusinit-gdiplusstartup
	ULONG_PTR token;
	GdiplusStartupInput input;
	input.GdiplusVersion = 1;
	input.SuppressBackgroundThread = false;

	GdiplusStartup(&token, &input, NULL);

	GetPointCountExample();

	//Shutdown GDI+ when finished using
	GdiplusShutdown(token);
}
