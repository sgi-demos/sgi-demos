#include "democolors.h"
#include "port.h"
unsigned short Grey(x)
unsigned short x;
{
	if (m_type == NONBUBBLE)
		return(CUECOLOR3[m_type]+(x<<1));
	else 
		return(CUECOLOR3[m_type]+x);
}
