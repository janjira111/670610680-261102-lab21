#include <windows.h>
#include <stdio.h>

double num1, num2, result;
char t1[100], t2[100], resultt[100];

HWND textfield, buttonadd, buttonsub, buttonmul, buttondiv, textbox1, textbox2;

/* This is where all the input to the window goes to */

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

	switch (Message)
	{

		/* Upon destruction, tell the main thread to stop */

	case WM_CREATE:
		textfield = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | WS_BORDER, 33, 20, 170, 22, hwnd, NULL, NULL, NULL);
		textbox1 = CreateWindow("EDIT", " ", WS_BORDER | WS_CHILD | WS_VISIBLE, 43, 50, 150, 22, hwnd, NULL, NULL, NULL);
		textbox2 = CreateWindow("EDIT", " ", WS_BORDER | WS_CHILD | WS_VISIBLE, 43, 80, 150, 22, hwnd, NULL, NULL, NULL);

		buttonadd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 115, 25, 25, hwnd, (HMENU)1, NULL, NULL);
		buttonsub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER, 87, 115, 25, 25, hwnd, (HMENU)2, NULL, NULL);
		buttonmul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER, 124, 115, 25, 25, hwnd, (HMENU)3, NULL, NULL);
		buttondiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER, 161, 115, 25, 25, hwnd, (HMENU)4, NULL, NULL);

		break;

	case WM_COMMAND:

		if (HIWORD(wParam) == BN_CLICKED)
		{
			GetWindowText(textbox1, t1, sizeof(t1));
			GetWindowText(textbox2, t2, sizeof(t2));

			num1 = atof(t1);
			num2 = atof(t2);

			switch (LOWORD(wParam))
			{

			case 1:
				result = num1 + num2;
				break;
			case 2:
				result = num1 - num2;
				break;
			case 3:
				result = num1 * num2;
				break;
			case 4:
				if (num2 != 0)
					result = num1 / num2;
				else
				{
					::MessageBox(hwnd, "Error", "Result", MB_OK);
					return 0;
				}
				break;
			}
			sprintf(resultt, "%f", result);
			::MessageBeep(MB_ICONERROR);
			::MessageBox(hwnd, resultt, "Result", MB_OK);
		}
		break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	/* All other messages (a lot of them) are processed using default procedures */
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd;	   /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg;	   /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 235, 0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	  /* Load a standard icon */
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator", WS_VISIBLE | WS_SYSMENU,
						  CW_USEDEFAULT, /* x */
						  CW_USEDEFAULT, /* y */
						  250,			 /* width */
						  200,			 /* height */
						  NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{							/* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg);	/* Send it to WndProc */
	}
	return msg.wParam;
}
