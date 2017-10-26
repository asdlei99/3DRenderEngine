/*
 *	@file		BigScreenCreateType.h
 *	@data		9:7:2012   10:50
 *	@author		zhu qing quan	
 *	@brief		����BigScreen�������͵ĵ�ö��
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RPC_BIGSCREEN_CREATE_TYPE_H_
#define _SOA_MIRROR_RPC_BIGSCREEN_CREATE_TYPE_H_

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	typedef enum BigScreenCreateType
	{
		Server_BigScreen = 1,		//�����������汾�ĵ���ǽ��Bigscreen
		WinForm_BigScreen,			//����WinForm�汾�ĵ���ǽ��Bigscreen
		WPF_Bigscreen,				//����WPF�汾�ĵ���ǽ��Bigscreen
	};
}
}
}

#endif