/**
 *	@author		zhuqingquan
 *	@date		2014-11-14
 *	@name		IRawFrameTexture.h
 *	@brief		ԭʼ����ͼ����ʾ���õ�Texture�ӿڶ��壬�ײ�ʹ��ID3D11Texture2Dʵ�֡�ͼ�����ݶ��ǽ���������ֵ
 *				YUVͼ��ARGBͼ�����ʾ���Լ̳иýӿڱ���ͼ������
 */

#pragma once
#ifndef _ZRENDER_IPICTURETEXTURE_H_
#define _ZRENDER_IPICTURETEXTURE_H_

#include <D3D11.h>
#include "DxRenderCommon.h"
#include "DxZRenderDLLDefine.h"

namespace zRender
{
	class SharedTexture;

	/**
	 * @name		IRawFrameTexture
	 * @brief		ԭʼ����ͼ����ʾ���õ�Texture�ӿڶ��壬�ײ�ʹ��ID3D11Texture2Dʵ�֡�ͼ�����ݶ��ǽ���������ֵ
	 *				YUVͼ��ARGBͼ�����ʾ���Լ̳иýӿڱ���ͼ������
	 **/
	class DX_ZRENDER_EXPORT_IMPORT IRawFrameTexture
	{
	public:
		/**
		 *  @name		IRawFrameTexture
		 *  @brief		���캯������ʼ������Ϊ0�����ݲ�����ʼ��ͼƬ����������
		 *	@param[in]	PIXFormat pixfmt ͼƬ����������
		 **/
		IRawFrameTexture(PIXFormat pixfmt) 
			: m_width(0), m_height(0), m_device(0), m_pixfmt(pixfmt) {};

		/**
		 *	@name		~IRawFrameTexture
		 *	@brief		��������
		 **/
		virtual ~IRawFrameTexture() = 0 {};

		/**
		 *	@name		create
		 *	@brief		�����ײ���ʾ��ID3D11Texture2D���ڱ���ͼƬ��������ʾ
		 *	@param[in]	ID3D11Device* device ������Texture��Դ������Device�豸
		 *	@param[in]	int width	ͼƬ�Ŀ�
		 *	@param[in]	int height  ͼƬ�ĸ�
		 *	@param[in]	const char* initData ��ʼ�������ݣ�NULL��ʾ���ڴ���ʱ��ʼ���������ṩͼƬ�������ݳ�ʼ��Texture
		 *	@param[in]	int dataLen ͼƬ�������ݵĳ��ȣ��ֽ������ó��ȱ�����ڻ����FRAMESIZE(width, height, pixfmt)
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		virtual int create(ID3D11Device* device, int width, int height,
							const char* initData, int dataLen) = 0;

		/**
		 *	@name		destroy
		 *	@brief		����create����������������Դ
		 *	@return		int 0--�ɹ�	<0--ʧ��
		 **/
		virtual int destroy() = 0;

		/**
		 *	@name		getTexture
		 *	@brief		��ȡ�Ѵ����ĵײ���ʾ��ID3D11Texture2D����
		 *	@param[out]	ID3D11Texture2D** outTexs �������д�����ID3D11Texture2D�����ָ������
		 *	@param[in,out]	int& texsCount	��Ϊ���������ʾָ������outTexs��ָ��ĸ����� ��Ϊ��������������Ч��ID3D11Texture2D����ĸ���
		 *	@return		int 0--�ɹ�	<0--ʧ�� �� ��createʧ�ܻ���destroy�Ѿ�����ʱ�����øýӿ�Ҳ����ʧ��
		 **/
		virtual int getTexture(ID3D11Texture2D** outTexs, int& texsCount) const = 0;

		/**
		 *	@name		getTexture
		 *	@brief		��ȡ�Ѵ����ĵײ���ʾ��ID3D11Texture2D�����Ӧ��ID3D11ShaderResourceView����
		 *	@param[out]	ID3D11ShaderResourceView** outSRVs �������д�����ID3D11ShaderResourceView�����ָ������
		 *	@param[in,out]	int& srvsCount	��Ϊ���������ʾָ������outSRVs��ָ��ĸ����� ��Ϊ��������������Ч��ID3D11ShaderResourceView����ĸ���
		 *	@return		int 0--�ɹ�	<0--ʧ�� �� ��createʧ�ܻ���destroy�Ѿ�����ʱ�����øýӿ�Ҳ����ʧ��
		 **/
		virtual int getShaderResourceView(ID3D11ShaderResourceView** outSRVs, int& srvsCount) const = 0;

		/**
		 *	@name		update
		 *	@brief		ʹ��pDataָ����ڴ��е����ݸ���Texture�����ݽ���������Texture�и���Textureԭ�е�����
		 *	@param[in]	const unsigned char* pData ��Ҫ���¿�����Texture�е����ݵ��ڴ��ַ
		 *				��Щ���ݽ�����Ϊ�������������Textureһ�������ݡ����dataLen����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int dataLen	pDataָ������ݵĳ��ȡ�����>=FRAMESIZE(width, height, pixfmt)
		 *	@param[in]	int yPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int uPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int vPitch	ͼƬ���ݵ��п�������һ������������ֽ���������>=FRAMEPITCH(width, pixfmt)
		 *	@param[in]	int width	ͼƬ�Ŀ�,����>0
		 *	@param[in]	int height  ͼƬ�ĸ�,����>0
		 *	@param[in]	const RECT& regionUpdated ͼƬ�����ݽ������������򣬸���������ݽ�������Texture�����Ͻ����λ��
		 *	@param[in]	ID3D11DeviceContext* d3dDevContex ���Texture������ID3D11Device�����Ӧ��ID3D11DeviceContext����
		 *	@return		int 0--�����ɹ�	<0--����ʧ��
		 **/
		virtual int update(const unsigned char* pData, int dataLen, int yPitch, int uPitch, int vPitch,  int width, int height,
							const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex) = 0;

		virtual int update(SharedTexture* pSharedTexture, const RECT& regionUpdated, ID3D11DeviceContext* d3dDevContex) = 0;

		/**
		 *	@name		getWidth
		 *	@brief		��ȡͼƬ�Ŀ�����ֵ
		 *	@return		int ͼƬ�Ŀ�
		 **/
		int getWidth()  const { return m_width; }

		/**
		 *	@name		getHeight
		 *	@brief		��ȡͼƬ�ĸߣ�����ֵ
		 *	@return		int ͼƬ�ĸ�
		 **/
		int getHeight() const { return m_height; }

		/**
		 *	@name		getParentDevice
		 *	@brief		��ȡ��Texture��Դ������ID3D11Device���󣬸ö�����create���óɹ��󱣴�
		 *	@return		ID3D11Device* Texture��Դ������ID3D11Device����
		 **/
		ID3D11Device* getParentDevice() const { return m_device; }

		/**
		 *	@name		getPixelFormat
		 *	@brief		��ȡͼƬ��������������
		 *	@return		PIXFormat ͼƬ����������
		 **/
		PIXFormat getPixelFormat() const { return m_pixfmt; }

	protected:
		PIXFormat m_pixfmt;
		int m_width;
		int m_height;
		ID3D11Device* m_device;

	private:
		IRawFrameTexture(const IRawFrameTexture&);
		IRawFrameTexture& operator=(const IRawFrameTexture&);
	};
}

#endif //_zRENDER_IPICTURETEXTURE_H_