/**
 *	@author		zhuqingquan
 *	@date		2014-10-17
 *	@name		DxRenderCommon.h
 *	@brief		define some common structure, micro define, const var be used in DxRender module
 */

#pragma once
#ifndef _ZRENDER_DXRENDER_COMMON_H_
#define _ZRENDER_DXRENDER_COMMON_H_

namespace zRender
{

#define RANGE_OF_ZINDEX_MIN 0.0f
#define RANGE_OF_ZINDEX_MAX 1000000.0f
#define POS_ZINDEX_OF_EYE -100

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

	struct RECT_f
	{
		float left;
		float right;
		float top;
		float bottom;

		RECT_f() : left(0.0), right(0.0), top(0.0), bottom(0.0)	{}
		RECT_f(float l, float r, float t, float b) : left(l), right(r), top(t), bottom(b)	{}

		float width() const { return right-left; }
		float height() const { return bottom-top; }

		/**
		 *	@name		isIntersect
		 *	@brief		�жϵ�ǰ�����Ƿ���other��ʾ�������ཻ�������ڲ���Ϊ���ཻ
		 *	@param[in]	const RECT_f& other ���Ƚϵ�����
		 *	@return		true--�������ཻ  false--���ཻ  
		 **/
		bool isIntersect(const RECT_f& other) const
		{
			const float dx = 0.00000001f;
			return !((this->left-other.right > dx)||
					 (this->right-other.left < dx)||
					 (this->bottom-other.top < dx)||
					 (this->top-other.bottom > dx));
		}

		bool isValid() const
		{
			//0.00001����Χ
			return ((right - left) > 0.00001) && ((bottom - top) > 0.00001);
		}

		bool operator==(const RECT_f& robj) const
		{
			return (left-robj.left < 0.00001) && (right-robj.right < 0.00001)
				&& (top-robj.top < 0.00001) && (bottom-robj.bottom < 0.00001)
				&& (robj.left-left < 0.00001) && (robj.right-right< 0.00001)
				&& (robj.top-top < 0.00001) && (robj.bottom - bottom < 0.00001);
		}
		void operator=(const RECT_f& robj)
		{
			left = robj.left;
			top = robj.top;
			right = robj.right;
			bottom = robj.bottom;
		}
	};

	/**
	 *	@brief ��������ö��
	 **/
	enum PIXFormat
	{
		PIXFMT_UNKNOW = 0,
		PIXFMT_YUV420P,		//4:2:0  Y-->U-->V
		PIXFMT_YUY2,		//4:2:2	 YUYVYUYV...
		PIXFMT_A8R8G8B8,	//ARGB
		PIXFMT_R8G8B8,
		PIXFMT_NV12,		//4:2:0  Y-->UV
		PIXFMT_R8G8B8X8,
		PIXFMT_YV12,		//4:2:0  Y-->V-->U
		PIXFMT_R8G8B8A8,	//RGBA
		PIXFMT_B8G8R8A8,	//BGRA
		PIXFMT_B8G8R8X8,	//BGRX
	};

	/**
	 *	@brief �������ص���ռ���ֽ�����ʹ�÷�ʽ�磺PixelByteCount[PIXFMT_YUV420P]������ʽ�Ľ����1.5
	 **/
	const float PixelByteCount[] = {0, 1.5, 2, 4, 3, 1.5, 4, 1.5, 4, 4, 4};

/**
*	@brief ����һ֡ͼƬ�����Ĵ�С��byte
**/
#define FRAMESIZE(width, height, pixfmt) ((width)*(height)*(zRender::PixelByteCount[pixfmt]))

/**
*	@brief ���㱣��ͼƬһ����������������ֽ�����byte
**/
#define FRAMEPITCH(width, pixfmt) ((width)*(zRender::PixelByteCount[pixfmt]))

	typedef enum _TEXTURE_USAGE
	{
		TEXTURE_USAGE_DEFAULT = 0,	//�������Դ���������Դ����֧��CPU��д��֧�ֹ���
		TEXTURE_USAGE_STAGE,		//���ڴ���������Դ��֧��CPU��д�����ɹ���
	}TEXTURE_USAGE;

	/**
	 *	@name		TextureSourceDesc
	 *	@brief		����Դ��TextureԴ���ݵ�������Ϣ
	 **/
	struct TextureSourceDesc
	{
		int width;				// �ֱ��ʣ���
		int height;				// �ֱ��ʣ���
		PIXFormat pixelFmt;		// ���ظ�ʽ��YUV or RGB��
		int pitchs[4];			// ÿ��planel��һ�����ݵ��ֽ���
		char* buffers[4];		// ÿ��planel���ݵ���ʼ��ַ
		bool isShared;			// �Ƿ���
		unsigned int hShared;	// ���ڴ򿪹����Դ��HANDLE

		TextureSourceDesc()
			: width(0), height(0), pixelFmt(PIXFMT_UNKNOW)
			, isShared(false), hShared(0)
		{
			pitchs[0] = pitchs[1] = pitchs[2] = pitchs[3] = 0;
			buffers[0] = buffers[1] = buffers[2] = buffers[3] = nullptr;
		}

		void set(const TextureSourceDesc& srcDesc)
		{
			width = srcDesc.width;
			height = srcDesc.height;
			pixelFmt = srcDesc.pixelFmt;
			isShared = srcDesc.isShared;
			hShared = srcDesc.hShared;
			pitchs[0] = srcDesc.pitchs[0];
			pitchs[1] = srcDesc.pitchs[1];
			pitchs[2] = srcDesc.pitchs[2];
			pitchs[3] = srcDesc.pitchs[3];
			buffers[0] = srcDesc.buffers[0];
			buffers[1] = srcDesc.buffers[1];
			buffers[2] = srcDesc.buffers[2];
			buffers[3] = srcDesc.buffers[3];

		}
	};
}

#endif //_zRENDER_DXRENDER_COMMON_H_