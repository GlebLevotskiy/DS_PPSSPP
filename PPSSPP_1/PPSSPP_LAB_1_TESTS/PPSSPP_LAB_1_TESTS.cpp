#include "pch.h"
#include "CppUnitTest.h"
#include <PPSSPP_LAB_1.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PPSSPPLAB1TESTS
{
	TEST_CLASS(PPSSPPLAB1TESTS)
	{
	public:
		
		TEST_METHOD(ShouldCountUniqueWordsOfTheString)
		{
			// Arrange
			string source = "asd aer asfg qe";
		
			// Act
			int result = getStringUniqueWordsCount(source);

			// Assert
			Assert::AreEqual(4, result);
		}

		TEST_METHOD(ShouldCountUniqueWordsOfTheInputFile)
		{
			// Arrange
			string source = "C:\\Users\\Gleb\\source\\repos\\PPSSPP_LAB_1\\PPSSPP_LAB_1_TESTS\\TextForTHeGetFileUniqueWordsCountFunctionTest.txt";

			// Act
			int result = getFileUniqueWordsCount(source);

			// Assert
			Assert::AreEqual(11, result);
		}
	};
}
