/*
 *	@file		BigScreenBackground.h
 *	@data		2013-7-23 15:25
 *	@author		zhu qing quan
 *	@brief		BigScreen������ͼ���ݹ������ṩ����
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RENDER_BIGSCREEN_BACKGROUND_H_
#define _SOA_MIRROR_RENDER_BIGSCREEN_BACKGROUND_H_

#include "BSFDataType.h"
#include "DxRenderCommon.h"
#include "IDisplayContentProvider.h"
#include <vector>

namespace SOA
{
namespace Mirror
{
namespace Render
{
	/**
	 * @name	BigScreenBackground
	 * @brief	����ǽ������ͼ���ݹ�����ṩ
	 */
	class BigScreenBackground
	{
	public:
		/**
		 * Method		BigScreenBackground
		 * @brief		���캯��
		 * @param[in]	const char * imageFileName ������ͼ���ļ�������ֻ֧��JPEGͼƬ
		 * @param[in]	int bigscreenWidth ����ǽ�Ŀ���4*3
		 * @param[in]	int bigscreenHeight ����ǽ�ĸߣ���4*3
		 * @param[in]	const Size & cellRsolution ����ǽ��ÿ������ķֱ��ʣ�������Ϊÿ������ķֱ��ʶ���һ����
		 *				������ڲ�ͬ�ֱ��ʵĴ�����ʹ�ö���ģʽ�ı�����ͼ����Ϊ�ϲ�ģʽ���ܿ�����Ч������
		 * @param[in]	SOA::Mirror::PIXFormat pixfomat JPEG������ʾΪ��ͼ������ظ�ʽ
		 */
		BigScreenBackground(const char* imageFileName,
							int  bigscreenWidth, int  bigscreenHeight,
							const Size& cellRsolution, zRender::PIXFormat pixfomat);
		/**
		 * Method		~BigScreenBackground
		 * @brief		��������
		 */
		virtual ~BigScreenBackground();

		/**
		 * Method		setBigscreenCellResolution
		 * @brief		���ô���ķֱ��ʣ�δʵ��
		 *				���ܹ������ϲ�ģʽ�´���ֱ��ʲ�ͬʱҲ���кܺõ���ʾЧ�������ø÷���
		 * @param[in]	const Size & resolution ����ķֱ���
		 * @return		bool true--���óɹ� false--����ʧ��
		 */
		virtual bool setBigscreenCellResolution(const Size& resolution) = 0;//���õ�������ķֱ���

		/**
		 * Method		allocBackgroundContentForBigscreenCell
		 * @brief		����ͼƬ������ͼƬ�ָΪÿ�����������ʾ���ݵ������ڴ�ռ�
		 * @return		void
		 */
		void allocBackgroundContentForBigscreenCell();

		/**
		 * Method		freeBackgroundContent
		 * @brief		��allocBackgroundContentForBigscreenCell�����з������ʾ������ռ�õ��ڴ�ռ��ͷ�
		 * @return		void
		 */
		virtual void freeBackgroundContent();

		/**
		 * Method		getBigscreenCellPaintRegion
		 * @brief		��ȡ������ͼ�ڵ��������е���ʾ����
		 * @param[in]	int XofBigScreen �����ڵ���ǽ�е�X����
		 * @param[in]	int YofBigScreen �����ڵ���ǽ�е�Y����
		 * @return		const SOA::Mirror::Render::RectCoordinate& ������ͼ�ڴ����е���ʾ����
		 */
		const SOA::Mirror::Render::RectCoordinate& getBigscreenCellPaintRegion(int XofBigScreen, int YofBigScreen);

		/**
		 * Method		getDataOfBigscreenCell
		 * @brief		��ȡ������������ʾ�ı�����ͼ���ڴ��
		 * @param[in]	int XOfBigScreen �����ڵ���ǽ�е�X����
		 * @param[in]	int YOfBigScreen �����ڵ���ǽ�е�Y����
		 * @param[out]	int & bufLen ���ݵĳ��ȣ�byte��
		 * @return		const byte* ָ�򱳾���ͼ���ڴ����׵�ַ
		 */
		const byte* getDataOfBigscreenCell(int XOfBigScreen, int YOfBigScreen, int& bufLen);

		/**
		 * Method		getDataContentOfBigscreenCell
		 * @brief		��ȡ������������ʾ�ı�����ͼ�������ṩ�ߣ��������ṩ�߿�������DxRender����ʾ
		 * @param[in]	int XOfBigScreen �����ڵ���ǽ�е�X����
		 * @param[in]	int YOfBigScreen �����ڵ���ǽ�е�Y����
		 * @return		zRender::IDisplayContentProvider* ������ͼ�������ṩ�� 
		 */
		zRender::IDisplayContentProvider* getDataContentOfBigscreenCell(int XofBigscreen, int YofBigscreen) const; 

		/**
		 * Method		getDisplayRegOfBigscreenCell
		 * @brief		��ȡ����������������ʾ����ͼƬ������������BigScreen�е�����
		 * @param[in]	int XOfBigScreen �����ڵ���ǽ�е�X����
		 * @param[in]	int YOfBigScreen �����ڵ���ǽ�е�Y����
		 * @return		zRender::RECT_f ����������������ʾ����ͼƬ������������BigScreen�е�����
		 */
		zRender::RECT_f getDisplayRegOfBigscreenCell(int XofBigscreen, int YofBigscreen) const;
	protected:

		struct BigScreenCellPaintRegion
		{
			int XOfBigScreen;
			int YOfBigScreen;
			int cellWidth;		//in pixel
			int cellHeight;		//in pixel
			SOA::Mirror::Render::RectCoordinate paintRegion;
			byte* pData;
			int dataLength;
			zRender::IDisplayContentProvider* m_dcproviders;
			zRender::RECT_f displayReg;

			BigScreenCellPaintRegion(int x, int y, int width, int height)
				: XOfBigScreen(x)
				, YOfBigScreen(y)
				, cellWidth(width)
				, cellHeight(height)
				, pData(NULL)
				, dataLength(0)
				, m_dcproviders(NULL)
			{
				paintRegion.left = paintRegion.right = paintRegion.bottom = paintRegion.top = -1;
			}
		};

		/**
		 * Method		splitBackgroundImageForBigscreenCell
		 * @brief		��ֱ�����ͼ��ÿ��������Ա����Լ��ı�����ͼ���ڴ��
		 * @return		void
		 */
		virtual void splitBackgroundImageForBigscreenCell() = 0;

		/**
		 * Method		scaleTheImageFile
		 * @brief		��СͼƬ����ͼƬ�ֱ��ʴ��ڴ���ֱ��ʣ�����ģʽ�����ߴ�����������ǽ�ķֱ��ʣ��ϲ�ģʽ��ʱ
		 *				��С֮��ͼƬ���ݺ�ȱ��ֲ���
		 * @param[in]	int dstImageWidth ��С��ͼƬ�Ŀ�
		 * @param[in]	int dstImageHeight ��С��ͼƬ�ĸ�
		 * @return		void
		 */
		void scaleTheImageFile(int dstImageWidth, int dstImageHeight);
	private:

		/**
		 * Method		decodeBackgroundImageFile
		 * @brief		��ȡ�ļ����ݲ�����
		 * @param[in]	const char * imageFileName ������ͼ�ļ���
		 * @param[in]	SOA::Mirror::PIXFormat pixfomat ��������صĸ�ʽ
		 * @return		void
		 */
		void decodeBackgroundImageFile(const char* imageFileName, zRender::PIXFormat pixfomat);

		/**
		 * Method		initBigScreenCellPaintRegion
		 * @brief		��ʼ��ÿ����������������Ϣ
		 *				ֻ�ǳ�ʼ����Ҫ��splitBackgroundImageForBigscreenCell����֮����Щ������Ϣ����Ч
		 * @param[in]	const Size & cellRsolution
		 * @return		void
		 */
		void initBigScreenCellPaintRegion(const Size& cellRsolution);

	protected:
		byte* m_decodedData;								//����������׵�ַ
		int m_decodedDataLen;								//��������ݳ���
		int m_bigScreenWidth;								//����ǽ�Ŀ���4*3
		int m_bigScreenHeight;								//����ǽ�ĸߣ���4*3
		int m_imageWidth;									//������ͼ�Ŀ�
		int m_imageHeight;									//������ͼ�ĸ�
		bool m_isSplited;									//��ʶ�Ƿ��Ѳ��ͼƬ��ÿ������
		zRender::PIXFormat m_pixformat;					//ͼƬ���������ظ�ʽ
		const Size m_bigscreenCellResolution;				//ÿ������ķֱ���	
		std::vector<BigScreenCellPaintRegion> m_regions;	//���д���ĵ�ͼ��ʾ�������Ϣ

	};

}
}
}

#endif // _SOA_MIRROR_RENDER_BIGSCREEN_BACKGROUND_H_