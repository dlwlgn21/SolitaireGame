#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <sstream>
#include "D2DFramework.h"
#include "MyBitmapManager.h"
#include "SolitaireGameManager.h"
#pragma comment (lib, "d2d1.lib")

using namespace solitaire;
HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WndProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"FAILED TO REGISTER", L"ERROR", MB_OK);
		return 0;
	}

	RECT rc{ 0, 0, 
		static_cast<LONG>(width), 
		static_cast<LONG>(height) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowEx(
		NULL,
		WINDOW_CLASS_NAME,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"FAILED TO CreateWindowEx", L"ERROR", MB_OK);
		return 0;
	}

	mHwnd = hwnd;

	// instance를 hwnd에 붙이는 것.
	SetWindowLongPtr(mHwnd, GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>(this));

	return S_OK;
}

HRESULT D2DFramework::InitD2D(HWND hwnd)
{
	HRESULT hr;
	// 1. D2D Factory 만들기 
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, 
		mspD2DFactory.GetAddressOf()
	);
	// Thread - 나혼자 바쁘게 일하는 것처럼 여러개 일을 함. 하나 뻗으면 다 뻗음

	/*
	if (FAILED(hr))
	{
		ShowErrorMsg(L"Failed To Create D2D Factory!");
		return hr;
	}
	*/
	
	ThrowIfFailed(hr);

    return CreateDeviceResources();
}

HRESULT D2DFramework::CreateDeviceResources()
{
	// 2. RenderTarget 생성
	RECT rc;
	GetClientRect(mHwnd, &rc);
	HRESULT hr = mspD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			mHwnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		mspRenderTarget.GetAddressOf()
	);
	ThrowIfFailed(hr);
	return hr;
}

HRESULT D2DFramework::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
	HRESULT hr;

	hr = CoInitialize(nullptr);
	ThrowIfFailed(hr);

	hr = InitWindow(hInstance, title, width, height);
	ThrowIfFailed(hr);

	hr = InitD2D(mHwnd);
	ThrowIfFailed(hr);

	hr = MyBitmapManager::GetInstance().Initialize(mspRenderTarget.Get());
	ThrowIfFailed(hr, "Failed To Initialze BitmapManager");

	// SH_SHOW 창모드로 실행해줌.
	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);
	return S_OK;
}

void D2DFramework::Release()
{
	mspRenderTarget.Reset();
	mspD2DFactory.Reset();
	CoUninitialize();
}

void D2DFramework::Render()
{
	HRESULT hr;
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	hr = mspRenderTarget->EndDraw();
	
	// RenderTarget 다시 만들어야 된다고 보낸 것.
	// 장치종속적인 자원이 Device Lost에 대처하는 방법.
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

int D2DFramework::GameLoop()
{
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, mHwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			Render();
		}
	}
	Release();

	return static_cast<int>(msg.wParam);
}

void D2DFramework::ShowErrorMsg(LPCWSTR msg, HRESULT err, LPCWSTR title)
{
	std::wostringstream oss;
	oss << L"ERROR : " << err << std::endl;
	oss << msg;

	OutputDebugString(oss.str().c_str());

}

LRESULT CALLBACK D2DFramework::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	SolitaireGameManager* gm = reinterpret_cast<SolitaireGameManager*>
		(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	switch (msg)
	{
	case WM_LBUTTONUP:
	{
		char buffer[64];
		float mouseX = static_cast<float>(LOWORD(lp));
		float mouseY = static_cast<float>(HIWORD(lp));
		gm->OnClick(mouseX, mouseY);
		sprintf(buffer, "(X : %.3f, Y : %.3f)\n", mouseX, mouseY);
		OutputDebugStringA(buffer);
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}

	return 0;
}
