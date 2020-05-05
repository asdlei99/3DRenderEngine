#pragma once
#ifndef _Z_RENDER_TEXTURE_FASTER_COPY_HELPER_H_
#define _Z_RENDER_TEXTURE_FASTER_COPY_HELPER_H_

#include "DxZRenderDLLDefine.h"
#include "DxRender.h"
#include "inc/TextureResource.h"

namespace zRender
{
	/**
	 *	@name	TextureFasterCopyHelper
	 *	@brief	ʵ���Ż����ڴ����ݿ�����Texture�е�Ч�ʵĲ���
	 *			��Э����ʵ�ֵķ�ʽʱĬ�ϴ�������ͬ����ʽ��Texture��һ��USAGEΪStage��һ��ΪDefault
	 *			����Ҫ���ڴ����ݿ�����Texture��ʱ���ȿ�����Stage��Texture�У�����Stage������Default��
	 **/
	class DX_ZRENDER_EXPORT_IMPORT TextureFasterCopyHelper
	{
	public:
		TextureFasterCopyHelper();
		~TextureFasterCopyHelper();

		int create(DxRender* render, const TextureSourceDesc& srcDesc);
		void release();
		int update(const TextureSourceDesc& srcDesc);

		ITextureResource* getTextureForDraw() const { return m_defaultTex; }
		ITextureResource* getTextureForUpdate() const { return m_stageTex; }
	private:
		TextureFasterCopyHelper(const TextureFasterCopyHelper&);
		TextureFasterCopyHelper& operator=(const TextureFasterCopyHelper&);

		ITextureResource* m_stageTex;
		ITextureResource* m_defaultTex;
	};
}

#endif//_Z_RENDER_TEXTURE_FASTER_COPY_HELPER_H_