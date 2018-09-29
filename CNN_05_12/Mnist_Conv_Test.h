#pragma once
#include "omp.h"
#include "LoadCSV.h"
#include "LayerQL.h"
#include "PooLayerQL.h"
#include "Conv_LayerQL.h"
#include "Sigmoid_LayerQL.h"
#include "Dim_ReduceQL.h"
#include "Fullconnect_LayerQL.h"
#include "Inter_LayerQL.h"
#include <math.h>
#include "Relu_LayerQL.h"
#include "SoftMax_LayerQL.h"
#include "Data_AugmentationQL.h"

namespace tinyDNN
{
	class Mnist_Conv_Test
	{
	public:
		Mnist_Conv_Test()
		{
			//this->mnist_conv_01();
			//this->mnist_conv_02();
			//this->mnist_conv_03();
			//this->mnist_conv_04();
			//this->cifar_10_conv_01();
			this->cifar_10_conv_01_01();
			//this->cifar_10_conv_02();

			//this->mnist_conv_05();

			//this->accu = 0.0;
			//this->cifar_10_conv_03();
		}
		~Mnist_Conv_Test(){}

		double accu;

		//��ʼ���ظ�����֤�Ƿ���ȷ
		void mnist_conv_01()
		{
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28,28);
			in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[4]);

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer,14,14);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 14, 14, 5, 1, 2 );	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			//**********************************************************************Sigmoid��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 7, 7);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 392, 10 );//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();


			o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(4);


			for (int i = 0; i < 100; i++)
			{
				//1
				pool_01->calForward();
				//2
				conv_01->calForward();
				//3
				sigmoid_01->calForward(1);
				//4
				pool_02->calForward();
				//5
				dim_reduce_01->calForward();
				//6
				fullconnect_01->calForward();
				//7
				sigmoid_02->calForward();
				//8
				lossLayer_01->calForward();

				//8
				lossLayer_01->calBackward();
				//7
				sigmoid_02->calBackward();
				//6
				fullconnect_01->calBackward();
				//5
				dim_reduce_01->calBackward();
				//4
				pool_02->calBackward();
				//3
				sigmoid_01->calBackward(1);
				//2
				conv_01->calBackward();
				//1
				pool_01->calBackward();

				//6
				fullconnect_01->upMatrix();
				//2
				conv_01->upMatrix();
			}

			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;

		}
		//ѵ������ MNIST TRAIN �� �� MNIST TRAIN ������֤
		void mnist_conv_02()
		{
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);
			in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[4]);

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 14, 14, 5, 1, 2);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			//**********************************************************************Sigmoid��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 7, 7);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 392, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();

			o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(4);

			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 55000; j++)
				{
					//���
					in_01->forward_Matrix_Vector.clear();
					in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);

					o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

					//1
					pool_01->calForward();
					//2
					conv_01->calForward();
					//3
					sigmoid_01->calForward(1);
					//4
					pool_02->calForward();
					//5
					dim_reduce_01->calForward();
					//6
					fullconnect_01->calForward();
					//7
					sigmoid_02->calForward();
					//8
					lossLayer_01->calForward();

					//8
					lossLayer_01->calBackward();
					//7
					sigmoid_02->calBackward();
					//6
					fullconnect_01->calBackward();
					//5
					dim_reduce_01->calBackward();
					//4
					pool_02->calBackward();
					//3
					sigmoid_01->calBackward(1);
					//2
					conv_01->calBackward();
					//1
					pool_01->calBackward();

					//6
					fullconnect_01->upMatrix();
					//2
					conv_01->upMatrix();
				}
			}

			for (int k = 1000; k < 1100; k++)
			{
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[k]);

				o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(k);

				//1
				pool_01->calForward();
				//2
				conv_01->calForward();
				//3
				sigmoid_01->calForward(1);
				//4
				pool_02->calForward();
				//5
				dim_reduce_01->calForward();
				//6
				fullconnect_01->calForward();
				//7
				sigmoid_02->calForward();
				//8
				lossLayer_01->calForward();

				//8
				lossLayer_01->calBackward();
				//7
				sigmoid_02->calBackward();
				//6
				fullconnect_01->calBackward();
				//5
				dim_reduce_01->calBackward();
				//4
				pool_02->calBackward();
				//3
				sigmoid_01->calBackward(1);
				//2
				conv_01->calBackward();
				//1
				pool_01->calBackward();

				//6
				fullconnect_01->upMatrix();
				//2
				conv_01->upMatrix();

				std::cout << k + 1 << " : *****************************************" << std::endl;
				std::cout << ( o_07->forward_Matrix->getMatrixQL() * 9 ).cast<int>() << std::endl;
			}
		}
		//ѵ������ MNIST TRAIN �� �� MNIST TRAIN ������֤
		void mnist_conv_03()
		{
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);
			in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[4]);

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 14, 14, 5, 1, 2);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			//**********************************************************************Sigmoid��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 7, 7);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 392, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();

			o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(4);


			//	 ������س�ʼʱ��
			DWORD load_time = GetTickCount();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 55000; j++)
				{
					//���
					in_01->forward_Matrix_Vector.clear();
					in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);

					o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

					//1
					pool_01->calForward();
					//2
					conv_01->calForward();
					//3
					sigmoid_01->calForward(1);
					//4
					pool_02->calForward();
					//5
					dim_reduce_01->calForward();
					//6
					fullconnect_01->calForward();
					//7
					sigmoid_02->calForward();
					//8
					lossLayer_01->calForward();

					//8
					lossLayer_01->calBackward();
					//7
					sigmoid_02->calBackward();
					//6
					fullconnect_01->calBackward();
					//5
					dim_reduce_01->calBackward();
					//4
					pool_02->calBackward();
					//3
					sigmoid_01->calBackward(1);
					//2
					conv_01->calBackward();
					//1
					pool_01->calBackward();

					//6
					fullconnect_01->upMatrix();
					//2
					conv_01->upMatrix();
				}
			}

			//*******************************************����
			LoadCSV::loadCSVTest();
			LoadCSV::loadCSV_Test_Vector();

			double numTotal = 0;
			for (int k = 0; k < 10000; k++)
			{
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector_T[k]);

				o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(k);

				//1
				pool_01->calForward();		//forward
				//2
				conv_01->calForward();
				//3
				sigmoid_01->calForward(1);
				//4
				pool_02->calForward();
				//5
				dim_reduce_01->calForward();
				//6
				fullconnect_01->calForward();
				//7
				sigmoid_02->calForward();
				//8
				lossLayer_01->calForward();

				////8
				//lossLayer_01->calBackward();	//back
				////7
				//sigmoid_02->calBackward();
				////6
				//fullconnect_01->calBackward();
				////5
				//dim_reduce_01->calBackward();
				////4
				//pool_02->calBackward();
				////3
				//sigmoid_01->calBackward(1);
				////2
				//conv_01->calBackward();
				////1
				//pool_01->calBackward();

				////6
				//fullconnect_01->upMatrix();		//up
				////2
				//conv_01->upMatrix();

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
		//��˫�������м��㣬��֤˫����ķ��򴫲�����ȷ�ԣ��� MNIST TRAIN ������֤
		void mnist_conv_04()
		{
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);
			in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[4]);

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 14, 14, 5, 1, 2);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			//**********************************************************************Sigmoid��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 7, 7, 3, 8, 1);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_04_02 = o_04 + conv_02;
			conv_02->calForward();


			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 7, 7);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04_02 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 8*7*7, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();

			o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(4);

			conv_01->upConv = 0.5;
			conv_02->upConv = 0.5;
			fullconnect_01->upFull = 0.15;
			//	 ������س�ʼʱ��
			DWORD load_time = GetTickCount();

			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 55000; j++)
				{
					//���
					in_01->forward_Matrix_Vector.clear();
					in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);

					o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

					//1
					pool_01->calForward();
					//2
					conv_01->calForward();
					//3
					sigmoid_01->calForward(1);
					//4
					pool_02->calForward();
					//***********************************
					conv_02->calForward();
					//5
					dim_reduce_01->calForward();
					//6
					fullconnect_01->calForward();
					//7
					sigmoid_02->calForward();
					//8
					lossLayer_01->calForward();

					//8
					lossLayer_01->calBackward();
					//7
					sigmoid_02->calBackward();
					//6
					fullconnect_01->calBackward();
					//5
					dim_reduce_01->calBackward();
					//***********************************
					conv_02->calBackward();
					//4
					pool_02->calBackward();
					//3
					sigmoid_01->calBackward(1);
					//2
					conv_01->calBackward();
					//1
					pool_01->calBackward();

					//6
					fullconnect_01->upMatrix();
					//2
					conv_01->upMatrix();
				}
			}

			//*******************************************����
			LoadCSV::loadCSVTest();
			LoadCSV::loadCSV_Test_Vector();

			double numTotal = 0;
			for (int k = 0; k < 10000; k++)
			{
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector_T[k]);

				o_08->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(k);

				//1
				pool_01->calForward();		//forward
											//2
				conv_01->calForward();
				//3
				sigmoid_01->calForward(1);
				//4
				pool_02->calForward();
				//***********************************
				conv_02->calForward();
				//5
				dim_reduce_01->calForward();
				//6
				fullconnect_01->calForward();
				//7
				sigmoid_02->calForward();
				//8
				lossLayer_01->calForward();

				////8
				//lossLayer_01->calBackward();	//back
				////7
				//sigmoid_02->calBackward();
				////6
				//fullconnect_01->calBackward();
				////5
				//dim_reduce_01->calBackward();
				////4
				//pool_02->calBackward();
				////3
				//sigmoid_01->calBackward(1);
				////2
				//conv_01->calBackward();
				////1
				//pool_01->calBackward();

				////6
				//fullconnect_01->upMatrix();		//up
				////2
				//conv_01->upMatrix();

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
		//�������þ�̲�ͳػ����Sigmoid��ͽ�ά�㣬������ȫ���Ӳ㣬����֤�������ȷ��
		void mnist_conv_05()
		{
			LoadCSV::loadCSVTrain();
			LoadCSV::loadCSV_Train_Vector();
			LoadCSV::loadCSVTest();
			LoadCSV::loadCSV_Test_Vector();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 14, 14, 5, 1, 2);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 7, 7, 3, 8, 1);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + conv_02;

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + sigmoid_02;

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 7, 7);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + dim_reduce_01;

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 8*7*7, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + fullconnect_01;

			std::shared_ptr<LayerQL<double>> sigmoid_03 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_09 = o_08 + sigmoid_03;

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_10 = o_09 + lossLayer_01;

			//	 ������س�ʼʱ��
			DWORD load_time = GetTickCount();

			for (int i = 0; i < 1; i++)
			{
				//		/ pow(10, i / 5);
				conv_01->upConv = 0.5 / pow(10, i / 2);
				conv_02->upConv = 0.5 / pow(10, i / 2);
				fullconnect_01->upFull = 0.12 / pow(10, i / 2);

				for (int j = 0; j < 55000; j++)
				{
					//���
					in_01->forward_Matrix_Vector.clear();
					in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);
					o_10->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

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
			double numTotal = 0;
			for (int k = 0; k < 10000; k++)
			{
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector_T[k]);
				o_10->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer_T->backward_Matrix->getMatrixQL().row(k);

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


		//ѵ������ Cifar-10 
		void cifar_10_conv_01()
		{
			LoadCifar_10::loadCifar_10_Train();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(32, 32);
			in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[4];

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 16, 16);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 16, 16, 3, 3, 1);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			//**********************************************************************Sigmoid��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 8, 8);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 16, 8, 8);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 16*8*8, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();

			o_08->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(4);;

			//return;

			for (int i = 0; i < 8; i++)
			{
				//	 ������س�ʼʱ��
				DWORD load_time = GetTickCount();

				if ( i < 2 )
				{
					conv_01->upConv = 0.5;
					fullconnect_01->upFull = 0.1;
				}
				else if (i < 4)
				{
					conv_01->upConv = 0.05;
					fullconnect_01->upFull = 0.01;
				}
				else if ( i < 6 )
				{
					conv_01->upConv = 0.01;
					fullconnect_01->upFull = 0.002;
				}
				else if ( i < 8 )
				{
					conv_01->upConv = 0.002;
					fullconnect_01->upFull = 0.0004;
				}
				//conv_01->upConv = 0.5 / pow(10, i/4);
				//fullconnect_01->upFull = 0.15 / pow(10, i/4);

				for (int j = 0; j < 50000; j++)
				{
					std::cout << j << std::endl;
					in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[j];

					o_08->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(j);

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

				this->cifar_10_Test(in_01, o_08, lossLayer_01);

				//ѵ���Ͳ�������ʱ��
				DWORD star_time = GetTickCount();

				//��������ʱ��
				std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
			}
		}


		//ѵ������ Cifar-10 
		void cifar_10_conv_01_01()
		{
			LoadCifar_10::loadCifar_10_Train();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(32, 32);
			in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[4];


			//**********************************************************************������ǿ��
			//0000000000000000000000000000000000000000000000000000000000000000000000

			std::shared_ptr<LayerQL<double>> data_Aumentation_01 = std::make_shared<Data_AugmentationQL<double>>(Data_Augmentation_Layer,0,0);
			std::shared_ptr<Inter_LayerQL<double>> o_00 = in_01 + data_Aumentation_01;

			data_Aumentation_01->calForward();


			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 16, 16);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_01 = o_00 + pool_01;

			//**********************************************************************�ػ���
			//1111111111111111111111111111111111111111111111111111111111111111111111
			pool_01->calForward();
			std::cout << o_01->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << (o_01->forward_Matrix_Vector[0]->getMatrixQL() * 9).cast<int>() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 16, 16, 3, 3, 1);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_01->calForward();
			std::cout << o_02->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_02->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;
			sigmoid_01->pRelu_k = 0.1;
			//**********************************************************************Relu��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01->calForward(1);
			std::cout << o_03->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_03->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 8, 8);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;


			//**********************************************************************�ػ���
			//4444444444444444444444444444444444444444444444444444444444444444444444
			pool_02->calForward();
			std::cout << o_04->forward_Matrix_Vector[0]->getMatrixQL() << std::endl;
			std::cout << "*******" << std::endl;
			std::cout << o_04->forward_Matrix_Vector[7]->getMatrixQL() << std::endl;
			//**********************************************************************



			std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 8, 8, 3, 16, 1);	//�����
			std::shared_ptr<Inter_LayerQL<double>> o_04_02 = o_04 + conv_02;

			//**********************************************************************�����
			//2222222222222222222222222222222222222222222222222222222222222222222222
			conv_02->calForward();


			std::shared_ptr<LayerQL<double>> sigmoid_01_02 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
			std::shared_ptr<Inter_LayerQL<double>> o_04_03 = o_04_02 + sigmoid_01_02;
			sigmoid_01_02->pRelu_k = 0.1;
			//**********************************************************************Relu��
			//3333333333333333333333333333333333333333333333333333333333333333333333
			sigmoid_01_02->calForward(1);


			std::shared_ptr<LayerQL<double>> pool_02_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 4, 4);	//�ػ���
			std::shared_ptr<Inter_LayerQL<double>> o_04_04 = o_04_03 + pool_02_02;

			pool_02_02->calForward();

			//return;

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 16, 4, 4);	//��ά��
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04_04 + dim_reduce_01;

			//**********************************************************************��ά��
			//55555555555555555555555555555555555555555555555555555555555555555555555
			dim_reduce_01->calForward();
			std::cout << o_05->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 16 * 4 * 4, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			//**********************************************************************ȫ���Ӳ�
			//66666666666666666666666666666666666666666666666666666666666666666666666
			fullconnect_01->calForward();
			std::cout << o_06->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//return;

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Relu_LayerQL<double>>(Relu_Layer);	//Relu��
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;
			sigmoid_02->pRelu_k = 0.1;
			//**********************************************************************Sigmoid��
			//77777777777777777777777777777777777777777777777777777777777777777777777
			sigmoid_02->calForward();
			std::cout << o_07->forward_Matrix->getMatrixQL() << std::endl;
			//**********************************************************************

			//====================================================================================================================================================================

			//std::shared_ptr<LayerQL<double>> fullconnect_01_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 30, 10);//ȫ���Ӳ�2
			//std::shared_ptr<Inter_LayerQL<double>> o_07_02 = o_07 + fullconnect_01_02;

			////**********************************************************************ȫ���Ӳ�
			////7777777777777777777777777777777777777777111111111111111111111111111111
			//fullconnect_01_02->calForward();



			//std::shared_ptr<LayerQL<double>> sigmoid_02_02 = std::make_shared<Relu_LayerQL<double>>(Relu_Layer);	//Relu��
			//std::shared_ptr<Inter_LayerQL<double>> o_07_03 = o_07_02 + sigmoid_02_02;
			//sigmoid_02_02->pRelu_k = 0.1;

			//sigmoid_02_02->calForward();

			//=====================================================================================================================================================================



			//return;

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<SoftMax_LayerQL<double>>(SoftMax_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			//**********************************************************************Loss��
			//88888888888888888888888888888888888888888888888888888888888888888888888
			lossLayer_01->calForward();

			o_08->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(4);;

			//return;

			for (int i = 0; i < 14; i++)
			{
				//	 ������س�ʼʱ��
				DWORD load_time = GetTickCount();

				sigmoid_01->pRelu_k = 0.12;
				sigmoid_01_02->pRelu_k = 0.12;
				sigmoid_02->pRelu_k = 0.12;
				//sigmoid_02_02->pRelu_k = 0.12;
				if (i < 2)
				{
					conv_01->upConv = 0.02;
					conv_02->upConv = 0.02;
					fullconnect_01->upFull = 0.015;
					//fullconnect_01_02->upFull = 0.015;
				}
				if (i < 4)
				{
					conv_01->upConv = 0.015;
					conv_02->upConv = 0.015;
					fullconnect_01->upFull = 0.009;
					//fullconnect_01_02->upFull = 0.009;
				}
				else if (i < 6)
				{
					conv_01->upConv = 0.008;
					conv_02->upConv = 0.008;
					fullconnect_01->upFull = 0.006;
					//fullconnect_01_02->upFull = 0.006;
				}
				//������ͻ��,�ص��ע���ѧϰ��
				else if (i < 8)
				{
					conv_01->upConv = 0.004;
					conv_02->upConv = 0.004;
					fullconnect_01->upFull = 0.003;
					//fullconnect_01_02->upFull = 0.003;
				}
				else if (i < 10)
				{
					conv_01->upConv = 0.002;
					conv_02->upConv = 0.002;
					fullconnect_01->upFull = 0.001;
					//fullconnect_01_02->upFull = 0.001;
				}
				else if (i < 12)
				{
					conv_01->upConv = 0.001;
					conv_02->upConv = 0.001;
					fullconnect_01->upFull = 0.0005;
					//fullconnect_01_02->upFull = 0.0005;
				}
				else if (i < 14)
				{
					conv_01->upConv = 0.0005;
					conv_02->upConv = 0.0005;
					fullconnect_01->upFull = 0.0002;
					//fullconnect_01_02->upFull = 0.0002;
				}
				else if (i < 18)
				{
					conv_01->upConv = 0.00005;
					conv_02->upConv = 0.00005;
					fullconnect_01->upFull = 0.00005;
				}
				//conv_01->upConv = 0.5 / pow(10, i/4);
				//fullconnect_01->upFull = 0.15 / pow(10, i/4);

//#pragma omp parallel
				for (int j = 0; j < 50000; j++)
				{
					//std::cout << j << std::endl;
					if (j % 10000 == 0) std::cout << i << "::" << j << std::endl;

					in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[j];

					o_08->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(j);

					//��ͷ��ʼ����ǰ�򴫲�
//#pragma omp parallel
					for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
					{
						(*k)->calForward();
					}
					//��ͷ��ʼ���򴫲� + Ȩ�ظ���
//#pragma omp parallel
					for (auto k = NetQL<double>::layerQLVector.rbegin(); k != NetQL<double>::layerQLVector.rend(); k++)
					{
						(*k)->calBackward();
						(*k)->upMatrix();
					}
				}

				this->cifar_10_Test(in_01, o_08, lossLayer_01);

				//ѵ���Ͳ�������ʱ��
				DWORD star_time = GetTickCount();

				//��������ʱ��
				std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
			}
		}


		void cifar_10_Test(std::shared_ptr<Inter_LayerQL<double>> inLayer, std::shared_ptr<Inter_LayerQL<double>> endLayer, std::shared_ptr<LayerQL<double>> lossLayer)
		{
			double numTotal = 0;
			for (int k = 0; k < 10000; k++)
			{
				inLayer->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector_T[k];
				endLayer->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable_T->getMatrixQL().row(k);

				//ǰ�򴫲���������

				for (auto k = NetQL<double>::layerQLVector.begin(); k != NetQL<double>::layerQLVector.end(); k++)
				{
					(*k)->calForward();
				}

				//����õ������ֵλ��
				int maxRow, maxColumn;
				lossLayer->left_Layer->forward_Matrix->getMatrixQL().maxCoeff(&maxRow, &maxColumn);
				//Lable�����ֵλ��
				int maxRow_T, maxColumn_T;
				lossLayer->right_Layer->backward_Matrix->getMatrixQL().maxCoeff(&maxRow_T, &maxColumn_T);
				//�ж��Ƿ���ȣ�����ȣ���+1
				if (maxColumn == maxColumn_T)
				{
					numTotal++;
				}
			}
			//��ȷ��
			this->accu = numTotal / 10000.00;
			std::cout << this->accu << std::endl;

		}
		//�����ֱ������ ��������һ��ȫ���� ����Ч������
		void cifar_10_conv_02()
		{
			LoadCifar_10::loadCifar_10_Train();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(32, 32);

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 32, 32, 5, 3, 2);	//�����1
			std::shared_ptr<Inter_LayerQL<double>> o_02 = in_01 + conv_01;

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 16, 16);	//�ػ���1
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_01;

			std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 16, 16, 3, 16, 1);	//�����2
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + conv_02;

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��2
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + sigmoid_02;

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 8, 8);	//�ػ���2
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + pool_02;

			std::shared_ptr<LayerQL<double>> conv_03 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 8, 8, 3, 16, 1);	//�����3
			std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + conv_03;

			std::shared_ptr<LayerQL<double>> sigmoid_03 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��3
			std::shared_ptr<Inter_LayerQL<double>> o_09 = o_08 + sigmoid_03;

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 8, 8, 8);	//��ά��1
			std::shared_ptr<Inter_LayerQL<double>> o_010 = o_09 + dim_reduce_01;

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 8 * 8 * 8, 10);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_011 = o_010 + fullconnect_01;

			std::shared_ptr<LayerQL<double>> sigmoid_04 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��4
			std::shared_ptr<Inter_LayerQL<double>> o_012 = o_011 + sigmoid_04;

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_013 = o_012 + lossLayer_01;


			////**********************************************************************�ػ���
			////1111111111111111111111111111111111111111111111111111111111111111111111

			//std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 16, 16, 3, 3, 1);	//�����
			//std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + conv_01;

			////**********************************************************************�����
			////2222222222222222222222222222222222222222222222222222222222222222222222

			//std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			//std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			////**********************************************************************Sigmoid��
			////3333333333333333333333333333333333333333333333333333333333333333333333

			//std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 8, 8);	//�ػ���
			//std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_02;

			////**********************************************************************�ػ���
			////4444444444444444444444444444444444444444444444444444444444444444444444

			//std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 16, 8, 8);	//��ά��
			//std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + dim_reduce_01;

			////**********************************************************************��ά��
			////55555555555555555555555555555555555555555555555555555555555555555555555

			//std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 16 * 8 * 8, 10);//ȫ���Ӳ�
			//std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + fullconnect_01;

			////**********************************************************************ȫ���Ӳ�
			////66666666666666666666666666666666666666666666666666666666666666666666666

			//std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��
			//std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + sigmoid_02;

			////**********************************************************************Sigmoid��
			////77777777777777777777777777777777777777777777777777777777777777777777777

			//std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			//std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + lossLayer_01;

			////**********************************************************************Loss��
			////88888888888888888888888888888888888888888888888888888888888888888888888

			for (int i = 0; i < 20; i++)
			{
				//	 ������س�ʼʱ��
				DWORD load_time = GetTickCount();

				//if (i < 10)
				//{
				//	conv_01->upConv = 0.5;
				//	conv_02->upConv = 0.5;
				//	conv_03->upConv = 0.5;
				//	fullconnect_01->upFull = 0.1;
				//}
				//else if (i < 4)
				//{
				//	conv_01->upConv = 0.05;
				//	conv_02->upConv = 0.05;
				//	conv_03->upConv = 0.05;
				//	fullconnect_01->upFull = 0.01;
				//}
				//else if (i < 6)
				//{
				//	conv_01->upConv = 0.01;
				//	conv_02->upConv = 0.01;
				//	conv_03->upConv = 0.01;
				//	fullconnect_01->upFull = 0.002;
				//}
				//else if (i < 8)
				//{
				//	conv_01->upConv = 0.002;
				//	conv_02->upConv = 0.002;
				//	conv_03->upConv = 0.002;
				//	fullconnect_01->upFull = 0.0004;
				//}

				conv_01->upConv = 0.5 / pow(10, i / 5);
				conv_02->upConv = 0.5 / pow(10, i / 5);
				conv_03->upConv = 0.5 / pow(10, i / 5);
				fullconnect_01->upFull = 0.1 / pow(10, i / 5);

				for (int j = 0; j < 50000; j++)
				{
					in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[j];

					o_013->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(j);

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

				this->cifar_10_Test(in_01, o_013, lossLayer_01);

				//ѵ���Ͳ�������ʱ��
				DWORD star_time = GetTickCount();

				//��������ʱ��
				std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
			}
		}

		//������ + ����ȫ���ӣ��μ�Tensorflowʵս88ҳ
		void cifar_10_conv_03()
		{
			LoadCifar_10::loadCifar_10_Train();

			std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(32, 32);

			std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 64, 32, 32, 5, 3, 2);	//�����1
			std::shared_ptr<Inter_LayerQL<double>> o_02 = in_01 + conv_01;

			std::shared_ptr<LayerQL<double>> sigmoid_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��
			std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + sigmoid_01;

			std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 16, 16);	//�ػ���1
			std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + pool_01;

			std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 64, 16, 16, 5, 64, 2);	//�����2
			std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + conv_02;

			std::shared_ptr<LayerQL<double>> sigmoid_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��2
			std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + sigmoid_02;

			std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 8, 8);	//�ػ���2
			std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + pool_02;

			//std::shared_ptr<LayerQL<double>> conv_03 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 8, 8, 8, 3, 16, 1);	//�����3
			//std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + conv_03;

			//std::shared_ptr<LayerQL<double>> sigmoid_03 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Conv_Layer);	//Sigmoid��3
			//std::shared_ptr<Inter_LayerQL<double>> o_09 = o_08 + sigmoid_03;

			std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 64, 8, 8);	//��ά��1
			std::shared_ptr<Inter_LayerQL<double>> o_010 = o_07 + dim_reduce_01;

			std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 64 * 8 * 8, 384);//ȫ���Ӳ�
			std::shared_ptr<Inter_LayerQL<double>> o_011 = o_010 + fullconnect_01;

			std::shared_ptr<LayerQL<double>> sigmoid_03_01 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��--
			std::shared_ptr<Inter_LayerQL<double>> o_011_01 = o_011 + sigmoid_03_01;

			std::shared_ptr<LayerQL<double>> fullconnect_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 384, 192);//ȫ���Ӳ�2
			std::shared_ptr<Inter_LayerQL<double>> o_011_02 = o_011_01 + fullconnect_02;

			std::shared_ptr<LayerQL<double>> sigmoid_03_02 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��4
			std::shared_ptr<Inter_LayerQL<double>> o_012_01 = o_011_02 + sigmoid_03_02;

			std::shared_ptr<LayerQL<double>> fullconnect_03 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 192, 10);//ȫ���Ӳ�2
			std::shared_ptr<Inter_LayerQL<double>> o_011_03 = o_012_01 + fullconnect_03;

			std::shared_ptr<LayerQL<double>> sigmoid_04 = std::make_shared<Sigmoid_LayerQL<double>>(Sigmoid_Layer);	//Sigmoid��4
			std::shared_ptr<Inter_LayerQL<double>> o_012 = o_011_03 + sigmoid_04;

			std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<MSE_Loss_LayerQL<double>>(MSE_Loss_Layer);//Loss��
			std::shared_ptr<Inter_LayerQL<double>> o_013 = o_012 + lossLayer_01;

			for (int i = 0; i < 20; i++)
			{
				//	 ������س�ʼʱ��
				DWORD load_time = GetTickCount();

				//if (i < 10)
				//{
				//	conv_01->upConv = 0.5;
				//	conv_02->upConv = 0.5;
				//	conv_03->upConv = 0.5;
				//	fullconnect_01->upFull = 0.1;
				//}
				//else if (i < 4)
				//{
				//	conv_01->upConv = 0.05;
				//	conv_02->upConv = 0.05;
				//	conv_03->upConv = 0.05;
				//	fullconnect_01->upFull = 0.01;
				//}
				//else if (i < 6)
				//{
				//	conv_01->upConv = 0.01;
				//	conv_02->upConv = 0.01;
				//	conv_03->upConv = 0.01;
				//	fullconnect_01->upFull = 0.002;
				//}
				//else if (i < 8)
				//{
				//	conv_01->upConv = 0.002;
				//	conv_02->upConv = 0.002;
				//	conv_03->upConv = 0.002;
				//	fullconnect_01->upFull = 0.0004;
				//}

				conv_01->upConv = 0.5 / pow(10, i / 5);
				conv_02->upConv = 0.5 / pow(10, i / 5);
				//conv_03->upConv = 0.5 / pow(10, i / 5);
				fullconnect_01->upFull = 0.1 / pow(10, i / 5);
				fullconnect_02->upFull = 0.1 / pow(10, i / 5);
				fullconnect_03->upFull = 0.1 / pow(10, i / 5);

				for (int j = 0; j < 50000; j++)
				{
					std::cout << i << "::" << j << "::" << this->accu << std::endl;

					in_01->forward_Matrix_Vector = LoadCifar_10::cifar_Input_Vector[j];

					o_013->backward_Matrix->setMatrixQL() = LoadCifar_10::cifar_Out_Lable->getMatrixQL().row(j);

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

				this->cifar_10_Test(in_01, o_013, lossLayer_01);

				//ѵ���Ͳ�������ʱ��
				DWORD star_time = GetTickCount();

				//��������ʱ��
				std::cout << "����������ʱ��Ϊ��" << (star_time - load_time) << "ms." << std::endl;
			}
		}
	};
}