#pragma once
namespace Process
{
	namespace EnvironmentBlock
	{
		enum class LdrDataTableModuleList
		{
			InLoadOrderModuleList,
			InMemoryOrderModuleList,
			InInitializationOrderModuleList
		};
	}  // namespace EnvironmentBlock
}  // namespace Process
