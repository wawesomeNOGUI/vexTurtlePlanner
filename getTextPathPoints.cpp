#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>

//use gdiplus library when compiling
#pragma comment( lib, "gdiplus" )

std::ofstream outputFile;

void stringToPath(const WCHAR* s)
{
	Gdiplus::GraphicsPath path;
	Gdiplus::FontFamily fontFamily(L"Courier New");

	path.AddString(
		s,
		-1,                 // NULL-terminated string
		&fontFamily,
		Gdiplus::FontStyleRegular,
		48,
		Gdiplus::Point(0, 0),
		NULL);

	//converts each curve in the path to a sequence of connected lines.
	//also can optionally change resolution of how many lines to turn curve into
	path.Flatten();
	
	Gdiplus::PathData pathData;
	path.GetPathData(&pathData);

	// print the path's data points to terminal
	for (INT j = 0; j < pathData.Count; ++j) {
		//start of new figure marker
		if ((int)pathData.Types[j] == 0) {
			//std::cout << "START\n";
			outputFile << "START\n";

		}

		//std::cout << "(" << pathData.Points[j].X << ", " << -pathData.Points[j].Y << ")\n";
		outputFile << pathData.Points[j].X << "\n" << -pathData.Points[j].Y << "\n";
	}
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

	//create fille for writing output to
	outputFile.open("path.txt");

	std::cout << "Input String: \n";

	std::wstring s;
	std::wcin >> s;

	//convert to WCHAR*
	const WCHAR* result = s.c_str();

	//get string path
	stringToPath(result);

	std::cout << "Path saved in path.txt. \n";

	//Shutdown GDI+ when finished using
	Gdiplus::GdiplusShutdown(token);

	outputFile.close();
}
