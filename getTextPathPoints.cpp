#include <windows.h>
#include <gdiplus.h>
#include <iostream>

//use gdiplus library when compiling
#pragma comment( lib, "gdiplus" )

void stringToPath(const WCHAR* s)
{
	Gdiplus::GraphicsPath path;
	Gdiplus::FontFamily fontFamily(L"Times New Roman");

	path.AddString(
		s,
		-1,                 // NULL-terminated string
		&fontFamily,
		Gdiplus::FontStyleRegular,
		48,
		Gdiplus::Point(50, 50),
		NULL);

	//applies a transformation to this path and converts each curve in the path to a sequence of connected lines.
	path.Flatten();
	//std::cout << path.GetLastStatus() << std::endl;
}

int main()
{
	//Must call GdiplusStartup before making any GDI+ calls
	//https://docs.microsoft.com/en-us/windows/win32/api/Gdiplusinit/nf-gdiplusinit-gdiplusstartup
	ULONG_PTR token;
	Gdiplus::GdiplusStartupInput input;
	input.GdiplusVersion = 1;
	input.SuppressBackgroundThread = false;

	Gdiplus::GdiplusStartup(&token, &input, NULL);

	//get string path
	stringToPath(L"Hello World!");

	//Shutdown GDI+ when finished using
	Gdiplus::GdiplusShutdown(token);
}
