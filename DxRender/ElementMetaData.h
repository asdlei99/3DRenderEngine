#pragma once
#ifndef _ZRENDER_ELEMENT_META_DATA_H_
#define _ZRENDER_ELEMENT_META_DATA_H_

#include "d3d11.h"
#include "DxRenderCommon.h"
#include "ElemDsplModel.h"

namespace zRender
{
	class TextureDataSource;
	class VertexVector;
	class DxRender;
	class BasicEffect;

	class ElementMetaData
	{
	public:
		ElementMetaData();
		~ElementMetaData();

		/**
		 *	@name		init
		 *	@brief		��ʼ��Element��MetaData
		 *	@param[in]	DxRender * render ������Դ��DxRender
		 *	@param[in]	const TCHAR * shaderFileName Shader�ļ���·��
		 *	@return		int 0--�ɹ�  ����--ʧ��  �ο�ConstDefine.h�е�ö��ֵ
		 **/
		int init(DxRender* render, const TCHAR* shaderFileName);
		/**
		 *	@name		deinit
		 *	@brief		�ͷ�init�е���Դ
		 *	@return		void
		 **/
		void deinit();

		/**
		 *	@name		isValid
		 *	@brief		MetaData�Ƿ���Ч
		 *	@return		bool true--��Ч  false--��Ч
		 **/
		bool isValid() const;

		/**
		 *	@name		getVertexData
		 *	@brief		��ȡ������Ϣ��IndexBuffer��Ϣ
		 *	@return		zRender::VertexVector*
		 **/
		VertexVector* getVertexData();

		/**
		 *	@name		getTextureDataSource
		 *	@brief		��ȡ�������ݶ���
		 *	@return		zRender::TextureDataSource*
		 **/
		TextureDataSource* getTextureDataSource();

		/**
		 *	@name		update
		 *	@brief		�����ݸ��µ��Դ���
		 *	@return		int
		 **/
		int update();

		/**
		 *	@name		getDsplModel
		 *	@brief		��ȡElement���Ͷ�Ӧ����ʾModel����
		 *	@return		zRender::ElemDsplModel<zRender::BasicEffect>* ��ʾModel����ָ��
		 **/
		ElemDsplModel<BasicEffect>* getDsplModel() const { return m_dsplModel; }

	private:
		int createDisplayModel(DxRender* render, const TCHAR* shaderFileName);

		TextureDataSource* m_textureDataSource;
		VertexVector* m_vertexVector;
		int m_vertexIdentify = 0;
		ElemDsplModel<BasicEffect>* m_dsplModel;
	};
}


#endif//_ZRENDER_ELEMENT_META_DATA_H_
