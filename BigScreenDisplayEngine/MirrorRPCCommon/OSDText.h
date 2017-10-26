#pragma once

#ifndef _SOA_MIRROR_RPC_OSD_TEXT_H_
#define _SOA_MIRROR_RPC_OSD_TEXT_H_

#include "msgpack.hpp"
#include "OSDTextType.h"

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	struct OSDText
	{
		std::string text;
		int type;

		OSDText(const std::string& textCt, OSDTextType textType)
			: text(textCt)
			, type(textType)
		{

		}
		OSDText()
			: type(OSDTextType::Text)
		{

		}
		OSDText(const OSDText& obj)
			: text(obj.text)
			, type(obj.type)
		{

		}

		MSGPACK_DEFINE(text, (int)type);
	};


	//OSDText����м䴫����
	//��Ϊ�йܵ�std::string���ݵ����й�DLL�л���ʧ���ݣ�������Ӵ��м䴫����
	struct OSDTextMedium
	{
		char* text;
		OSDTextType type;
	};

	/**
	 * @name	Shadow
	 * @brief	����OSD��Ӱ�Ĳ���
	 */
	struct Shadow
	{
		unsigned int		color;				//������ɫ
		unsigned int		skewingPixels;		//����ƫ�Ƶ����ظ���
		unsigned float		angle;				//����ƫ�ƵĽǶ�

		MSGPACK_DEFINE(color, skewingPixels, angle);
	};
}		
}
}
#endif 