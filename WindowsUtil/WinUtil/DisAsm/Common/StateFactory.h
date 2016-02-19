#pragma once
#include "Common.h"
#include "Disassembler_Trait.h"
namespace Disassembler
{


	// 参数为需要使用此类的类型（Disassembler）
	template<typename T, typename TTrait = Disassembler_Trait<T>>
	struct StateFactory
	{
		typedef typename TTrait::TStateUsed ParamType;
		typedef int (*NextStateFunction)(ParamType*);
		
		// 下面是子类需要编写的函数

		/// <summary>
		/// 获取任意状态
		/// </summary>
		/// <param name="stateId">状态ID</param>
		/// <returns>状态处理函数指针,返回0表示退出</returns>
		// static NextStateFunction GetStateFunction(unsigned char stateId);

		/// <summary>
		/// 获取状态入口
		/// </summary>
		// static int GetBeginStateID();

		/// <summary>
		/// 获取状态终止ID
		/// </summary>
		// static int GetEndStateID();

	};
}  // namespace Disassembler

