/**
 *	@author		zhuqingquan
 *	@date		2014-11-19
 *	@name		YUVTexture_Packed.h
 *	@brief		NV12���͵�YUV�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_NV12����
 */

#pragma once
#ifndef _ZRENDER_YUVTEXTURE_NV12_H_
#define _ZRENDER_YUVTEXTURE_NV12_H_

#include "IDisplayContentProvider.h"
#include "IRawFrameTexture.h"

namespace zRender
{
	class YUVTexture_NV12 : public IRawFrameTexture
	{
	public:
		/**
		 *	@name		YUVTexture_NV12
		 *	@brief		���캯����ֻ�ǹ��������û���ڴ˴���Texture��Դ
		 *				�������ɹ��������create�ӿڴ���Texture��Դ
		 *	@param[in]	PIXFormat pixfmt NV12�ڴ沼�ֵ�YUVͼƬ�������ڴ��ŵĸ�ʽ��������PIXFMT_NV12���������������µ���createʧ��
		 **/
		YUVTexture_NV12(PIXFormat pixfmt);

		/**
		 *	@name		~YUVTexture_NV12
		 *	@brief		�����������ͷ��Ѿ�������Texture��Դ
		 **/
		~YUVTexture_NV12();

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
		 *				��Щ���ݽ�����Ϊ�������������Textureһ�������ݣ�NV12�������dataLen����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int dataLen	pDataָ������ݵĳ��ȡ�����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int yPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int uPitch	ͼƬ���ݵ��п�uv���ݵ�ÿ�в���
		 *	@param[in]	int vPitch	ͼƬ���ݵ��п���������NV12��ʽ��������Ч
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
		YUVTexture_NV12(const YUVTexture_NV12&);
		YUVTexture_NV12& operator=(const YUVTexture_NV12&);

		ID3D11Texture2D* m_yTex;
		ID3D11Texture2D* m_uvTex;
		ID3D11ShaderResourceView*	m_ySRV;
		ID3D11ShaderResourceView*	m_uvSRV;
	};
}

#endif //_ZRENDER_YUVTEXTURE_NV12_H_