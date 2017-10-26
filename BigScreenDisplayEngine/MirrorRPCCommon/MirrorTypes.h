#pragma once

#ifndef _MIRROR_TYPES_H_
#define _MIRROR_TYPES_H_

namespace SOA{
	namespace Mirror{

		//����ö�����͡�
		enum PIXFormat
		{
			PIXFMT_UNKOWN = 0,
			PIXFMT_YUV420P,
			PIXFMT_YUY2,
			PIXFMT_A8R8G8B8,
			PIXFMT_R8G8B8,
			PIXFMT_NV12,
			PIXFMT_X8R8G8B8,

			PIXFMT_PCM = 100
		};

		const float SizeOfPixel[] = {0, 1.5, 2, 4, 3, 1.5, 4};

		/*
		 * ����룬ý������ö�����͡�
		 */
		enum Codec
		{
			CODEC_UNKOWN = 0,

			//video codec		//�����ı����ʽ��
			CODEC_H264 = 1,			//H264��ʽ����������
			CODEC_MPEG4,		//MPEG4��ʽ����������
			CODEC_MJPEG,		//MJPEG��ʽ����������
			CODEC_MPEG2_VIDEO = 100,//MPEG2��Ƶ���������͡�
			CODEC_HIK,           //��������������

			//source codec		//ý��������Դ�����͡�
			CODEC_H264_NAL = 4,		//NAL����Դ����
			CODEC_H264_RTP,		//H264��ʽ��������RTP����Դ����
			CODEC_RTSP,			//RTSP����Դ����
			CODEC_MPEG4_RTP,	//MPEG4��ʽ��������RTP����Դ����
			CODEC_MJPEG_RTP,	//MJPEG��ʽ��������RTP����Դ����
			CODEC_MPEG2_RTP,	//MPEG2��ʽ��������RTP����Դ���ͣ���������MPEG2_ES��һ�����з�װ�ĸ�ʽ��
			CODEC_MPEG2_ES_RTP,	//MP2��ʽ��������RTP����Դ���ͣ�ֱ�ӵ�MPEG2������û�з�װ��ʽ��
			CODEC_HIK_AV,       //������ý�������ͣ�������

			//audio codec
			CODEC_G711_ALAW = 1000,
			CODEC_G711_ULAW,
			CODEC_MPEG2_AUDIO,	//MPEG2��Ƶ���������͡�
			CODEC_AAC,
		};

		/*
		 * ��ɫ�ṹ��
		 */
		struct Color
		{
			unsigned char a;
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};

		/*
		 * ��32Ϊ����ֵת��ΪColor����
		 */
		inline Color ColorFrom(unsigned int color)
		{
			Color bigColor;
			bigColor.a = (unsigned char)((color & 0xff000000) >> 24);
			bigColor.r = (unsigned char)((color & 0x00ff0000) >> 16);
			bigColor.g = (unsigned char)((color & 0x0000ff00) >> 8);
			bigColor.b = (unsigned char)(color & 0x000000ff);
			return bigColor;
		}

		/*
		 * ��Color����ת��Ϊ32Ϊ����ֵ
		 */
		inline unsigned int ColorTo(const Color& color)
		{
			unsigned int result = 0;
			//memcpy(&result, &color, sizeof(result));
			unsigned int tmp = color.a;
			result = (result | (tmp << 24));
			tmp = color.r;
			result = (result | (tmp << 16));
			tmp = color.g;
			result = (result | (tmp << 8));
			tmp = color.b;
			result = (result | (tmp));
			return result;
		}

		/*
		 * ��ȡ��sampleColor��ɫ���������ɫ
		 */
		inline Color getMaxDistinctionColor(const Color& sampleColor)
		{
			Color result;
			result.a = sampleColor.a;
			result.r = sampleColor.r>=128 ? 0x00 : 0xFF;
			result.g = sampleColor.g>=128 ? 0x00 : 0xFF;
			result.b = sampleColor.b>=128 ? 0x00 : 0xFF;
			return result;
		}

		/*
		 * RTSPý������Դ�����ӷ�ʽ��
		 */
		enum ConnectionType
		{
			UnicastRtp = 0,
			MulticastRtp,
			OverHttp,
			Tcp
		};

		/*
		 * �����������͡�
		 */
		enum StreamType
		{
			STREAM_T_UNKOWN = 0,
			STREAM_T_VIDEO,
			STREAM_T_AUDIO,
			STREAM_T_MIXED//����Ƶ���
		};

		/*
		 * ����֡����ʾ�Ķ�ʱ������
		 */
		enum TimerType
		{
			TIMER_T_UNKOWN = 0,//��ϵͳȷ����ʱ�������͡�
			TIMER_T_VIDEOCARD,//�Կ���ʱ����
			TIMER_T_MEDIATIMER,//ý�������ʱ����
		};

		/*
		 * �滭����
		 */
		enum DrawType
		{
			DT_T_UNKOWN = 0,//
			DT_T_TEXTURE_ONLY,//ֻ��������滭
			DT_T_SURFACE_ONLY,//ֻ���ñ���
			DT_T_SURFACE_TO_TEXTURE,//���ñ��浽����Ļ滭
		};

		struct BigScreenConfig
		{
			BigScreenConfig():pixFormatOfView(PIXFormat::PIXFMT_A8R8G8B8)
				,drawType(DrawType::DT_T_TEXTURE_ONLY)
				,bScaleForDraw(true)
				,timeType(TimerType::TIMER_T_VIDEOCARD)
				,refreshRate(60)
			{

			}
			PIXFormat pixFormatOfView;
			DrawType drawType;

			bool bScaleForDraw;
			TimerType timeType;
			int refreshRate;
		};

		/*
		 *	����ǽ������ͼ����ʾģʽ
		 */
		enum BigScreenBackgroundMode
		{
			BS_BACKGROUNDMODE_Independent   = 0,		//����ģʽ
			BS_BACKGROUNDMODE_Merged		= 1,		//�ϲ�ģʽ
		};
	}
}

#endif //_MIRROR_TYPES_H_