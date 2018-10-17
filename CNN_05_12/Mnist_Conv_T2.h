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
	//	99.03%
	void mnist_Conv_T_1()
	{
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSV_Train_Vector();
		LoadCSV::loadCSVTest();
		LoadCSV::loadCSV_Test_Vector();

		std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);
		//						����			�������			����			����				����˿��		����˼�Ƭ		������	
		std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 28, 28, 5, 1, 2);	//�����
		std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + conv_01;


		std::shared_ptr<LayerQL<double>> rule_01 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + rule_01;
		//rule_01->pRelu_k = 0.1;


		std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
		std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + pool_01;


		//						����			�������			����			����				����˿��		����˼�Ƭ		������	
		std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 14, 14, 3, 16, 1);	//�����
		std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + conv_02;


		std::shared_ptr<LayerQL<double>> rule_02 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + rule_02;
		//rule_02->pRelu_k = 0.1;


		std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
		std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + pool_02;


		std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 16, 7, 7);	//��ά��
		std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + dim_reduce_01;


		std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 16 * 7 * 7, 10);//ȫ���Ӳ�
		std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + fullconnect_01;


		std::shared_ptr<LayerQL<double>> rule_03 = std::make_shared<Relu_LayerQL<double>>(Relu_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_09 = o_08 + rule_03;
		//rule_03->pRelu_k = 0.1;

		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<SoftMax_LayerQL<double>>(SoftMax_Layer);//Loss��
		std::shared_ptr<Inter_LayerQL<double>> o_10 = o_09 + lossLayer_01;

		for (int i = 0; i < 14; i++)
		{
			//	 ������س�ʼʱ��
			DWORD load_time = GetTickCount();

			rule_01->pRelu_k = 0.12;
			rule_02->pRelu_k = 0.12;
			rule_03->pRelu_k = 0.12;

			if (i < 2)
			{
				conv_01->upConv = 0.02;
				conv_02->upConv = 0.02;
				fullconnect_01->upFull = 0.015;
			}
			if (i < 4)
			{
				conv_01->upConv = 0.015;
				conv_02->upConv = 0.015;
				fullconnect_01->upFull = 0.009;
			}
			else if (i < 6)
			{
				conv_01->upConv = 0.008;
				conv_02->upConv = 0.008;
				fullconnect_01->upFull = 0.006;
			}
			//������ͻ��,�ص��ע���ѧϰ��
			else if (i < 8)
			{
				conv_01->upConv = 0.004;
				conv_02->upConv = 0.004;
				fullconnect_01->upFull = 0.003;
			}
			else if (i < 10)
			{
				conv_01->upConv = 0.002;
				conv_02->upConv = 0.002;
				fullconnect_01->upFull = 0.001;
			}
			else if (i < 12)
			{
				conv_01->upConv = 0.001;
				conv_02->upConv = 0.001;
				fullconnect_01->upFull = 0.0005;
			}
			else if (i < 14)
			{
				conv_01->upConv = 0.0005;
				conv_02->upConv = 0.0005;
				fullconnect_01->upFull = 0.0002;
			}
			else if (i < 18)
			{
				conv_01->upConv = 0.00005;
				conv_02->upConv = 0.00005;
				fullconnect_01->upFull = 0.00005;
			}

			//#pragma omp parallel
			for (int j = 0; j < 55000; j++)
			{
				if (j % 10000 == 0) std::cout << i << "::" << j << std::endl;
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);
				o_10->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

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
	}

	//	99.03%
	void mnist_Conv_T_2()
	{
		LoadCSV::loadCSVTrain();
		LoadCSV::loadCSV_Train_Vector();
		LoadCSV::loadCSVTest();
		LoadCSV::loadCSV_Test_Vector();

		std::shared_ptr<Inter_LayerQL<double>> in_01 = std::make_shared<Inter_LayerQL<double>>(28, 28);
		//						����			�������			����			����				����˿��		����˼�Ƭ		������	
		std::shared_ptr<LayerQL<double>> conv_01 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 28, 28, 5, 1, 2);	//�����
		std::shared_ptr<Inter_LayerQL<double>> o_01 = in_01 + conv_01;


		std::shared_ptr<LayerQL<double>> rule_01 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_02 = o_01 + rule_01;
		//rule_01->pRelu_k = 0.1;


		std::shared_ptr<LayerQL<double>> pool_01 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 14, 14);	//�ػ���
		std::shared_ptr<Inter_LayerQL<double>> o_03 = o_02 + pool_01;


		//						����			�������			����			����				����˿��		����˼�Ƭ		������	
		std::shared_ptr<LayerQL<double>> conv_02 = std::make_shared<Conv_LayerQL<double>>(Conv_Layer, 16, 14, 14, 3, 16, 1);	//�����
		std::shared_ptr<Inter_LayerQL<double>> o_04 = o_03 + conv_02;


		std::shared_ptr<LayerQL<double>> rule_02 = std::make_shared<Relu_LayerQL<double>>(Relu_Conv_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_05 = o_04 + rule_02;
		//rule_02->pRelu_k = 0.1;


		std::shared_ptr<LayerQL<double>> pool_02 = std::make_shared<PooLayerQL<double>>(Pool_Layer, 7, 7);	//�ػ���
		std::shared_ptr<Inter_LayerQL<double>> o_06 = o_05 + pool_02;


		std::shared_ptr<LayerQL<double>> dim_reduce_01 = std::make_shared<Dim_ReduceQL<double>>(Dim_Reduce_Layer, 16, 7, 7);	//��ά��
		std::shared_ptr<Inter_LayerQL<double>> o_07 = o_06 + dim_reduce_01;


		std::shared_ptr<LayerQL<double>> fullconnect_01 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 16 * 7 * 7, 30);//ȫ���Ӳ�
		std::shared_ptr<Inter_LayerQL<double>> o_08 = o_07 + fullconnect_01;


		std::shared_ptr<LayerQL<double>> rule_03 = std::make_shared<Relu_LayerQL<double>>(Relu_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_09 = o_08 + rule_03;
		//rule_03->pRelu_k = 0.1;



		std::shared_ptr<LayerQL<double>> fullconnect_02 = std::make_shared<Fullconnect_LayerQL<double>>(Fullconnect_Layer, 30, 10);//ȫ���Ӳ�
		std::shared_ptr<Inter_LayerQL<double>> o_09_02 = o_09 + fullconnect_02;


		std::shared_ptr<LayerQL<double>> rule_04 = std::make_shared<Relu_LayerQL<double>>(Relu_Layer);	//Relu��
		std::shared_ptr<Inter_LayerQL<double>> o_09_03 = o_09_02 + rule_04;
		//rule_03->pRelu_k = 0.1;



		std::shared_ptr<LayerQL<double>> lossLayer_01 = std::make_shared<SoftMax_LayerQL<double>>(SoftMax_Layer);//Loss��
		std::shared_ptr<Inter_LayerQL<double>> o_10 = o_09_03 + lossLayer_01;

		for (int i = 0; i < 18; i++)
		{
			//	 ������س�ʼʱ��
			DWORD load_time = GetTickCount();

			rule_01->pRelu_k = 0.12;
			rule_02->pRelu_k = 0.12;
			rule_03->pRelu_k = 0.12;
			rule_04->pRelu_k = 0.12;

			if (i < 2)
			{
				conv_01->upConv = 0.02;
				conv_02->upConv = 0.02;
				fullconnect_01->upFull = 0.015;
				fullconnect_02->upFull = 0.015;
			}
			if (i < 4)
			{
				conv_01->upConv = 0.015;
				conv_02->upConv = 0.015;
				fullconnect_01->upFull = 0.009;
				fullconnect_02->upFull = 0.009;
			}
			else if (i < 6)
			{
				conv_01->upConv = 0.008;
				conv_02->upConv = 0.008;
				fullconnect_01->upFull = 0.006;
				fullconnect_02->upFull = 0.006;
			}
			//������ͻ��,�ص��ע���ѧϰ��
			else if (i < 8)
			{
				conv_01->upConv = 0.004;
				conv_02->upConv = 0.004;
				fullconnect_01->upFull = 0.003;
				fullconnect_02->upFull = 0.003;
			}
			else if (i < 10)
			{
				conv_01->upConv = 0.002;
				conv_02->upConv = 0.002;
				fullconnect_01->upFull = 0.001;
				fullconnect_02->upFull = 0.001;
			}
			else if (i < 12)
			{
				conv_01->upConv = 0.001;
				conv_02->upConv = 0.001;
				fullconnect_01->upFull = 0.0005;
				fullconnect_02->upFull = 0.0005;
			}
			else if (i < 14)
			{
				conv_01->upConv = 0.0005;
				conv_02->upConv = 0.0005;
				fullconnect_01->upFull = 0.0002;
				fullconnect_02->upFull = 0.0002;
			}
			else if (i < 18)
			{
				conv_01->upConv = 0.00025;
				conv_02->upConv = 0.00025;
				fullconnect_01->upFull = 0.00015;
				fullconnect_02->upFull = 0.00015;
			}

			//#pragma omp parallel
			for (int j = 0; j < 55000; j++)
			{
				if (j % 10000 == 0) std::cout << i << "::" << j << std::endl;
				//���
				in_01->forward_Matrix_Vector.clear();
				in_01->forward_Matrix_Vector.push_back(LoadCSV::conv_Input_Vector[j]);
				o_10->backward_Matrix->setMatrixQL() = LoadCSV::output_Layer->backward_Matrix->getMatrixQL().row(j);

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
	}
}