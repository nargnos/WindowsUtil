_Windows中用到的一些工具类_

#PE
##PE解析
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

_缺读取器的结构有,Debug,Exception,Security,Architecture,Tls,LoadConfig,BoundImport,ComDescriptor.<br>
decoder可以返回结构指针,缺少读取器是因为不常用, 以后用到再补_


##PE修改
_未完成, 如果需要修改,现在可以用decoder返回的地址修改_


##PE映射
_待续_

#进程
##解析PEB
```c++
#include <Process\EnvironmentBlock\EnvironmentBlock.h>  
```
包含：  
1.PEB、TEB结构定义  
　_定义来自reactos源码_  
　取得PEB后,根据定义可以读取PEB结构  

2.LdrDataTableEntry读取器  
　可以使用三种方式遍历LdrDataTable  

3.搜索LdrDataTable,取得已经载入的DLL的句柄的函数  

##Hook
###导入表(IAT) Hook
```c++
#include <Process\Hook\IatHook.h>  
```

###导出表(EAT) Hook
```c++
#include <Process\Hook\EatHook.h>  
```
###延迟导入表(DelayLoad) Hook
```c++
#include <Process\Hook\DelayLoadHook.h>  
```

###API Hook
```c++
#include <Process\Hook\ApiHook.h> 
// ...
oldFunctionAddress =(decltype(&MessageBoxA))HookApi32(MessageBoxA, MessageBoxA_Hook1);

```
包含了一个查表法编写的返回指令长度的Opcode解析器 (Process\Hook\Opcode)  
支持多次Hook同一个函数  
_64位的解析器未测试, 所以64位的Hook未编写, UnHook 待续(通常不需要)_

##动态调用
```c++
#include <Process\LazyLoad\LazyLoadSystemApi.h> 
// 直接使用已经定义的Kernel32_Dll、NtDll_Dll、User32_Dll来动态调用函数，
// 不全，只注册了常用的一些函数
Kernel32_Dll._GetSystemInfo(&sysinfo);
// ... 
NtDll_Dll._NtFreeVirtualMemory(hProcess,
					&lpAddress,
					&dwSize,
					dwFreeType);
// ...

```


##重写WinApi
在上面动态调用的例子中, 如果只需要基础的LoadLibrary和GetProcAddress, 可以
```c++
#include <Process\LazyLoad\LazyLoad.h>  
```
里面包含了重写的两个函数和一些扩展. _LoadLibraryW使用ntdll.dll(读取PEB取到的句柄)的LdrLoadDll来载入dll,
已存在dll的句柄都是通过读取peb获得的. _GetProcAddress使用的是解析pe获取的函数地址.  

代码、dll注入使用的一些函数重写了(不需要重写版本可以使用Kernel32_Dll的动态调用版本)
```c++
#include <Process\OverwriteWinApi\OverwriteWinApi.h>  
```
包括打开进程、读写释放远程进程内存、设置内存保护标记、设置线程上下文信息等  
_启动远程线程等函数等写到再添加, 所以这部分待续_

##注入
_待续_


#其它
##DisAsm
_未完成, 在apihook中编写了一个只解析长度的版本_
