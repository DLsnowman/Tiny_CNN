#pragma once

#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
#include "Test.h"

namespace tinyDNN
{
	class LoadCSV
	{
	public:
		LoadCSV();
		~LoadCSV();
		//װ��ѵ����
		static void loadCSVTrain();
		//װ�ز��Լ�
		static void loadCSVTest();
	};
}
