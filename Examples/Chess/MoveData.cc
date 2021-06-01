#include "MoveData.h"
#include "Feld.h"
#include "Figure.h"

void MoveData::operator() () {
	which->fig_->Move(dest);
}