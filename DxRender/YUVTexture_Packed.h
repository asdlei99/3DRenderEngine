/**
 *	@author		zhuqingquan
 *	@date		2014-11-19
 *	@name		YUVTexture_Packed.h
 *	@brief		�������ڴ沼�ֵ�YUV�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_YUY2����
 */

#pragma once
#ifndef _ZRENDER_YUVTEXTURE_PACKED_H_
#define _ZRENDER_YUVTEXTURE_PACKED_H_

#include "DxZRenderDLLDefine.h"
#include "IDisplayContentProvider.h"
#include "IRawFrameTexture.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace zRender
{
	/**
	 *	@name	YUVTexture_Packed
	 *	@brief	�������ڴ沼�ֵ�YUV�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_YUY2����
	 **/
	class DX_ZRENDER_EXPORT_IMPORT YUVTexture_Packed : public IRawFrameTexture
	{
	public:
		/**
		 *	@name		YUVTexture_Packed
		 *	@brief		���캯����ֻ�ǹ��������û���ڴ˴���Texture��Դ
		 *				�������ɹ��������create�ӿڴ���Texture��Դ
		 *	@param[in]	PIXFormat pixfmt �������ڴ沼�ֵ�YUVͼƬ�������ڴ��ŵĸ�ʽ��������PIXFMT_YUY2���������������µ���createʧ��
		 **/
		YUVTexture_Packed(PIXFormat pixfmt);

		/**
		 *	@name		~YUVTexture_Packed
		 *	@brief		�����������ͷ��Ѿ�������Texture��Դ
		 **/
		~YUVTexture_Packed();

		/**
		 *	@name		create
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int create(ID3D11Device* device, int width, int height,
					const char* initData, int dataLen);

		/**
		 *	@name		destroy
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int destroy();

		/**
		 *	@name		getTexture
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int getTexture(ID3D11Texture2D** outYUVTexs, int& texsCount) const;

		/**
		 *	@name		getShaderResourceView
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int getShaderResourceView(ID3D11ShaderResourceView** outYUVSRVs, int& srvsCount) const;

		/**
		 *	@name		update
		 *	@brief		ʹ��pDataָ����ڴ��е����ݸ���Texture�����ݽ���������Texture�и���Textureԭ�е�����
		 *	@param[in]	const unsigned char* pData ��Ҫ���¿�����Texture�е����ݵ��ڴ��ַ
		 *				��Щ���ݽ�����Ϊ�������������Textureһ�������ݣ������͵�YUV���ݣ���YUY2�������dataLen����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int dataLen	pDataָ������ݵĳ��ȡ�����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int yPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int uPitch	ͼƬ���ݵ��п���YUY2��ʽ�иò�����Ч
		 *	@param[in]	int vPitch	ͼƬ���ݵ��п���YUY2��ʽ�иò�����Ч
		 *	@param[in]	int width	ͼƬ�Ŀ�,����>0
		 *	@param[in]	int height  ͼƬ�ĸ�,����>0
		 *	@param[in]	const RECT& regionUpdated ͼƬ�����ݽ������������򣬸���������ݽ�������Texture�����Ͻ����λ��
		 *	@param[in]	ID3D11DeviceContext* d3dDevContex ���Texture������ID3D11Device�����Ӧ��ID3D11DeviceContext����
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		int update(const unsigned char* pData, int dataLen, int yPitch, int uPitch, int vPitch, int width, int height,
							const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);

		virtual int update(SharedTexture* pSharedTexture, const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
	private:
		YUVTexture_Packed(const YUVTexture_Packed&);
		YUVTexture_Packed& operator=(const YUVTexture_Packed&);

		struct FrameTexture
		{
			ID3D11Texture2D* m_yuvTexStage;

			ID3D11Texture2D* m_yuvTex;
			ID3D11Texture2D* m_parityTex;
			ID3D11ShaderResourceView*	m_yuvSRV;
			ID3D11ShaderResourceView*	m_paritySRV;
			int m_width;
			int m_height;
			PIXFormat m_pixfmt;

			FrameTexture() 
				: m_width(0), m_height(0)
				, m_yuvTexStage(NULL)
				, m_yuvTex(NULL), m_parityTex(NULL)
				, m_yuvSRV(NULL), m_paritySRV(NULL)
			{

			}

			void destroy();

			int update(const unsigned char* pData, int dataLen, int yPitch, int uPitch, int vPitch, int width, int height,
				const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
			int getTexture(ID3D11Texture2D** outYUVTexs, int& texsCount) const;
			int getShaderResourceView(ID3D11ShaderResourceView** outYUVSRVs, int& srvsCount) const;
			bool valid() const;
		};
		FrameTexture m_VideoFrame;

		FrameTexture create_txframe(ID3D11Device* device, int width, int height,
			const char* initData, int dataLen);
	};
}

#pragma warning(pop)

#endif ///_ZRENDER_YUVTEXTURE_PACKED_H_