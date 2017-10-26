/**
 *	@author		zhuqingquan
 *	@date		2014-11-19
 *	@name		ARGBTexture_8.h
 *	@brief		ARGB�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_A8R8G8B����,PIXFMT_R8G8B8��֧��
 */

#pragma once
#ifndef _ZRENDER_ARGB_TEXTURE_H_
#define _ZRENDER_ARGB_TEXTURE_H_

#include "IRawFrameTexture.h"

namespace zRender
{
	/**
	 *	@name		ARGBTexture_8
	 *	@brief		ARGB�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_A8R8G8B8���ͣ�PIXFMT_R8G8B8��֧��
	 */
	class ARGBTexture_8 : public IRawFrameTexture
	{
	public:
		/**
		 *	@name		ARGBTexture_8
		 *	@brief		���캯����ֻ�ǹ��������û���ڴ˴���Texture��Դ
		 *				�������ɹ��������create�ӿڴ���Texture��Դ
		 *	@param[in]	PIXFormat pixfmt ARGBͼƬ�������ڴ��ŵĸ�ʽ��������PIXFMT_A8R8G8B8���������������µ���createʧ��
		 **/
		ARGBTexture_8(PIXFormat pixfmt);

		/**
		 *	@name		~ARGBTexture_8
		 *	@brief		�����������ͷ��Ѿ�������Texture��Դ
		 **/
		~ARGBTexture_8();

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
		 *				��Щ���ݽ�����Ϊ�������������Textureһ�������ݣ���ARGB�������dataLen����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int dataLen	pDataָ������ݵĳ��ȡ�����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int yPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int uPitch	ͼƬ���ݵ��п�����RGB���ݱ�����������
		 *	@param[in]	int vPitch	ͼƬ���ݵ��п�����RGB���ݱ�����������
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
		ARGBTexture_8(const ARGBTexture_8&);
		ARGBTexture_8& operator=(const ARGBTexture_8&);
		struct FrameTexture
		{
			ID3D11Texture2D*			m_rgbTexStage;
			ID3D11Texture2D*			m_rgbTex;
			ID3D11ShaderResourceView*	m_rgbSRV;
			int m_width;
			int m_height;
			PIXFormat m_pixfmt;

			FrameTexture() 
				: m_width(0), m_height(0)
				, m_rgbTex(NULL)
				, m_rgbSRV(NULL)
				, m_rgbTexStage(NULL)
			{

			}

			void destroy();

			int update_A8R8G8B8(const unsigned char* pData, int dataLen, int dataPitch, int width, int height,
				const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
			int update_R8G8B8(const unsigned char* pData, int dataLen, int dataPitch, int width, int height,
				const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
			int getTexture(ID3D11Texture2D** outYUVTexs, int& texsCount) const;
			int getShaderResourceView(ID3D11ShaderResourceView** outYUVSRVs, int& srvsCount) const;
			bool valid() const;
		};
		FrameTexture create_txframe(ID3D11Device* device, int width, int height,
			const char* initData, int dataLen);

		FrameTexture m_VideoFrame;

		//int update_A8R8G8B8(const unsigned char* pData, int dataLen, int dataPitch, int width, int height,
		//	const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
		//int update_R8G8B8(const unsigned char* pData, int dataLen, int dataPitch, int width, int height,
		//	const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);

	};
}

#endif //_zRENDER_ARGB_TEXTURE_H_