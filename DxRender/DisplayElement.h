/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		DisplayElement.h
 *	@brief		��������ʾ�����ݵ��߼��ࡣ�����а�����������ʾ����Ҫ��������Ϣ���綥����Ϣ��Texture��world�����ת������ʹ�õ�Shader
 */

#pragma once
#ifndef _ZRENDER_DISPLAYELEMENT_H_
#define _ZRENDER_DISPLAYELEMENT_H_

#include "DxZRenderDLLDefine.h"
#include <memory>
#ifdef _WINDOWS

#include "IDisplayContentProvider.h"
#include "Vertex.h"
#include "IRawFrameTexture.h"
#include "DxRenderCommon.h"
#include "Effects.h"
#include "ElemDsplModel.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace zRender
{
	class Texture;
	class DxRender_D3D11;
	class BasicEffect;
	//template<> class ElemDsplModel<BasicEffect>;

	/**
	 *	@name	DisplayElement
	 *	@brief	��ʾ���ݵ���Դ��
	 **/
	class DX_ZRENDER_EXPORT_IMPORT DisplayElement
	{
	public:
		/**
		 *	@name		DisplayElement
		 *	@brief		���캯����������󣬲������κ���Դ
		 *	@param[in]	DxRender_D3D11* dxRender DxRender����ָ��
		 *	@param[in]	ID3D11Device* d3dDevice D3DDevice����ָ��
		 *	@param[in]	ID3D11DeviceContext* contex ��d3dDevice������Ӧ���豸������
		 **/
		DisplayElement(DxRender_D3D11* dxRender, ID3D11Device* d3dDevice, ID3D11DeviceContext* contex);

		/**
		 *	@name		~DisplayElement
		 *	@brief		���������������й���������Դ�����ͷ�
		 **/
		~DisplayElement();

		/**
		 *	@name		setDisplayRegion
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ��
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ���ݵ�����
		 *	@param[in]	const RECT_f& displayReg	��ʾ��ʾ����ĵ�����ϵλ��
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setDisplayRegion(const RECT_f& displayReg, float zIndex);//�����ƶ����������ݵ���ʾλ��

		/**
		 *	@name		setDisplayZIndex
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ�õ�Z����
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ����Z���������
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		**/
		int setDisplayZIndex(float zIndex);

		float getZIndex() const;

		/**
		 *	@name		setTexture
		 *	@brief		��������Texture����ز�����Ϣ
		 *				�ڴ˲��ᴴ���ͷ���Դ����createRenderResource�����ͷ���Ҫ�ͷŲ����´���Texture��Դ
		 *	@param[in]	YUVFormat_Packed pixfmt	Texture���ظ�ʽ�����ظ�ʽ�ı䲻һ���ᵼ����Դ���´�������YUYV->UYVY
		 *	@param[in]	int width	Texture�Ŀ�widthֵ�ĸı佫������Դ���´�����ֵ��Ϊ>0
		 *	@param[in]	int height	Texture�ĸߣ�heightֵ�ĸı佫������Դ���´�����ֵ��Ϊ>0
		 *	@param[in]	TextureDataSource* dataSrc ������Դ����Դ�ĸı䲻�ᵼ����Դ���´���
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setTexture(PIXFormat pixfmt, int width, int height);

		/**
		 *	@name		setTextureDataSource
		 *	@brief		��������Texture�����������ṩ����
		 *				��drawʱ����ö��������ã���Ӹö����п����������ݵ�D3D11��Texture�Դ���
		 *	@param[in]	TextureDataSource* dataSrc ������Դ����Դ�ĸı䲻�ᵼ����Դ���´���
		 *				dataSrcΪNULLʱ�������Texture������Դ��Texture������£���ʱ����textureReg�����壬����飬������
		 *	@param[in]	const RECT_f& textureReg dataSrc�е����򣬸�DisplayElement����ֻ��ʾ�������е����ݡ�������ꡣȡֵ��Χ[0~1]
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setTextureDataSource(TextureDataSource* dataSrc, const RECT_f& textureReg);

		/**
		 *	@name		setVertex
		 *	@brief		�������ö��������Ϣ
		 *				�������������1-������Ϣȫ�����£�2-֮ǰ�Ķ�����Ϣ���ָ���
		 *	@param		VertexVector* vertexInfo	������Ϣ��֧�����ò�ͬ�Ķ�����Ϣ�����������ͬһ������
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setVertex(VertexVector* vertexInfo);

		/**
		 *	@name		getVertex
		 *	@brief		��ȡ���������Ϣ����
		 *	@return		VertexVector* ���ض��������Ϣ����NULL--ʧ��
		 **/
		VertexVector* getVertex() const { return m_curVerVec; }

		/**
		 *	@name		createRenderResource
		 *	@brief		����Render��Ⱦ��������Ҫ��ϵͳ��Դ
		 *				��������Դ����������Buffer��Index Buffer��Texture��Shader
		 *				����ö���δ��ʼ����ʧ�ܣ������Դ֮ǰ�Ѿ����������޸������ò�������Texture�Ŀ�ߣ�
		 *				��֮ǰ��������Դ���ͷţ�Ȼ���ٴ����µ���Դ������Ӧ����ȷ������ʹ���ϵ���Դ��������߳����⡣
		 *				ֻ����������Ҫ�����������´�������Դ�������ɹ��Ż᷵�سɹ���
		 *	@return		int	 0--�ɹ�  <0--ʧ��
		 **/
		int createRenderResource();

		/**
		 *	@name		releaseRenderResource
		 *	@brief		�ͷ��Ѿ���������Դ
		 *	@return		int	 0--�ɹ�  <0--ʧ��
		 **/
		int releaseRenderResource();

		DxRender_D3D11* getParentDxRender() const { return m_dxRender; }
		IRawFrameTexture* getTexture() const { return m_texture; }
		ID3D11Buffer* getVertexBuffer() const { return m_VertexBuf; }
		ID3D11Buffer* getIndexBuffer() const { return m_IndexBuf; }
		DXGI_FORMAT getIndexBufferFormat() const { return m_IndexFmt; }
		XMFLOAT4X4 getWorldTransformMatrices() const	{return m_WorldTransformMat;}

		/**
		 *	@name		updateTexture
		 *	@brief		����Texture������
		 *				�����ڵ�����createRenderResource�ɹ�����øýӿڲ������壬���Ϊ����Texture���ýӿ�ʲô������
		 *				�ýӿڴ�TextureDataSource�����н��ڴ濽����Texture���Դ��У����TextureDataSource����δ���£������κο���
		 *	@param[in,out]	int& identify	��ǰ�Ѿ����Ƶ�Texture�ı�ʶ�������Texture�����ݸ��³ɹ�����ò��������޸�
		 *	@return		int 0--�ɹ�  <0--ʧ��
		 **/
		int updateTexture(int& identify);

		/**
		 *	@name		isValid
		 *	@brief		�жϸ���ʾ�����Ƿ��ṩ����ȷ��ʾ�������Դ����Ϣ
		 *	@return		bool true--������ʾ  false--������ʾ
		 **/
		bool isValid() const;

		/**
		 *	@name			setAlpha
		 *	@brief			������ʾ����͸���ȣ���Ч��Χ��1.0f -- 0.0f��
		 *	@param[in]		float alpha ͸���ȣ�1.0fΪ��͸���� 0.0fΪȫ͸��
		 **/
		void setAlpha(float alpha);
		/**
		 *	@name			getAlpha
		 *	@brief			��ȡ��ǰ���õ�͸����
		 *	@return			float 
		 **/
		float getAlpha() const;
		void enableTransparent(bool enable);
		bool isEnableTransparent() const { return m_isEnableTransparent;}

		int createDsplModel(ElemDsplModel<BasicEffect>** ppModel)
		{
			if (ppModel == NULL)	return -1;
			ElemDsplModel<BasicEffect>* model = new ElemDsplModel<BasicEffect>();
			if (NULL == model)	return -2;
			*ppModel = model;
			return 0;
		}

		void ReleaseDsplModel(ElemDsplModel<BasicEffect>** ppModel)
		{
			if (ppModel && *ppModel)
			{
				ElemDsplModel<BasicEffect>* model = *ppModel;
				delete model;
				*ppModel = NULL;
			}
		}

		bool setDsplModel(ElemDsplModel<BasicEffect>* model)
		{
			if (NULL == model)	return false;
			m_dsplModel = model;
			return true;
		}

		ElemDsplModel<BasicEffect>* getDsplModel() const { return m_dsplModel; }
		int draw();
		//////////////////////////֧�ִ򿪹����Դ�������ʾ///////////////////////////////
		int openSharedTexture(IRawFrameTexture* sharedTexture);
	private:
		DisplayElement(const DisplayElement& rObj);
		DisplayElement& operator=(const DisplayElement& robj);

		//�������ͷ���Դ
		int createTextureResource();
		int releaseTexTureResource();
		int createVertexBuffer();
		int releaseVertexBuffer();
		int createIndexBuffer();
		int releaseIndexBuffer();

		DxRender_D3D11* m_dxRender;
		ID3D11Device*	m_device;
		ID3D11DeviceContext* m_context;

		ElemDsplModel<BasicEffect>* m_dsplModel;

		VertexVector* m_curVerVec;
		bool m_isVertexInfoUpdated;
		PIXFormat m_TexFmt;
		int	m_TexWidth;
		int m_TexHeight;
		TextureDataSource* m_TexDataSrc;
		RECT_f	m_TexEffectiveReg;
		bool m_isTextureUpdated;

		IRawFrameTexture*	m_texture;//std::shared_ptr<YUVTexture_Packed*>
		ID3D11Buffer*		m_VertexBuf;//std::shared_ptr<ID3D11Buffer*>
		ID3D11Buffer*		m_IndexBuf;//std::shared_ptr<ID3D11Buffer*>
		DXGI_FORMAT			m_IndexFmt;//
		XMFLOAT4X4			m_WorldTransformMat;
		float				m_alpha;
		bool				m_isEnableTransparent;
	};
}
#pragma warning(pop)

#endif

#endif	//_zRENDER_DISPLAYELEMENT_H_