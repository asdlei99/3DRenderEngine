/**
 *	@author		zhuqingquan
 *	@date		2014-10-20
 *	@name		Vertex.h
 *	@brief		����Vertex�ṹ�����ݵĶ��壬�Լ���Ӧ��InputLayout�ṹ��Ķ���
 *				�ýṹ����Ϣ��fx�ļ��ж�Ӧ�����붥����Ϣ�Ĳ��ֶ�Ӧ�����޸ı���ͬʱ�޸�
 */

#pragma once
#ifndef _ZRENDER_VERTEX_H_
#define _ZRENDER_VERTEX_H_

#include <vector>
#include "DxZRenderDLLDefine.h"

#ifdef _WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <xnamath.h>
#endif //_WINDOWS

#pragma warning(push)
#pragma warning(disable:4251)

namespace zRender
{
#ifdef _WINDOWS
	/**
	 *	@name	Vertex
	 *	@brief	�����������Ϣ
	 **/
	struct Vertex
	{
		XMFLOAT3 Pos;		//�������꣬(x,y,z),����ʹ�õ����屾�������ϵ
		XMFLOAT3 Normal;	//��ʱ����
		XMFLOAT2 Tex;		//�ö����Ӧ����Texture�е�λ�ã����û��������Ⱦ��ps Effect��ʹ��Texture�������
		XMFLOAT4 Color;		//��ʹ�ô�ɫ��Ⱦʱʹ�øó�Ա
	};

	/**
	 *	@name	InputLayoutDesc
	 *	@brief	Vertex�ṹ���ڴ沼����Ϣ����������
	 **/
	class InputLayoutDesc
	{
	public:
		// Init like const int A::a[4] = {0, 1, 2, 3}; in .cpp file.
		static const D3D11_INPUT_ELEMENT_DESC Basic32[4];
	};
#endif //_WINDOWS

	/**
	 *	@name	VertexVector
	 *	@brief	Vertex���飬����һ�鶥����Ϣ�����������������˽ṹ�Լ�������˽ṹ��Ӧ��index��Ϣ
	 *			�������˽ṹ��ͬ�ĵĶ�����Ϣ������Ӷ�ͬһ��������
	 **/
	class DX_ZRENDER_EXPORT_IMPORT VertexVector
	{
	public:
		/**
		 *	@name		VertexVector
		 *	@brief		���캯��������һ���洢�ض��������͵Ķ�����Ϣ������
		 *	@param[in]	D3D11_PRIMITIVE_TOPOLOGY topology �����������������
		 **/
		VertexVector(D3D11_PRIMITIVE_TOPOLOGY topology);

		/**
		 *	@name		VertexVector
		 *	@brief		��������
		 **/
		~VertexVector();

		/**
		 *	@name		addVertexs
		 *	@brief		��Ӷ�����Ϣ�Լ���֮��Ӧ���±���Ϣ����ӵ���Ϣ���ڱ������п���һ�ݣ��±���Ϣ�����޸�
		 *	@param[in]	const Vertex* vertexList ������Ϣ������
		 *	@param[in]	int vertexCount ������Ϣ������ĳ���
		 *	@param[in]	const UINT* indexList �±���Ϣ������
		 *	@param[in]	int indexCount �±���Ϣ������ĳ���
		 *	@return		int 0--�ɹ�	<0--ʧ�ܣ��������Ϸ������޷�������Դʱ�������ʧ��
		 **/
		int addVertexs(const Vertex* vertexList, int vertexCount, 
						const UINT* indexList, int indexCount);

		/**
		 *	@name		clearVertexs
		 *	@brief		ɾ��������Ϣ�Լ���֮��Ӧ���±���Ϣ��
		 *	@return		int 0--�ɹ�	<0--ʧ��
		 **/
		int clearVertexs();

		/**
		 *	@name		getVertexDataAddr
		 *	@brief		��ȡ�����Ŷ�����Ϣ���ڴ���׵�ַ
		 *	@param[out]	int& dataLen �������������ڴ���ֽ���
		 *	@return		const unsigned char* �����Ŷ�����Ϣ���ڴ���׵�ַ, NULL--�޶�����Ϣ
		 **/
		const unsigned char* getVertexData(int& dataLen) const;

		/**
		 *	@name		getIndexDataAddr
		 *	@brief		��ȡ�������±���Ϣ���ڴ���׵�ַ
		 *	@param[out]	int& dataLen �������������ڴ���ֽ���
		 *	@return		const unsigned char* �������±���Ϣ���ڴ���׵�ַ, NULL--���±���Ϣ
		 **/
		const unsigned char* getIndexData(int& dataLen) const;

		size_t getVertexCount() const { return m_Vertexs.size(); }
		size_t getIndexCount() const  { return m_Indexs.size(); }

		Vertex* getVertex(int index) const;
		UINT	getIndex(int index) const;

		D3D11_PRIMITIVE_TOPOLOGY getPrimitiveTopology() const { return m_topology; }
		DXGI_FORMAT getIndexBufferFormat() const { return m_IndexFmt; }

	private:
		D3D11_PRIMITIVE_TOPOLOGY m_topology;
		DXGI_FORMAT			m_IndexFmt = DXGI_FORMAT_R32_UINT;//
		std::vector<UINT>	m_Indexs;
		std::vector<Vertex> m_Vertexs;
	};
}
#pragma warning(pop)

#endif //_ZRENDER_VERTEX_H_