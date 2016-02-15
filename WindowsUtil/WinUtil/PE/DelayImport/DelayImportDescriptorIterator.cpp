#include "DelayImportDirectory.h"
PE::DelayImportDescriptorIterator::DelayImportDescriptorIterator(DelayImportDirectory* delayImport) :delayImport(delayImport)
{
	assert(delayImport != NULL);
}

PE::DelayImportDescriptorIterator::~DelayImportDescriptorIterator()
{
}


// Í¨¹ý IIterator ¼Ì³Ð

PImgDelayDescr PE::DelayImportDescriptorIterator::Current()
{
	return currentDelay;
}

bool PE::DelayImportDescriptorIterator::Next()
{
	if (!currentDelay)
	{
		currentDelay = delayImport->data;
		canCreateIterator = true;
		return true;
	}
	else
	{
		currentDelay++;
		if (currentDelay->grAttrs)
		{
			canCreateIterator = true;
			return true;
		}
	}
	canCreateIterator = false;
	return false;
}

void PE::DelayImportDescriptorIterator::Reset()
{
	canCreateIterator = false;
	currentDelay = NULL;
}
