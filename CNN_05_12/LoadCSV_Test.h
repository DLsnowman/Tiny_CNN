#pragma once
#include "LoadCSV.h"
namespace tinyDNN
{
	class LoadCSV_Test
	{
	public:
		LoadCSV_Test()
		{
			this->dim2_Matrix();
		}
		~LoadCSV_Test()
		{
		}

		void dim2_Matrix()
		{
			//���Լ��ؾ����άͼ��,ѵ����
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();

			std::cout << LoadCSV::conv_Input_Vector[2]->getMatrixQL() << std::endl;
			std::cout << ( LoadCSV::conv_Input_Vector[2]->getMatrixQL() * 9).cast<int>() << std::endl;


			LoadCSV::loadCSVTest();
			LoadCSV::loadCSV_Test_Vector();

			std::cout << LoadCSV::conv_Input_Vector_T[2]->getMatrixQL() << std::endl;
			std::cout << (LoadCSV::conv_Input_Vector_T[2]->getMatrixQL() * 9).cast<int>() << std::endl;
		}
	};
}