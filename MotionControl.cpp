// MotionControl.cpp: implementation of the CMotionControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YuanDao.h"
#include "MotionControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMotionControl::CMotionControl()
{

}

CMotionControl::~CMotionControl()
{

}


long GetFileInfo(FILE *pfile)
{
	//
	long nLength = 0;
	char c[1];
	if (pfile == NULL)
	{
		return nLength;
	}
	
	//
	while (!feof(pfile))
	{
		fread(c, sizeof(char), 1, pfile);
		nLength++;
	}
	//	char t;
	//	t = c[1];
	rewind(pfile);
	return nLength;
}

