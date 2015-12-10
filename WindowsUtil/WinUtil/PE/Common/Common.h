#pragma once
#include <Windows.h>
#include <cassert>
#include <memory>
#include "PeStruct.h"
#include "DataDirectory.h"
#include "..\PeDecoder.h"


#include "GetIterator.h"
#include "IGetValue.h"
#include "IIterator.h"
#include "InitStruct.h"
#include "..\DosHeader\DosHeader.h"
#include "..\NtHeader\NtHeader.h"
#include "..\Section\Section.h"
#include "..\Reloc\RelocDirectory.h"
#include "..\Export\ExportDirectory.h"
#include "..\Import\ImportDirectory.h"
#include "..\Resource\ResourceDirectory.h"
#include "..\EntryException\EntryExceptionDirectory.h"
#include "..\Security\SecurityDirectory.h"
#include "..\Architecture\ArchitectureDirectory.h"
#include "..\Globalptr\GlobalptrDirectory.h"
#include "..\BoundImport\BoundImportDirectory.h"
#include "..\ComDescriptor\ComDescriptorDirectory.h"
#include "..\DelayImport\DelayImportDirectory.h"
#include "..\Iat\IatDirectory.h"
#include "..\LoadConfig\LoadConfigDirectory.h"
#include "..\Tls\TlsDirectory.h"
#include "..\DebugDirectory\DebugDirectory.h"



