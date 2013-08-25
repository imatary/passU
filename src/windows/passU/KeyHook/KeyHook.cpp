#include <Windows.h>

HINSTANCE g_hInstance;		// Instance Handle

HHOOK	g_hKeyboardHook;	// KeyBoard Hook Handle
HHOOK	g_hMouseHook;		// Mouse Hook Handle

// Shared DATA
#pragma data_seg(".shared")
HWND g_hWnd = NULL;		// Main hwnd. We will get this from the App
#pragma data_seg()

char *szMessageString(int ID);

/* _______________________________________________________________________________ 

		Get Window Handle
_______________________________________________________________________________  */

extern "C" __declspec(dllexport)
void SetWindowHandleToDll(HWND hWnd)
{
	g_hWnd = hWnd;
}

/* _______________________________________________________________________________ 

		Hook Procedure
_______________________________________________________________________________  */

// Keyboard Hook Procedure
extern "C" __declspec(dllexport)
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	//TCHAR s[256];
									
	KBDLLHOOKSTRUCT *pKey = (KBDLLHOOKSTRUCT *)lParam;

		//MessageBox(g_hWnd, "keyboardHook", "vkCode : ", MB_OK);
	


	if(nCode<0)
		return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);

	
	if(wParam == WM_KEYDOWN){
		
	//	MessageBox(g_hWnd, "hellokey",0,0);
		
		//SendMessage(g_hWnd, (WM_USER + 1001) , wParam, lParam); // keyboard message

	}

	// MessageBox(NULL, "Keyboard", "Hook", MB_OK);  <-- ¥������ ��..

//	return 1;		// ���� ��ü�ο� �޽��� ���� ����--> �ڱ� �����ε� Ű���� �޼����� �� �޴´�?
	return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport)
LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam){
	if(nCode < 0 )
		return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);

	if(wParam == WM_LBUTTONDOWN){ // ���� ��ư DOWN
	//	MessageBox(g_hWnd, "LBUTTONDOWN", "WM_LBUTTONDOWN", MB_OK);
	
	} else if (wParam == WM_LBUTTONUP){ // ���� ��ư UP
	
	//	MessageBox(g_hWnd, "LBUTTONUP", "WM_LBUTTONUP", MB_OK);
	
	} else if (wParam == WM_RBUTTONDOWN){ // ������ ��ư DOWN
		
	//	MessageBox(g_hWnd, "RBUTTONDOWN", "WM_RBUTTONDOWN", MB_OK);
	
	} else if(wParam == WM_RBUTTONUP){ // ������ ��ư UP
		
	//	MessageBox(g_hWnd, "RBUTTONUP", "WM_RBUTTONUP", MB_OK);
	
	} else if(wParam == WM_MOUSEWHEEL){ // �� ������ ��
		
	//	MessageBox(g_hWnd, "MOUSEWHEEL", "WM_MOUSEWHEEL", MB_OK);
	
	//} else if(wParam == WM_MOUSEMOVE){ // ���콺 ������ ��
	//		
	//	//MessageBox(g_hWnd, "MOUSEMOVE", "WM_MOUSEMOVE", MB_OK);
	//
	} else if(wParam == WM_MBUTTONDOWN){ // �� ��ư DOWN
			
		MessageBox(g_hWnd, "MBUTTONDOWN", "WM_MBUTTONDOWN", MB_OK);
	
	} else if(wParam == WM_MBUTTONUP){ // �� ��ư UP
			
		MessageBox(g_hWnd, "MBUTTONUP", "WM_MBUTTONUP", MB_OK);
	
	}

	return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

/* _______________________________________________________________________________ 

		Install Method (Hook)
_______________________________________________________________________________  */

// WH_KEYBOARD : Ű���� ��ŷ
extern "C" __declspec(dllexport)
HHOOK InstallKeyboardHook()
{
	g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookProc, g_hInstance, 0);

	return g_hKeyboardHook;
}

// WH_MOUSE_LL ���콺 ��ŷ
extern "C" __declspec(dllexport)
HHOOK InstallMouseHook(){
	g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, g_hInstance, 0);


	return g_hMouseHook;
}

/* _______________________________________________________________________________ 

		Uninstall Method (Hook)
_______________________________________________________________________________  */

// Keyboard�� �� ���ν����� �����Ѵ�.
extern "C" __declspec(dllexport)
void UnInstallKeyboardHook()
{
	UnhookWindowsHookEx(g_hKeyboardHook);
}

// Mouse ��ŷ ����
extern "C" __declspec(dllexport)
void UnInstallMouseHook()
{
	UnhookWindowsHookEx(g_hMouseHook);
}

/* _______________________________________________________________________________ 

		Dll Main
_______________________________________________________________________________  */

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD fdwReason,LPVOID lpRes)
{
	g_hInstance = hInst;
	return TRUE;
}