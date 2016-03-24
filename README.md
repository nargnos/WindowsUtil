_平时用到的一些工具类, 这部分内容涉及面比较广, 慢慢补全_  
_未完成, 某些代码需要重新实现, pe部分编译后不够小, 需要改得更简洁_  

#PE
###PE解析
```c++
#include <PE\PeDecoder.h>  
```
可以调用子文件夹的迭代器头文件, 可解析PE文件的:  
* 节表  
* 导入表  
* 导出表  
* 资源  
* 重定位表  
* 延迟导入表  

_缺读取器的结构有_  
_Debug,Exception,Security,Architecture,Tls,LoadConfig,BoundImport,ComDescriptor._  
_pedecoder可以返回结构指针, 缺少读取器是因为不常用, 以后用到再补_

###PE修改
_未完成, 如果需要修改,现在可以用decoder返回的地址修改_



#进程
###解析PEB
```c++
#include <Process\EnvironmentBlock\EnvironmentBlock.h>  
```
包含：  
1.PEB、TEB结构定义  
_定义来自reactos源码_  

2.LdrDataTableEntry读取器  
　可以使用三种方式遍历LdrDataTable  

3.搜索LdrDataTable,取得已经载入的DLL的句柄的函数  

###Hook
####导入表(IAT) Hook
```c++
#include <Process\Hook\IatHook.h>  
```

####导出表(EAT) Hook
```c++
#include <Process\Hook\EatHook.h>  
```
_不支持64位_  

####延迟导入表(DelayLoad) Hook
```c++
#include <Process\Hook\DelayLoadHook.h>  
```
_使用vs2015后,相关结构定义的头文件在sdk中改名了,所以用的是新的那一个定义,旧版本编译时可能会找不到相关定义_  

####API Hook
```c++
#include <Process\Hook\ApiHook.h> 
// ...
oldFunctionAddress =(decltype(&MessageBoxA))HookApi32(MessageBoxA, MessageBoxA_Hook1);

```
包含了一个返回指令长度的Opcode解析器 (Process\Hook\Opcode)  
支持多次Hook同一个函数, 也有只hook一次的精简版本  
_UnHook 待续(通常不需要)_


###动态调用
```c++
#include <Process\LazyLoad\LazyLoadSystemApi.h> 
// 直接使用已经定义的Kernel32_Dll、NtDll_Dll、User32_Dll来动态调用函数，
// 不全，只注册了常用的一些函数, 使用方法类似:
Kernel32_Dll._GetSystemInfo(&sysinfo);
// ... 
NtDll_Dll._NtFreeVirtualMemory(hProcess,
					&lpAddress,
					&dwSize,
					dwFreeType);
// ...

```


###重写WinApi
在上面动态调用的例子中, 如果只需要基础的LoadLibrary和GetProcAddress, 可以
```c++
#include <Process\LazyLoad\LazyLoad.h>  
```
里面包含了重写的两个函数和一些扩展. _LoadLibraryW使用ntdll.dll(读取PEB取到的句柄)的LdrLoadDll来载入dll,
已存在dll的句柄都是通过读取peb获得的. _GetProcAddress使用的是解析pe获取的函数地址.  

代码、dll注入相关的一些函数重写了(不需要重写版本可以使用Kernel32_Dll的动态调用版本).
```c++
#include <Process\OverwriteWinApi\OverwriteWinApi.h>  
```
_代码修改自reactos_  
包括打开进程、读写释放远程进程内存、设置内存保护标记、设置线程上下文信息等  
_启动远程线程等函数等写到再添加, 所以这部分待续_


#其它
###DisAsm
_未完成, 太费时, 先在apihook中编写了一个只解析指令长度的版本(这个版本有bug，等新的完成再替换掉)_
