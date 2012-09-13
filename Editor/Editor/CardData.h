#ifndef _CARDDATA_H_
#define _CARDDATA_H_

#pragma once

typedef struct _SCard
{
	DWORD			uId;
	int				nType;
	int				nAttack;
	std::wstring	strName;
	std::wstring	strSeries;
	std::wstring	strDesc;
	std::wstring	strFileName;
}
SCard;

enum ECardType
{
	eType_None,
	eType_Monster1,
	eType_Monster2,
	eType_Monster3,
	eType_Magic,
	eType_Trap,

	eType_Max
};

static const TCHAR* g_szCardType[eType_Max] = 
{
	_T("None"),
	_T("Monster Level 1"),
	_T("Monster Level 2"),
	_T("Monster Level 3"),
	_T("Magic"),
	_T("Trap"),
};

static ECardType StringToType(const TCHAR* szType)
{
	int nType = 0;
	for (int i = 0; i < eType_Max; ++i)
	{
		if (0 == _tcsicmp(szType, g_szCardType[i]))
		{
			nType = i;
			break;
		}
	}
	return static_cast<ECardType>(nType);
}

class CCardData
{
public:
	~CCardData();

public:
	static CCardData& Instance()
	{
		static CCardData s_cInstance;
		return s_cInstance;
	}

	std::vector<SCard>& GetCards(){return m_vecCards;}

	bool LoadFile();
	bool SaveFile();

	bool AddCard(const SCard& rCard);
	bool DeleteCard(DWORD uId);

protected:
	CCardData(void);
	explicit CCardData(const CCardData&){}
	CCardData& operator=(const CCardData&){}

	DWORD GenId();

private:
	std::vector<SCard>		m_vecCards;
};

#endif