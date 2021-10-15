#include <gtest/gtest.h>
#include <Refureku/Refureku.h>

//=========================================================
//============ Namespace::getNamespaceByName ==============
//=========================================================

TEST(Rfk_Namespace_getNamespaceByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getNamespaceByName, ExistantNamespaceName)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByName("nested_namespace"), nullptr);
}

TEST(Rfk_Namespace_getNamespaceByName, NonExistantNamespaceName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByName("inexistant_namespace"), nullptr);
}

//=========================================================
//========== Namespace::getNamespaceByPredicate ===========
//=========================================================

TEST(Rfk_Namespace_getNamespaceByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Namespace_getNamespaceByPredicate, FindingPredicate)
{
	char firstLetter = 'n';

	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByPredicate([](rfk::Namespace const& np, void* data)
			  {
				  return np.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getNamespaceByPredicate, NotFindingPredicate)
{
	char firstLetter = 'v';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByPredicate([](rfk::Namespace const& np, void* data)
			  {
				  return np.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getNamespaceByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespaceByPredicate([](rfk::Namespace const&, void*)
			  {
				  throw std::logic_error("Something wrong happened!");

				  return true;
			  }, nullptr), std::logic_error);
}

//=========================================================
//========== Namespace::getNamespacesByPredicate ==========
//=========================================================

TEST(Rfk_Namespace_getNamespacesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespacesByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Namespace_getNamespacesByPredicate, FindingPredicate)
{
	char firstLetter = 'n';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespacesByPredicate([](rfk::Namespace const& np, void* data)
			  {
				  return np.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 2u);
}

TEST(Rfk_Namespace_getNamespacesByPredicate, NotFindingPredicate)
{
	char firstLetter = 'v';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespacesByPredicate([](rfk::Namespace const& np, void* data)
			  {
				  return np.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 0u);
}

TEST(Rfk_Namespace_getNamespacesByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getNamespacesByPredicate([](rfk::Namespace const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============== Namespace::foreachNamespace ==============
//=========================================================

TEST(Rfk_Namespace_foreachNamespace, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachNamespace(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachNamespace, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachNamespace([](rfk::Namespace const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachNamespace, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachNamespace([](rfk::Namespace const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return true;
				 }, &counter));

	EXPECT_EQ(counter, np->getNamespacesCount());
}

TEST(Rfk_Namespace_foreachNamespace, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachNamespace([](rfk::Namespace const&, void*)
				{
					throw std::logic_error("Something wrong happened here!");

					return true;
				}, nullptr), std::logic_error);
}

//=========================================================
//=============== Namespace::getStructByName ==============
//=========================================================

TEST(Rfk_Namespace_getStructByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getStructByName, ExistingStruct)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("TestNamespaceNestedStruct"), nullptr);
}

TEST(Rfk_Namespace_getStructByName, NonExistingStruct)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByName("NonExistingStruct"), nullptr);
}

//=========================================================
//============ Namespace::getStructByPredicate ============
//=========================================================

TEST(Rfk_Namespace_getStructByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Namespace_getStructByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByPredicate([](rfk::Struct const& struct_, void* data)
			  {
				  return struct_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getStructByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByPredicate([](rfk::Struct const& struct_, void* data)
			  {
				  return struct_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getStructByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructByPredicate([](rfk::Struct const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============ Namespace::getStructsByPredicate ===========
//=========================================================

TEST(Rfk_Namespace_getStructsByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Namespace_getStructsByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructsByPredicate([](rfk::Struct const& struct_, void* data)
			  {
				  return struct_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 2u);
}

TEST(Rfk_Namespace_getStructsByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructsByPredicate([](rfk::Struct const& struct_, void* data)
			  {
				  return struct_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 0u);
}

TEST(Rfk_Namespace_getStructsByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getStructsByPredicate([](rfk::Struct const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//================ Namespace::foreachStruct ===============
//=========================================================

TEST(Rfk_Namespace_foreachStruct, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachStruct(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachStruct, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachStruct([](rfk::Struct const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachStruct, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachStruct([](rfk::Struct const&, void* data)
				{
					int& counter = *reinterpret_cast<int*>(data);
					counter++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, np->getStructsByPredicate([](rfk::Struct const&, void*) { return true; }, nullptr).size());
}

TEST(Rfk_Namespace_foreachStruct, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachStruct([](rfk::Struct const&, void*)
				 {
					 throw std::logic_error("Something wrong happened here!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//================ Namespace::getClassByName ==============
//=========================================================

TEST(Rfk_Namespace_getClassByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getClassByName, ExistingStruct)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByName("TestNamespaceNestedClass"), nullptr);
}

TEST(Rfk_Namespace_getClassByName, NonExistingStruct)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByName("NonExistingClass"), nullptr);
}

//=========================================================
//============= Namespace::getClassByPredicate ============
//=========================================================

TEST(Rfk_Namespace_getClassByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Namespace_getClassByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByPredicate([](rfk::Class const& class_, void* data)
			  {
				  return class_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getClassByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByPredicate([](rfk::Class const& class_, void* data)
			  {
				  return class_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getClassByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassByPredicate([](rfk::Class const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============ Namespace::getClassesByPredicate ===========
//=========================================================

TEST(Rfk_Namespace_getClassesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassesByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Namespace_getClassesByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassesByPredicate([](rfk::Class const& class_, void* data)
			  {
				  return class_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 3u);
}

TEST(Rfk_Namespace_getClassesByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassesByPredicate([](rfk::Class const& class_, void* data)
			  {
				  return class_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 0u);
}

TEST(Rfk_Namespace_getClassesByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getClassesByPredicate([](rfk::Class const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//================ Namespace::foreachClass ================
//=========================================================

TEST(Rfk_Namespace_foreachClass, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachClass(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachClass, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachClass([](rfk::Class const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachClass, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachClass([](rfk::Class const&, void* data)
				{
					int& counter = *reinterpret_cast<int*>(data);
					counter++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, np->getClassesByPredicate([](rfk::Struct const&, void*) { return true; }, nullptr).size());
}

TEST(Rfk_Namespace_foreachClass, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachClass([](rfk::Class const&, void*)
				 {
					 throw std::logic_error("Something wrong happened here!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//================ Namespace::getEnumByName ==============
//=========================================================

TEST(Rfk_Namespace_getEnumByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getEnumByName, ExistingStruct)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByName("TestNamespaceNestedEnum"), nullptr);
}

TEST(Rfk_Namespace_getEnumByName, NonExistingStruct)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByName("NonExistingEnum"), nullptr);
}

//=========================================================
//============= Namespace::getEnumByPredicate ============
//=========================================================

TEST(Rfk_Namespace_getEnumByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Namespace_getEnumByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByPredicate([](rfk::Enum const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getEnumByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByPredicate([](rfk::Enum const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getEnumByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumByPredicate([](rfk::Enum const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============= Namespace::getEnumsByPredicate ============
//=========================================================

TEST(Rfk_Namespace_getEnumesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumsByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Namespace_getEnumesByPredicate, FindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumsByPredicate([](rfk::Enum const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 1u);
}

TEST(Rfk_Namespace_getEnumesByPredicate, NotFindingPredicate)
{
	char firstLetter = 't';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumsByPredicate([](rfk::Enum const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 0u);
}

TEST(Rfk_Namespace_getEnumesByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getEnumsByPredicate([](rfk::Enum const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//================ Namespace::foreachEnum =================
//=========================================================

TEST(Rfk_Namespace_foreachEnum, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachEnum(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachEnum, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachEnum([](rfk::Enum const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachEnum, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachEnum([](rfk::Enum const&, void* data)
				{
					int& counter = *reinterpret_cast<int*>(data);
					counter++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, np->getEnumsByPredicate([](rfk::Enum const&, void*) { return true; }, nullptr).size());
}

TEST(Rfk_Namespace_foreachEnum, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachEnum([](rfk::Enum const&, void*)
				 {
					 throw std::logic_error("Something wrong happened here!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============== Namespace::foreachArchetype ==============
//=========================================================

TEST(Rfk_Namespace_foreachArchetype, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachArchetype(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachArchetype, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachArchetype([](rfk::Archetype const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachArchetype, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachArchetype([](rfk::Archetype const&, void* data)
				{
					int& counter = *reinterpret_cast<int*>(data);
					counter++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, np->getArchetypesCount());
}

TEST(Rfk_Namespace_foreachArchetype, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachArchetype([](rfk::Archetype const&, void*)
				 {
					 throw std::logic_error("Something wrong happened here!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============= Namespace::getVariableByName ==============
//=========================================================

TEST(Rfk_Namespace_getVariableByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getVariableByName, ValidNameDefaultFlags)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName("var_nested_extern"), nullptr);
}

TEST(Rfk_Namespace_getVariableByName, ValidNameNonValidFlags)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByName("var_nested_extern", rfk::EVarFlags::Static), nullptr);
}

//=========================================================
//=========== Namespace::getVariableByPredicate ===========
//=========================================================

TEST(Rfk_Namespace_getVariableByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByPredicate(nullptr, nullptr), nullptr);
}

TEST(Rfk_Namespace_getVariableByPredicate, FindingPredicate)
{
	char firstLetter = 'v';

	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByPredicate([](rfk::Variable const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getVariableByPredicate, NotFindingPredicate)
{
	char firstLetter = 'T';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByPredicate([](rfk::Variable const& enum_, void* data)
			  {
				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter), nullptr);
}

TEST(Rfk_Namespace_getVariableByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariableByPredicate([](rfk::Variable const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//=========== Namespace::getVariablesByPredicate ==========
//=========================================================

TEST(Rfk_Namespace_getVariablesByPredicate, NullptrPredicate)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariablesByPredicate(nullptr, nullptr).size(), 0u);
}

TEST(Rfk_Namespace_getVariablesByPredicate, FindingPredicate)
{
	char firstLetter = 'v';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariablesByPredicate([](rfk::Variable const& var, void* data)
			  {
				  return var.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 1u);
}

TEST(Rfk_Namespace_getVariablesByPredicate, NotFindingPredicate)
{
	char firstLetter = 'V';

	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariablesByPredicate([](rfk::Variable const& var, void* data)
			  {
				  return var.getName()[0] == *reinterpret_cast<char*>(data);
			  }, &firstLetter).size(), 0u);
}

TEST(Rfk_Namespace_getVariablesByPredicate, ThrowingPredicate)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getVariablesByPredicate([](rfk::Variable const&, void*)
				 {
					 throw std::logic_error("Something wrong happened!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============== Namespace::foreachVariable ===============
//=========================================================

TEST(Rfk_Namespace_foreachVariable, NullptrVisitor)
{
	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachVariable(nullptr, nullptr));
}

TEST(Rfk_Namespace_foreachVariable, BreakingVisitor)
{
	int counter = 0;

	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachVariable([](rfk::Variable const&, void* data)
				 {
					 int& counter = *reinterpret_cast<int*>(data);
					 counter++;

					 return false;
				 }, &counter));

	EXPECT_EQ(counter, 1);
}

TEST(Rfk_Namespace_foreachVariable, NonBreakingVisitor)
{
	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
	int counter = 0;


	EXPECT_TRUE(np->foreachVariable([](rfk::Variable const&, void* data)
				{
					int& counter = *reinterpret_cast<int*>(data);
					counter++;

					return true;
				}, &counter));

	EXPECT_EQ(counter, np->getVariablesCount());
}

TEST(Rfk_Namespace_foreachVariable, ThrowingVisitor)
{
	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachVariable([](rfk::Variable const&, void*)
				 {
					 throw std::logic_error("Something wrong happened here!");

					 return true;
				 }, nullptr), std::logic_error);
}

//=========================================================
//============= Namespace::getFunctionByName ==============
//=========================================================

TEST(Rfk_Namespace_getFunctionByName, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName(nullptr), nullptr);
}

TEST(Rfk_Namespace_getFunctionByName, ValidNameDefaultFlags)
{
	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName("func_nested_return_noParam"), nullptr);
}

TEST(Rfk_Namespace_getFunctionByName, ValidNameNonValidFlags)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName("func_nested_return_noParam", rfk::EFunctionFlags::Inline), nullptr);
}

//=========================================================
//============ Namespace::getFunctionByName<> =============
//=========================================================

TEST(Rfk_Namespace_getFunctionByNameTemplate, NullptrName)
{
	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName<int()>(nullptr), nullptr);
}

TEST(Rfk_Namespace_getFunctionByNameTemplate, UnvalidPrototypeValidNameDefaultFlags)
{
	//EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByName<int()>(""), nullptr);
}

////=========================================================
////=========== Namespace::getFunctionByPredicate ===========
////=========================================================
//
//TEST(Rfk_Namespace_getFunctionByPredicate, NullptrPredicate)
//{
//	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByPredicate(nullptr, nullptr), nullptr);
//}
//
//TEST(Rfk_Namespace_getFunctionByPredicate, FindingPredicate)
//{
//	char firstLetter = 'v';
//
//	EXPECT_NE(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByPredicate([](rfk::Function const& enum_, void* data)
//			  {
//				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
//			  }, &firstLetter), nullptr);
//}
//
//TEST(Rfk_Namespace_getFunctionByPredicate, NotFindingPredicate)
//{
//	char firstLetter = 'T';
//
//	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByPredicate([](rfk::Function const& enum_, void* data)
//			  {
//				  return enum_.getName()[0] == *reinterpret_cast<char*>(data);
//			  }, &firstLetter), nullptr);
//}
//
//TEST(Rfk_Namespace_getFunctionByPredicate, ThrowingPredicate)
//{
//	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionByPredicate([](rfk::Function const&, void*)
//				 {
//					 throw std::logic_error("Something wrong happened!");
//
//					 return true;
//				 }, nullptr), std::logic_error);
//}
//
////=========================================================
////=========== Namespace::getFunctionsByPredicate ==========
////=========================================================
//
//TEST(Rfk_Namespace_getFunctionsByPredicate, NullptrPredicate)
//{
//	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionsByPredicate(nullptr, nullptr).size(), 0u);
//}
//
//TEST(Rfk_Namespace_getFunctionsByPredicate, FindingPredicate)
//{
//	char firstLetter = 'v';
//
//	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionsByPredicate([](rfk::Function const& func, void* data)
//			  {
//				  return func.getName()[0] == *reinterpret_cast<char*>(data);
//			  }, &firstLetter).size(), 1u);
//}
//
//TEST(Rfk_Namespace_getFunctionsByPredicate, NotFindingPredicate)
//{
//	char firstLetter = 'V';
//
//	EXPECT_EQ(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionsByPredicate([](rfk::Function const& func, void* data)
//			  {
//				  return func.getName()[0] == *reinterpret_cast<char*>(data);
//			  }, &firstLetter).size(), 0u);
//}
//
//TEST(Rfk_Namespace_getFunctionsByPredicate, ThrowingPredicate)
//{
//	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->getFunctionsByPredicate([](rfk::Function const&, void*)
//				 {
//					 throw std::logic_error("Something wrong happened!");
//
//					 return true;
//				 }, nullptr), std::logic_error);
//}
//
////=========================================================
////============== Namespace::foreachFunction ===============
////=========================================================
//
//TEST(Rfk_Namespace_foreachFunction, NullptrVisitor)
//{
//	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachFunction(nullptr, nullptr));
//}
//
//TEST(Rfk_Namespace_foreachFunction, BreakingVisitor)
//{
//	int counter = 0;
//
//	EXPECT_FALSE(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachFunction([](rfk::Function const&, void* data)
//				 {
//					 int& counter = *reinterpret_cast<int*>(data);
//					 counter++;
//
//					 return false;
//				 }, &counter));
//
//	EXPECT_EQ(counter, 1);
//}
//
//TEST(Rfk_Namespace_foreachFunction, NonBreakingVisitor)
//{
//	rfk::Namespace const* np = rfk::getDatabase().getNamespaceByName("test_namespace");
//	int counter = 0;
//
//
//	EXPECT_TRUE(np->foreachFunction([](rfk::Function const&, void* data)
//				{
//					int& counter = *reinterpret_cast<int*>(data);
//					counter++;
//
//					return true;
//				}, &counter));
//
//	EXPECT_EQ(counter, np->getFunctionsCount());
//}
//
//TEST(Rfk_Namespace_foreachFunction, ThrowingVisitor)
//{
//	EXPECT_THROW(rfk::getDatabase().getNamespaceByName("test_namespace")->foreachFunction([](rfk::Function const&, void*)
//				 {
//					 throw std::logic_error("Something wrong happened here!");
//
//					 return true;
//				 }, nullptr), std::logic_error);
//}