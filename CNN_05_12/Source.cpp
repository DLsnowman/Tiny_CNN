#pragma once
#include "MatrixQL.h"
#include "iostream"
#include "memory"
#include "Fullconnect_LayerQL.h"
#include "Bias_LayerQL.h"
#include "Test.h"
#include "Conv_Test.h"
#include "Pool_Test.h"
#include "Sigmoid_Test.h"
#include "Dim_Reduce_Test.h"
#include "LoadCSV_Test.h"
#include "Mnist_Conv_Test.h"
#include "Relu_LayerQL_Test.h"
#include "SoftMax_Layer_Test.h"
#include "Data_Augmentation_Test.h"
#include "Mnist_Conv_T2.h"
using namespace tinyDNN;
int main()
{
	//Test test;
	//�����
	//Conv_Test test;
	//Pool_Test pool_Test;
	
	//Sigmoid��
	//Sigmoid_Test test;
	
	//��ά��
	//Dim_Reduce_Test test;

	//�������ݲ�
	//LoadCSV_Test test;

	//����������ǿ��
	//Data_Augmentation_Test test;

	////���Ծ�������=======================================================================================
	//Mnist_Conv_Test test;

	//����Relu��
	//Relu_LayerQL_Test test;

	//����Softmax��
	//SoftMax_Layer_Test test;

	mnist_Conv_T_1();

	return 0;
}