#include "LoadCSV.h"

namespace tinyDNN
{
	//����MNIST���ݼ���ѵ������55000��
	std::shared_ptr<Inter_LayerQL<double>> LoadCSV::input_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 784);
	std::shared_ptr<Inter_LayerQL<double>> LoadCSV::output_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 10);
	//����MNIST���ݼ������Լ���10000��
	std::shared_ptr<Inter_LayerQL<double>> LoadCSV::input_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 784);
	std::shared_ptr<Inter_LayerQL<double>> LoadCSV::output_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 10);
	//����MNIST���ݼ�����ά����ѵ������55000��
	std::vector<std::shared_ptr<MatrixQL<double>>> LoadCSV::conv_Input_Vector;
	//����MNIST���ݼ�����ά����
	std::vector<std::shared_ptr<MatrixQL<double>>> LoadCSV::conv_Input_Vector_T;

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
				LoadCSV::input_Layer->forward_Matrix->setMatrixQL()(lineNum, inNum) = atoi(str.c_str());
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
				LoadCSV::output_Layer->backward_Matrix->setMatrixQL()(lineNum_L, inNum) = atoi(str.c_str());
				inNum++;
			}
			lineNum_L++;
		}

		LoadCSV::input_Layer->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer->forward_Matrix->getMatrixQL() / 255;

		//std::cout << MatrixWAndB::maTrixTrainToal.row(0) << std::endl;
		//std::cout << MatrixWAndB::maTrixTrainToalL.row(0) << std::endl;
	}

	void LoadCSV::loadCSVTest()
	{
		LoadCSV::input_Layer_T->forward_Matrix->setMatrixQL();
		LoadCSV::output_Layer_T->backward_Matrix->setMatrixQL();

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
				LoadCSV::input_Layer_T->forward_Matrix->setMatrixQL()(lineNum, inNum) = atoi(str.c_str());
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
				LoadCSV::output_Layer_T->backward_Matrix->setMatrixQL()(lineNum_L, inNum) = atoi(str.c_str());
				inNum++;
			}
			lineNum_L++;
		}

		LoadCSV::input_Layer_T->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer_T->forward_Matrix->getMatrixQL() / 255;

		//std::cout << MatrixWAndB::maTrixTrainToal.row(0) << std::endl;
		//std::cout << MatrixWAndB::maTrixTrainToalL.row(0) << std::endl;
	}

	//��ѵ����ͼƬת��ΪVectorͼƬ����
	void LoadCSV::loadCSV_Train_Vector()
	{
		for ( int i= 0 ; i <55000; i++ )
		{
			Eigen::Map<MatrixD> mapMatrix( ( (MatrixD)(LoadCSV::input_Layer->forward_Matrix->getMatrixQL().row(i)) ).data(), 28, 28);

			std::shared_ptr<MatrixQL<double>> convMatrix = std::make_shared<MatrixQL<double>>(28,28);
			convMatrix->setMatrixQL() = mapMatrix;

			conv_Input_Vector.push_back(convMatrix);
		}

		std::cout << ((conv_Input_Vector[999])->getMatrixQL() * 9 ).cast<int>() << std::endl;
	}

	//�����Լ�ͼƬת��ΪVectorͼƬ����
	void LoadCSV::loadCSV_Test_Vector()
	{
		for (int i = 0; i < 10000; i++)
		{
			Eigen::Map<MatrixD> mapMatrix( ( (MatrixD)(LoadCSV::input_Layer_T->forward_Matrix->getMatrixQL().row(i)) ).data(), 28, 28 );

			std::shared_ptr<MatrixQL<double>> convMatrix = std::make_shared<MatrixQL<double>>(28,28);
			convMatrix->setMatrixQL() = mapMatrix;

			conv_Input_Vector_T.push_back(convMatrix);
		}

		std::cout << (( conv_Input_Vector_T[999] )->getMatrixQL() * 9).cast<int>() << std::endl;
	}
}