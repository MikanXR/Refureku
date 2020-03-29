#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>

#include "TypeInfo/Archetype.h"
#include "TypeInfo/Fields/Field.h"
#include "TypeInfo/Fields/StaticField.h"
#include "TypeInfo/Methods/Method.h"
#include "TypeInfo/Methods/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/GeneratedTraits.h"

namespace rfk
{
	class Struct : public Archetype
	{
		public:
			struct Parent
			{
				struct Hasher
				{
					size_t operator()(rfk::Struct::Parent const& parent) const
					{
						return std::hash<rfk::Struct const*>()(parent.type);
					}
				};

				struct Equal
				{
					bool operator()(rfk::Struct::Parent const& p1, rfk::Struct::Parent const& p2) const
					{
						return p1.type == p2.type;
					}
				};

				EAccessSpecifier	access;
				Struct const*		type;
			};

			/** Structs this struct inherits directly in its declaration. This list includes ONLY reflected parents */
			std::unordered_set<Parent, Parent::Hasher, Parent::Equal>						directParents;

			/** Structs inheriting from this struct, regardless of their inheritance depth. This list includes ONLY reflected children */
			std::unordered_set<Struct const*>												children;

			/** All tagged fields contained in this struct, may they be declared in this struct or one of its parents (direct or not) */
			std::unordered_multiset<Field, Entity::NameHasher, Entity::EqualName>			fields;

			/** All tagged static fields contained in this struct, may they be declared in this struct or one of its parents (direct or not)  */
			std::unordered_multiset<StaticField, Entity::NameHasher, Entity::EqualName>		staticFields;

			/** All tagged methods declared in this struct */
			std::unordered_multiset<Method, Entity::NameHasher, Entity::EqualName>			methods;

			/** All tagged static methods declared in this struct */
			std::unordered_multiset<StaticMethod, Entity::NameHasher, Entity::EqualName>	staticMethods;

			Struct(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Struct(Struct const&)																		= delete;
			Struct(Struct&&)																			= default;
			~Struct()																					= default;

			/**
			*	Get the field named fieldName in this struct.
			*	The method returns nullptr if no field named fieldName was found. 
			*/
			Field const*						getField(std::string const& fieldName)						const	noexcept;

			/**
			*	Get the static field named fieldName in this struct.
			*	The method returns nullptr if no static field named fieldName was found. 
			*/
			StaticField const*					getStaticField(std::string const& fieldName)				const	noexcept;

			/**
			*	Get the first found method named methodName which has at least all the provided flags, nullptr if none if found.
			*	If shouldInspectParents is set to true, the search will be extended to parents structs recursively.
			*/
			Method const*						getMethod(std::string const& methodName,
														  uint16 minFlags = EMethodFlags::Default,
														  bool shouldInspectParents = false)				const	noexcept;
			std::vector<Method const*>			getMethods(std::string const& methodName,
														   uint16 minFlags = EMethodFlags::Default,
														   bool shouldInspectParents = false)				const	noexcept;

			/**
			*
			*/
			StaticMethod const*					getStaticMethod(std::string const& methodName,
																uint16 minFlags = EMethodFlags::Default,
																bool shouldInspectParents = false)			const	noexcept;
			std::vector<StaticMethod const*>	getStaticMethods(std::string const& methodName,
																 uint16 minFlags = EMethodFlags::Default,
																 bool shouldInspectParents = false)			const	noexcept;

			//TODO templated staticGetMethod with provided prototype
			//TODO not templated staticGetMethod with provided prototype

			/**
			*	Return true if this type inherits from the provided type, else false.
			*/
			bool inheritsFrom(Struct const& otherType)														const	noexcept;
			
			/**
			*	Return true if this type is a parent (direct or not) of the provided type, else false.
			*/
			bool isBaseOf(Struct const& otherType)															const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType* makeInstance(ArgTypes&&... args)													const	noexcept;

			/**
			*	Add the type T to this type's parents if possible
			*/
			template <typename T>
			void __RFKaddToParents(EAccessSpecifier inheritanceAccess)												noexcept;

			template <typename T>
			void __RFKaddRequiredMethods(std::string&& instantiatePrototype)										noexcept;

			template <typename ReturnType, typename... ArgTypes>
			void __RFKaddInstantiationMethod(std::string&& methodName, uint64 methodId, rfk::EAccessSpecifier accessSpecifier, ReturnType*(*function)(ArgTypes...)) noexcept;

			Struct& operator=(Struct const&)	= delete;
			Struct& operator=(Struct&&)			= default;
	};

	#include "TypeInfo/Struct.inl"
}