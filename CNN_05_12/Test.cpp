#include "Test.h"

namespace tinyDNN
{
	////����MNIST���ݼ���ѵ������55000��
	//std::shared_ptr<Inter_LayerQL<double>> Test::input_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 784);
	//std::shared_ptr<Inter_LayerQL<double>> Test::output_Layer = std::make_shared<Inter_LayerQL<double>>(55000, 10);
	////����MNIST���ݼ������Լ���10000��
	//std::shared_ptr<Inter_LayerQL<double>> Test::input_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 784);
	//std::shared_ptr<Inter_LayerQL<double>> Test::output_Layer_T = std::make_shared<Inter_LayerQL<double>>(10000, 10);

	Test::Test()
	{
		//Full_Layer ForwardTrans	����ȫ���Ӳ����ǰ����
		//this->Fullconnect_Layer_Forward_Test();
		////Full_Layer BackwardTrans	����ȫ���Ӳ����󴫲�
		//this->Fullconnect_Layer_Backward_Test();
		//Full_Layer_update		����ȫ���Ӳ��Ȩ�ظ��£������õ���SGD��ÿ����һ�������ݸ���һ��
		//this->Fullconnect_Layer_Update_Test();
		//Full_Layer_update_batch	����ȫ���Ӳ��Ȩ�ظ��£������õ���MBGD������BATCH������
		//this->Fullconnect_Layer_Update_Batch_Test();

		//======================================================================================

		////Bias_Layer ForwardTrans		����Bias�����ǰ����
		//this->Bias_Layer_Forward_Test();
		////Bias_Layer BackwardTrans	����Bias�����󴫲�
		//this->Bias_Layer_Backward_Test();
		////Bias_Layer update	����bias���b���£�����SGD
		//this->Bias_Layer_Update_Test();
		////Bias_Layer_Batch update		����bias���b���£�����MBGD
		//this->Bias_Layer_Update_Batch_Test();

		//======================================================================================

		//Operator_Layer	������Ԫ��������� + �����м���Ȩ�صȲ���������
		//this->Operator_Test();

		//======================================================================================

		//Sigmoid_LayerQL ForwardTrans	����Sigmoid���������ǰ����
		//this->Sigmoid_LayerQL_Forward_Test();
		//Sigmoid_LayerQL BackwardTrans	����Sigmoid������ķ��򴫲�
		//this->Sigmoid_LayerQL_Backward_Test();

		//======================================================================================

		//MSE_LOSS_BACKWARD_TEST()	����Loss��ķ��򴫲�
		//this->MSE_Loss_LayerQL_Backward_Test();

		//======================================================================================
		////����SGD
		this->Mnist_Test();
		////���������½� 100һ��
		//this->Mnist_Test_02();
		//���������¼ܣ�10һ��
		//this->Mnist_Test_03();

		//======================================================================================
		////���Լ��ؾ����άͼ��,ѵ����
		//LoadCSV::loadCSVTrain();
		//LoadCSV::loadCSV_Train_Vector();
		////���Լ��ؾ����άͼ�񣬲��Լ�
		//LoadCSV::loadCSVTest();
		//LoadCSV::loadCSV_Test_Vector();
		
		//======================================================================================
		////����Mnist�������
		//this->Mnist_Test_Conv();


	}

	Test::~Test(){}
	
	//============================================================================

	//����ȫ���Ӳ��ǰ�򴫲�
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
	//����ȫ���Ӳ�ķ��򴫲�
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
	//����ȫ���Ӳ��Ȩ�ظ��£������õ���SGD��ÿ����һ�������ݸ���һ��
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
	//����ȫ���Ӳ��Ȩ�ظ��£������õ���MBGD������BATCH������
	void Test::Fullconnect_Layer_Update_Batch_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(3, 5);
		left_Layer->forward_Matrix->setMatrixQL() << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11 ,12, 13, 14, 15;

		std::shared_ptr<LayerQL<double>> fullLayerTest = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 5, 10);

		std::shared_ptr<Inter_LayerQL<double>> right_Layer = left_Layer + fullLayerTest;

		right_Layer->backward_Matrix->setMatrixQL().resize(3, 10);
		right_Layer->backward_Matrix->setMatrixQL().setConstant(1);

		fullLayerTest->upMatrix_batch(0.35);
	}

	//============================================================================

	//����Bias�����ǰ����
	void Test::Bias_Layer_Forward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(2,3);
		left_Layer->forward_Matrix->setMatrixQL().setConstant(1.2);
		std::cout << left_Layer->forward_Matrix->getMatrixQL() << std::endl;

		std::shared_ptr<LayerQL<double>> bias_Layer = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 3, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> out_01 = left_Layer + bias_Layer;

		bias_Layer->calForward();

		std::cout << bias_Layer->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer->right_Layer->forward_Matrix->getMatrixQL() << std::endl;
		//*******************************************************************************************************//

		std::shared_ptr<LayerQL<double>> bias_Layer_02 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 3, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> out_02 = out_01 + bias_Layer_02;

		bias_Layer_02->calForward();

		std::cout << bias_Layer_02->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer_02->right_Layer->forward_Matrix->getMatrixQL() << std::endl;

		//*******************************************************************************************************//

		std::shared_ptr<LayerQL<double>> bias_Layer_03 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 3, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> out_03 = out_02 + bias_Layer_03;

		bias_Layer_03->calForward();

		std::cout << bias_Layer_03->left_Layer->forward_Matrix->getMatrixQL() << std::endl;
		std::cout << bias_Layer_03->right_Layer->forward_Matrix->getMatrixQL() << std::endl;

	}
	//����Bias�����󴫲�
	void Test::Bias_Layer_Backward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> InLayer_01 = std::make_shared<Inter_LayerQL<double>>();
		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer,3, 5, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> InLayer_02 = InLayer_01 + biasLayer_01;
		biasLayer_01->right_Layer->backward_Matrix->setMatrixQL().resize(3, 5);
		biasLayer_01->right_Layer->backward_Matrix->setMatrixQL().setOnes();
		std::cout << biasLayer_01->right_Layer->backward_Matrix->getMatrixQL() << std::endl;

		biasLayer_01->calBackward();

		std::cout << biasLayer_01->left_Layer->backward_Matrix->getMatrixQL() << std::endl;

	}
	//����bias���b���£�����SGD
	void Test::Bias_Layer_Update_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(1, 5);
		left_Layer->forward_Matrix->setMatrixQL().setConstant(1.2);

		std::shared_ptr<LayerQL<double>> bias_Layer = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 5, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> right_01 = left_Layer + bias_Layer;

		right_01->backward_Matrix->setMatrixQL().resize(1, 5);
		right_01->backward_Matrix->setMatrixQL().setConstant(10);

		bias_Layer->upMatrix();

	}
	//����bias���b���£�����MBGD
	void Test::Bias_Layer_Update_Batch_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> left_Layer = std::make_shared<Inter_LayerQL<double>>(3, 5);
		left_Layer->forward_Matrix->setMatrixQL().setConstant(1.2);

		std::shared_ptr<LayerQL<double>> bias_Layer = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 5, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> right_01 = left_Layer + bias_Layer;

		right_01->backward_Matrix->setMatrixQL().resize(3, 5);
		right_01->backward_Matrix->setMatrixQL().setConstant(10);

		bias_Layer->upMatrix_batch(0.35);
	}

	//============================================================================

	//����Sigmoid���ǰ�򴫲�
	void Test::Sigmoid_LayerQL_Forward_Test()
	{
		std::shared_ptr<Inter_LayerQL<double>> intputLayer_01 = std::make_shared<Inter_LayerQL<double>>(2,5);
		intputLayer_01->forward_Matrix->setMatrixQL().setOnes();

		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inputLayer_02 = intputLayer_01 + sigmoidLayer_01;

		sigmoidLayer_01->calForward();

		std::cout << inputLayer_02->forward_Matrix->getMatrixQL() << std::endl;

	}
	//����Sigmoid��ķ��򴫲�
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

	//============================================================================

	//������С������ʧ����
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
	
	//============================================================================

	//���Բ��������
	void Test::Operator_Test(){}

	//============================================================================
	
	void Test::Mnist_Test()
	{
		//��������
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSVTest();

		//��������㣬1��784��
		std::shared_ptr<Inter_LayerQL<double>> inLayer_01 = std::make_shared<Inter_LayerQL<double>>(1, 784);
		//������һ��ȫ���Ӳ㣬784��100��
		std::shared_ptr<LayerQL<double>> fullLayer_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 784, 100);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_02 = inLayer_01 + fullLayer_01;
		//������һ��Bias�㣬1��100��

		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 100, 0.1);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_03 = inLayer_02 + biasLayer_01;

		//������һ��sigmoid��
		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_04 = inLayer_03 + sigmoidLayer_01;

		//�����ڶ���ȫ���Ӳ�
		std::shared_ptr<LayerQL<double>> fullLayer_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 100, 10);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_05 = inLayer_04 + fullLayer_02;
		//�����ڶ���BIAS��
		std::shared_ptr<LayerQL<double>> biasLayer_02 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 10, 0.1);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_06 = inLayer_05 + biasLayer_02;
		//�����ڶ���SIGMOID��
		std::shared_ptr<LayerQL<double>> sigmoidLayer_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		//�ϲ�ǰ����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_07 = inLayer_06 + sigmoidLayer_02;

		//����Loss��
		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);
		//�����
		std::shared_ptr<Inter_LayerQL<double>> inLayer_08 = inLayer_07 + lossLayer_01;

		//	 ������س�ʼʱ��
		DWORD load_time = GetTickCount();

		for (int i = 0; i < 2 ; i ++)
		{
			for (int j = 0; j < 55000; j++)
			{
				//���������ݼ��ؽ������
				inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer->forward_Matrix->getMatrixQL().row(j);
				//���������ݼ��ؽ������
				inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);
				//��ͷ��ʼ����ǰ�򴫲�
				for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
				{
					(*k)->calForward();
				}
				//��ͷ��ʼ���򴫲� + Ȩ�ظ���
				for (auto k = NetQL<double>::layerQLVector.rbegin(); k != NetQL<double>::layerQLVector.rend(); k++)
				{
					(*k)->calBackward();
					(*k)->upMatrix();
				}
			}
		}

		//����ȷ�����ݽ��м���
		double numTotal = 0;
		//�ӵ�һ����ʼ���Բ��Լ�
		for ( int i = 0; i <10000; i ++ )
		{
			//���������������
			inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer_T->forward_Matrix->getMatrixQL().row(i);
			inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(i);
			//ǰ�򴫲���������
			for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
			{
				(*k)->calForward();
			}
			//����õ������ֵλ��
			int maxRow, maxColumn;
			lossLayer_01->left_Layer->forward_Matrix->getMatrixQL().maxCoeff(&maxRow, &maxColumn);
			//Lable�����ֵλ��
			int maxRow_T, maxColumn_T;
			lossLayer_01->right_Layer->backward_Matrix->getMatrixQL().maxCoeff(&maxRow_T, &maxColumn_T);
			//�ж��Ƿ���ȣ�����ȣ���+1
			if (maxColumn == maxColumn_T)
			{
				numTotal++;
			}
		}
		//��ȷ��
		std::cout << numTotal / 10000.00 << std::endl;

		//ѵ���Ͳ�������ʱ��
		DWORD star_time = GetTickCount();

		//��������ʱ��
		std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
	}

	void Test::Mnist_Test_02()
	{
		//��������
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSVTest();

		//��һ����㣬ÿ��ѵ��100�У�784��
		std::shared_ptr<Inter_LayerQL<double>> inLayer_01 = std::make_shared<Inter_LayerQL<double>>(100, 784);
		std::shared_ptr<LayerQL<double>> fullLayer_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 784, 100);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_02 = inLayer_01 + fullLayer_01;
		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 100, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_03 = inLayer_02 + biasLayer_01;
		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_04 = inLayer_03 + sigmoidLayer_01;

		//�ڶ�����㣬ÿ��ѵ��100�У�10��
		std::shared_ptr<LayerQL<double>> fullLayer_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 100, 10);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_05 = inLayer_04 + fullLayer_02;
		std::shared_ptr<LayerQL<double>> biasLayer_02 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 10, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_06 = inLayer_05 + biasLayer_02;
		std::shared_ptr<LayerQL<double>> sigmoidLayer_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_07 = inLayer_06 + sigmoidLayer_02;

		//Loss��������
		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_08 = inLayer_07 + lossLayer_01;

		//������س�ʼʱ��
		DWORD load_time = GetTickCount();

		//��ͷ��ʼ����
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 550; j++)
			{
				//ÿ��ȡ100�����ݼ���
				inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer->forward_Matrix->getMatrixQL().block(j*100, 0, 100, 784);
				inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().block(j * 100, 0, 100, 10);
				//ǰ�򴫲�
				for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
				{
					(*k)->calForward();
				}
				//���򴫲�
				for (auto k = NetQL<double>::layerQLVector.rbegin(); k != NetQL<double>::layerQLVector.rend(); k++)
				{
					(*k)->calBackward();
					(*k)->upMatrix_batch(0.0035);
				}
			}
		}
		//������ȷ��
		double numTotal = 0;
		for (int i = 0; i < 10000; i++)
		{
			//���в��ԣ�ÿ�β���һ��
			inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer_T->forward_Matrix->getMatrixQL().row(i);
			inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(i);
			//ǰ�򴫲�
			for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
			{
				(*k)->calForward();
			}

			int maxRow, maxColumn;
			lossLayer_01->left_Layer->forward_Matrix->getMatrixQL().maxCoeff(&maxRow, &maxColumn);

			int maxRow_T, maxColumn_T;
			lossLayer_01->right_Layer->backward_Matrix->getMatrixQL().maxCoeff(&maxRow_T, &maxColumn_T);
			//������ȷ��
			if (maxColumn == maxColumn_T)
			{
				numTotal++;
			}
		}
		//������ȷ��
		std::cout << numTotal / 10000.00 << std::endl;
		//ѵ���Ͳ�������ʱ��
		DWORD star_time = GetTickCount();
		//��������ʱ��
		std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
	}

	void Test::Mnist_Test_03()
	{
		//��������
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSVTest();
		//����� 10 �� 784��
		std::shared_ptr<Inter_LayerQL<double>> inLayer_01 = std::make_shared<Inter_LayerQL<double>>(10, 784);
		//��һ���
		std::shared_ptr<LayerQL<double>> fullLayer_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 784, 100);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_02 = inLayer_01 + fullLayer_01;
		std::shared_ptr<LayerQL<double>> biasLayer_01 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 100, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_03 = inLayer_02 + biasLayer_01;
		std::shared_ptr<LayerQL<double>> sigmoidLayer_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_04 = inLayer_03 + sigmoidLayer_01;
		//�ڶ����
		std::shared_ptr<LayerQL<double>> fullLayer_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 100, 10);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_05 = inLayer_04 + fullLayer_02;
		std::shared_ptr<LayerQL<double>> biasLayer_02 = std::make_shared<Bias_LayerQL<double>>(Bias_Layer, 1, 10, 0.1);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_06 = inLayer_05 + biasLayer_02;
		std::shared_ptr<LayerQL<double>> sigmoidLayer_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_07 = inLayer_06 + sigmoidLayer_02;
		//Loss��
		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);
		std::shared_ptr<Inter_LayerQL<double>> inLayer_08 = inLayer_07 + lossLayer_01;

		//������س�ʼʱ��
		DWORD load_time = GetTickCount();
		//ѵ����ʼ
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5500; j++)
			{
				//ÿ��ѵ��10��
				inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer->forward_Matrix->getMatrixQL().block(j * 10, 0, 10, 784);
				inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().block(j * 10, 0, 10, 10);
				//ǰ�򴫲�
				for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
				{
					(*k)->calForward();
				}
				//���򴫲�
				for (auto k = NetQL<double>::layerQLVector.rbegin(); k != NetQL<double>::layerQLVector.rend(); k++)
				{
					(*k)->calBackward();
					(*k)->upMatrix_batch(0.35);
				}
			}
		}
		//������ȷ��
		double numTotal = 0;
		for (int i = 0; i < 10000; i++)
		{
			//���Կ�ʼ
			inLayer_01->forward_Matrix->setMatrixQL() = LoadCSV::input_Layer_T->forward_Matrix->getMatrixQL().row(i);
			inLayer_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(i);
			//ǰ�򴫲�
			for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
			{
				(*k)->calForward();
			}
			
			int maxRow, maxColumn;
			lossLayer_01->left_Layer->forward_Matrix->getMatrixQL().maxCoeff(&maxRow, &maxColumn);

			int maxRow_T, maxColumn_T;
			lossLayer_01->right_Layer->backward_Matrix->getMatrixQL().maxCoeff(&maxRow_T, &maxColumn_T);
			//��ȷ��
			if (maxColumn == maxColumn_T)
			{
				numTotal++;
			}
		}
		//������ȷ��
		std::cout << numTotal / 10000.00 << std::endl;
		//	ѵ���Ͳ�������ʱ��
		DWORD star_time = GetTickCount();
		//�������ʱ��
		std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
	}



	void Test::Mnist_Test_Conv()
	{
		//���Լ��ؾ����άͼ��,ѵ����
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSV_Train_Vector();

		//��������㣬1��784��
		std::shared_ptr<Inter_LayerQL<double>> inLayer_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);

		for (int i = 0; i < 1; i++)
		{
			for (int j = 999; j < 1000; j++)
			{
				inLayer_01->forward_Matrix = LoadCSV::conv_Input_Vector[j];

				std::cout << (inLayer_01->forward_Matrix->getMatrixQL()*9).cast<int>() << std::endl;
			}
		}

		std::shared_ptr<LayerQL<double>> poolLayer_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer,14,14);
		//������Գ������ظ�ֵ�����
		std::shared_ptr<Inter_LayerQL<double>> out_01 = inLayer_01 + poolLayer_01;
		poolLayer_01->right_Layer->forward_Matrix->setMatrixQL().resize(14, 14);

		poolLayer_01->calForward();

		std::cout << (out_01->forward_Matrix->getMatrixQL() * 9).cast<int>() << std::endl;

		//============================================================================================================

		poolLayer_01->left_Layer->backward_Matrix->setMatrixQL().resize(28, 28);

		poolLayer_01->right_Layer->backward_Matrix = poolLayer_01->right_Layer->forward_Matrix;

		poolLayer_01->calBackward();

		std::cout << (inLayer_01->backward_Matrix->getMatrixQL() * 9).cast<int>() << std::endl;

		//============================================================================================================

		std::cout << "=======================================================================================" << std::endl;
		//���Լ��ؾ����άͼ��,ѵ����
		LoadCSV::loadCSVTest();
		LoadCSV::loadCSV_Test_Vector();

		//��������㣬1��784��
		std::shared_ptr<Inter_LayerQL<double>> inLayer_01_T = std::make_shared<Inter_LayerQL<double>>(28, 28);

		for (int i = 0; i < 1; i++)
		{
			for (int j = 999; j < 1000; j++)
			{
				inLayer_01_T->forward_Matrix = LoadCSV::conv_Input_Vector_T[j];

				std::cout << (inLayer_01_T->forward_Matrix->getMatrixQL() * 9).cast<int>() << std::endl;
			}
		}
		//===========================================================================================================
	}
}