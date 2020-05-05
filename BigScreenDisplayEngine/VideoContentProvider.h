/**
 *	@author		zhuqingquan
 *	@date		2015-1-10
 *	@name		VideoContentProvider.h
 *	@brief		��ʾ���ݵ��ṩ�ߵ�ʵ����֮һ���̳�IDisplayContentProvider�ӿ�
 *				����ֻ������һ֡ͼ�����ݵĽ�����������ݣ����в�����ԭʼ���ݡ��������ֻ��ʹ��ͼ�����ݵ�һ������������ʾ�������Ǿ������򣬲�֧��������״
 **/

#pragma once
#ifndef _SOA_MIRROR_RENDER_VIDEO_CP_H_
#define _SOA_MIRROR_RENDER_VIDEO_CP_H_

#include "IDisplayContentProvider.h"
#include <ConstDefine.h>

namespace zRender
{
	class IRawFrameTexture;
}

namespace SOA
{
namespace Mirror
{
namespace Render
{
	/**
	 *	@name		PictureTextureDataSource
	 *	@brief		ͼƬ���ݵ��ṩ��Ļ���ӿڣ�����ͼƬ���ݿ���ͨ���̳иýӿڣ�ʹ��ͼƬ������DxRender����ʾ
	 **/
	class PictureTextureDataSource : public zRender::TextureDataSource
	{
	public:
		/**
		 *	@name		PictureTextureDataSource
		 *	@brief		Ĭ�Ϲ��캯�����������ݳ�Ա����ʼ����Ĭ��ֵ�����̳�������ڹ���֮���޸����ݳ�Ա��ֵ
		 **/
		PictureTextureDataSource()
			: m_isUpdatedIdentify(0)
			, m_frameHeight(0), m_frameWidth(0), m_framePixFmt(zRender::PIXFMT_UNKNOW)
		{			
		}

		/**
		 *	@name		PictureTextureDataSource
		 *	@brief		���캯�����ڹ���ʱָ��ͼƬ�ķֱ���
		 *	@param[in]	int width ͼƬ��
		 *	@param[in]	int height ͼƬ��
		 **/
		PictureTextureDataSource(int width, int height)
			: m_isUpdatedIdentify(0)
			, m_frameHeight(height), m_frameWidth(width), m_framePixFmt(zRender::PIXFMT_UNKNOW)
			, m_Pitch(0)
		{
			
		}

		/**
		 *	@name		~PictureTextureDataSource
		 *	@brief		�������������г�Ա�������ó�Ĭ��ֵ
		 **/
		virtual ~PictureTextureDataSource() = 0
		{
			m_isUpdatedIdentify = 0;
			m_frameHeight = 0;
			m_frameWidth = 0;
			m_framePixFmt = zRender::PIXFMT_UNKNOW;
		}

		/**
		 *	@name		isUpdated
		 *	@brief		ͼƬ�Ƿ��и��£�ͨ�������ʶ�����ж�ͼƬ�Ƿ����
		 *	@param[in]	int identify ͼƬ�Ƿ��и��µı�ʶ����������ڲ���ʶͼƬ����״̬�������Ȳ�����ֵ��������ΪͼƬ�ѱ�����
		 *				ʹ���߿�����getData��copyDataToTexture�л�ȡ���ڲ���ʶͼƬ����״̬������
		 *				Ȼ�������������Ϊ�������ж��ϴε�����getData��copyDataToTexture֮��ͼƬ�����ݸ���
		 *				ʹ���߿������øò���Ϊ0����÷������Ƿ���true
		 *	@return		true--ͼƬ�����и���	false--ͼƬ����û�и���
		 **/
		bool isUpdated(int identify) const {return m_isUpdatedIdentify>identify;}

		/**
		 *	@name		getTextureProfile
		 *	@brief		��ȡͼƬ���ݵ������Ϣ�������ݵĳ��ȣ����ݵ��п��Լ���
		 *				�����ȡ����ͼƬ��Ч�������ݵ���Ϣ������������ͼƬ����Ϣ
		 *	@param[in]	const RECT_f& textureReg ��Ҫ��ȡ��ͼƬ�����򣬸ò�����ʾ�û���Ҫ��ȡͼƬ�����������Ϣ��
		 *				�ò���Ϊ������꣬ȡֵ��ΧΪ[0,1]
		 *				����ͼƬ��Ϊһ�����壬����ò���Ϊ[0, 0, 0.5, 0.5]���ȡ����ϢΪͼƬ���Ͻ��ķ�֮һ���ֵĿ�ߵȡ�
		 *	@param[out]	int& dataLen �������ݵĳ���
		 *	@param[out]	int& pitch ����ͼƬ���ݵ��п�
		 *	@param[out]	int& width ����ͼƬ�����ؿ�
		 *	@param[out]	int& height ����ͼƬ�ĸ�
		 *	@param[out]	int& pixelFmt ����ͼƬ�����ظ�ʽ
		 *	@return		int 0--��ȡ�ɹ�  <0--ʧ�ܣ������ǳ�Ա����δ��ʼ�����߳�Ա����ֵ���Ϸ�
		 **/
		int getTextureProfile(const zRender::RECT_f& textureReg, int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, zRender::PIXFormat& pixelFmt)
		{
			if(textureReg.left<0 || textureReg.left>=1 || textureReg.top<0 || textureReg.top>=1
				|| textureReg.width() <= 0 || textureReg.height()<=0 || textureReg.right>1 ||textureReg.bottom>1)
			{
		#ifdef _DEBUG
				printf("Error in PictureTextureDataSource::getTextureProfile : param [textureReg] is invalid.(L=%f, R=%f, T=%f, B=%f)\n",
					textureReg.left, textureReg.right, textureReg.top, textureReg.bottom);
		#endif
				return -1;
			}
			if(m_framePixFmt==zRender::PIXFMT_UNKNOW || m_frameWidth==0 || m_frameHeight==0)
				return -2;
			float texReg_width = textureReg.width();
			float texReg_height = textureReg.height();
			float effReg_width = m_effectiveReg.width();
			float effReg_height = m_effectiveReg.height();
			float actual_width = texReg_width * effReg_width * m_frameWidth;
			float actual_height = texReg_height * effReg_height * m_frameHeight;
			width = actual_width;
			height = actual_height;
			yPitch = m_Pitch;//FRAMEPITCH(width, m_framePixFmt);
			dataLen = yPitch * height;
			pixelFmt = m_framePixFmt;
			return 0;
		}

		//virtual unsigned char* getData(int& dataLen, int& pitch, int& upitch, int& vpitch, int& width, int& height, zRender::PIXFormat& pixelFmt, RECT& effectReg, int& identify)
		virtual unsigned char* getData(int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, zRender::PIXFormat& pixelFmt, RECT& effectReg, int& identify)
		{
			return NULL;
		}
		
		zRender::SharedTexture* getSharedTexture(RECT& effectReg, int& identify)
		{
			return NULL;
		}

		zRender::IRawFrameTexture* getTexture() {
			return NULL;
		}

		//virtual int copyDataToTexture(const zRender::RECT_f& textureReg, unsigned char* dstTextureData, int pitch, int height, int& identify) = 0;
		virtual int copyDataToTexture(const zRender::RECT_f& textureReg, unsigned char* dstTextureData, int pitch, int height, int& identify)
		{
			return 0;
		}

		/**
		 *	@name		setEffectiveReg
		 *	@brief		����ͼƬ����Ч��������֮��ʹ����ֻ�ܻ�ȡ������Ч���򲿷ֵ���Ϣ������
		 *	@param[in]	const zRender::RECT_f& textureEffectiveReg ͼƬ��Ч����
		 *				ȡֵ��ΧΪ[0,1]��Ϊ�������
		 *	@return		0--�ɹ�  false--ʧ�ܣ��������Ϸ�
		 **/
		int setEffectiveReg(const zRender::RECT_f& textureEffectiveReg)
		{
			if(textureEffectiveReg.left<0 || textureEffectiveReg.left>=1 || textureEffectiveReg.top<0 || textureEffectiveReg.top>=1
				|| textureEffectiveReg.width() <= 0 || textureEffectiveReg.height()<=0 || textureEffectiveReg.right>1 ||textureEffectiveReg.bottom>1)
			{
		#ifdef _DEBUG
				printf("Error in setEffectiveReg::setEffectiveReg : param [textureReg] is invalid.(L=%f, R=%f, T=%f, B=%f)\n",
					textureEffectiveReg.left, textureEffectiveReg.right, textureEffectiveReg.top, textureEffectiveReg.bottom);
		#endif
				return -1;
			}
			m_effectiveReg = textureEffectiveReg;
			m_isUpdatedIdentify++;
			return 0;
		}

		/**
		 *	@name		getEffectiveReg
		 *	@brief		��ȡͼƬ����Ч����
		 *	@return		zRender::RECT_f ͼƬ����Ч����������꣬ȡֵ��Χ[0,1]
		 **/
		zRender::RECT_f getEffectiveReg() const
		{
			return m_effectiveReg;
		}

		/**
		 *	@name		getTextureCount
		 *	@brief		��ȡElement�����TextureResource�ĸ���
		 *	@return		zRender::VertexVector*
		 **/
		virtual int getTextureCount() const { return 1; }

		/**
		 *	@name		getTextureSourceDesc
		 *	@brief		��ȡ�±�Ϊindex��Texture��Ӧ������Դ�����ݸ�ʽ
		 *	@param[in]	int index TextureResource���±�
		 *	@param[out] TextureSourceDesc* srcDesc ��������Դ�����ݸ�ʽ
		 **/
		virtual int getTextureSourceDesc(int index, zRender::TextureSourceDesc* srcDesc) const
		{
			if (index > 0 || srcDesc == nullptr)
				return DXRENDER_RESULT_PARAM_INVALID;
			//fixme
			return DXRENDER_RESULT_OK;
		}

		/**
		 *	@name		updateTextures
		 *	@brief		��TextureDataSource�е����ݸ��µ�TextureResource��
		 *	@param[in]	TextureResource* textureArray TextureResource����
		 *	@param[in]  int index ��Ҫ���µ�Texture���ݵ��±�Index
		 *	@param[out] unsigned int& newIdentify �ɹ����º󱣴��µ����ݰ汾��ʶֵ�����δ�����򲻸���
		 **/
		virtual int updateTextures(zRender::ITextureResource* textureArray, int index, unsigned int& newIdentify)
		{
			if (index < 0 || index>=getTextureCount() || textureArray == nullptr)
				return DXRENDER_RESULT_PARAM_INVALID;
			return DXRENDER_RESULT_OK;
		}

		/**
		 *	@name		isTextureUpdated
		 *	@brief		��ȡ�±�Ϊindex��Texture��Ӧ������Դ�������Ƿ����˸ı�
		 *	@param[in]	int index TextureResource���±�
		 *	@param[in]  �ⲿ���е����¸��µ�TextureResource�ļ����汾�����Texture
		 *	@return		true--Texture����Դ�����˸��� false--δ����
		 **/
		virtual bool isTextureUpdated(int index, unsigned int identify)
		{
			if (index < 0 || index>1)
				return false;
			return m_isUpdatedIdentify > identify;;

		}
	protected:
		int m_isUpdatedIdentify;
		int m_frameWidth;
		int m_frameHeight;
		int m_Pitch;
		zRender::PIXFormat m_framePixFmt;

	private:
		zRender::RECT_f m_effectiveReg;
	};
	
	/**
	 *	@name		VideoContentProvider
	 *	@brief		��Ƶ�����ṩ�ߵ�ʵ���࣬ʵ����Ƶ��ʾ������Ϣ���ṩ
	 *				�ڸ����У��ṩ��TextureDataSource��������Ǽ̳���PictureTextureDataSource�ӿڵ������ṩͼƬ�������ݵ���
	 *				�ṩ�Ķ�����Ϣ���Ƕ���(0.0,0.0)�붥��(1.0, 1.0)�����ɵľ��ζ�����Ϣ
	 *				��ʵ���಻�ṩShader������Ϣ��ʹ��Ĭ�ϵ�Shader�ļ�������ʾ
	 **/
	class VideoContentProvider : public zRender::IDisplayContentProvider
	{
	public:
		/**
		 *	@name		VideoContentProvider
		 *	@brief		���캯����ʹ��PictureTextureDataSource��������ָ����Ϊ����
		 *	@param[in]	SOA::Mirror::Render::PictureTextureDataSource* PictureTextureDataSource��������ָ�� 
		 **/
		VideoContentProvider(SOA::Mirror::Render::PictureTextureDataSource* tds, const zRender::RECT_f& effctiveReg)
			: m_dataSrc(tds)
			, m_vv(new zRender::VertexVector(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST))
		{
			//Ĭ�ϵľ��εĶ���
			zRender::Vertex ver[4];
			ver[0].Pos = XMFLOAT3(0.0, 0.0, 0.0);
			ver[0].Tex = XMFLOAT2(0.0, 1.0);
			ver[1].Pos = XMFLOAT3(1.0, 0.0, 0.0);
			ver[1].Tex = XMFLOAT2(1.0, 1.0);
			ver[2].Pos = XMFLOAT3(0.0, 1.0, 0.0);
			ver[2].Tex = XMFLOAT2(0.0, 0.0);
			ver[3].Pos = XMFLOAT3(1.0, 1.0, 0.0);
			ver[3].Tex = XMFLOAT2(1.0, 0.0);
			UINT index[6] = {0, 2, 3, 0, 3, 1};
			m_vv->addVertexs(ver, 4, index, 6);
			m_vvCount = 1;

			if(m_dataSrc)
				m_dataSrc->setEffectiveReg(effctiveReg);
			m_vertexIdentify = 1;
		}

		/**
		 *	@name		~VideoContentProvider
		 *	@brief		�ͷ������Դ
		 **/
		~VideoContentProvider()
		{
			delete m_vv;
			m_vv = NULL;
			m_vertexIdentify = 0;

			m_dataSrc = NULL;
		}

		/**
		 *	@name		isVertexUpdated
		 *	@brief		������Ϣ�Ƿ��Ѿ�����
		 *	@param[in]	int identify ������Ϣ�Ƿ��и��µı�ʶ����������ڲ���ʶ������Ϣ����״̬�������Ȳ�����ֵ��������Ϊ������Ϣ�ѱ�����
		 *				getVertexs���Ի�ȡ����ǰ�Ķ�����Ϣ����״̬�ı�ʶ��
		 *	@return		true--������Ϣ�ѱ�����  false--δ����
		 **/
		bool isVertexUpdated(int identify) const { return m_vertexIdentify>identify; }

		/**
		 *	@name		getVertexs
		 *	@brief		��ȡ������Ϣ
		 *	@param[out]	zRender::VertexVector** vv ����������Ϣ�����飬�����ж������
		 *	@param[out]	int& vvCount ������Ϣ����ĸ���
		 *	@param[in,out] int& identify ��������ߵ�ǰ�����еĶ�����Ϣ״̬��ʶ�����������ڲ���״̬��ʶ��
		 *	@return		int	0--�ɹ�  ����--ʧ��
		 **/
		int getVertexs(zRender::VertexVector** vv, int& vvCount, int& identify)
		{
			if(vv==NULL || vvCount<1)
				return -1;
			if(m_vertexIdentify<identify)
				return 1;
			*vv = m_vv;
			vvCount = m_vvCount;
			identify = m_vertexIdentify;
			return 0;
		}

		/**
		 *	@name		getTextureDataSource
		 *	@brief		��ȡ���桢�ṩ��Ƶ���ݵ�TextureDataSource����ָ��
		 *	@return		zRender::TextureDataSource* ���桢�ṩ��Ƶ���ݵ�TextureDataSource����ָ��
		 **/
		zRender::TextureDataSource* getTextureDataSource() { return m_dataSrc; }

		/**
		 *	@name		getShader
		 *	@brief		��ȡ��ʾ�����Shader���ݣ��ڸ�����ֱ�ӷ���NULL��ʹ��Ĭ�ϵ�Shader
		 *	@return		����NULL
		 **/
		void* getShader() { return NULL; }

		void increaseAuthorization()
		{
			if(m_dataSrc!=NULL)
				m_dataSrc->increaseAuthorization();
		}
		void decreaseAuthorization()
		{
			if(m_dataSrc!=NULL)
				m_dataSrc->decreaseAuthorization();
		}
	private:
		SOA::Mirror::Render::PictureTextureDataSource* m_dataSrc;
		int m_vertexIdentify;
		zRender::VertexVector* m_vv;
		int m_vvCount;
	};

	class RawFrameRefData : public PictureTextureDataSource
	{
	public:
		RawFrameRefData(unsigned char* frameData, unsigned long dataLen,
						int width, int height, int pitch, zRender::PIXFormat pixfmt)
						: PictureTextureDataSource(width, height)
						, m_pFrameData(frameData), m_DataLen(dataLen)
		{
			m_framePixFmt = pixfmt;
			m_Pitch = pitch;
		}

		~RawFrameRefData() {}

		unsigned char* getData(int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, zRender::PIXFormat& pixelFmt, RECT& effectReg, int& identify);
		//int getTextureProfile(const zRender::RECT_f& textureReg, int& dataLen, int& yPitch, int& uPitch, int& vPitch, int& width, int& height, zRender::PIXFormat& pixelFmt)
		//{
		//	return -1;
		//}

		int copyDataToTexture(const zRender::RECT_f& textureReg, unsigned char* dstTextureData, int pitch, int height, int& identify)
		{
			return -1;
		}

	private:
		unsigned char* m_pFrameData;
		unsigned long m_DataLen;

		bool isFrameParamValid() const
		{
			return m_pFrameData!=NULL && m_frameWidth>0 && m_frameHeight>0
				&& m_framePixFmt!=zRender::PIXFMT_UNKNOW 
				&& m_Pitch>=FRAMEPITCH(m_frameWidth, m_framePixFmt)
				&& m_DataLen >= m_Pitch*m_frameHeight;
		}
	};
}
}
}

#endif //_SOA_MIRROR_RENDER_FRAME_DATA_REF_CP_H_