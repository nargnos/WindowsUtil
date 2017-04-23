_平时用到的一些工具类, 这部分内容涉及面比较广, 慢慢补全_  
_未完成, 某些代码需要重新实现, pe部分编译后不够小, 需要改得更简洁_  
_用编译器内部函数代替汇编(比如取fs，为的是64位编译方便），可能某些旧版编译器不支持，而且用的C++14，VC6会编译不过，自己改改吧_  
_里面可能会包含一些无用代码文件（未完成待补足的代码），都已排除出vs项目外，以vs项目包含的文件为主_   
_相关函数接口会慢慢补sal_  
_等完成再把文档全面补充_  

# 简要说明  
## PE部分  
### PE解析  
_用法见PeImageTest.cpp_  
```c++
#include <PE\PeDecoder.h>  
```
**目前可以解析：**
* Dos头
* Nt头  
* 节表  
* 导入表  
* 导出表  
* 资源  
* 重定位表  
* 延迟导入表  

**缺读取器的结构有：**  
* Debug
* Exception
* Security
* Architecture
* Tls
* LoadConfig
* BoundImport
* ComDescriptor 

_pedecoder可以返回结构指针, 缺少读取器是因为不常用, 以后用到再补_  
_之后需要用C++.Net封装迁移到C#_  

### PE修改  
_未完成, 先写完解析再写, 如果需要修改,现在可以用decoder返回的地址修改_

## 系统部分  
_包含Dll调用等，有些杂，项目名用得不准确，后面会单独分_  
### 解析PEB  
_用法见ProcessLibTest.cpp_  
```c++
#include <Process\LdrDataTable.h>  
```
包含：  
1.PEB、TEB结构定义  
_定义来自reactos源码_  

2.LdrDataTableEntry读取器  
　可以使用三种方式遍历LdrDataTable  

3.搜索LdrDataTable,取得已经载入的DLL的句柄的函数  


### 动态调用  
```c++
#include <Process\Kernel32.h> 
#include <Process\NtDll.h>
```
_首次调用时才会载入相关dll和函数，使用搜索Ldr的方式找NtDll，LoadLibrary和GetProcAddress都是用重写的API_   
_预先定义了常用函数的一些仿函数，想到更简单的方法再替换_  


### 重写WinApi   
```c++
#include <Process\GetProcAddress.h>  
#include <Process\LoadLibrary.h>
#include <Process\OpenProcess.h>
#include <Process\ReadProcessMemory>
#include <Process\SetThreadContext>
#include <Process\VirtualAlloc>
#include <Process\VirtualFree>
#include <Process\VirtualProtect>
#include <Process\VirtualQuery>
#include <Process\WriteProcessMemory>
```
_仅重写常用的几个函数，用的是NtDll（PEB获得）里的函数_  
_GetProcAddress用前面的PE库解析_   
_启动远程线程等函数等写到再添加, 所以这部分待续_  


## Hook
### 导入表(IAT) Hook
```c++
#include <Hook\IatHook.h>  
```

### 导出表(EAT) Hook
```c++
#include <Hook\EatHook.h>  
```
_不支持64位_  

### 延迟导入表(DelayLoad) Hook
```c++
#include <Hook\DelayLoadHook.h>  
```
_使用vs2015后,相关结构定义的头文件在sdk中改名了,所以用的是新的那一个定义,旧版本编译时可能会找不到相关定义_  
_延迟导入表因为这个原因修改过，没做新的测试_  

### API Hook
```c++
#include <Hook\ApiHook.h> 
```
_现在是可用的，需要自己确定备份长度，可能有bug自己测一测_  
_这部分未写完整，需要写一个反汇编引擎实现自动判断修改长度_   
_之前写的引擎因为Intel的CPU文档解析例子跟Opcode表有冲突先暂停等文档修复再处理，已移除出项目，等写好再加回来（可能会久点，大部分忘了，有空再Load那段知识）_  
_UnHook 待续(通常不需要)_  


## 其它
临时起意封装的一些WinApi，没什么意义  
_有 Coroutine\ Fiber\ ThreadPool 等_  

