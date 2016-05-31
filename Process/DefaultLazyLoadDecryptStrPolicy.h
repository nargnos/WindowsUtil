#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// 不处理加解密
			struct DefaultLazyLoadDecryptStrPolicyW
			{
				typedef LPCWSTR EncryptStr;
				typedef LPCWSTR DecryptStr;
				// 将指定类型解密为目标类型（如string）
				static DecryptStr Decrypt(EncryptStr str);
				// 取目标类型取字符串指针（内部c_str就行）
				static LPCWSTR GetStr(DecryptStr& str);
			};
			struct DefaultLazyLoadDecryptStrPolicyA
			{
				typedef LPCSTR EncryptStr;
				typedef LPCSTR DecryptStr;
				static DecryptStr Decrypt(EncryptStr str);
				static LPCSTR GetStr(DecryptStr& str);
			};
		}  // namespace Detail


	}  // namespace LazyLoad
}  // namespace Process
