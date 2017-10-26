/**
 *	@author		zhuqingquan
 *	@date		2014-10-28
 *	@name		BigView.h
 *	@brief		��ʾ���ݵ��ṩ�ߣ�BigView�ṩBigViewport��ʾʱ����Ķ�����Ϣ��������Ϣ��Shader��Ϣ���Լ�������Ϣ
 *				����Ϊ���࣬�ṩ�ӿ��Լ�Ĭ��ʵ�֣��û�����ͨ���̳иýӿ��ṩ���ḻ���͵�BigView
 */
#pragma once
#ifndef _SOA_MIRROR_RENDER_BIGVIEW_H_
#define _SOA_MIRROR_RENDER_BIGVIEW_H_

#include "IDisplayContentProvider.h"
#include "DxRenderCommon.h"
#include <list>

namespace SOA
{
namespace Mirror
{
namespace Render
{
	class BigViewportPartition;

	class BigView
	{
	public:
		BigView(const zRender::RECT_f& effectiveReg);
		virtual ~BigView();

		virtual zRender::IDisplayContentProvider* applyAuthorization(BigViewportPartition* bvpp);
		virtual int releaseAutorization(BigViewportPartition* bvpp);
		virtual int setEffectiveReg(const zRender::RECT_f& effectiveReg);
		virtual bool isNeedShow() const;

	private:
		int createContentProvider();
		void releaseContentProvider();

		std::list<BigViewportPartition*> m_authorizatedViewportPartion;
		zRender::RECT_f m_effectiveReg;
		zRender::IDisplayContentProvider* m_contentProvider;
	};
}//namespace Render
}//namespace Mirror
}//namespace SOA

#endif //_SOA_MIRROR_RENDER_BIGVIEW_H_