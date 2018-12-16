/*****************************************************************************
	File: main.cpp
	Author: ciaoSora
	Desc: Deal with Windows and DirectX stuffs
*****************************************************************************/

#include <windows.h>
#include <d3d9.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "utility.h"
#include "GameObject.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "winmm.lib")

//program settings
const string APPTITLE = "Snake";
const int SCREENW = 800;
const int SCREENH = 600;

//Direct3D objects
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 pDevice = NULL;
LPD3DXSPRITE pSprite = NULL;

bool gameover = false;
GameObject* gameobjects[10];

//macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// Game initialization function
bool DirectX_Init(HWND hwnd) {
	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(hwnd, "Error initializing Direct3D", "Error", MB_OK);
		return FALSE;
	}

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREENW;
	d3dpp.BackBufferHeight = SCREENH;
	d3dpp.hDeviceWindow = hwnd;

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&pDevice);

	if (pDevice == NULL) {
		MessageBox(hwnd, "Error creating Direct3D device", "Error", MB_OK);
		return FALSE;
	}

	HRESULT result = D3DXCreateSprite(pDevice, &pSprite);
	if (FAILED(result)) {
		MessageBox(hwnd, "Error creataing Sprite object", "Error", MB_OK);
		return FALSE;
	}

	srand(timeGetTime());

	gameobjects[0] = new Snake();
	gameobjects[1] = new Food();

	return TRUE;
}

// Game ready
void Game_Ready() {
	for (int i = 0; i < sizeof gameobjects / sizeof(GameObject*); ++i) {
		if (gameobjects[i]) {
			gameobjects[i]->Start();
		}
	}
}

// Game update function
void Game_Run(HWND hwnd) {
	if (!pDevice) {
		return;
	}

	util::UpdateDeltaTime();

	for (int i = 0; i < sizeof gameobjects / sizeof(GameObject*); ++i) {
		if (gameobjects[i]) {
			gameobjects[i]->Update();
		}
	}

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(247, 238, 214), 1.0f, 0);

	if (pDevice->BeginScene()) {
		pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < sizeof gameobjects / sizeof(GameObject*); ++i) {
			if (gameobjects[i]) {
				gameobjects[i]->Draw();
			}
		}

		pSprite->End();
		pDevice->EndScene();

		pDevice->Present(NULL, NULL, NULL, NULL);
	}

	if (KEY_DOWN(VK_ESCAPE)) {
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
		
}

// Game shutdown function
void DirectX_End(HWND hwnd) {
	if (pSprite) {
		pSprite->Release();
		pSprite = NULL;
	}
	if (pDevice) {
		pDevice->Release();
		pDevice = NULL;
	}
	if (d3d) {
		d3d->Release();
		d3d = NULL;
	}

	for (int i = 0; i < sizeof gameobjects / sizeof(GameObject*); ++i) {
		if (gameobjects[i]) {
			delete gameobjects[i];
			gameobjects[i] = NULL;
		}
	}
}


// Windows event handling function
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		gameover = true;
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Main Windows entry function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	MSG msg;

	//set the new window's properties
	//previously found in the MyRegisterClass function
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = "MainWindowClass";

	if (!RegisterClassEx(&wc)) {
		return FALSE;
	}


	RECT rect;
	rect.top = rect.left = 0;
	rect.right = SCREENW;
	rect.bottom = SCREENH;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);

	//create a new window
	//previously found in the InitInstance function
	HWND hwnd = CreateWindow("MainWindowClass", APPTITLE.c_str(),
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top, (HWND)NULL,
		(HMENU)NULL, hInstance, (LPVOID)NULL);

	if (hwnd == 0) {
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	if (!DirectX_Init(hwnd)) {
		return FALSE;
	}

	Game_Ready();
	while (!gameover) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Game_Run(hwnd);
	}

	DirectX_End(hwnd);

	return msg.wParam;
}
