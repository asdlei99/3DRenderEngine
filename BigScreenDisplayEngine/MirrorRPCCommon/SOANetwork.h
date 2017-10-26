/*
 * @file	SOANetwork.h
 * @author	zhu qing quan
 * @date	2012-4-16  13:51
 * @brief	SOA��Ŀ�鹫����������صĹ��߶���ʵ��
			��֧�֣���ȡ����IP���������롢�㲥��ַ��ѯ�ʱ���IP�Ƿ����
 * @Copyright (C) 2011, by Ragile Corporation
 */

#pragma once

#ifndef __SOANetwork_H__
#define __SOANetwork_H__

#include <string>
#include <vector>

namespace SOA
{
	typedef struct IP_INFO_tag
	{
		std::string ip;
		std::string netMask;
		std::string broadcast;
	}IP_INFO;

	/**
	 * Method		getIPConfig
	 * @brief		��ȡ������IP���ã�����IP���������롢�㲥��ַ��
	 * @param[out]	ipInfos IP_INFO�ṹ������
	 * @return		int ��ȡ����IP_INFO�ṹ��ĸ���, -1Ϊ��ȡʧ��
	 */
	int getIPConfig(std::vector<IP_INFO>& ipInfos);

	/**
	 * Method		isConnectable
	 * @brief		����IP�Ƿ����
	 * @param[in]	localIP ����ip��ַ
	 * @return		true--���� false--������
	 */
	bool isConnectable( const char* localIP );

	/**
	 * Method		isNetworkCableConnected
	 * @brief		�ж������Ƿ����Ӻ�
	 * @return		bool true--���Ӻ� false--δ����
	 */
	bool isNetworkCableConnected();

	/**
	 * Method		isHostIPAvailable
	 * @brief		�ж�������IP�����Ƿ����
	 *				�������������IP��Ϊ�쳣��
	 *				1���ֶ�����IPΪ"169.254.*.*",��������Ϊ"255.255.0.0"
	 *				2��û�н����ֶ����ã����޷���DHCP��������ȡ��IP��ϵͳ�Զ���IP����Ϊ"169.254.*.*",��������Ϊ"255.255.0.0"
	 * @param[in]	const std::vector<IP_INFO> & ipInfos �������е�IP��ַ
	 * @return		bool true--����  false--������
	 */
	bool isHostIPAvailable(const std::vector<IP_INFO>& ipInfos);
}

#endif // SOANetwork_H__