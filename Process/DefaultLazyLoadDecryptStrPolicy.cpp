#include "stdafx.h"
#include "DefaultLazyLoadDecryptStrPolicy.h"

LPCWSTR Process::LazyLoad::Detail::DefaultLazyLoadDecryptStrPolicyW::Decrypt(EncryptStr str)
{
	return str;
}

LPCWSTR Process::LazyLoad::Detail::DefaultLazyLoadDecryptStrPolicyW::GetStr(DecryptStr & str)
{
	return str;
}

LPCSTR Process::LazyLoad::Detail::DefaultLazyLoadDecryptStrPolicyA::Decrypt(EncryptStr str)
{
	return str;
}

LPCSTR Process::LazyLoad::Detail::DefaultLazyLoadDecryptStrPolicyA::GetStr(DecryptStr & str)
{
	return str;
}
