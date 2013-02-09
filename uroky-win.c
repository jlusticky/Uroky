#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Josef Lusticky (C) 2012

const char * progname = "Uroky";

HWND hwndCastka; // pocatecni castka na uctu
HWND hwndUrok; // urok v procentech
HWND hwndRoky; // pocet roku vedeni sporeni
HWND hwndMesicnivklad; // mesicni vklad na ucet
HWND hwndPrispevek; // prispevek
HWND hwndVysledek; // vysledna nasporena castka

TCHAR buf[255];

enum hmenuID
{
	ID_LABEL,

	ID_CASTKA,
	ID_UROK,
	ID_ROKY,
	ID_MESICNIVKLAD,
	ID_PRISPEVEK,
	ID_MESICNE,
	ID_SPOCITAT,
	ID_VYSLEDEK,
};

void spocitej(BOOL prispevekmesicne)
{	
	int len;
	int droky;
	double dcastka;
	double durok;
	double dmesicnivklad;
	double dprispevek;
	
	len = GetWindowTextLength(hwndCastka) + 1;
	if (len > 255)
	{
		goto bignumber;
	}
	GetWindowText(hwndCastka, buf, len);
	dcastka = strtod(buf, NULL);
	
	len = GetWindowTextLength(hwndUrok) + 1;
	if (len > 255)
	{
		goto bignumber;
	}
	GetWindowText(hwndUrok, buf, len);
	char *comma = strchr(buf, ',');
	if (comma != NULL)
	{
		*comma = (char) '.';
	}
	durok = strtod(buf, NULL);
	
	len = GetWindowTextLength(hwndMesicnivklad) + 1;
	if (len > 255)
	{
		goto bignumber;
	}
	GetWindowText(hwndMesicnivklad, buf, len);
	dmesicnivklad = strtod(buf, NULL);
	
	len = GetWindowTextLength(hwndPrispevek) + 1;
	if (len > 255)
	{
		goto bignumber;
	}
	GetWindowText(hwndPrispevek, buf, len);
	dprispevek = strtod(buf, NULL);
	
	
	len = GetWindowTextLength(hwndRoky) + 1;
	if (len > 255)
	{
		goto bignumber;
	}
	GetWindowText(hwndRoky, buf, len);
	droky = strtoul(buf, NULL, 10);

/*	
	printf("dcastka %f\n", dcastka);
	printf("durok %f\n", durok);
	printf("dmesicnivklad %f\n", dmesicnivklad);
	printf("dprispevek %f\n", dprispevek);
*/
	
	durok /= (double) 12; // mesicni urok
	durok /= 100; // na procenta
	durok += 1; // nasobeni
	
	int i,j;
	for (i = 0; i < droky ; i++)
	{
		for (j = 0; j < 12; j++)
		{
			dcastka += dmesicnivklad;
			if (prispevekmesicne)
			{
				dcastka += dprispevek;
			}
			dcastka = dcastka * durok;
		}
		if (!prispevekmesicne)
		{
			dcastka += dprispevek; // rocni prispevek
		}
	}
	char buf[255];
	snprintf(buf, sizeof(buf), "%f", dcastka);
	
	SetWindowText(hwndVysledek, buf);
	
	return;
	
bignumber:
	SetWindowText(hwndVysledek, "CHYBA: Prilis velke cislo");
	return;
}

void AddMenus(HWND hwnd)
{
	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, "&New");
	AppendMenu(hMenu, MF_STRING, IDM_FILE_OPEN, "&Open");
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, IDM_FILE_QUIT, "&Quit");

	//AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, "&File");
	SetMenu(hwnd, hMenubar);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			AddMenus(hwnd);

			CreateWindow(TEXT("STATIC"), "Soucasna castka na uctu:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 20, 290, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndCastka = CreateWindow(TEXT("Edit"), TEXT("10000"), ES_NUMBER | WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 20, 150, 20, hwnd, (HMENU) ID_CASTKA, NULL, NULL);
				
				
			CreateWindow(TEXT("STATIC"), "Urok v procentech:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 45, 290, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndUrok = CreateWindow(TEXT("Edit"), TEXT("1.50"), WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 45, 150, 20, hwnd, (HMENU) ID_UROK, NULL, NULL);
				
				
			CreateWindow(TEXT("STATIC"), "Pocet roku vedeni sporeni:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 70, 290, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndRoky = CreateWindow(TEXT("Edit"), TEXT("5"), ES_NUMBER | WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 70, 150, 20, hwnd, (HMENU) ID_ROKY, NULL, NULL);
				
				
			CreateWindow(TEXT("STATIC"), "Mesicni vklad:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 95, 290, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndMesicnivklad = CreateWindow(TEXT("Edit"), TEXT("300"), ES_NUMBER | WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 95, 150, 20, hwnd, (HMENU) ID_MESICNIVKLAD, NULL, NULL);
				
			
			CreateWindow(TEXT("STATIC"), "Prispevek:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 120, 290-90, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndPrispevek = CreateWindow(TEXT("Edit"), TEXT("200"), ES_NUMBER | WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 120, 150, 20, hwnd, (HMENU) ID_PRISPEVEK, NULL, NULL);

			CreateWindow(TEXT("button"), TEXT("Mesicne"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
				310-90, 120, 90, 20, hwnd, (HMENU) ID_MESICNE, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			//CheckDlgButton(hwnd, ID_MESICNE, BST_CHECKED);
			
			CreateWindow(TEXT("button"), TEXT("Spocitat"), WS_VISIBLE | WS_CHILD,
				310, 145, 150, 20, hwnd, (HMENU) ID_SPOCITAT, NULL, NULL);
				
				
			CreateWindow(TEXT("STATIC"), "Vysledna nasporena castka:", WS_CHILD | WS_VISIBLE | SS_LEFT,
				10, 170, 290, 20, hwnd, (HMENU) ID_LABEL, NULL, NULL);
				
			hwndVysledek = CreateWindow(TEXT("Edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
				310, 170, 150, 20, hwnd, (HMENU) ID_VYSLEDEK, NULL, NULL);
			
			break;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == ID_SPOCITAT)
			{
				BOOL prispevekmesicne = IsDlgButtonChecked(hwnd, ID_MESICNE);
				spocitej(prispevekmesicne);
			}
			else if (LOWORD(wParam) == ID_MESICNE)
			{
				BOOL checked = IsDlgButtonChecked(hwnd, ID_MESICNE);
				if (checked)
				{
					CheckDlgButton(hwnd, ID_MESICNE, BST_UNCHECKED);
					
				}
				else
				{
					CheckDlgButton(hwnd, ID_MESICNE, BST_CHECKED);
				}
			}
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int CmdShow)
{
	MSG msg;
	WNDCLASS wc = {0}; /// FIX
	wc.lpszClassName = TEXT(progname);
	wc.hInstance     = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = WndProc;
	wc.hCursor       = LoadCursor(0,IDC_ARROW);
  
	RegisterClass(&wc);
	CreateWindow(wc.lpszClassName, TEXT(progname), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 250, 250, 500, 300, 0, 0, hInstance, 0);  

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return (int)msg.wParam;
}
