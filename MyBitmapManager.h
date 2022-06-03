#pragma once

#include <wrl/client.h>
#include <d2d1.h>
#include <map>
#include <string>
#include <wincodec.h>
#include "D2DFramework.h"
#include "ComException.h"

namespace solitaire
{
	class MyBitmapManager
	{
	public:
		static MyBitmapManager& GetInstance();

		HRESULT Initialize(ID2D1HwndRenderTarget* pRT);
		void Release();

		ID2D1Bitmap* LoadBitmapVersionTwo(std::wstring filename);
	
	private:
		MyBitmapManager() = default;
		MyBitmapManager(const MyBitmapManager& other);
		MyBitmapManager& operator=(const MyBitmapManager& other) {}

		HRESULT LoadWICBitmapImg(std::wstring filename, ID2D1Bitmap** ppBitmap);

	private:
		ID2D1HwndRenderTarget* mpRenderTarget{};
		Microsoft::WRL::ComPtr<IWICImagingFactory> mcpWICFactory{};
		std::map<std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>> mBitmapResources;


	};

}

