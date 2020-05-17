#pragma once
#ifndef _ZRENDER_ELEMENT_DRAWING_CONTEXT_H_
#define _ZRENDER_ELEMENT_DRAWING_CONTEXT_H_

#include "ElemDsplModel.h"
#include "Effects.h"
#include "LightHelper.h"

namespace zRender
{
	class BasicEffect;
	class DxRender;
	class ElementMetaData;
	class ITextureResource;

	class ElementDrawingContext
	{
	public:
//		const XMFLOAT4X4& getWorldTransformMatrix() const { return m_WorldTransformMat; }
//		void setWorldTransformMatrix(const XMFLOAT4X4& worldMat);
//
//// 		const XMFLOAT4X4& getViewTransformMatrix() const { return m_viewTransform; }
//// 		void setViewTransformMatrix(const XMFLOAT4X4& viewMat);
//
////		const XMFLOAT4X4& getProjectionTransformMatrix() const { return m_projTransform; }
////		void setProjectionTransformMatrix(const XMFLOAT4X4& projectionMat);
//
//		const Material& getMaterial() const;
//		void setMaterial(const Material& material);
		virtual ~ElementDrawingContext() = 0 {}

		virtual int apply(DxRender* render, ITextureResource* textures[], int textureCount,
			ID3D11Buffer* vtBuf, ID3D11Buffer* indexBuffer, ElementMetaData* metadata) = 0;


		/**
		 *	@name		setDisplayRegion
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ��
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ���ݵ�����
		 *	@param[in]	const RECT_f& displayReg	��ʾ��ʾ����ĵ�����ϵλ��
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		virtual int setDisplayRegion(const RECT_f& displayReg, float zIndex) = 0;//�����ƶ����������ݵ���ʾλ��

		/**
		 *	@name		setZIndex
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ�õ�Z����
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ����Z���������
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		**/
		virtual int setZIndex(float zIndex) = 0;

		virtual float getZIndex() const = 0;

		/**
		 *	@name		setDsplModel
		 *	@brief		����ʹ�õ�Display Model
		 *	@param[in]	ElemDsplModel<BasicEffect> * dsplModel ElemDsplModel����
		 *	@return		void
		 **/
		virtual void setDsplModel(ElemDsplModel<BasicEffect>* dsplModel) = 0;

		virtual void enableTransparent(bool enable) = 0;
		virtual bool isEnableTransparent() const = 0;

		/**
		 *	@name			setAlpha
		 *	@brief			������ʾ����͸���ȣ���Ч��Χ��1.0f -- 0.0f��
		 *	@param[in]		float alpha ͸���ȣ�1.0fΪ��͸���� 0.0fΪȫ͸��
		 **/
		virtual void setAlpha(float alpha) = 0;
		/**
		 *	@name			getAlpha
		 *	@brief			��ȡ��ǰ���õ�͸����
		 *	@return			float
		 **/
		virtual float getAlpha() const = 0;
	};

}
#endif//_ZRENDER_ELEMENT_DRAWING_CONTEXT_H_
