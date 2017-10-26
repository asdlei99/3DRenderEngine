/*
 *	@file		DeviceBaseInfo.h
 *	@data		2013-9-17 20:01
 *	@author		zhu qing quan
 *	@brief		�豸�Ļ�����Ϣ�����豸ID��ͨ��ID���豸���͡��ͺŵ�
 *  @Copyright	(C) 2013, by Ragile Corporation
 */

#pragma once
#ifndef _SOA_MIRROR_RPC_DEVICE_BASE_INFO_H_
#define _SOA_MIRROR_RPC_DEVICE_BASE_INFO_H_

#include <vector>
#include <string>
#include "msgpack.hpp"

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	/**
	 * @name	DeviceBaseInfo
	 * @brief	�豸�Ļ�����Ϣ
	 */
	struct DeviceBaseInfo
	{
		std::string deviceID;		//�豸ID������Ψһ��ʶһ���豸
		std::string channelID;		//ͨ��ID�����ͬһ���豸���ж��ͨ�������ڱ�ʶͨ���е�ID
		//std::string url;			//�����豸����ȡ�豸��Դ�������豸��URL
		std::string friendlyName;	//�Ѻ����ơ������û���ȡ����ı��������ܲ�Ψһ
		std::string path;			//���豸�����л�ȡ���豸����λ�õ�·�������Դ��˽��豸�Ľӿ���Ϣ
		std::string description;	//�豸��������Ϣ����Ʒ�ơ������̡��ͺŵ�
		std::string category;		//�豸����
		bool		isValid;		//���豸�Ƿ����

		MSGPACK_DEFINE(deviceID, channelID, /*url, */friendlyName, path, description, category, isValid);
	};

	/**
	 * @name	DeviceBaseInfoCollection
	 * @brief	�豸������Ϣ�ļ���
	 */
	struct DeviceBaseInfoCollection
	{
		std::vector<DeviceBaseInfo> deviceVec;

		MSGPACK_DEFINE(deviceVec);
	};
}
}
}

#endif // _SOA_MIRROR_RPC_DEVICE_BASE_INFO_H_