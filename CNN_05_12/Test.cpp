#include "Test.h"

namespace tinyDNN
{
	std::shared_ptr<Inter_LayerQL<double>> Test::input_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 784);
	std::shared_ptr<Inter_LayerQL<double>> Test::output_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 10);

	std::shared_ptr<Inter_LayerQL<double>> Test::input_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 784);
	std::shared_ptr<Inter_LayerQL<double>> Test::output_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 10);

	Test::Test()
	{
		//Full_Layer ForwardTrans
		//this->Fullconnect_Layer_Forward_Test();
		////Full_Layer BackwardTrans
		//this->Fullconnect_Layer_Backward_Test();
		//Full_Layer_update
		//this->Fullconnect_Layer_Update_Test();
		////Bias_Layer ForwardTrans
		//this->Bias_Layer_Forward_Test();
		////Bias_Layer BackwardTrans
		//this->Bias_Layer_Backward_Test();
		////Bias_Layer update
		//this->Bias_Layer_Update_Test();
		//Operator_Layer
		//this->Operator_Test();
		//==========================================
		//Sigmoid_LayerQL ForwardTrans
		//this->Sigmoid_LayerQL_Forward_Test();
		//Sigmoid_LayerQL BackwardTrans
		//this->Sigmoid_LayerQL_Backward_Test();
		//MSE_LOSS_BACKWARD_TEST()
		//this->MSE_Loss_LayerQL_Backward_Test();

		//==========================================
		this->Mnist_Test();

	}

	Test::~Test()
	{
	}
	
	void Test::Fullconnect_Layer_Forward_Test()
	{
		//	������������ָ��
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(2,3);
		left_Layer->forward_Matrix->setMatrixQL() << 1,2,3,4,5,6;
		std::cout << left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		//	������һ��ȫ���Ӳ�
		std::shared_ptr<LayerQL<double>> fullLayerTest = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 3, 5);
		//	������ȫ���Ӳ�����
		std::shared_ptr<Inter_LayerQL<double>> out_01 = left_Layer + fullLayerTest;
		//	��ǰ����ȫ����
		fullLayerTest->calForward();
		//	���ȫ����ǰ��Ĳ�
		std::cout << fullLayerTest->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << fullLayerTest->right_Layer->forward_Matrix->getMatrixQL() << std::endl;
		//	�����ڶ���ȫ���Ӳ�
		std::shared_ptr<LayerQL<double>> fullLayerTest_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 5, 7);
		std::shared_ptr<Inter_LayerQL<double>> out_02 = out_01 + fullLayerTest_02;
		//	�ڶ���ȫ���Ӳ���ǰ����
		fullLayerTest_02->calForward();
		//	����ڶ���ȫ���Ӳ�ļ�����
		std::cout << fullLayerTest_02->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << fullLayerTest_02->right_Layer->forward_Matrix->getMatrixQL() << std::endl;
	}

	void Test::Fullconnect_Layer_Backward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> InLayer_01 = std::make_shared<Inter_LayerQL<double>>();

		//	��һ���м��
		std::shared_ptr<LayerQL<double>> fullLayer_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer,2,3);
		//	��һ�����
		std::shared_ptr<Inter_LayerQL<double>> InLayer_02 = InLayer_01 + fullLayer_01;
		//	�ڶ����м��
		std::shared_ptr<LayerQL<double>> fullLayer_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer,3,5);
		//	�ڶ������
		std::shared_ptr<Inter_LayerQL<double>> InLayer_03 = InLayer_02 + fullLayer_02;
		//	��ʼ���ڶ����LOSS
		InLayer_03->backward_Matrix = std::make_unique<MatrixQL<double>>(1, 5);
		InLayer_03->backward_Matrix->setMatrixQL().setConstant(1.0);
		
		std::cout << fullLayer_02->right_Layer->backward_Matrix->getMatrixQL() << std::endl;
		fullLayer_02->calBackward();
		std::cout << fullLayer_02->left_Layer->backward_Matrix->getMatrixQL() << std::endl;		
		
		int mm = 0;

	}

	void Test::Fullconnect_Layer_Update_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(1, 5);
		left_Layer->forward_Matrix->setMatrixQL() << 1, 2, 3, 4, 5;

		std::shared_ptr<LayerQL<double>> fullLayerTest = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 5, 10);

		std::shared_ptr<Inter_LayerQL<double>> right_Layer = left_Layer + fullLayerTest;

		right_Layer->backward_Matrix->setMatrixQL().resize(1, 10);
		right_Layer->backward_Matrix->setMatrixQL().setConstant(1);
		
		fullLayerTest->upMatrix();

	}

	void Test::Bias_Layer_Forward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(2,3);
		left_Layer->forward_Matrix->setMatrixQL().setConstant(1.2);
		std::cout << left_Layer->forward_Matrix->getMatrixQL() << std::endl;

		std::shared_ptr<LayerQL<double>> bias_Layer = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 2, 3);
		std::shared_ptr<Inter_LayerQL<double>> out_01 = left_Layer + bias_Layer;

		bias_Layer->calForward();

		std::cout << bias_Layer->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer->right_Layer->forward_Matrix->getMatrixQL() << std::endl;
		//*******************************************************************************************************//

		std::shared_ptr<LayerQL<double>> bias_Layer_02 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 2, 3);
		std::shared_ptr<Inter_LayerQL<double>> out_02 = out_01 + bias_Layer_02;

		bias_Layer_02->calForward();

		std::cout << bias_Layer_02->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer_02->right_Layer->forward_Matrix->getMatrixQL() << std::endl;

		//*******************************************************************************************************//

		std::shared_ptr<LayerQL<double>> bias_Layer_03 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 2, 3);
		std::shared_ptr<Inter_LayerQL<double>> out_03 = out_02 + bias_Layer_03;

		bias_Layer_03->calForward();

		std::cout << bias_Layer_03->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer_03->right_Layer->forward_Matrix->getMatrixQL() << std::endl;

	}

	void Test::Bias_Layer_Backward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> InLayer_01 = std::make_shared<Inter_LayerQL<double>>();
		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer,3, 5);
		std::shared_ptr<Inter_LayerQL<double>> InLayer_02 = InLayer_01 + biasLayer_01;
		biasLayer_01->right_Layer->backward_Matrix->setMatrixQL().resize(3, 5);
		biasLayer_01->right_Layer->backward_Matrix->setMatrixQL().setOnes();
		std::cout << biasLayer_01->right_Layer->backward_Matrix->getMatrixQL() << std::endl;

		biasLayer_01->calBackward();

		std::cout << biasLayer_01->left_Layer->backward_Matrix->getMatrixQL() << std::endl;

	}

	void Test::Bias_Layer_Update_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(1, 5);
		left_Layer->forward_Matrix->setMatrixQL().setConstant(1.2);

		std::shared_ptr<LayerQL<double>> bias_Layer = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 5);
		std::shared_ptr<Inter_LayerQL<double>> right_01 = left_Layer + bias_Layer;

		right_01->backward_Matrix->setMatrixQL().resize(1, 5);
		right_01->backward_Matrix->setMatrixQL().setConstant(10);

		bias_Layer->upMatrix();

	}

	void Test::Sigmoid_LayerQL_Forward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> intputLayer_01 = std::make_shared<Inter_LayerQL<double>>(2,5);
		intputLayer_01->forward_Matrix->setMatrixQL().setOnes();

		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inputLayer_02 = intputLayer_01 + sigmoidLayer_01;

		sigmoidLayer_01->calForward();

		std::cout << inputLayer_02->forward_Matrix->getMatrixQL() << std::endl;

	}

	void Test::Sigmoid_LayerQL_Backward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> intputLayer_01 = std::make_shared<Inter_LayerQL<double>>();

		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inputLayer_02 = intputLayer_01 + sigmoidLayer_01;

		inputLayer_02->forward_Matrix->setMatrixQL().resize(2, 5);
		inputLayer_02->forward_Matrix->setMatrixQL().setConstant(0.5);

		inputLayer_02->backward_Matrix->setMatrixQL().resize(2, 5);
		inputLayer_02->backward_Matrix->setMatrixQL().setConstant(1);
		sigmoidLayer_01->calBackward();

		std::cout << intputLayer_01->backward_Matrix->getMatrixQL() << std::endl;
	}

	void Test::MSE_Loss_LayerQL_Backward_Test()
	{
		using inLayer = std::shared_ptr<Inter_LayerQL<double>>;
		inLayer input_01 = std::make_shared<Inter_LayerQL<double>>(2,5);
		input_01->forward_Matrix->setMatrixQL().setRandom();
		std::cout << input_01->forward_Matrix->getMatrixQL() << std::endl;

		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);

		inLayer input_02 = input_01 + lossLayer_01;

		input_02->backward_Matrix->setMatrixQL().resize(2, 5);
		input_02->backward_Matrix->setMatrixQL().setConstant(1.0);
		
		lossLayer_01->calBackward();

		std::cout << input_01->backward_Matrix->getMatrixQL() << std::endl;

	}

	void Test::Operator_Test()
	{


	}

	void Test::Mnist_Test()
	{
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSVTest();

		std::shared_ptr<Inter_LayerQL<double>> inLayer_01 = std::make_shared<Inter_LayerQL<double>>(1, 784);
		std::shared_ptr<LayerQL<double>> fullLayer_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 784, 10);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_02 = inLayer_01 + fullLayer_01;
		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 10);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_03 = inLayer_02 + biasLayer_01;
		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_04 = inLayer_03 + sigmoidLayer_01;
		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_05 = inLayer_04 + lossLayer_01;

		//	 ������س�ʼʱ��
		DWORD load_time = GetTickCount();

		for (int i = 0; i < 2 ; i ++)
		{
			for (int j = 0; j < 55000; j++)
			{
				inLayer_01->forward_Matrix->setMatrixQL() = Test::input_Layer->forward_Matrix->getMatrixQL().row(j);
				inLayer_05->backward_Matrix->setMatrixQL() = Test::output_Layer->backward_Matrix->getMatrixQL().row(j);

				fullLayer_01->calForward();
				biasLayer_01->calForward();
				sigmoidLayer_01->calForward();
				lossLayer_01->calForward();

				//std::cout << j << std::endl;
				//std::cout << inLayer_04->forward_Matrix->getMatrixQL() << std::endl;

				lossLayer_01->calBackward();
				sigmoidLayer_01->calBackward();
				biasLayer_01->calBackward();
				fullLayer_01->calBackward();

				fullLayer_01->upMatrix();
				biasLayer_01->upMatrix();
			}
		}

		//	ѵ���Ͳ�������ʱ��
		DWORD star_time = GetTickCount();

		std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;


		//std::cout << input_Layer->forward_Matrix->getMatrixQL().row(9999) << std::endl;
		//std::cout << input_Layer_T->forward_Matrix->getMatrixQL().row(9999) << std::endl;

		//std::cout << output_Layer->backward_Matrix->getMatrixQL().row(0) << std::endl;
		//std::cout << output_Layer_T->backward_Matrix->getMatrixQL().row(0) << std::endl;
	}
}