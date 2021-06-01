//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.
#pragma once
#include <libpq-fe.h>
#include <afxdialogex.h>
bool LogIn(const CString&, const CString&);
bool Register(const CString&, const CString&);
void Initilize();
struct Activity{
	CString name, status, loca, desc, role;
	int maxnum, curnum, sttime, fntime;
} ;
struct Reply{
	CString user, act, content;
	int uuid, replyto;
} ;
void GetActivity(const CString&, Activity*, int &, bool);
void InsertList(CListCtrl*, Activity*, int);
int CALLBACK CompareFunc1(LPARAM, LPARAM, LPARAM);
int CALLBACK CompareFunc2(LPARAM, LPARAM, LPARAM);
CString GetReplyString();
CString GetTitle();
CString GetDesc();
void DeleteAct();
void QuitAct();
bool JoinInAct();
CString GetRepStr(Reply *);
bool stoitrans(const CString &, int &);
bool ApplyActivity(const Activity &);
bool ModifyActivity(const Activity &);
void GetReplies(const CString &, Reply *, int &);
void InsertReply(const Reply &);
bool FindAct(const CString &);
int timetoll(const CTime &, const CTime &);
CTime lltotime(int);
void FinishConnection();
void _debug(int);
extern CString useruid;
extern Activity *curact;
extern Reply *curreply;
const int MAX_ACT = 20000, MAX_REP = 100000;
