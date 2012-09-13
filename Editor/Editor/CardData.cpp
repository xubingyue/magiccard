#include "StdAfx.h"
#include "CardData.h"

CCardData::CCardData(void)
{
}

CCardData::~CCardData(void)
{
}
bool CCardData::LoadFile()
{

	return false;
}

bool CCardData::SaveFile()
{

	return false;
}

bool CCardData::AddCard(const SCard& rCard)
{
	if (0 == rCard.uId)
	{
		// New Card
	}
	else
	{
		// Revise Card

	}

	return false;
}

bool CCardData::DeleteCard(DWORD uId)
{

	return false;
}

DWORD CCardData::GenId()
{
	static DWORD i = 0;

	return ++i;
}
