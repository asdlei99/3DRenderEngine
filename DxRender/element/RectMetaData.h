#pragma once
#ifndef _Z_RENDER_RECT_META_DATA_H_
#define _Z_RENDER_RECT_META_DATA_H_

#include "ElementMetaData.h"

namespace zRender
{
	class TextureDataSource;
	class VertexVector;
	class DxRender;
	class BasicEffect;

	/**
	 *	@name	RectMetaData
	 *	@brief	The meta data for draw Rect element
	 **/
	class RectMetaData : public ElementMetaData
	{
	public:
		RectMetaData();
		virtual ~RectMetaData();

		/**
		 *	@name		init
		 *	@brief		��ʼ��Element��MetaData
		 *	@param[in]	DxRender * render ������Դ��DxRender
		 *	@param[in]	const TCHAR * shaderFileName Shader�ļ���·��
		 *	@return		int 0--�ɹ�  ����--ʧ��  �ο�ConstDefine.h�е�ö��ֵ
		 **/
		virtual int init(DxRender* render, const TCHAR* shaderFileName);
		/**
		 *	@name		deinit
		 *	@brief		�ͷ�init�е���Դ
		 *	@return		void
		 **/
		virtual void deinit();

		/**
		 *	@name		isValid
		 *	@brief		MetaData�Ƿ���Ч
		 *	@return		bool true--��Ч  false--��Ч
		 **/
		virtual bool isValid() const;

		/**
		 *	@name		getVertexData
		 *	@brief		��ȡ������Ϣ��IndexBuffer��Ϣ
		 *	@return		zRender::VertexVector*
		 **/
		virtual VertexVector* getVertexData();

		/**
		 *	@name		getTextureDataSource
		 *	@brief		��ȡ�������ݶ���
		 *	@return		zRender::TextureDataSource*
		 **/
		virtual TextureDataSource* getTextureDataSource() const { return m_textureDataSource; }

		/**
		 *	@name		setTextureDataSource
		 *	@brief		������������Դ����
		 *	@param[in]	zRender::TextureDataSource* ��������Դ����
		 **/
		virtual void setTextureDataSource(TextureDataSource* textureDataSrc)
		{
			m_textureDataSource = textureDataSrc;
		}

		virtual bool isTextureNeedUpdate(int& identify);

		/**
		 *	@name		update
		 *	@brief		�����ݸ��µ��Դ���
		 *	@return		int
		 **/
		virtual int update();

		/**
		 *	@name		getDsplModel
		 *	@brief		��ȡElement���Ͷ�Ӧ����ʾModel����
		 *	@return		zRender::ElemDsplModel<zRender::BasicEffect>* ��ʾModel����ָ��
		 **/
		virtual ElemDsplModel<BasicEffect>* getDsplModel() const { return m_dsplModel; }

	private:
		int createDisplayModel(DxRender* render, const TCHAR* shaderFileName);

		TextureDataSource* m_textureDataSource;
		VertexVector* m_vertexVector;
		int m_vertexIdentify = 0;
		ElemDsplModel<BasicEffect>* m_dsplModel;
	};
}

#endif
