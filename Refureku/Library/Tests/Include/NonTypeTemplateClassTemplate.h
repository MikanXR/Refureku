/**
*	Copyright (c) 2021-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "TestEnum.h"

#include "Generated/NonTypeTemplateClassTemplate.rfkh.h"

template <std::size_t Value>
class CLASS() SingleNonTypeTemplateClassTemplate
{
	private:
		FIELD()
		int intArray[Value];

	SingleNonTypeTemplateClassTemplate_GENERATED
};

template <TestEnumClass EnumClass, std::size_t Size>
class CLASS() MultipleNonTypeTemplateClassTemplate
{
	MultipleNonTypeTemplateClassTemplate_GENERATED
};

File_NonTypeTemplateClassTemplate_GENERATED