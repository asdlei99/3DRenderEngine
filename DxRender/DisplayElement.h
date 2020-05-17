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
#include "DxRenderCommon.h"
#include "Effects.h"
#include "ElemDsplModel.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace zRender
{
	class DxRender_D3D11;
	class BasicEffect;
	class RectangleDataCtxInitializer;
	class ElementDrawingContext;
	class ElementMetaData;
	class TextureFasterCopyHelper;

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
		 *	@param[in]	DxRender* dxRender DxRender����ָ��
		 **/
		DisplayElement(DxRender* dxRender);

		/**
		 *	@name		~DisplayElement
		 *	@brief		���������������й���������Դ�����ͷ�
		 **/
		virtual ~DisplayElement() = 0;

		/**
		 *	@name		setDisplayRegion
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ��
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ���ݵ�����
		 *	@param[in]	const RECT_f& displayReg	��ʾ��ʾ����ĵ�����ϵλ��
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int move(const RECT_f& displayReg, float zIndex);//�����ƶ����������ݵ���ʾλ��

		/**
		 *	@name		setDisplayZIndex
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ�õ�Z����
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ����Z���������
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		**/
		int setZIndex(float zIndex);

		float getZIndex() const;

		/**
		 *	@name		setTextureDataSource
		 *	@brief		��������Texture�����������ṩ����
		 *				��drawʱ����ö��������ã���Ӹö����п����������ݵ�D3D11��Texture�Դ���
		 *	@param[in]	TextureDataSource* dataSrc ������Դ����Դ�ĸı䲻�ᵼ����Դ���´���
		 *				dataSrcΪNULLʱ�������Texture������Դ��Texture������£���ʱ����textureReg�����壬����飬������
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setTextureDataSource(TextureDataSource* dataSrc);

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
		void releaseRenderResource();

		DxRender* getParentDxRender() const { return m_dxRender; }
		ID3D11Buffer* getVertexBuffer() const { return m_VertexBuf; }
		ID3D11Buffer* getIndexBuffer() const { return m_IndexBuf; }

		/**
		 *	@name		updateTexture
		 *	@brief		��TextureDataSource�е����ݸ��µ�Texture�ڣ���Ҫ�ȵ���setTextureDataSource��
		 *				�����ڵ�����createRenderResource�ɹ�����øýӿڲ������壬���δ����Texture���ýӿ�ʲô������
		 *				�ýӿڴ�TextureDataSource�����н��ڴ濽����Texture���Դ��У����TextureDataSource����δ���£������κο���
		 *	@return		int 0--�ɹ�  <0--ʧ��
		 **/
		int updateTexture();

		/**
		 *	@name		isValid
		 *	@brief		�жϸ���ʾ�����Ƿ��ṩ����ȷ��ʾ�������Դ����Ϣ
		 *	@return		bool true--������ʾ  false--������ʾ
		 **/
		virtual bool isValid() const;

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
		bool isEnableTransparent() const;

		int draw();

		ElementMetaData* getMetaData() const { return m_MetaData; }

	protected:

		/**
		 *	@name		init
		 *	@brief		��ʼ�������MetaData��DrawingContext�ĳ�ʼ��
						���캯���н�ֱ�ӵ�������������л�����ʼ��
		 *	@return		int 0--�ɹ�  ����--ʧ��
		 **/
		virtual int init(DxRender* dxRender) = 0;

		/**
		 *	@name		deinit
		 *	@brief		�ͷ�init�����д�������Դ
		 *	@return		int 0--�ɹ�  ����--ʧ��
		 **/
		virtual void deinit() = 0;

		RectangleDataCtxInitializer* m_DataCtxInitializer;
		ElementDrawingContext* m_DrawingContext;
		ElementMetaData* m_MetaData;

		DxRender* m_dxRender;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;

		bool m_isVertexInfoUpdated;
		bool m_isTextureUpdated;
	private:
		DisplayElement(const DisplayElement& rObj);
		DisplayElement& operator=(const DisplayElement& robj);

		//�������ͷ���Դ
		int createTextureResource();
		int createTextureResource(TextureDataSource* dataSrc);
		void releaseTextureResource();
		int createVertexBuffer();
		int releaseVertexBuffer();
		int createIndexBuffer();
		int releaseIndexBuffer();
		void setupApplyingTextureList();

		struct TextureResContext
		{
			TextureResContext(ITextureResource* tex, TextureFasterCopyHelper* texHelper)
				: texture(tex), textureHelper(texHelper)
				, identifyForData(0), identifyForFormat(0)
			{

			}

			TextureResContext()
				: texture(nullptr), identifyForData(0), identifyForFormat(0)
			{

			}

			ITextureResource* texture;
			TextureFasterCopyHelper* textureHelper;
			unsigned int identifyForData;
			unsigned int identifyForFormat;
		};

		std::vector<ITextureResource*> m_applyingTexture;
		std::vector<TextureResContext> m_textureRes;
		ID3D11Buffer*		m_VertexBuf;
		ID3D11Buffer*		m_IndexBuf;
	};
}
#pragma warning(pop)

#endif

#endif	//_zRENDER_DISPLAYELEMENT_H_