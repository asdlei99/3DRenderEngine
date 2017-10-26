/*
 *	@file		BigScreenInfo.h
 *	@data		26:6:2012   14:58
 *	@author		zhu qing quan	
 *	@brief		BigScreen��������Ϣ��������С���Լ�ÿ�����ڵľ��	
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once

#ifndef _BIG_SCREEN_INFO_H_
#define _BIG_SCREEN_INFO_H_

#include "msgpack.hpp"

#ifdef BIGSCREENINFO_DLL_EXPORT
#define BIGSCREENINFO_EXPORT_IMPORT _declspec(dllexport)
#else
#define BIGSCREENINFO_EXPORT_IMPORT _declspec(dllimport)
#endif

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	struct BIGSCREENINFO_EXPORT_IMPORT WindowInfo
	{
		WindowInfo();
		~WindowInfo();

		int handle;
		int monitor;

		MSGPACK_DEFINE(handle, monitor);
	};

	struct BIGSCREENINFO_EXPORT_IMPORT BigScreenInfo
	{
		BigScreenInfo();
		
		~BigScreenInfo();		

		const BigScreenInfo& operator=(const BigScreenInfo& info);

		void addWindowInfo(WindowInfo& info);

		int width;
		int height;
		std::vector<WindowInfo>* windowInfos;

		MSGPACK_DEFINE(width, height, *windowInfos);
	};
}
}
}

#endif