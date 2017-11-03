/**
 *	@author		zhuqingquan
 *	@date		2014-10-28
 *	@name		IDisplayContentProvider.h
 *	@brief		��ʾ���ݵ��ṩ�ߵĽӿڶ��壬���幩�ⲿ��ȡ��ʾ��Ⱦ����Ķ�����Ϣ������Texture��Shader���ݵ���Ϣ�Ľӿ�
 */

#pragma once
#ifndef _ZRENDER_IDISPLAYCONTENTPROVIDER_H_
#define _ZRENDER_IDISPLAYCONTENTPROVIDER_H_

#include "Vertex.h"
#include "DxRenderCommon.h"
#include "DxZRenderDLLDefine.h"

namespace zRender
{
	class SharedTexture;
	class IRawFrameTexture;

	/**
	 *	@name		TextureDataSource
	 *	@brief		�������ݻ�ȡ�����µĽӿڶ���
	 **/
	class DX_ZRENDER_EXPORT_IMPORT TextureDataSource
	{
	public:
		/**
		 *	@name		TextureDataSource
		 *	@brief		���캯��
		 **/
		TextureDataSource() {};

		/**
		 *	@name		~TextureDataSource
		 *	@brief		�������������鷽�����ɼ̳�
		 **/
		virtual ~TextureDataSource() = 0 {};

		/**
		 *	@name		isUpdated
		 *	@brief		��ȡ��ǰ���������Ƿ��Ѹ��£��û����Ը��ݸ÷�������ֵ�ж��Ƿ���Ҫ������������
		 *	@param[in]	int identify �û���ǰ�����е��������ݵı�ʶ������ʶ�û���ǰʹ�õ���������
		 *	@return		bool true--���������Ѹ���	false--��������Ϊ����
		 **/
		virtual bool isUpdated(int identify) const = 0;

		/**
		 *	@name		getTextureProfile
		 *	@brief		��ȡ�������ݵ������Ϣ�������ݵĳ��ȣ����ݵ��п��Լ���
		 *				�����ȡ������������textureRegָ���������е�������Ϣ
		 *	@param[in]	const RECT_f& textureReg ��Ҫ��ȡ����������򣬸ò�����ʾ�û���Ҫ��ȡ�������������Ϣ��
		 *				�ò���Ϊ������꣬ȡֵ��ΧΪ[0,1]
		 *				����������Ϊһ�����壬����ò���Ϊ[0, 0, 0.5, 0.5]���ȡ����ϢΪTexture���Ͻ��ķ�֮һ���ֵĿ�ߵȡ�
		 *	@param[out]	int& dataLen �������ݵĳ���
		 *	@param[out]	int& yPitch �����������ݵ��п�Y���ݻ���RGB���ݡ�YUY2���ݵ��п�
		 *	@param[out]	int& uPitch �����������ݵ��п�U���ݻ���UV��VU���ݵ��п�
		 *	@param[out]	int& vPitch �����������ݵ��п�V���ݵ��п�
		 *	@param[out]	int& width ������������ؿ�
		 *	@param[out]	int& height ��������ĸ�
		 *	@param[out]	int& pixelFmt ������������ظ�ʽ
		 *	@return		int 0--��ȡ�ɹ�  <0--ʧ�ܣ������ǳ�Ա����δ��ʼ�����߳�Ա����ֵ���Ϸ�
		 **/
		virtual int getTextureProfile(const RECT_f& textureReg, int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, PIXFormat& pixelFmt) = 0;

		/**
		 *	@name		getData
		 *	@brief		��ȡ�������ݵ������Ϣ�������ݵ��׵�ַ�����ݵĳ��ȣ����ݵ��п��Լ���
		 *				�����ȡ�����������������ݣ������������һ����
		 *	@param[out]	int& dataLen �������ݵĳ���
		 *	@param[out]	int& yPitch �����������ݵ��п�Y���ݻ���RGB���ݡ�YUY2���ݵ��п�
		 *	@param[out]	int& uPitch �����������ݵ��п�U���ݻ���UV��VU���ݵ��п�
		 *	@param[out]	int& vPitch �����������ݵ��п�V���ݵ��п�
		 *	@param[out]	int& width ������������ؿ�
		 *	@param[out]	int& height ��������ĸ�
		 *	@param[out]	PIXFormat& pixelFmt ������������ظ�ʽ
		 *	@return		unsigned char* ��NULL--�������ݵ��׵�ַ	 NULL--������
		 **/
		virtual unsigned char* getData(int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, PIXFormat& pixelFmt, RECT& effectReg, int& identify) = 0;
		
		/**
		 *	@name		getSharedTexture
		 *	@brief		��ȡ�����Դ����
		 *	@return		SharedTexture* ��NULL--�����Դ����	 NULL--������
		 **/
		virtual SharedTexture* getSharedTexture(RECT& effectReg, int& identify) = 0;

		virtual IRawFrameTexture* getTexture() = 0;

		/**
		 *	@name		copyDataToTexture
		 *	@brief		�����ݿ�����D3D11�е�Texture�����С�
		 *	@param[in]	const RECT_f& textureReg ��Ҫ��������������򣬸ò�����ʾ�û���Ҫ������������������ݡ�
		 *				�ò���Ϊ������꣬ȡֵ��ΧΪ[0,1]
		 *				����������Ϊһ�����壬����ò���Ϊ[0, 0, 0.5, 0.5]�򿽱�Texture���Ͻ��ķ�֮һ���ֵ����ݡ�
		 *	@param[in]	unsigned char* dstTextureData Texture�����Ӧ���Դ���Դ���׵�ַ
		 *	@param[in]	int pitch Texture�����Ӧ���Դ���Դ���п�
		 *	@param[in]	int height Texture�����Ӧ���Դ���Դ�ĸ�
		 *	@param[out]	int& identify ����ɹ��򴫳����ο�����Texture���ݵı�ʶ���������´ο���ͨ�������ʶ����ѯ�Ƿ�Texture��������
		 *	@return		int 0--�����ɹ�	 <0--����ʧ��  >0--δ���£����追��
		 **/
		virtual int copyDataToTexture(const RECT_f& textureReg, unsigned char* dstTextureData, int pitch, int height, int& identify) = 0;

		virtual void increaseAuthorization() {};
		virtual void decreaseAuthorization() {};
	};

	/**
	 *	@name		IDisplayContentProvider
	 *	@brief		��ʾ���ݵ��ṩ�ߵĽӿڶ��壬���幩�ⲿ��ȡ��ʾ��Ⱦ����Ķ�����Ϣ������Texture��Shader���ݵ���Ϣ�Ľӿ�
	 **/
	class DX_ZRENDER_EXPORT_IMPORT IDisplayContentProvider
	{
	public:
		/**
		 *	@name		IDisplayContentProvider
		 *	@brief		���캯��
		 **/
		IDisplayContentProvider() {};

		/**
		 *	@name		~IDisplayContentProvider
		 *	@brief		�������������鷽�����ɼ̳�
		 **/
		virtual ~IDisplayContentProvider() = 0
		{
		}

		/**
		 *	@name		isVertexUpdated
		 *	@brief		��ȡ��ǰ�Ķ�����Ϣ�Ƿ񱻸���
		 *				ͨ��ƥ�����identify�붥����Ϣ�ı�ʾ�����ж϶�����Ϣ�Ƿ񱻸���
		 *	@param[in]	int identify ������Ϣ�ı�ʶ��
		 *	@return		int 0--�ɹ�  <0--ʧ��
		 **/
		virtual bool isVertexUpdated(int identify) const = 0;

		/**
		 *	@name		getVertexs
		 *	@brief		��ȡ���ж�����Ϣ����ͬ���˹�ϵ�Ķ�����벻ͬ��VertexVector�����С�
		 *	@param[in,out]	VertexVector** vv �������˹���Ķ�����Ϣ��VertexVector��������飬�ⲿ�����ͷŸ����飬���ڴ���IDisplayContentProvider�����ͷ�
		 *	@param[in,out] int& vvCount �������˹���Ķ�����Ϣ��VertexVector���������ĳ���
		 *	@param[in,out]	int& identify ������Ϣ�ı�ʶ��
		 *	@return		int 0--�ɹ�  <0--ʧ��
		 **/
		virtual int getVertexs(VertexVector** vv, int& vvCount, int& identify) = 0;

		/**
		 *	@name		getTextureDataSource
		 *	@brief		��ȡ���������ṩ����µĶ���
		 *	@return		TextureDataSource* ��NULL--���������ṩ����µĶ���  NULL--���������
		 **/
		virtual TextureDataSource* getTextureDataSource() = 0;

		/**
		 *	@name		getShader
		 *	@brief		��ȡ��Ⱦ�����Shader��Դ���ýӿ���ʱ�����ã�����ֵ��ʱδ����
		 *	@return		void* ��ʱδ����
		 **/
		virtual void* getShader() = 0;

		virtual void increaseAuthorization() {};
		virtual void decreaseAuthorization() {};
	};
}//namespace zRender

#endif //_zRENDER_IDISPLAYCONTENTPROVIDER_H_