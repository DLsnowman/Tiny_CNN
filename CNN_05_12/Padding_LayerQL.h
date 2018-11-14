#pragma once
#include "LayerQL.h"

namespace tinyDNN
{
	template <typename Dtype>
	class Padding_LayerQL : public LayerQL<Dtype>
	{
	public:
		Padding_LayerQL(LayerType type, int rowNum, int colNum, int padSize);
		~Padding_LayerQL() override final;
		//��ǰ����������Vector�еľ����
		void calForward(int type = 0) const override final;
		void calForward_Vector() const;

		//���򴫲�������
		void calBackward(int type = 0) override final;
		void calBackward_Vector();

		void upMatrix() override final {};
		void upMatrix_batch(Dtype upRate) override final {};

	private:
		int rowNum;
		int colNum;
		int padSize;
	};

}