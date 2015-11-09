/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
	Provides a fullscreen mode and icon to 
	http://www.winprog.org/tutorial/simple_window.html 
	Adapted into a class.
Date: 2014/05
----------------------------------------------*/
#ifndef __WINDOWCLASS_H_
#define __WINDOWCLASS_H_

#include <windows.h>
#include "Resource.h"
#include "RE\system\REDefinitions.h" //ReEng basic Definitions

namespace ReEng
{

class ReEngDLL WindowClass
{
	bool m_bFullscreen = false; //Run in fullscreen mode?
	bool m_bBorderless = false; //Run with borders?
	bool m_bWindowCrated = false; //Window has been created

	int m_nWindowPosX = 0; //Window position on screen (X)
	int m_nWindowPosY = 0; //Window position on screen (Y)
	
	int m_nWidth = 1080; //Window width
	int m_nHeight = 720; //Window height

	int m_nCommandShow = 0; //Number of arguments

	LPCWSTR m_sWindowName; //Name of the window
	HWND m_hWindowHandler; //Window handler

	HINSTANCE m_hInstance; //Window Instance
	WNDPROC m_Callback; //Associated Callback for this window
	
public:
	/*
	Constructor
	*/
	WindowClass(void);
	/*
	Constructor
	*/
	WindowClass(HINSTANCE a_hInstance, int a_nCmdShow, WNDPROC a_WndProc);

	/*
	void SetWindowInstance(HINSTANCE hInstance);
		Sets the window Instance
	*/
	void SetWindowInstance(HINSTANCE a_hInstance);

	/*
	void SetWindowCallback(WNDPROC WndProc);
		Sets the window callback
	*/
	void SetWindowCallback(WNDPROC a_WndProc);

	/*
	void SetIncomingArguments(int nCmdShow);
		Sets the number of incoming arguments
	*/
	void SetIncomingArguments(int a_nCmdShow);

	/*
	CreateMEWindow
		Creates window with the provided arguments
	Arguments:
		LPCWSTR windowName = L"Window" -> Name of the window
		int width = 1280 -> width of the window
		int height = 720 -> height of the window
	*/
	int CreateMEWindow(LPCWSTR a_windowName = L"Window", int a_nWidth = 1280, int a_nHeight = 720);

	/*
	GetHandler
		Returns the window handler
	*/
	HWND GetHandler(void);

	/*
	SetFullscreen(bool input = true)
		Sets whether or not the program will run in fullscreen
	*/
	void SetFullscreen(bool a_bInput = true);

	/*
	SetBorderless(bool input = true)
		Sets whether or not the window will be borderless
	*/
	void SetBorderless(bool a_bInput = true);

	/*
	void CreateConsoleWindow(void)
		Allocates a console window for output
	*/
	void CreateConsoleWindow(void);

private:
	/*
	Copy Constructor
	*/
	WindowClass(const WindowClass& other);

	/*
	Copy Assignment Operator
	*/
	WindowClass& operator=(const WindowClass& other);

	/*
	void Init(void);
		Initializes the member variables
	*/
	void Init(void);
};

}

#endif /*__WINDOWCLASS_H__*/