/**
 *	@author		zhuqingquan
 *	@date		2014-10-28
 *	@name		BigViewportPartition.h
 *	@brief		��ʾBigViewport�зֺ��ڵ��������е���ʾ����
 */

#pragma once
#ifndef _SOA_MIRROR_RENDER_BIGVIEWPORT_PARTITION_H_
#define _SOA_MIRROR_RENDER_BIGVIEWPORT_PARTITION_H_

#include "DxRenderCommon.h"
#include "IDisplayContentProvider.h"
namespace zRender
{
	class DisplayElement;
}

namespace SOA
{

namespace Mirror
{
namespace Render
{
	class RenderDrawing;
	class BigView;

	class BigViewportPartition
	{
	public:
		BigViewportPartition(const zRender::RECT_f& regOfBigScreen, const zRender::RECT_f& regOfBigViewport, RenderDrawing* rd);
		~BigViewportPartition();

		int attachDisplayElement(zRender::DisplayElement* de);
		zRender::DisplayElement* getAttachedDisplayElement() const;

		int attachBigView(BigView* view);
		int disattachView();
		BigView* getAttachedView() const;

		RenderDrawing* getRenderDrawing() const;
		int move(const const zRender::RECT_f& regOfBigScreen, const zRender::RECT_f& regOfBigViewport);

		int update();
		int notifyToRelease();
		bool isNeedRelease() const { return m_curDrawedTextureIdentify==-1 && m_curDrawedVertexIdentify==-1; }
		bool isValid() const;

		zRender::RECT_f getRegOfBigScreen() const
		{
			return m_regOfBigScreen;
		}

		zRender::RECT_f getRegOfBigViewport() const
		{
			return m_regOfBigViewport;
		}
		
		/**
		 *	@name		setZIndex
		 *	@brief		����BigViewport���ڵ�Z�����꣬ʵ�ֻ�����ӵĲ�ι���
		 *	@param[in]	int zIndex Z������ֵ����ֵͨ���ۺ�BigWindow��BigViewport��Z�������ɣ���ʽΪ ((zOfWindow << 16) | zOfViewport)
		 *				���� zOfWindow��zOfViewport��ȡֵ��Χ��Ϊ [0,1000]
		 **/
		void setZIndex(int zIndex);

		/**
		 *	@name		getZIndex
		 *	@brief		��ȡBigViewport���ڵ�Z�����꣬ʵ�ֻ�����ӵĲ�ι���
		 *	@return		int zIndex Z������ֵ����ֵͨ���ۺ�BigWindow��BigViewport��Z�������ɣ���ʽΪ ((zOfWindow << 16) | zOfViewport)
		 *				���� zOfWindow��zOfViewport��ȡֵ��Χ��Ϊ [0,1000]
		 **/
		int getZIndex() const  { return m_ZIndex; }
	private:
		void updateVertex();
		void updateTexture();

		RenderDrawing* m_renderDrawing;
		zRender::RECT_f m_regOfBigScreen;
		zRender::RECT_f m_regOfBigViewport;
		int m_ZIndex;
		zRender::DisplayElement* m_attachedDE;
		BigView* m_attachedView;
		zRender::IDisplayContentProvider* m_cttProvider;
		int m_curDrawedVertexIdentify;
		int m_curDrawedTextureIdentify;
	};
}
}
}

#endif