/*
 *	@file		IndependentBigScreenBackground.h
 *	@data		2013-7-23 19:00
 *	@author		zhu qing quan
 *	@brief		����ģʽ�ı�����ͼ
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RENDER_INDEPENDENT_BIGSCREEN_BACKGROUND_H_
#define _SOA_MIRROR_RENDER_INDEPENDENT_BIGSCREEN_BACKGROUND_H_

#include "BigScreenBackground.h"

namespace SOA
{
namespace Mirror
{
namespace Render
{
	/**
	 * @name	IndependentBigScreenBackground
	 * @brief	����ģʽ�ı�����ͼ
	 */
	class IndependentBigScreenBackground : public BigScreenBackground
	{
	public:
		IndependentBigScreenBackground(const char* imageFileName,
										int  bigscreenWidth, int  bigscreenHeight,
										const Size& cellRsolution, zRender::PIXFormat pixfomat);

		virtual ~IndependentBigScreenBackground();

		bool setBigscreenCellResolution(const Size& resolution);

	private:
		/**
		 * Method		splitBackgroundImageForBigscreenCell
		 * @brief		�ڶ���ģʽ��ֻ��ͼƬ����С�����������в��
		 * @return		void
		 */
		void splitBackgroundImageForBigscreenCell();
	};
}
}
}

#endif // _SOA_MIRROR_RENDER_INDEPENDENT_BIGSCREEN_BACKGROUND_H_