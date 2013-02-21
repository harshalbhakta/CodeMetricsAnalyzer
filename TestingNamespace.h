////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TestingNamespace.h (ver 1.0)  -  TEst file to test is namespace detection works.							  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace OuterNameSpace
{

	namespace InnerNameSpace
	{
	
		class TestingClass {

			void function();

			void function_cpp();

			void fucntion_cpp_2();

		private :

			int member_data; // Line 28


		};

		void TestingClass::function()
		{
		
			member_data = 10; // Line 36

		}

	}


}