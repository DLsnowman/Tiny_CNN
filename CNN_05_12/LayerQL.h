#pragma once
#include "MatrixQL.h"
#include "memory"
#include <iostream>
#include "Inter_LayerQL.h"
namespace tinyDNN 
{
	//struct LayerParameter
	//{
	//	int layerType;
	//	int intNum;
	//	int outNum;
	//	int actType;
	//	int initialType;
	//};
	enum LayerType 
	{	
		Fullconnect_Layer = 1,
		Bias_Layer = 2,
		//Inter_Layer = 3
	};



	template <typename Dtype>
	class LayerQL
	{
	public:
		explicit LayerQL( LayerType type ) ;
		virtual ~LayerQL();

		virtual void calForward( std::unique_ptr<MatrixQL<Dtype>>& feed_Left, std::unique_ptr<MatrixQL<Dtype>>& feed_Right ) const = 0;
		virtual void calBackward( std::unique_ptr<MatrixQL<Dtype>>& loss_Right, std::unique_ptr<MatrixQL<Dtype>>& loss_Left ) = 0;
		

		friend class Test;
		template <typename Dtype> friend std::shared_ptr<Inter_LayerQL<Dtype>> operator+( std::shared_ptr<Inter_LayerQL<Dtype>>& operLeft,  std::shared_ptr<LayerQL<Dtype>>& operRight);
		//virtual std::unique_ptr<LayerQL<Dtype>> operator+(const std::unique_ptr<LayerQL<Dtype>>& operRight) const = 0;

		//friend virtual std::unique_ptr<LayerQL<Dtype>> operator-(const std::unique_ptr<LayerQL<Dtype>>& operLeft, const std::unique_ptr<LayerQL<Dtype>>& operRight) const = 0;

	protected:
		LayerType layerType;
		std::shared_ptr<Inter_LayerQL<Dtype>> left_Layer;
		std::shared_ptr<Inter_LayerQL<Dtype>> right_Layer;

	};

	//	��Ԫ�������������
	template <typename Dtype>
	std::shared_ptr<Inter_LayerQL<Dtype>> operator+( std::shared_ptr<Inter_LayerQL<Dtype>>& operLeft,  std::shared_ptr<LayerQL<Dtype>>& operRight)
	{
		std::shared_ptr<Inter_LayerQL<Dtype>> test = std::make_shared<Inter_LayerQL<Dtype>>();
		test->forward_Matrix = std::make_unique<MatrixQL<Dtype>>(2, 3);
	
		operRight->left_Layer = operLeft;
		operRight->right_Layer = test;

		return test;
	}
	//******************************************************************************************************************************
	template <typename Dtype>
	LayerQL<Dtype>::LayerQL( LayerType type ) : layerType(type)
	{
		std::cout << "Layer Start!" << std::endl;

		////����һ���µľ���Wָ��
		//std::unique_ptr<MatrixQL<Dtype>> iniMatrix(new MatrixQL<Dtype>(3, 3));
		////�õ���Ա����ĵ�ַ�ͳ�ʼ������ָ��ĵ�ַ
		//std::cout << wMatrixQL.get() << std::endl;
		//std::cout << iniMatrix.get() << std::endl;
		////�õ���Ա����ĵ�ַ�ͳ�ʼ������ָ������ĵ�ַ
		//std::cout << &wMatrixQL << std::endl;
		//std::cout << &iniMatrix << std::endl;

		////�ֱ���reset��std::move���ַ���ת������ָ�������Ȩ
		//this->wMatrixQL = std::move(iniMatrix);
		////this->wMatrixQL.reset(iniMatrix.release());
		////�ٴδ�ӡ��Ա�����ַ�ͳ�ʼ�����ַ��������������ָ������ĵ�ַ�����ˡ�
		////˵��move�ǰ�������ֵ������ת���ˡ�
		//std::cout << wMatrixQL.get() << std::endl;
		//std::cout << iniMatrix.get() << std::endl;

		//std::cout << &wMatrixQL << std::endl;
		//std::cout << &iniMatrix << std::endl;

		////����Ա���������
		//this->wMatrixQL->setMatrixQL().setRandom();
		////��ӡ��Ա����
		//std::cout << this->wMatrixQL->getMatrixQL() << std::endl;
	}

	template <typename Dtype>
	LayerQL<Dtype>::~LayerQL()
	{
		std::cout << "Layer Over!" << std::endl;
	}
}

