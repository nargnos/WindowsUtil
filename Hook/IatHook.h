#pragma once
#include <Windows.h>
#include <memory>
#include <unordered_map>
namespace PeDecoder
{
	__interface IPeImage;
	class ImportDirectory;
}  // namespace PeDecoder
namespace Hook
{
	class IatHook
	{
	public:
		using HookPlace = PVOID;
		using FuncPtr = LPCVOID;
		class DllNameProxy;
		class ProcNameProxy;
		~IatHook();
		static _STD shared_ptr<IatHook> Instance(const _STD wstring & moduleName);
		static _STD shared_ptr<IatHook> Instance(HMODULE module);
		bool CanIatHook() const;
		explicit operator bool() const;
		DllNameProxy operator[](const _STD string & dllName);
		bool IsHooked(const _STD string & dllName, const _STD string & procName);
		// 返回旧函数地址，如果失败返回nullptr
		FuncPtr Hook(const _STD string & dllName, const _STD string & procName, LPCVOID hookFunc);
		bool UnHook(const _STD string & dllName, const _STD string & procName);
		FuncPtr GetOldFunction(const _STD string & dllName, const _STD string & procName) const;
	private:
		IatHook(const IatHook&) = delete;
		IatHook& operator=(const IatHook&) = delete;
		IatHook(HMODULE module);

		using FunctionBackup = _STD pair<HookPlace, FuncPtr>;
		using BackupType = _STD unordered_map<_STD string, FunctionBackup>;

		FunctionBackup Find(const _STD string & dllName, const _STD string & procName)const;
		bool CheckFunctionBackup(const FunctionBackup& val);
		_STD unordered_map<_STD string, BackupType> backup_;
		_STD shared_ptr<PeDecoder::IPeImage> module_;
		_STD unique_ptr<PeDecoder::ImportDirectory> importDirectory_;
		bool canHook_;
	};

	class IatHook::DllNameProxy
	{
	public:
		DllNameProxy(IatHook& iatHook, const _STD string & dllName);
		ProcNameProxy operator[](const _STD string& procName);
	private:
		const _STD string dllName_;
		IatHook& iatHook_;
	};

	class IatHook::ProcNameProxy
	{
	public:
		ProcNameProxy(IatHook& iatHook, const _STD string & dllName, const _STD string & procName);
		FuncPtr operator=(FuncPtr func);
		explicit operator bool() const;
		FuncPtr operator &() const;
		bool UnHook();
	private:
		const _STD string dllName_;
		const _STD string procName_;
		IatHook& iatHook_;
	};

}  // namespace Hook