/**
 *	@author		zhuqingquan
 *	@date		2014-11-19
 *	@name		YUVTexture_Planar.h
 *	@brief		ƽ�����ڴ沼�ֵ�YUV�������͵�ͼƬ���Կ�����ʾ�����Texture��Դ�࣬��ֻ֧��PIXFMT_YUV420P��PIXFMT_YV12����
 */


#pragma once
#ifndef _ZRENDER_YUVTEXTURE_H_
#define _ZRENDER_YUVTEXTURE_H_

#include <vector>
#include "DxRenderCommon.h"
#include "inc/RawFrameTextureBase.h"

namespace zRender
{
	/**
	 *	@name	YUVTexture_Planar
	 *	@brief	YUVͼƬ���Կ�����ʾ�����Texture��Դ�ֻ࣬������ƽ���������ڴ沼�ָ�ʽ��YUVͼƬ������YUV420P��I420����YV12
	 **/
	class YUVTexture_Planar : public RawFrameTextureBase
	{
	public:
		/**
		 *	@name		YUVTexture_Planar
		 *	@brief		���캯����ֻ�ǹ��������û���ڴ˴���Texture��Դ
		 *				�������ɹ��������create�ӿڴ���Texture��Դ
		 *	@param[in]	PIXFormat yuvFmt YUVͼƬ�������ڴ��ŵĸ�ʽ��������PIXFMT_YUV420P����PIXFMT_YV12���������������µ���createʧ��
		 **/
		YUVTexture_Planar(PIXFormat yuvFmt);

		/**
		 *	@name		~YUVTexture_Planar
		 *	@brief		�����������ͷ��Ѿ�������Texture��Դ
		 **/
		~YUVTexture_Planar();

		/**
		 *	@name		create
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int create(ID3D11Device* device, int width, int height,
					const char* initData, int dataLen);

		virtual int create(ID3D11Device* device, int width, int height, TEXTURE_USAGE usage, bool bShared, const char* initData, int dataLen, int pitch);

		/**
		 *	@name		destroy
		 *	@brief		�μ�����ӿ� @ref IRawFrameTexture �Ķ���˵��
		 **/
		int destroy();

		/**
		 *	@name		update
		 *	@brief		ʹ��pDataָ����ڴ��е����ݸ���Texture�����ݽ���������Texture�и���Textureԭ�е�����
		 *	@param[in]	const unsigned char* pData ��Ҫ���¿�����Texture�е����ݵ��ڴ��ַ
		 *				��Щ���ݽ�����Ϊ�������������Textureһ�������ݣ���YUV420P��YV12�������dataLen����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int dataLen	pDataָ������ݵĳ��ȡ�����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int yPitch	��Ϊ��YUVƽ�沼�֣�Yÿ�����ݵĵ��п�
		 *	@param[in]	int uPitch	��Ϊ��YUVƽ�沼�֣�Uÿ�����ݵĵ��п�
		 *	@param[in]	int vPitch	��Ϊ��YUVƽ�沼�֣�Vÿ�����ݵĵ��п�
		 *	@param[in]	int width	ͼƬ�Ŀ�,����>0
		 *	@param[in]	int height  ͼƬ�ĸ�,����>0
		 *	@param[in]	const RECT& regionUpdated ͼƬ�����ݽ������������򣬸���������ݽ�������Texture�����Ͻ����λ��
		 *	@param[in]	ID3D11DeviceContext* d3dDevContex ���Texture������ID3D11Device�����Ӧ��ID3D11DeviceContext����
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		int update(const unsigned char* pData, int dataLen, int yPitch, int uPitch, int vPitch, int width, int height,
							const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);

		virtual int update(SharedTexture* pSharedTexture, const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);

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
	private:
		YUVTexture_Planar(const YUVTexture_Planar&);
		YUVTexture_Planar& operator=(const YUVTexture_Planar&);

		struct FrameTexture
		{
			ID3D11Texture2D* m_yTexStage;
			ID3D11Texture2D* m_uTexStage;
			ID3D11Texture2D* m_vTexStage;

			ID3D11Texture2D* m_yTex;
			ID3D11Texture2D* m_uTex;
			ID3D11Texture2D* m_vTex;
			ID3D11ShaderResourceView*	m_ySRV;
			ID3D11ShaderResourceView*	m_uSRV;
			ID3D11ShaderResourceView*	m_vSRV;
			int m_width;
			int m_height;
			PIXFormat m_pixfmt;

			FrameTexture() 
				: m_width(0), m_height(0)
				, m_yTex(NULL), m_uTex(NULL), m_vTex(NULL)
				, m_ySRV(NULL), m_uSRV(NULL), m_vSRV(NULL)
				, m_yTexStage(NULL), m_uTexStage(NULL), m_vTexStage(NULL)
			{

			}

			void destroy();

			int update(const unsigned char* pData, int dataLen, int yPitch, int uPitch, int vPitch, int width, int height,
				const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex);
			virtual int update(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dDevContex, SharedTexture* pSharedTexture, const RECT& regionUpdated);
			int getTexture(ID3D11Texture2D** outYUVTexs, int& texsCount) const;
			int getShaderResourceView(ID3D11ShaderResourceView** outYUVSRVs, int& srvsCount) const;
			bool valid() const;
		};
		FrameTexture m_VideoFrame;

		FrameTexture create_txframe(ID3D11Device* device, int width, int height,
							const char* initData, int dataLen);
	};
}

#endif //_ZRENDER_YUVTEXTURE_H_