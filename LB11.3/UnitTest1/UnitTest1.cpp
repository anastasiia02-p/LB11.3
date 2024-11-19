#include "pch.h"
#include "CppUnitTest.h"
#include "../LB11.3/main.cpp"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			bool result = IsValidDate(29, 2, 2024); // Високосний рік
			Assert::IsTrue(result, L"29 лютого 2024 має бути валідною датою.");
		}
	};
}
