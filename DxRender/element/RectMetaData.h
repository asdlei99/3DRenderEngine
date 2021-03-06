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
		 *	@brief		初始化Element的MetaData
		 *	@param[in]	DxRender * render 创建资源的DxRender
		 *	@param[in]	const TCHAR * shaderFileName Shader文件的路径
		 *	@return		int 0--成功  其他--失败  参考ConstDefine.h中的枚举值
		 **/
		virtual int init(DxRender* render, const TCHAR* shaderFileName);
		/**
		 *	@name		deinit
		 *	@brief		释放init中的资源
		 *	@return		void
		 **/
		virtual void deinit();

		/**
		 *	@name		isValid
		 *	@brief		MetaData是否有效
		 *	@return		bool true--有效  false--无效
		 **/
		virtual bool isValid() const;

		/**
		 *	@name		getVertexData
		 *	@brief		获取顶点信息、IndexBuffer信息
		 *	@return		zRender::VertexVector*
		 **/
		virtual VertexVector* getVertexData();

		/**
		 *	@name		getTextureDataSource
		 *	@brief		获取纹理数据对象
		 *	@return		zRender::TextureDataSource*
		 **/
		virtual TextureDataSource* getTextureDataSource() const { return m_textureDataSource; }

		/**
		 *	@name		setTextureDataSource
		 *	@brief		设置纹理数据源对象
		 *	@param[in]	zRender::TextureDataSource* 纹理数据源对象
		 **/
		virtual void setTextureDataSource(TextureDataSource* textureDataSrc)
		{
			m_textureDataSource = textureDataSrc;
		}

		virtual bool isTextureNeedUpdate(int& identify);

		/**
		 *	@name		update
		 *	@brief		将数据更新到显存中
		 *	@return		int
		 **/
		virtual int update();

		/**
		 *	@name		getDsplModel
		 *	@brief		获取Element类型对应的显示Model对象
		 *	@return		zRender::ElemDsplModel<zRender::BasicEffect>* 显示Model对象指针
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
