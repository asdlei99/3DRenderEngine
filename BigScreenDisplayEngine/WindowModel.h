#pragma once

#include <windows.h>
#include <stdio.h>
#include "Rectangle.h"
//using namespace std;
class WindowModel
{
private:
	bool	m_bRuning;
	WNDCLASSEX m_wc;
	HANDLE	m_hWindowMessageThread;	
	bool	m_bWindowMessageThreadExit;
	bool	m_bWindowsCreated;
	int	m_monitorCount;
public:
	WindowModel();
	~WindowModel();

	/**
	 * Method		createWinddows
	 * @brief		�������壬�����ȵ���setWindowRect���ô������ڵ�λ�úʹ�С���ٵ��ø÷�����������
	 * @return		HWND �������� NULL--ʧ��
	 */
	HWND	createWindows();

	/**
	 * Method		showWindow
	 * @brief		��ʾ����
	 * @return		void
	 */
	void showWindow();

	/**
	 * Method		hideWindow
	 * @brief		���ش���
	 * @return		void
	 */
	void hideWindow();

	/**
	 * Method		setBackColor
	 * @brief		���ô��ڵı�����ɫ��û�е��ø÷���֮ǰ����Ϊ��ɫ����
	 * @param[in]	DWORD color ��ɫֵARGB
	 * @return		bool true--���óɹ�  false--����ʧ��
	 */
	bool setBackColor(DWORD color);

	/**
	 * Method		drawText
	 * @brief		�ڴ����е�ĳ����������ʾ�������ݣ���ʱû���ṩ����������ݵĽӿ�
	 *				�ýӿ���ʾ��̵�����ʱЧ����Ϻã���ΪĬ��Ч����������������������ʾ���򣬲����Զ�����
	 * @param[in]	const char * text ��������
	 * @param[in]	const SOA::Mirror::RPC::RectCoordinate & rectOfWindow ��ʾ���򣬹�һ�������ʾ������������ڵ�����
	 * @return		bool true--�ɹ� false--ʧ��
	 */
	bool drawText(const TCHAR* text, const SOA::Mirror::RPC::RectCoordinate& rectOfWindow, COLORREF fontColor);

	/**
	 * Method		setWindowRect
	 * @brief		���ô��ڵ�λ�úʹ�С����Ҫ��createWindows����֮ǰ���ã�֮����ò���ı䴰��λ�á���С
	 * @param[in]	RECT rect ���ڵ�λ�úʹ�С
	 * @return		void
	 */
	void setWindowRect(RECT rect)
	{
		m_winRect = rect;
	}

	/**
	 * Method		getWindowRect
	 * @brief		��ȡ���ڵ�λ�úʹ�С
	 * @return		RECT ���ڵ�λ�úʹ�С
	 */
	RECT getWindowRect()
	{
		return m_winRect;
	}

	HWND m_hwnd;

private:
	static DWORD getWindowMessageThread(void *pParam);
	void getWindowMessageThreadCallback();
	HWND createWindow(int w_left,int w_top,int w_width,int w_height);
	HWND createWindow_internal(int x,int y,int width,int height,HINSTANCE hInstance);
	RECT m_winRect;
};