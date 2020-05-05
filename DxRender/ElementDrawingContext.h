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
		ElementDrawingContext(int width, int height);


		const XMFLOAT4X4& getWorldTransformMatrix() const { return m_WorldTransformMat; }
		void setWorldTransformMatrix(const XMFLOAT4X4& worldMat);

// 		const XMFLOAT4X4& getViewTransformMatrix() const { return m_viewTransform; }
// 		void setViewTransformMatrix(const XMFLOAT4X4& viewMat);

//		const XMFLOAT4X4& getProjectionTransformMatrix() const { return m_projTransform; }
//		void setProjectionTransformMatrix(const XMFLOAT4X4& projectionMat);

		const Material& getMaterial() const;
		void setMaterial(const Material& material);

		int apply(DxRender* render, IRawFrameTexture* texture, ID3D11Buffer* vtBuf, ID3D11Buffer* indexBuffer, ElementMetaData* metadata);

		int apply(DxRender* render, ITextureResource* textures[], int textureCount,
			ID3D11Buffer* vtBuf, ID3D11Buffer* indexBuffer, ElementMetaData* metadata);


		/**
		 *	@name		setDisplayRegion
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ��
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ���ݵ�����
		 *	@param[in]	const RECT_f& displayReg	��ʾ��ʾ����ĵ�����ϵλ��
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		 **/
		int setDisplayRegion(const RECT_f& displayReg, float zIndex);//�����ƶ����������ݵ���ʾλ��

		/**
		 *	@name		setZIndex
		 *	@brief		���ø���ʾ��������ʾ��������ϵ�е�λ�õ�Z����
		 *				�û���ͨ���������ø�λ�ôﵽ�ƶ���ʾ����Z���������
		 *	@param[in]	float zIndex ��ǰ��ʾԭʼ���ڶ����Z����ƫ��
		 *	@return		int 0--�ɹ� <0--ʧ��	�ò������Ϸ�ʱʧ��
		**/
		int setZIndex(float zIndex);

		float getZIndex() const;

		/**
		 *	@name		setDsplModel
		 *	@brief		����ʹ�õ�Display Model
		 *	@param[in]	ElemDsplModel<BasicEffect> * dsplModel ElemDsplModel����
		 *	@return		void
		 **/
		void setDsplModel(ElemDsplModel<BasicEffect>* dsplModel) { m_dsplModel = dsplModel; }

		void enableTransparent(bool enable) { m_isEnableTransparent = enable; }
		bool isEnableTransparent() const { return m_isEnableTransparent; }

		/**
		 *	@name			setAlpha
		 *	@brief			������ʾ����͸���ȣ���Ч��Χ��1.0f -- 0.0f��
		 *	@param[in]		float alpha ͸���ȣ�1.0fΪ��͸���� 0.0fΪȫ͸��
		 **/
		void setAlpha(float alpha);
		/**
		 *	@name			getAlpha
		 *	@brief			��ȡ��ǰ���õ�͸����
		 *	@return			float
		 **/
		float getAlpha() const;
	private:

		XMFLOAT4X4			m_WorldTransformMat;
		XMFLOAT4X4			m_worldBaseTransform;
		XMFLOAT4X4			m_viewTransform;
		XMFLOAT4X4			m_projTransform;
		ElemDsplModel<BasicEffect>* m_dsplModel;
		float m_aspectRatio;
		float				m_alpha;
		bool				m_isEnableTransparent;
	};

}
#endif//_ZRENDER_ELEMENT_DRAWING_CONTEXT_H_
