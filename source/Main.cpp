#include <Windows.h>
#include "res.h"


HINSTANCE hInst;
int widthSize;
int heightSize;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		PostQuitMessage(0);
		return TRUE;

	case WM_LBUTTONDOWN:
		CHAR szText[200];
		wsprintf(szText, "Mouse clicked in x = %d, y = %d", LOWORD(lParam), HIWORD(lParam));
		MessageBox(hwndDlg, szText, TEXT("Click Position"), MB_OK);
		return TRUE;

  case WM_PAINT:  //Rysowanie okna
    HDC hDC; // uchwyt do kontekstu urz¹dzenia 
    hDC = GetDC(hwndDlg); // pobranie uchwytu do kontekstu okna 

    

    //Dodawanie t³a
    HBITMAP hBitmap;
    hBitmap = (HBITMAP) LoadImage(NULL, "..\\source\\661.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    HDC hDCBitmap;

    RECT myStrecher;
    GetWindowRect(hwndDlg, &myStrecher);
    widthSize = myStrecher.right - myStrecher.right;
    heightSize = myStrecher.bottom - myStrecher.top;

    hDCBitmap = CreateCompatibleDC(hDC); //Utworzenie kopatybilengo kontekstu  
    SelectObject(hDCBitmap, hBitmap); //Wybranie bitmapy w kontekscie 
    BitBlt(hDC, 0, 0, 500, 275, hDCBitmap, 0, 0, SRCCOPY); //Skopiowanie obrazu

    SetStretchBltMode(hDCBitmap, HALFTONE);
    StretchBlt(hDCBitmap, 0, 0, widthSize, heightSize, hDCBitmap, 0, 0, 400, 400, SRCCOPY);

    DeleteDC(hDCBitmap); //Usuniecie kontekstu 
    DeleteObject(hBitmap);

    SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));    //Pobranie i aktywacja                   
                                                         //czcionki 
    SetTextColor(hDC, RGB(255, 0, 0));                   //Ustawienie koloru 
    TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27);
    ReleaseDC(hwndDlg, hDC); // Zwolnienie kontekstu urz¹dzenia 
    break;


	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED: // Works. Commented, because not needed at the moment.
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON1:
				MessageBox(hwndDlg, TEXT("Test"), TEXT("Clicked Test Button"), MB_OK);
				HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
				int iTextLength = GetWindowTextLength(hwndEditBox);
				CHAR szText[50];
				GetWindowText(hwndEditBox, szText, iTextLength + 1);

				SetWindowText((HWND)lParam, szText);

				return TRUE;
			}
			
			return TRUE;
		/*case EN_CHANGE: // STACK OVERFLOW. CHECK IF CHANGED. IF SO - CHANGE. IF NOT - MISS INSTRUCTIONS.
			HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
			int iTextLength = GetWindowTextLength(hwndEditBox);
			CHAR szText[50];
			GetWindowText(hwndEditBox, szText, iTextLength + 1);

			// ERROR WHILE USING THIS FUNCTION
			SetWindowText(HWND(lParam), szText);

			return TRUE;*/
		}
		return FALSE;
	}
	return FALSE;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
	ShowWindow(hwndMainWindow, iCmdShow);
  hInst = hInstance;
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}