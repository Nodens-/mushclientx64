// chatlistensock.cpp : implementation file
//

// But does it get goat's blood out?



#include "stdafx.h"
#include "MUSHclient.h"
#include "doc.h"

#include <stddef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CChatListenSocket, CAsyncSocket)

CChatListenSocket::CChatListenSocket(CMUSHclientDoc* pDoc)
{
	m_pDoc = pDoc;

}   // end of constructor

CChatListenSocket::~CChatListenSocket()
{

	// cancel callbacks for closed sockets

	Close();

}     // end of destructor

void CChatListenSocket::OnAccept(int nErrorCode)
{

	m_pDoc->ChatNote(eChatConnection, "Incoming chat call");

	CChatSocket* pSocket = new CChatSocket(m_pDoc);
	int SockAddrLen = sizeof(pSocket->m_ServerAddr);

	/*We disable "Don't use reinterpret_cast" warning for this particular piece of code
	* because this is the proper way do this, according to the BSD socket API -- Nodens
	*/
	#pragma warning( push )
	#pragma warning( disable : 26490)
	if (!Accept(*pSocket,
		reinterpret_cast<SOCKADDR*> (&pSocket->m_ServerAddr),
		&SockAddrLen))
	{
		m_pDoc->ChatNote(eChatConnection, "Cannot accept call.");
		delete pSocket;
		return;
	}
	#pragma warning( pop ) 
	pSocket->AsyncSelect();
	pSocket->m_bIncoming = true;

	pSocket->m_strServerName = inet_ntoa(pSocket->m_ServerAddr.sin_addr);


	m_pDoc->ChatNote(eChatConnection,
		TFormat(
			"Accepted call from %s port %d",
			(LPCTSTR) pSocket->m_strServerName,
			ntohs(pSocket->m_ServerAddr.sin_port)));

	m_pDoc->m_ChatList.AddTail(pSocket);

	pSocket->m_iChatStatus = eChatAwaitingConnectionRequest;
} // end of OnAccept


