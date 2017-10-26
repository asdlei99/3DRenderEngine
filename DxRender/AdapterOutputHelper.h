/**
 *	@date		2017:6:22   15:21
 *	@name	 	AdapterOutputHelper.h
 *	@brief		logger for DxRender module
 **/
#ifndef _DX_RENDER_ADAPTER_OUTPUT_HELPER_H_
#define _DX_RENDER_ADAPTER_OUTPUT_HELPER_H_

#include <vector>
#include <Windows.h>
#include "DxZRenderDLLDefine.h"

namespace zRender
{
	/**
	 *	@name			getScreenLogicSysPos
	 *	@brief			��ȡ���������������ӵ���ʾ���ڲ���ϵͳ�е��߼�λ������.
	 *	@param[out]		std::vector<RECT>& outPosVec
	 *	@return			int outPosVec����Ϣ�ĸ�����-1--ʧ��
	 **/
	int DX_ZRENDER_EXPORT_IMPORT getAllScreenLogicSysPos(std::vector<RECT>& outPosVec);
	/**
	 *	@name			getScreenLogicSysPos
	 *	@brief			��ȡ����hwnd���ڵ���ʾ����ϵͳ�е��߼�λ������.
	 *	@param[in]		HWND hwnd
	 *	@return			RECT hwnd���ڵ���ʾ����ϵͳ�е��߼�λ������
	 **/
	RECT DX_ZRENDER_EXPORT_IMPORT getScreenLogicSysPos(HWND hwnd);
}

#endif//_DX_RENDER_ADAPTER_OUTPUT_HELPER_H_