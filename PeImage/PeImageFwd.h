#pragma once
namespace PeDecoder
{
	class ArchitectureDirectory;
	class BoundImportDirectory;
	class ComDescriptorDirectory;
	class DataDirectoryEntries;
	class DebugDirectory;
	class DelayImportDirectory;
	class DosHeader;
	class DosStub;
	class ExceptionDirectory;
	class ExportDirectory;
	class GlobalptrDirectory;
	class IatDirectory;
	class ImportDirectory;
	class LoadConfigDirectory;
	class NtHeader;
	class PeImage;
	class RelocDirectory;
	class ResourceDirectory;
	class SectionHeaders;
	class SecurityDirectory;
	class TlsDirectory;
	class ImportDescriptor;
	template<typename>
	class ImportThunk;
	class DelayImportDescriptor;
	class DelayImportDirectory;
	class RelocDirectory;
	class BaseRelocation;
	class ImportDirectoryIterator;
	class ExportDirectoryIterator;
	class ExportIteratorNode;
	template<typename>
	class ImportThunkIterator;
	template<typename>
	class ImportThunkIteratorBase;
	class RelocDirectoryIterator;
	class TypeOffsetIterator;
	class TypeOffset;
	class ResourceEntry;
	class ResourceEntryIterator;
	class ResourceDirectoryNode;
}  // namespace PeDecoder
