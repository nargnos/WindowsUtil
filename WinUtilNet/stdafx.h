#pragma once
// 这个项目包装pedecoder只供解析程序（c#）使用（只考虑解析，所以一次读所有内容), 只做相关函数包装，其它用不到的就算了，
// 另外一些数组什么的本来用迭代器模式编写的，这边直接导出数组（因为控件一次全部显示）

// 用到的所有IntPtr在读取文件时表示偏移量，读内存时表示内存指针，输出值的时候会取它的字长，这样导致在64位下读取文件时显示字长过长
// 所以只编32位，解析文件都能载入的

// FIX: 因为需要每个值都能输出Offset，如果用PtrToStructure取数据会得不到指针，为每个成员添加计算偏移量的代码需要写很多（而且没规律），如果一个个取又跟现在用的差不多了
// 所以暂时先用笨方法取指针，等想到更好的再替换

#include <PeImage\PeDecoder.h>
#define NAMESPACE Wrapper
namespace NAMESPACE {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	// 载入新文件时需要执行
	interface class IReset
	{
		void Reset() = 0;
	};


}


//#include "Converters.h"
//#include "StructOffset.h"
//#include "UITypeEditor.h"
//#include "UnmanagedMemory.h"
//#include "UnmanagedArray.h"
//#include "UnmanagedValue.h"
//#include "PeStructWrapper.h"
//#include "UnmanagedEnum.h"

