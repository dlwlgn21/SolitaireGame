#include "MyBitmapManager.h"

using namespace Microsoft::WRL;
using namespace std;

namespace solitaire
{
	MyBitmapManager& MyBitmapManager::GetInstance()
	{
		static MyBitmapManager instance;
		return instance;
	}

	HRESULT MyBitmapManager::Initialize(ID2D1HwndRenderTarget* pRT)
	{
		if (pRT == nullptr)
		{
			OutputDebugStringA("nullptr error MyBitmapManager::Initialize ");
			return E_FAIL;
		}
		HRESULT hr;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(mcpWICFactory.GetAddressOf())
		);
		ThrowIfFailed(hr, "Error while CoCreateInstance");

		mpRenderTarget = pRT;


		return S_OK;
	}
	HRESULT MyBitmapManager::LoadWICBitmapImg(std::wstring filename, ID2D1Bitmap** ppBitmap)
	{
		HRESULT hr;
		ComPtr<IWICBitmapDecoder> decoder;

		hr = mcpWICFactory->CreateDecoderFromFilename(
			filename.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			decoder.GetAddressOf()
		);

		ThrowIfFailed(hr, "Error while CreateDecoderFromFilename()");
		ComPtr<IWICBitmapFrameDecode> frame;

		hr = decoder->GetFrame(0, frame.GetAddressOf());
		ThrowIfFailed(hr, "Error while GetFrame()");

		ComPtr<IWICFormatConverter> converter;
		hr = mcpWICFactory->CreateFormatConverter(converter.GetAddressOf());
		ThrowIfFailed(hr, "Error while CreateFormatConverter()");


		hr = converter->Initialize(
			frame.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0,
			WICBitmapPaletteTypeCustom
		);
		ThrowIfFailed(hr, "Error converter->Initialize()");

		hr = mpRenderTarget->CreateBitmapFromWicBitmap(
			converter.Get(),
			ppBitmap
		);

		ThrowIfFailed(hr, "Error CreateBitmapFromWicBitmap()");

		return S_OK;
	}

	HRESULT MyBitmapManager::LoadBitmapWithScale(std::wstring filename, ID2D1Bitmap** ppBitmap, float xScale, float yScale)
	{
		HRESULT hr;
		ComPtr<IWICBitmapDecoder> decoder;

		hr = mcpWICFactory->CreateDecoderFromFilename(
			filename.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			decoder.GetAddressOf()
		);

		ThrowIfFailed(hr, "Error while CreateDecoderFromFilename()");
		ComPtr<IWICBitmapFrameDecode> frame;

		hr = decoder->GetFrame(0, frame.GetAddressOf());
		ThrowIfFailed(hr, "Error while GetFrame()");
		
		ComPtr<IWICBitmapScaler> scalerer;
		hr = mcpWICFactory->CreateBitmapScaler(scalerer.GetAddressOf());
		ThrowIfFailed(hr, "Error while CreateBitmapScaler()");
		
		// TODO : MUST CHECK ERORR
		UINT width;
		UINT height;
		frame.Get()->GetSize(&width, &height);

		hr = scalerer->Initialize(
			frame.Get(),
			static_cast<UINT>(width * xScale),
			static_cast<UINT>(height * yScale),
			WICBitmapInterpolationModeFant
		);
		ThrowIfFailed(hr, "Error while IWICBitmapScaler->Initialize()");


		ComPtr<IWICFormatConverter> converter;
		hr = mcpWICFactory->CreateFormatConverter(converter.GetAddressOf());
		ThrowIfFailed(hr, "Error while CreateFormatConverter()");


		hr = converter->Initialize(
			frame.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0,
			WICBitmapPaletteTypeCustom
		);
		ThrowIfFailed(hr, "Error converter->Initialize()");

		hr = mpRenderTarget->CreateBitmapFromWicBitmap(
			converter.Get(),
			ppBitmap
		);

		ThrowIfFailed(hr, "Error CreateBitmapFromWicBitmap()");
		return S_OK;
	}

	void MyBitmapManager::Release()
	{
		for (auto& e : mBitmapResources)
		{
			e.second.Reset();
		}
		mBitmapResources.clear();
		mcpWICFactory.Reset();
	}

	ID2D1Bitmap* MyBitmapManager::LoadBitmapVersionTwo(std::wstring filename)
	{
		HRESULT hr;
		auto result = mBitmapResources.insert({ filename, nullptr });
		if (result.second == true)
		{
			ComPtr<ID2D1Bitmap> pBitmap = ComPtr<ID2D1Bitmap>();
			hr = LoadWICBitmapImg(filename, pBitmap.GetAddressOf());
			ThrowIfFailed(hr, "Error While IN LoadBitmap, LoadWICBitmapImg() ");
			result.first->second = pBitmap;
		}

		return result.first->second.Get();
	}

	ID2D1Bitmap* MyBitmapManager::LoadBitmapScaleVerson(std::wstring filename, float xScale, float yScale)
	{
		HRESULT hr;
		auto result = mBitmapResources.insert({ filename, nullptr });
		if (result.second == true)
		{
			ComPtr<ID2D1Bitmap> pBitmap = ComPtr<ID2D1Bitmap>();
			hr = LoadBitmapWithScale(filename, pBitmap.GetAddressOf(), xScale, yScale);
			ThrowIfFailed(hr, "Error While IN LoadBitmap, LoadWICBitmapImg() ");
			result.first->second = pBitmap;
		}

		return result.first->second.Get();
	}

}
