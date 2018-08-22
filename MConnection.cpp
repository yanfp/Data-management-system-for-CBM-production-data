
#include "stdafx.h"
#include "MConnection.h"
using namespace ADOCONST;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////

MConnection::MConnection()
{
	CoInitialize(NULL);  
	m_pConn.CreateInstance(L"ADODB.Connection");
    //m_pConn.CreateInstance(__uuidof(Connection));
	//default set
    m_pConn->PutCursorLocation(CursorLocation::adUseClient);
}

MConnection::~MConnection()
{
    Release();
	CoUninitialize();  
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Property Get/Set Method                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////

//Property: ConnectionString  
CString MConnection::GetConnectionString() const
{
    return (CString)(char*)(m_pConn->GetConnectionString());
}

void MConnection::SetConnectionString(CString strConn)
{
    m_pConn->PutConnectionString(_bstr_t(strConn));
}

void MConnection::SetConnectionString(char *charConn)
{
	m_pConn->PutConnectionString(_bstr_t(charConn));
}


//Property: ConnectionTimeout  
long MConnection::GetConnectionTimeout() const
{
    return m_pConn->GetConnectionTimeout();
}

void MConnection::SetConnectionTimeout(long time)
{
    m_pConn->PutConnectionTimeout(time);
}

//Property: CursorLocation  
CursorLocationEnum MConnection::GetCursorLocation() const
{
	return m_pConn->GetCursorLocation();
}

void MConnection::SetCursorLocation(CursorLocationEnum CursorLocation)
{
    m_pConn->PutCursorLocation(CursorLocation);
}

//Property: CommandTimeout  
long MConnection::GetCommandTimeout() const
{
    return m_pConn->GetCommandTimeout();
}

void MConnection::SetCommandTimeout(long time)
{
    m_pConn->PutCommandTimeout(time);
}

//Property: State  
ObjectStateEnum MConnection::GetState() const
{
    return (ObjectStateEnum)(m_pConn->GetState());
}


//Property: m_sErrorMessage
CString MConnection::GetErrorMessage() const
{
	return m_sErrorMessage;
}

//Property: m_pConn
_ConnectionPtr MConnection::GetConnection() const
{
	return m_pConn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Core Method                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////

//Open 
bool MConnection::Open(CString ConnectionString,CString UserID,CString Password, ConnectOptionEnum ConnectOption)
{
	try
	{
		if(m_pConn==NULL)
		{
			m_pConn.CreateInstance(L"ADODB.Connection");
		}

		HRESULT hRsut=m_pConn->Open((_bstr_t)ConnectionString,(_bstr_t)UserID,(_bstr_t)Password,(long)ConnectOption);
		
		if(SUCCEEDED(hRsut))
		{
			return true;
		}
		else
		{
			m_sErrorMessage=L"There is an error when open the connection!";
			return false;
		}
	}
    catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: Close()!";
		return false;	
	}
}


//Close
bool MConnection::Close()
{
	if(m_pConn==NULL)
	{
        m_sErrorMessage=L"Connectin is not available!";
		return true;
	}
	
	try
	{
		ObjectStateEnum state=(ObjectStateEnum)(m_pConn->GetState());
		
		if(state==ObjectState::adStateOpen)
		{
			HRESULT hRsut=m_pConn->Close();
			if(SUCCEEDED(hRsut))
			{
				return true;
			}
			else
			{
				//m_sErrorMessage
				m_sErrorMessage=L"Failed to close the connection!";
				return false;
			}
			
		}

		return true;
	}
	catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: Close()!";
		return false;	
	}
}


//Cancel
bool MConnection::Cancel()
{
	if(m_pConn==NULL)
	{
		//m_sErrorMessage
        m_sErrorMessage=L"Connectin is not available!";
		return false;
	}
	
	try
	{
		HRESULT hRsut=m_pConn->Cancel();
		if(SUCCEEDED(hRsut))
		{
			return true;
		}
		else
		{
			//m_sErrorMessage
			m_sErrorMessage=L"Failed to cancel!";
			return false;
		}
	}
	catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: Cancel()!";
		return false;	
	}
}


//Release
void MConnection::Release()
{
	if(m_pConn!=NULL)
	{
		try
		{
            Close();
			m_pConn.Release();
			m_pConn=NULL;
		}
		catch(_com_error e)
		{
            throw e;
		}
	}
}


//BeginTrans
long MConnection::BeginTrans()
{
	return m_pConn->BeginTrans();
}


//CommitTrans
bool  MConnection::CommitTrans()
{
	if(m_pConn==NULL)
	{
		//m_sErrorMessage
        m_sErrorMessage=L"Connectin is not available!";
		return false;
	}
	
	try
	{
		HRESULT hRsut=m_pConn->CommitTrans();
		if(SUCCEEDED(hRsut))
		{
			return true;
		}
		else
		{
			//m_sErrorMessage
			m_sErrorMessage=L"Failed to commit the tranction!";
			return false;
		}
	}
	catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: CommitTrans()!";
		return false;	
	}
}


//RollbackTrans
bool MConnection::RollbackTrans()
{
	if(m_pConn==NULL)
	{
		//m_sErrorMessage
        m_sErrorMessage=L"Connectin is not available!";
		return false;
	}
	
	try
	{
		HRESULT hRsut=m_pConn->RollbackTrans();
		if(SUCCEEDED(hRsut))
		{
			return true;
		}
		else
		{
			//m_sErrorMessage
			m_sErrorMessage=L"Failed to rollback the tranction!";
			return false;
		}
	}
	catch(_com_error e)
	{
		//m_sErrorMessage
		m_sErrorMessage=L"There is an error when called then function: RollbackTrans()!";
		return false;	
	}

}