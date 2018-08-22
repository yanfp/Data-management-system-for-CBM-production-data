#include "stdafx.h"
#include "MRecordset.h"
using namespace     ADOCONST;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction                                                                       //
//////////////////////////////////////////////////////////////////////////////////////////////////// 

MRecordset::MRecordset()
{
	CoInitialize(NULL);  
	m_pRst.CreateInstance(L"ADODB.Recordset");
	//m_pRst.CreateInstance(__uuidof(Recordset));

	//default set
	
}

MRecordset::~MRecordset()
{
	Release();
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// Property Get/Set Method                                                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////// 

//Property: RecordCount
long MRecordset::GetRecordCount() const
{
	return m_pRst->GetRecordCount();
}

//Property: PageCount
long MRecordset::GetPageCount() const
{
	return m_pRst->GetPageCount();
}

//Property: PageSize
long MRecordset::GetPageSize() const
{
	return m_pRst->GetPageSize();
}

void MRecordset::SetPageSize(long pageSize)
{
	m_pRst->PutPageSize(pageSize);
}

//Property: AbsolutePage
long MRecordset::GetAbsolutePage() const
{
	return m_pRst->GetAbsolutePage();
}

void MRecordset::SetAbsolutePage(long page)
{
	m_pRst->PutAbsolutePage((PositionEnum)page);	
}

//Property: AbsolutePosition
long MRecordset::GetAbsolutePosition() const
{
	return m_pRst->GetAbsolutePosition();
}

void MRecordset::SetAbsolutePosition(long pos)
{
	m_pRst->PutAbsolutePosition(PositionEnum(pos));
}

//Property: State
ObjectStateEnum MRecordset::GetState() const
{
	return (ObjectStateEnum)m_pRst->GetState();
}

//Property: CursorLocation
void MRecordset::SetCursorLocation(CursorLocationEnum CursorLocation)
{
	m_pRst->PutCursorLocation(CursorLocation);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// Core Method                                                                                    //
//////////////////////////////////////////////////////////////////////////////////////////////////// 

//Open
void MRecordset::Open(CString Source,MConnection & ActiveConn,CursorTypeEnum CursorType,LockTypeEnum LockType,long Options)
{
    m_pRst->Open(_variant_t(Source),ActiveConn.GetConnection().GetInterfacePtr(),CursorType,LockType,Options);
}


void MRecordset::Open(CString Source,_ConnectionPtr pConn,CursorTypeEnum CursorType, LockTypeEnum LockType,long Options)
{
	m_pRst->Open(_variant_t(Source),pConn.GetInterfacePtr(),CursorType,LockType,Options);	
}


//Close
bool MRecordset::Close() 
{
	if(m_pRst==NULL)
	{
        m_sErrorMessage=L"Recordset is not available!";
		return true;
	}
	
	try
	{
		ObjectStateEnum state=(ObjectStateEnum)(m_pRst->GetState());
		
		if(state==ObjectState::adStateOpen)
		{
			HRESULT hRsut=m_pRst->Close();
			if(SUCCEEDED(hRsut))
			{
				return true;
			}
			else
			{
				m_sErrorMessage=L"Failed to close the Recordset!";
				return false;
			}
			
		}
		
		return true;
	}
	catch(_com_error e)
	{
		m_sErrorMessage=L"There is an error when called then function: Close()!";
		return false;	
	}
}

//Release
void MRecordset::Release()
{
	if(m_pRst!=NULL)
	{
		try
		{
			Close();
			m_pRst.Release();
			m_pRst=NULL;
		}
		catch(_com_error e)
		{
            throw e;
		}
	}
}



//rstBOF
bool MRecordset::rstBOF()
{
	return (m_pRst->GetrstBOF()==VARIANT_TRUE?true:false);
}

//rstEOF
bool MRecordset::rstEOF()
{
	return (m_pRst->GetrstEOF()==VARIANT_TRUE?true:false);
}

//MoveFirst: Move the cursor to the first record.
void MRecordset::MoveFirst()  
{
	m_pRst->MoveFirst();
}

//MoveLast: Move the cursor to the last record.
void MRecordset::MoveLast()
{
	m_pRst->MoveLast();
}

//MovePrevious
void MRecordset::MovePrevious()
{
	if(m_pRst->GetrstBOF()!=VARIANT_TRUE)
	{
		m_pRst->MovePrevious();
	}
}

//MoveNext
void MRecordset::MoveNext()
{
	if(m_pRst->GetrstEOF()!=VARIANT_TRUE)
	{
		m_pRst->MoveNext();
	}
}

//MoveNext
void MRecordset::Move(long pos)
{
	if(m_pRst->GetrstEOF()!=VARIANT_TRUE)
	{
		m_pRst->Move(pos);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Recordset update db                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////

//AddNew
void MRecordset::AddNew()
{
	m_pRst->AddNew();
}

//Delete
void MRecordset::Delete(AffectEnum Option)
{
	m_pRst->Delete(Option);
}

//Update
void MRecordset::Update()
{
	m_pRst->Update();
}

//Cancel
void MRecordset::Cancel()
{
	m_pRst->Cancel();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GetValues                                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////// 

//GetString
CString MRecordset::GetString(CString columnName)
{
	try
	{
		_variant_t var=m_pRst->GetCollect(_variant_t(columnName));
		if(var.vt=VT_NULL)
			return NULL;
		else
			return (CString)(char *)(_bstr_t)var;
	}
	catch(_com_error e)
	{
		throw e;	
	}
}

CString MRecordset::GetString(long index)
{
	try
	{
		_variant_t var=m_pRst->GetCollect(_variant_t(index));
		if(var.vt==VT_NULL)
			return L"";
		else
			return (CString)(char *)(_bstr_t)var;
	}
	catch(_com_error e)
	{
		throw e;	
	}

}
//GetInt
int MRecordset::GetInt(CString columnName)
{
	try
	{
		return (short)m_pRst->GetCollect(_variant_t(columnName));
	}
	catch(_com_error e)
	{
		throw e;	
	}
}