#pragma once
#include "../LazyLoad/LazyLoad.h"
namespace Process
{
	namespace Remote
	{
		class RemoteProccess
		{
		public:
			explicit RemoteProccess(HANDLE process);
			~RemoteProccess();
		private:

		};

	}  // namespace Remote
}  // namespace Process
