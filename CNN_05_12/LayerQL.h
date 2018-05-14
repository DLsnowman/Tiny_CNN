#pragma once
#include "MatrixQL.h"
#include "memory"
#include <iostream>
namespace tinyDNN 
{
	struct LayerParameter
	{
		int layerType;
		int intNum;
		int outNum;
		int actType;
		int initialType;


	};

	template <typename Dtype>
	class LayerQL
	{
	public:
		explicit LayerQL();
		virtual ~LayerQL();

		virtual void calForward( std::unique_ptr<MatrixQL<Dtype>>& matrixIn, std::unique_ptr<MatrixQL<Dtype>>& matrixOut ) const  = 0;
		virtual void calBackward( std::unique_ptr<MatrixQL<Dtype>>& matrixIn, std::unique_ptr<MatrixQL<Dtype>>& matrixOut )  = 0;


	};

	template <typename Dtype>
	LayerQL<Dtype>::LayerQL()
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

