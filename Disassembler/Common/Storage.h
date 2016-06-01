#pragma once
#include "Common.h"
#include "Interface\IStorage.h"
namespace Disassembler
{
	class StorageBase :public IStorage
	{
	public:
		StorageBase();
		StorageBase(const StorageBase& val);
		virtual void SetInitialPosition(const void * pos) override;
		virtual const unsigned char* GetCurrentPosition() override;
		virtual void NextByte() override;
		virtual bool IsSuccess() override;
		void SetSuccess();
		virtual void Seek(int offset) override;
	private:
		const unsigned char* beginPos;
		const unsigned char* currentPos;
		bool isSuccess;
		
	};




}  // namespace Disassembler