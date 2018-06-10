#pragma once
#include <Eigen/Core>
#include<cmath>

namespace tinyDNN {

	template <typename Dtype>
	class MatrixQL
	{
		//	����ײ�Eigen����ģ��
		using MatrixData = Eigen::Matrix <Dtype, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
	public:
		//	MatrixQL() = default;
		//	��ʽ����ģ�幹�캯��
		explicit MatrixQL(int rowNum, int colNum);
		//	��������
		~MatrixQL();

		const MatrixData& getMatrixQL() const;
		MatrixData& setMatrixQL();

	private:
		//	�����ײ����
		MatrixData matrixData;
		//	��������
		int rowNum;
		//	��������
		int colNum;
	};

	//	ģ�幹�캯��
	template <typename Dtype>
	MatrixQL<Dtype>::MatrixQL(int rowNum, int colNum) : rowNum(rowNum), colNum(colNum)
	{
		//std::cout << "Matrix Start!" << std::endl;
		
		//	�������ĵײ���������ô�С
		this->matrixData.resize(this->rowNum, this->colNum);
	}

	//	ģ����������
	template <typename Dtype>
	MatrixQL<Dtype>::~MatrixQL()
	{
		//std::cout << "Matrix Over!" << std::endl;
	}

	//	ȡ���ײ����ݿ�
	//	ע�⣺���ﷵ��ģ�����ڶ������͵�ʱ����Ҫ��typeName
	template <typename Dtype>
	const typename MatrixQL<Dtype>::MatrixData& MatrixQL<Dtype>::getMatrixQL() const
	{
		return this->matrixData;
	}

	template <typename Dtype>
	typename MatrixQL<Dtype>::MatrixData& MatrixQL<Dtype>::setMatrixQL()
	{
		return this->matrixData;
	}
}