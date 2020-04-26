#pragma once
#ifndef _Z_RENDER_TEXTURE_RESOURCE_H_
#define _Z_RENDER_TEXTURE_RESOURCE_H_

#include "DxRenderCommon.h"
#include "DxZRenderDLLDefine.h"
#include <D3D11.h>
#include "DxRender.h"

namespace zRender
{
	struct DX_ZRENDER_EXPORT_IMPORT ITextureResource
	{
		virtual ~ITextureResource() = 0 {}

		virtual int create(DxRender* render, const TextureSourceDesc& srcDesc, TEXTURE_USAGE usage) = 0;
		virtual void release() = 0;
		virtual int createResourceView() = 0;
		virtual void releaseResourceView() = 0;
		virtual int update(const TextureSourceDesc& srcDesc) = 0;
		virtual int getTextures(ID3D11Texture2D** outTexs, int& texsCount) const = 0;
		virtual int getResourceView(ID3D11ShaderResourceView** outSRVs, int& srvsCount) const = 0;
		virtual int copyResource(const ITextureResource* res) = 0;
		virtual ITextureResource* copy() = 0;
		virtual int acquireSync(int key, unsigned int timeout) = 0;
		virtual int releaseSync(int key) = 0;

		virtual PIXFormat getSrcPixelFormat() const = 0;
		virtual bool valid() const = 0;
	};

	class DX_ZRENDER_EXPORT_IMPORT TextureResource : public ITextureResource
	{
	public:
		TextureResource();
		virtual ~TextureResource();

		virtual int create(DxRender* render, const TextureSourceDesc& srcDesc, TEXTURE_USAGE usage);
		int create(ID3D11Device* device, int width, int height, DXGI_FORMAT dxgifmt, TEXTURE_USAGE usage, bool bShared, const char* initData, int dataLen, int pitch);
		virtual void release();
		virtual int update(const TextureSourceDesc& srcDesc);
		
		int width() const { return m_width; }
		int height() const { return m_height; }
		DXGI_FORMAT pixfmt() const { return m_dxgifmt; }
		TEXTURE_USAGE usage() const { return m_usage; }
		virtual PIXFormat getSrcPixelFormat() const { return m_pixfmt; }
		virtual bool valid() const { return m_texture != NULL; }

		virtual int createResourceView();
		virtual void releaseResourceView();
		virtual int getResourceView(ID3D11ShaderResourceView** outSRVs, int& srvsCount) const;
		//ID3D11ShaderResourceView* getResourceView() const { return m_rsv; }
		//ID3D11Texture2D* getTexture() const { return m_texture; }

		virtual TextureResource* copy();
		virtual int copyResource(const ITextureResource* res);
		

		virtual int getTextures(ID3D11Texture2D** outTexs, int& texsCount) const;
		bool isShared() const { return m_bShared; }
		HANDLE getSharedHandle() const { return m_sharedHandle; }

		virtual int acquireSync(int key, unsigned int timeout);
		virtual int releaseSync(int key);

		bool dumpToFile(const TCHAR* filePathName);
		bool dumpToBuffer(unsigned char* outBuffer, int* in_outBufferLen, int* outPitch);
		int copyTexture(ID3D11Texture2D* d3dTex2D);
		int open(ID3D11Device* device, HANDLE sharedHandle);
	private:

		int update(const unsigned char* pData, int dataLen, int dataPitch, int width, int height,
			const RECT& regionUpdated);
		void getSharedHandleFromTexture();
	private:
		ID3D11Texture2D*			m_texture;		//init when call create()
		ID3D11ShaderResourceView*	m_rsv;			//init when call createResourceView()
		int m_width;
		int m_height;
		PIXFormat m_pixfmt;
		DXGI_FORMAT m_dxgifmt;
		TEXTURE_USAGE m_usage;
		bool m_bShared;
		HANDLE m_sharedHandle;						//be getted when call create() and bShared==true
		IDXGIKeyedMutex* m_resMutex;				//be getted when call create() and bShared==true

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
	};
}

#endif //_Z_RENDER_TEXTURE_RESOURCE_H_