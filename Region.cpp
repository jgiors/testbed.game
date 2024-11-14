///@file
#include "precomp.h"
#include "Region.h"

engine::Region::Region(engine::Region *pParent, size_t maxWidth, size_t maxHeight, size_t maxChildren)
: _pParent(pParent), _cells(maxWidth, maxHeight, 0, 0), _children(maxChildren)
{

}