#include "stdafx.h"
#include "Plugin.h"

inline void UnManagedPlugin::OnClick(System::Object ^ sender, System::EventArgs ^ e)
{
	if (sender->GetType() == ToolStripMenuItem::typeid)
	{
		funcMap[((ToolStripMenuItem^)sender)->Text](); // 必定存在
	}
}

inline UnManagedPlugin::UnManagedPlugin() {}

inline UnManagedPlugin ^ UnManagedPlugin::CreateInstance(HMODULE dll)
{
	auto result = gcnew UnManagedPlugin();
	result->getName = (GetNameDef)GetProcAddress(dll, "GetName");
	result->onFileOpened = (OnFileOpenedDef)GetProcAddress(dll, "OnFileOpened");
	result->onFileClosed = (OnFileClosedDef)GetProcAddress(dll, "OnFileClosed");
	result->getMenuNames = (GetMenuNamesDef)GetProcAddress(dll, "GetMenuNames");
	result->getMenuFunctions = (GetMenuFunctionsDef)GetProcAddress(dll, "GetMenuFunctions");
	result->getMenuCount = (GetMenuCountDef)GetProcAddress(dll, "GetMenuCount");

	if (result->getName &&
		result->onFileOpened &&
		result->onFileClosed &&
		result->getMenuNames &&
		result->getMenuFunctions &&
		result->getMenuCount)
	{
		return result;
	}
	return nullptr;
}

inline void UnManagedPlugin::OnFileOpened(IntPtr base, long long size, bool isReadonly)
{
	onFileOpened(base.ToPointer(), size, isReadonly);
}

inline void UnManagedPlugin::OnFileClosed()
{
	onFileClosed();
}

inline List<ToolStripMenuItem^>^ UnManagedPlugin::GetMenus()
{
	auto result = gcnew List<ToolStripMenuItem^>();
	for each (auto var in funcMap)
	{
		auto tmpMenu = gcnew ToolStripMenuItem(var.Key);
		tmpMenu->Click += gcnew System::EventHandler(this, &UnManagedPlugin::OnClick);
		result->Add(tmpMenu);
	}
	return result;
}

inline String ^ UnManagedPlugin::GetName()
{
	// 初始化菜单关联托管，因为函数定义不方便绑定到click事件
	funcMap = gcnew Dictionary<String^, Action^>();
	int count = getMenuCount();
	auto menuNames = getMenuNames();
	auto menuFuncs = getMenuFunctions();
	for (int i = 0; i < count; i++)
	{
		auto tmpName = marshal_as<String^>(menuNames[i]);
		auto tmpFunc = (Action^)Marshal::GetDelegateForFunctionPointer(IntPtr(menuFuncs[i]), Action::typeid);

		funcMap->Add(tmpName, tmpFunc);
	}

	return marshal_as<String^>(getName());
}

inline PeidPlugin::PeidPlugin() {}

inline PeidPlugin ^ PeidPlugin::CreateInstance(HMODULE dll)
{
	auto result = gcnew PeidPlugin();
	result->doMyJob = (DoMyJobDef)GetProcAddress(dll, "DoMyJob");
	result->loadDll = (LoadDllDef)GetProcAddress(dll, "LoadDll");
	if (result->doMyJob && result->loadDll)
	{
		return result;
	}
	return nullptr;
}

inline String ^ PeidPlugin::GetName()
{
	return marshal_as<String^>(loadDll());
}

inline int PeidPlugin::DoMyJob(IntPtr hMainDlg, String ^ szFname, int lpReserved, IntPtr lpParam)
{
	auto str = String::IsNullOrEmpty(szFname) ? "" : marshal_as<std::string>(szFname);
	return doMyJob((HWND)hMainDlg.ToPointer(), (char*)str.c_str(), lpReserved, lpParam.ToPointer());
}

inline PluginFactory::PluginFactory() {}

inline void PluginFactory::AddPlugin(Dictionary<String^, IPluginBase^>^% dic, IPluginBase ^ plugin)
{
	auto name = plugin->GetName();
	if (dic->ContainsKey(name))
	{
		return;
	}
	dic->Add(name, plugin);
}

inline bool PluginFactory::IsSameMethod(MethodInfo ^ method1, MethodInfo ^ method2)
{
	bool isSame = true;
	if (method1 == nullptr || method2 == nullptr)
	{
		return false;
	}
	if (method1->ReturnParameter->Name != method2->ReturnParameter->Name)
	{
		return false;
	}
	auto param1 = method1->GetParameters();
	auto param2 = method2->GetParameters();

	if (param1->Length != param2->Length)
	{
		return false;
	}
	for (int i = 0; i < param1->Length; i++)
	{
		if (param1[i]->ParameterType->Name != param2[i]->ParameterType->Name)
		{
			isSame = false;
			break;
		}
	}
	return isSame;
}

inline void PluginFactory::LoadAssemblyPlugin(Assembly ^ assembly, Dictionary<String^, IPluginBase^>^% result)
{
	//auto result = gcnew Dictionary<String^, IPlugin^>();
	auto interfaceType = IPlugin::typeid;
	for each(auto assemblyType in assembly->GetTypes())
	{
		try
		{
			if (!assemblyType->IsClass || !assemblyType->IsPublic || assemblyType->IsAbstract)
			{
				continue;
			}
			auto assemblyInterfaceType = assemblyType->GetInterface(interfaceType->FullName);
			if (assemblyInterfaceType == interfaceType)
			{
				// 继承接口
				auto instance = (IPlugin^)assembly->CreateInstance(assemblyType->FullName);
				// 构造输出
				AddPlugin(result, instance);
			}
			else
			{
				// 不继承接口，但是有相同函数定义的类
				auto funcMap = gcnew Dictionary<String^, MethodInfo^>();
				bool isSame = true;
				for each(auto interfaceMethod in interfaceType->GetMethods())
				{
					auto assemblyMethod = assemblyType->GetMethod(interfaceMethod->Name);
					if (assemblyMethod == nullptr)
					{
						break;
					}
					isSame = IsSameMethod(interfaceMethod, assemblyMethod);
					if (!isSame)
					{
						break;
					}
					else
					{
						funcMap->Add(interfaceMethod->Name, assemblyMethod);
					}
				}

				if (isSame)
				{
					// 构造输出funcMap
					auto obj = assembly->CreateInstance(assemblyType->FullName);
					// TODO: 需要做一个包装转换，先放着
				}

			}
		}
		catch (...)
		{
		}
	}
	//return result;
}

inline IPluginBase ^ PluginFactory::LoadUnManagedPlugin(String ^ path)
{
	auto str = marshal_as<std::wstring>(path);
	HMODULE dll;
	try
	{
		auto pathStr = str.c_str();
		dll = LoadLibraryW(pathStr);
	}
	catch (...)
	{
		return nullptr;
	}
	IPluginBase^ result = PeidPlugin::CreateInstance(dll);
	if (result == nullptr)
	{
		result = UnManagedPlugin::CreateInstance(dll);
	}
	if (result == nullptr)
	{
		FreeLibrary(dll);
	}
	return result;
}

inline Dictionary<String^, IPluginBase^>^ PluginFactory::GetPlugins(String ^ dirName)
{
	auto path = Path::Combine(Application::StartupPath, dirName);
	if (!Directory::Exists(path))
	{
		return nullptr;
	}
	auto result = gcnew Dictionary<String^, IPluginBase^>();
	for each(auto item in Directory::GetFiles(path, "*.dll"))
	{
		auto fullPath = item;// Path::GetFullPath(item);
		if (String::IsNullOrEmpty(fullPath))
		{
			continue;
		}
		Assembly^ assembly = nullptr;
		try
		{
			assembly = Assembly::LoadFile(fullPath);
		}
		catch (...)
		{
			// 非.netDll
			auto tmpPlugin = PluginFactory::LoadUnManagedPlugin(fullPath);
			if (tmpPlugin)
			{
				AddPlugin(result, tmpPlugin);
			}

			continue;
		}
		PluginFactory::LoadAssemblyPlugin(assembly, result);

	}
	return result;
}

inline ToolStripMenuItem ^ PluginMenuManager::BuildMenu(String ^ menuName, PeidPlugin ^ plugin)
{
	auto tmpMenu = gcnew ToolStripMenuItem(menuName);
	tmpMenu->Click += gcnew System::EventHandler(this, &PluginMenuManager::OnClick);
	return tmpMenu;
}

inline ToolStripMenuItem ^ PluginMenuManager::BuildMenu(String ^ menuName, IPlugin ^ plugin)
{
	auto tmpMenu = gcnew ToolStripMenuItem(menuName);
	tmpMenu->DropDownItems->AddRange(plugin->GetMenus()->ToArray());
	return tmpMenu;
}

inline void PluginMenuManager::RunPeidPlugin(Object ^ plugin)
{
	(static_cast<PeidPlugin^>(plugin))->DoMyJob(hMainDlg, path, 0, IntPtr::Zero);
}

inline void PluginMenuManager::OnClick(System::Object ^ sender, System::EventArgs ^ e)
{

	auto plugin = plugins[((ToolStripMenuItem^)sender)->Text];
	auto type = plugin->GetType();
	if (type == PeidPlugin::typeid)
	{
		(gcnew Threading::Tasks::Task(gcnew Action<Object^>(this, &PluginMenuManager::RunPeidPlugin), plugin))->Start();
	}
}

inline void PluginMenuManager::AddMenu(ToolStripMenuItem ^ item)
{
	menu->DropDownItems->Add(item);
}

inline PluginMenuManager::PluginMenuManager(ToolStripMenuItem ^ menu)
{
	isFileOpen = false;
	this->menu = menu;
	plugins = PluginFactory::GetPlugins("Plugins");
	if (plugins == nullptr)
	{
		return;
	}
	// 添加menu
	for each (auto var in plugins)
	{
		ToolStripMenuItem^ tmpMenu = nullptr;
		auto type = var.Value->GetType();
		if (type == PeidPlugin::typeid)
		{
			tmpMenu = BuildMenu(var.Key, static_cast<PeidPlugin^>(var.Value));
		}
		/*	else if (type == UnManagedPlugin::typeid)
		{
		tmpMenu=BuildMenu(static_cast<UnManagedPlugin^>(var.Value));
		}*/
		else if (type == IPlugin::typeid)
		{
			tmpMenu = BuildMenu(var.Key, static_cast<IPlugin^>(var.Value));
		}
		if (tmpMenu != nullptr)
		{
			menu->Owner->Invoke(gcnew Action<ToolStripMenuItem^>(this, &PluginMenuManager::AddMenu), tmpMenu);
		}

	}
}

inline void PluginMenuManager::OnOpenFIle(IntPtr hMainDlg, String ^ path, IntPtr base, long long size, bool isReadonly)
{
	isFileOpen = true;
	this->hMainDlg = hMainDlg;
	this->path = path;
	this->base = base;
	this->size = size;
	this->isReadonly = isReadonly;
	if (plugins == nullptr)
	{
		return;
	}
	for each (auto var in plugins->Values)
	{
		auto type = var->GetType();
		if (type == IPlugin::typeid)
		{
			static_cast<IPlugin^>(var)->OnFileOpened(base, size, isReadonly);
		}
	}
}

inline void PluginMenuManager::OnCloseFile()
{
	isFileOpen = false;
	this->path = String::Empty;
	this->base = IntPtr::Zero;
	this->size = 0;
	if (plugins == nullptr)
	{
		return;
	}
	for each (auto var in plugins->Values)
	{
		auto type = var->GetType();
		if (type == IPlugin::typeid)
		{
			static_cast<IPlugin^>(var)->OnFileClosed();
		}
	}
}
