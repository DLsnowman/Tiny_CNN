#pragma once
#include "PooLayerQL.h"

namespace tinyDNN
{
	template <typename Dtype>
	class Pool_Test
	{
	public:
		Pool_Test()
		{
			this->pool_Average_Vector();
		}

		void pool_Average_Vector()
		{
			//���Լ��ؾ����άͼ��,ѵ����
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();




		}

		void pool_Test()
		{
				
		}

		~Pool_Test(){}
	};
}