#pragma once
#ifndef _Z_RENDER_ZRECT_H_
#define _Z_RENDER_ZRECT_H_

#include "DisplayElement.h"
#include "DxZRenderDLLDefine.h"

namespace zRender
{
	class DX_ZRENDER_EXPORT_IMPORT ZRect : public DisplayElement
	{
	public:
		ZRect(DxRender* dxRender);
		virtual ~ZRect();

		static ZRect* create(DxRender* dxRender, const RECT_f& displayReg, int zIndex);
		static void release(ZRect** rectElem);
	protected:
		/**
		 *	@name		init
		 *	@brief		��ʼ�������MetaData��DrawingContext�ĳ�ʼ��
						���캯���н�ֱ�ӵ�������������л�����ʼ��
		 *	@return		int 0--�ɹ�  ����--ʧ��
		 **/
		virtual int init(DxRender* dxRender);

		/**
		 *	@name		deinit
		 *	@brief		�ͷ�init�����д�������Դ
		 *	@return		int 0--�ɹ�  ����--ʧ��
		 **/
		virtual void deinit();
	};
}

#endif//_Z_RENDER_ZRECT_H_