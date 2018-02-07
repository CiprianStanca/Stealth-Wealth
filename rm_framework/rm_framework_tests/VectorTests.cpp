#include "stdafx.h"
#include "CppUnitTest.h"

#include "rm_framework.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace rm_framework_tests
{		
	TEST_CLASS(VectorClassUnitTests)
	{
	public:
		

		TEST_METHOD(VectorInitialisesProperly)
		{
			// TODO: Your test code here
			CVector3 vec1(1,2,3);
			Assert::AreEqual (1.0f,vec1.m_fX);
		}

		TEST_METHOD(Vector3TimesEqualOperatorCheckX)
		{
			// TODO: Your test code here
			CVector3 vec1(1,2,3);
			vec1*=5;
			Assert::AreEqual (5.0f,vec1.m_fX);
		}

		TEST_METHOD(Vector3TimesEqualOperatorCheckY)
		{
			// TODO: Your test code here
			CVector3 vec1(1,2,3);
			vec1*=5;
			Assert::AreEqual (10.0f,vec1.m_fY);
		}

		TEST_METHOD(TransformInitializes)
		{
			CTransform t;
			Assert::AreEqual (0.0f,t.GetPosition().m_fX);
		}

		TEST_METHOD(TransformGetForwardZ)
		{
			CTransform t;
			CVector3 vec;
			t.GetForwardDirection(&vec);

			Assert::AreEqual (-1.0f,vec.m_fZ);
		}

		TEST_METHOD(TransformGetrightX)
		{
			CTransform t;
			CVector3 vec;
			t.GetRightDirection(&vec);

			Assert::AreEqual (1.0f,vec.m_fX);
		}

		TEST_METHOD(Transform90GetrightZ)
		{
			CTransform t;
			t.SetYaw(90);
			CVector3 vec;
			t.GetRightDirection(&vec);

			Assert::AreEqual (1.0f,vec.m_fZ,0.001f);
		}

		TEST_METHOD(Transform30GetrightZ)
		{
			CTransform t;
			t.SetYaw(30);
			CVector3 vec;
			t.GetRightDirection(&vec);

			Assert::AreEqual (-0.5f,vec.m_fZ);
		}

		TEST_METHOD(Transform30GetrightX)
		{
			CTransform t;
			t.SetYaw(30);
			CVector3 vec;
			t.GetRightDirection(&vec);

			Assert::AreEqual (0.866f,vec.m_fX,0.001f);
		}
	};
}