/**
 *	@date		2017-07-25
 *	@name		SharedFrameTexture.h
 *	@brief		Shared ID3D11Texture2D objs
 */

#pragma once
#ifndef _Z_RENDER_SHARED_FRAME_TEXTURE_H_
#define _Z_RENDER_SHARED_FRAME_TEXTURE_H_

#include "DxRenderCommon.h"
#include <d3d9.h>
#include <D3D11.h>
#include <string>

namespace zRender
{
	class SharedResource
	{
	public:
		SharedResource(HANDLE hRes, REFIID resIID);
		SharedResource();
		~SharedResource();

		//miplevels = 1, Stage, CPU_ACCESS_WRITE
		int create(ID3D11Device* pSrcDevice, ID3D11DeviceContext* devContex, DXGI_FORMAT fmt, int width, int height, int usage, const unsigned char* initData, int dataLen);
		int open(ID3D11Device* pOtherDevice, void** ppOpendSharedResource, IDXGIKeyedMutex** keyMutex);
		int open(IDirect3DDevice9Ex* pOtherDevice, void** ppOpendSharedResource);
		int update(ID3D11Device* pSrcDevice, ID3D11DeviceContext* devContex, int width, int height, const unsigned char* initData, int dataLen, int pitch);

		HANDLE getSharedHandle() const { return m_hRes; }
		ID3D11Texture2D* getTextureRes() const { return m_textureRes; }
		REFIID getTextureTypeID() const;
		DXGI_FORMAT getTextureFmt() const { return m_fmt; }
		//��create�����ˣ����ص��ַ�����ΪNULL�������Open����Դ�򷵻ص��ַ���Ϊ"".
		const std::wstring& getAdapterName() const { return m_strAdapter; }

		DWORD AcquireSync(DWORD timeout);
		DWORD ReleaseSync();
	private:
		void getAdapterName(ID3D11Device* pSrcDevice);

		HANDLE m_hRes;
		REFIID m_resIID;
		DXGI_FORMAT m_fmt;
		std::wstring m_strAdapter;
		//create�ӿ��д�������ڴ���Texture��Device�����Device��open�ӿ��е�Device���ܲ���ͬһ�������Ըù����Դ��ʹ����Ӧ�ò���ֱ��ʹ�����Texture
		ID3D11Texture2D* m_textureRes;
		IDXGIKeyedMutex* m_resMutex;
		UINT acqKey;
		UINT relKey;
	};//class SharedFrameTexture

	class SharedTexture
	{
	public:
		virtual ~SharedTexture() = 0 {};
		/**
		 *	@name		create
		 *	@brief		�����ɹ����Texture����Դ���ݵ������߸��𴴽����Texture
		 *				���ø÷����ɹ����û���ͨ��getSharedResource�ӿڻ�ȡ���ö����а����Ĺ���Texture��Դ
		 *				��SharedResource�����ṩ�ӿ�����open�����Texture
		 *	@param[in]	PIXFormat fmt Texture�����ظ�ʽ���ò���������SharedTexture�ڰ�����SharedResource�������
		 *	@param[in]	int width	ͼƬ�Ŀ�
		 *	@param[in]	int height  ͼƬ�ĸ�
		 *	@param[in]	const char* initData ��ʼ�������ݣ�NULL��ʾ���ڴ���ʱ��ʼ���������ṩͼƬ�������ݳ�ʼ��Texture
		 *	@param[in]	int dataLen ͼƬ�������ݵĳ��ȣ��ֽ������ó��ȱ�����ڻ����FRAMESIZE(width, height, pixfmt)
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		virtual int create(PIXFormat fmt, int width, int height,
							const unsigned char* initData, int dataLen, int yPitch, int uvPitch) = 0;

		/**
		 *	@name		release
		 *	@brief		�ͷ�create�����д�������Դ
		 *	@return		int 0--�ɹ�	<0--ʧ��
		 **/
		virtual int release() = 0;

		virtual int update(PIXFormat fmt, int width, int height,
			const unsigned char* initData, int dataLen, int yPitch, int uvPitch) = 0;
		
		/**
		 *	@name		getSharedResource
		 *	@brief		��ȡ��create�����д�����SharedResource�������
		 *				�û���ʹ�øö��У����踺���ͷţ��ö�����release֮���ٿ���
		 *	@param[out]	SharedResource** ppSharedRes ����SharedResource�������ָ��
		 *	@param[out]	int& count ��ȡSharedResource������еĸ���
		 *
		 *	@return		int SharedResource�����ж������
		 **/
		virtual int getSharedResource(SharedResource** ppSharedRes, int& count) = 0;

		virtual bool getDescription(PIXFormat& fmt, int& width, int& height) = 0;
	};

	class SharedTexture_ARGB8 : public SharedTexture
	{
	public:
		SharedTexture_ARGB8(ID3D11Device* pSrcDevice, ID3D11DeviceContext* devContex);
		~SharedTexture_ARGB8();

		virtual int create(PIXFormat fmt, int width, int height,
						const unsigned char* initData, int dataLen, int yPitch, int uvPitch);
		virtual int release();
		virtual int update(PIXFormat fmt, int width, int height,
			const unsigned char* initData, int dataLen, int yPitch, int uvPitch);
		virtual int getSharedResource(SharedResource** ppSharedRes, int& count);
		virtual bool getDescription(PIXFormat& fmt, int& width, int& height);
	private:
		SharedResource* m_resARGB;
	};

	class SharedTexture_I420P : public SharedTexture
	{
	public:
		SharedTexture_I420P(ID3D11Device* pSrcDevice, ID3D11DeviceContext* devContex);
		~SharedTexture_I420P();

		virtual int create(PIXFormat fmt, int width, int height,
							const unsigned char* initData, int dataLen, int yPitch, int uvPitch);
		virtual int release();
		virtual int update(PIXFormat fmt, int width, int height,
			const unsigned char* initData, int dataLen, int yPitch, int uvPitch);
		virtual int getSharedResource(SharedResource** ppSharedRes, int& count);
		virtual bool getDescription(PIXFormat& fmt, int& width, int& height);
	private:
		SharedResource* m_resList[3];
		int m_resCount;

		ID3D11Device* m_pSrcDevice;
		ID3D11DeviceContext* m_devContext;

		PIXFormat m_pixfmt;
		int m_width;
		int m_height;
	};
}

#endif //_Z_RENDER_SHARED_FRAME_TEXTURE_H_