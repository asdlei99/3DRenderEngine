/*
 *	@file		MergedBigScreenBackground.h
 *	@data		2013-7-23 20:10
 *	@author		zhu qing quan
 *	@brief		�ϲ�ģʽ�ı�����ͼ
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RENDER_MERGED_BIGSRCEEN_BACKGROUND_H_
#define _SOA_MIRROR_RENDER_MERGED_BIGSRCEEN_BACKGROUND_H_

#include "BigScreenBackground.h"

namespace SOA
{
namespace Mirror
{
namespace Render
{
	class MergedBigScreenBackground : public BigScreenBackground
	{
	public:
		MergedBigScreenBackground(const char* imageFileName,
			int  bigscreenWidth, int  bigscreenHeight,
			const Size& cellRsolution, zRender::PIXFormat pixfomat);

		virtual ~MergedBigScreenBackground();

		/**
		 * Method		freeBackgroundContent
		 * @brief		�ͷ�������ڴ棬��Ϊ�ϲ�ģʽ��ͼƬ�����˲�֣����������������ڴ�ռ�
		 *				����Ҫ��д�÷������ͷ��ڴ�
		 * @return		void
		 */
		void freeBackgroundContent();

		bool setBigscreenCellResolution(const Size& resolution);

	private:
		/**
		 * Method		splitBackgroundImageForBigscreenCell
		 * @brief		�ϲ�ģʽ��Խ�����ͼƬ���в��
		 * @return		void
		 */
		void splitBackgroundImageForBigscreenCell();
	};
}
}
}

#endif // _SOA_MIRROR_RENDER_MERGED_BIGSRCEEN_BACKGROUND_H_