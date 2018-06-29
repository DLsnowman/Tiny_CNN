#pragma once
#include "LayerQL.h"

namespace tinyDNN
{
	template <typename Dtype>
	class Padding_LayerQL : public LayerQL<Dtype>
	{
	public:
		explicit Padding_LayerQL(LayerType type, int rowNum, int colNum, int padSize);
		~Padding_LayerQL() override final;
		//��ǰ����������Vector�еľ����
		void calForward() const override final;
		void calForward_Vector() const;

		//���򴫲�������
		void calBackward() override final;
		void calBackward_Vector();

		void upMatrix() override final {};
		void upMatrix_batch(Dtype upRate) override final {};

	private:
		int rowNum;
		int colNum;
		int padSize;
	};

}