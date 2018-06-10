#include "LoadCSV.h"

namespace tinyDNN
{
	LoadCSV::LoadCSV(){}

	LoadCSV::~LoadCSV(){}

	void LoadCSV::loadCSVTrain()
	{
		// ���� ѵ���� �� ѵ���ļ�
		std::ifstream inFile("H:/CNN_0510/DATA/MNISTDATA_CSV/train.csv", std::ios::in);
		std::string lineStr;
		int lineNum = 0;
		while (std::getline(inFile, lineStr))
		{
			std::stringstream ss(lineStr);
			std::string str;
			// ���ն��ŷָ�  
			int inNum = 0;
			while (std::getline(ss, str, ','))
			{
				Test::input_Layer->forward_Matrix->setMatrixQL()(lineNum, inNum) = atoi(str.c_str());
				inNum++;
			}

			lineNum++;
		}
		//getchar();

		// ���� ѵ���� ��ѵ�� Lable�ļ�
		std::ifstream inFile_L("H:/CNN_0510/DATA/MNISTDATA_CSV/trainL.csv", std::ios::in);
		std::string lineStr_L;
		int lineNum_L = 0;
		while (std::getline(inFile_L, lineStr_L))
		{
			std::stringstream ss(lineStr_L);
			std::string str;
			// ���ն��ŷָ�  
			int inNum = 0;
			while (std::getline(ss, str, ','))
			{
				Test::output_Layer->backward_Matrix->setMatrixQL()(lineNum_L, inNum) = atoi(str.c_str());
				inNum++;
			}
			lineNum_L++;
		}

		Test::input_Layer->forward_Matrix->setMatrixQL() = Test::input_Layer->forward_Matrix->getMatrixQL() / 255;

		//std::cout << MatrixWAndB::maTrixTrainToal.row(0) << std::endl;
		//std::cout << MatrixWAndB::maTrixTrainToalL.row(0) << std::endl;
	}


	void LoadCSV::loadCSVTest()
	{
		Test::input_Layer_T->forward_Matrix->setMatrixQL();
		Test::output_Layer_T->backward_Matrix->setMatrixQL();

		// ������Լ���ѵ���ļ�
		std::ifstream inFile("H:/CNN_0510/DATA/MNISTDATA_CSV/test.csv", std::ios::in);
		std::string lineStr;
		int lineNum = 0;
		while (std::getline(inFile, lineStr))
		{
			std::stringstream ss(lineStr);
			std::string str;
			// ���ն��ŷָ�  
			int inNum = 0;
			while (std::getline(ss, str, ','))
			{
				Test::input_Layer_T->forward_Matrix->setMatrixQL()(lineNum, inNum) = atoi(str.c_str());
				inNum++;
			}

			lineNum++;
		}
		//getchar();

		// ������Լ���Lable�ļ�
		std::ifstream inFile_L("H:/CNN_0510/DATA/MNISTDATA_CSV/testL.csv", std::ios::in);
		std::string lineStr_L;
		int lineNum_L = 0;
		while (std::getline(inFile_L, lineStr_L))
		{
			std::stringstream ss(lineStr_L);
			std::string str;
			// ���ն��ŷָ�  
			int inNum = 0;
			while (std::getline(ss, str, ','))
			{
				Test::output_Layer_T->backward_Matrix->setMatrixQL()(lineNum_L, inNum) = atoi(str.c_str());
				inNum++;
			}
			lineNum_L++;
		}

		Test::input_Layer_T->forward_Matrix->setMatrixQL() = Test::input_Layer_T->forward_Matrix->getMatrixQL() / 255;

		//std::cout << MatrixWAndB::maTrixTrainToal.row(0) << std::endl;
		//std::cout << MatrixWAndB::maTrixTrainToalL.row(0) << std::endl;
	}
}