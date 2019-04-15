#include "..\stdafx.h"
#include "Controllable.h"

void Controllable::SetControl(bool manualInput)
{
	_AIControl = !manualInput;
}