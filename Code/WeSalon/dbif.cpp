//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.
#define _CRT_SECURE_NO_WARNINGS
#include "dbif.h"
#include "ManageDlg.h"
#include "ViewDlg.h"
CString useruid;
Reply *curreply;
Activity *curact;
PGconn *g_conn;
typedef PGresult pgr;
pgr *AssertSql(const char *s){
	pgr *res = PQexec(g_conn, s);
	auto t = PQresultStatus(res);
	if (t == PGRES_BAD_RESPONSE || t == PGRES_FATAL_ERROR){
		char *s1 = PQerrorMessage(g_conn);
		//MessageBox(0, A2W(s), _T("Error Executing"), MB_OK);
		FILE *f = fopen("dberror.log", "w");
		fprintf(f, "YJ: %s\nError: %s\n", s, s1);
		fclose(f);
		PQfinish(g_conn);
		PQclear(res);
		exit(0);
	}
	return res;
}
bool LogIn(const CString &username, const CString &password){
	//Verify and set "useruid" variable.
	if (username.GetLength() > 20 || password.GetLength() > 30)
		return false;
	char p[200];
	sprintf(p, "SELECT * FROM USERL WHERE USERNAME = '%s';", (CStringA)username);
	pgr *res = AssertSql(p);
	if (!PQntuples(res)){
		PQclear(res);
		return false;
	}
	if (strcmp((CStringA)password, PQgetvalue(res, 0, 1)))
		return false;
	useruid = username;
	return true;
}
bool Register(const CString &username, const CString &password){
	//Verify and set "useruid" variable.
	//MessageBox "Success Register"
	if (username.GetLength() > 20 || password.GetLength() > 30)
		return false;
	char p[200];
	sprintf(p, "SELECT * FROM USERL WHERE USERNAME = '%s';", (CStringA)username);
	pgr *res = AssertSql(p);
	if (PQntuples(res)){
		PQclear(res);
		return false;
	}
	PQclear(res);
	sprintf(p, "INSERT INTO USERL VALUES ('%s', '%s')", (CStringA)username, (CStringA)password);
	PQclear(AssertSql(p));
	useruid = username;
	return true;
}
void Initilize(){
	//Connect, If no db create.
	const char *connInfo = "user=postgres password=patrick+ dbname=postgres";
	g_conn = PQconnectdb(connInfo);
	if (PQstatus(g_conn) == CONNECTION_BAD){
		MessageBox(0, _T("Failed to connect database xD"), _T("Error"), MB_OK);
		exit(1);
	}
	pgr *res = PQexec(g_conn, "SELECT * FROM USERL;");
	if (PQresultStatus(res) == PGRES_FATAL_ERROR){
		/*
		char *s = PQerrorMessage(g_conn);
		FILE *f = fopen("output.txt", "w");
		fprintf(f, s);
		fprintf(f, "\nTTT %d %d\n", PQresultStatus(res), PGRES_COMMAND_OK);
		fclose(f);
		PQfinish(g_conn);
		PQclear(res);
		exit(0);
		*/
		MessageBox(0, _T("New database created"), _T("Create"), MB_OK);
		const char *p1 =
			"CREATE TABLE USERL(" \
				"USERNAME VARCHAR(20) NOT NULL UNIQUE,"\
				"USERPASSWORD VARCHAR(30) NOT NULL,"\
				"PRIMARY KEY (USERNAME)"\
			");";
		const char *p2 =
			"CREATE TABLE ACTIVITY("\
				"ACTNAME VARCHAR(20) NOT NULL UNIQUE,"\
				"USERNAME VARCHAR(20) NOT NULL,"\
				"STATUS VARCHAR(20) NOT NULL CHECK (STATUS IN ('Voting', 'Coming Soon', 'Ongoing', 'Finished')),"\
				"STTIME BIGINT NOT NULL,"\
				"FNTIME BIGINT NOT NULL CHECK (FNTIME >= STTIME),"\
				"LOCATION VARCHAR(30) NOT NULL,"\
				"CAPACITY INTEGER NOT NULL,"\
				"DESCRIPTION VARCHAR(500),"\
				"PRIMARY KEY (ACTNAME),"\
				"FOREIGN KEY (USERNAME) REFERENCES USERL (USERNAME) ON DELETE CASCADE ON UPDATE CASCADE"\
			");";
		const char *p3 =
			"CREATE TABLE PARTICIPATION("\
				"PARTIUID SERIAL NOT NULL UNIQUE,"\
				"ACTNAME VARCHAR(20) NOT NULL,"\
				"USERNAME VARCHAR(20) NOT NULL,"\
				"PRIMARY KEY (PARTIUID),"\
				"FOREIGN KEY (USERNAME) REFERENCES USERL (USERNAME) ON DELETE CASCADE ON UPDATE CASCADE,"\
				"FOREIGN KEY (ACTNAME) REFERENCES ACTIVITY (ACTNAME) ON DELETE CASCADE ON UPDATE CASCADE"\
			");";
		const char *p4 =
			"CREATE TABLE COMMENT("\
				"COMUID SERIAL NOT NULL UNIQUE,"\
				"USERNAME VARCHAR(20) NOT NULL,"\
				"ACTNAME VARCHAR(20) NOT NULL,"\
				"REPLYTO INTEGER,"\
				"CONTENT VARCHAR(1000) NOT NULL,"\
				"PRIMARY KEY (COMUID),"\
				"FOREIGN KEY (USERNAME) REFERENCES USERL (USERNAME) ON UPDATE CASCADE,"\
				"FOREIGN KEY (ACTNAME) REFERENCES ACTIVITY (ACTNAME) ON UPDATE CASCADE,"\
				"FOREIGN KEY (REPLYTO) REFERENCES COMMENT (COMUID) ON UPDATE CASCADE"\
			");";
		PQclear(AssertSql(p1));
		PQclear(AssertSql(p2));
		PQclear(AssertSql(p3));
		PQclear(AssertSql(p4));
	}
	PQclear(res);
}
void FinishConnection(){
	//MessageBox(0, _T("Finish"), _T("TT"), MB_OK);
	//PQfinish(g_conn);
}
void GetActivity(const CString &keyword,
	Activity *resA, int &resN, bool useuuid){
	//Get activity with keyword.
	//Store in resA.
	//Role: Participant, Holder, N/A
	//useuuid: Get activities about the user
	char p[300], tmp[200];
	sprintf(p, "SELECT * FROM ACTIVITY");
	if (useuuid){
		sprintf(tmp, " WHERE (USERNAME = '%s' OR EXISTS(SELECT * FROM PARTICIPATION WHERE USERNAME = '%s'))", (CStringA)useruid, (CStringA)useruid);
		strcat(p, tmp);
	}
	if (keyword.GetLength()){
		strcat(p, useuuid ? " AND" : " WHERE");
		sprintf(tmp, " (ACTNAME LIKE '%%%s%%' OR LOCATION LIKE '%%%s%%' OR DESCRIPTION LIKE '%%%s%%')", (CStringA)keyword, (CStringA)keyword, (CStringA)keyword);
		strcat(p, tmp);
	}
	pgr *res = AssertSql(p);
	resN = PQntuples(res);
	/*
	FILE *f = fopen("dbcheck.log", "w");
	fprintf(f, "%d\n", resN);
	fclose(f);
	*/
	for (int i = 0; i < resN; ++i){
		resA[i].name = (CString)(CStringA)PQgetvalue(res, i, 0);
		resA[i].loca = (CString)(CStringA)PQgetvalue(res, i, 5);
		resA[i].desc = (CString)(CStringA)PQgetvalue(res, i, 7);
		resA[i].status = (CString)(CStringA)PQgetvalue(res, i, 2);
		stoitrans((CString)(CStringA)PQgetvalue(res, i, 3), resA[i].sttime);
		stoitrans((CString)(CStringA)PQgetvalue(res, i, 4), resA[i].fntime);
		stoitrans((CString)(CStringA)PQgetvalue(res, i, 6), resA[i].maxnum);
		sprintf(p, "SELECT COUNT(*) FROM PARTICIPATION WHERE ACTNAME = '%s';", PQgetvalue(res, i, 0));
		pgr *res2 = AssertSql(p);
		stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), resA[i].curnum);
		PQclear(res2);
		if ((CString)(CStringA)PQgetvalue(res, i, 1) == useruid){
			resA[i].role = _T("Holder"); continue;
		}
		sprintf(p, "SELECT * FROM PARTICIPATION WHERE ACTNAME = '%s' AND USERNAME = '%s';", PQgetvalue(res, i, 0), (CStringA)useruid);
		pgr *res1 = AssertSql(p);
		resA[i].role = PQntuples(res1) ? _T("Participant") : _T("N/A");
		PQclear(res1);
	}
	PQclear(res);
}

void InsertList(CListCtrl *p, Activity *act, int nact){
	//Insert activities into insertlist
	//First we have to clear the list so we have to 
	while (p->GetItemCount()) p->DeleteItem(0);
	/*
	FILE *f = fopen("insert.log", "w");
	fprintf(f, "%d\n", nact);
	fclose(f);
	*/
	for (int i = 0; i < nact; ++i){
		p->InsertItem(i, act[i].name);
		p->SetItemText(i, 1, act[i].status);
		CTime st = lltotime(act[i].sttime), fn = lltotime(act[i].fntime);
		p->SetItemText(i, 2, st.Format("%Y-%m-%d %H:%M:%S"));
		p->SetItemText(i, 3, fn.Format("%Y-%m-%d %H:%M:%S"));
		p->SetItemText(i, 4, act[i].loca);
		CString tmp;
		tmp.Format(_T("%d/%d"), act[i].curnum, act[i].maxnum);
		p->SetItemText(i, 5, tmp);
		p->SetItemText(i, 6, act[i].role);
	}
}

double GetRatio(const CString &s){
	int p = s.Find('/'), r1 = 0.3, r2;
	stoitrans(s.Left(p), r1);
	stoitrans(s.Right(s.GetLength() - p - 1), r2);
	//FILE *f1 = fopen("de1.log", "w");
	//fprintf(f1, "%s, %.3lf\n", (CStringA)s, 1.0 * r1 / r2);
	return 1.0 * r1 / r2;
}

CString turn(const CString &s, int len){
	CString t = s.Left(len);
	t.Replace(_T("'"), _T("''"));
	return t;
}

int CALLBACK CompareFunc1(LPARAM l1, LPARAM l2, LPARAM l3){
	//Dialogue: ManageDlg
	ManageDlg *p = (ManageDlg*)l3;
	CListCtrl *q = &p->m_list;
	CString s1 = q->GetItemText(l1, p->sortid);
	CString s2 = q->GetItemText(l2, p->sortid);
	int res = p->stflg[p->sortid], res1;
	if (p->sortid != 5) res1 = s1 < s2 ? -1 : 1;
	else res1 = GetRatio(s1) < GetRatio(s2) ? -1 : 1;
	return res * res1;
}

int CALLBACK CompareFunc2(LPARAM l1, LPARAM l2, LPARAM l3){
	//Dialogue: ViewDlg
	ViewDlg *p = (ViewDlg*)l3;
	CListCtrl *q = &p->m_list;
	CString s1 = q->GetItemText(l1, p->sortid);
	CString s2 = q->GetItemText(l2, p->sortid);
	int res = p->stflg[p->sortid], res1;
	if (p->sortid != 5) res1 = s1 < s2 ? -1 : 1;
	else res1 = GetRatio(s1) < GetRatio(s2) ? -1 : 1;
	return res * res1;
}

CString GetReplyString(){
	//Get reply string like below with curreply.
	//return _T("Reply to DSB #250");
	CString s1, s2;
	s1 = _T("Reply to ") + curreply->user;
	s2.Format(_T(" #%d:"), curreply->uuid);
	return s1 + s2;
}

CString GetTitle(){
	//Get activity name with curact.
	return curact->name;
}

CString GetDesc(){
	return curact->desc;
}

void DeleteAct(){
	//Delete Activity* and all relations
	char p[200];
	sprintf(p, "DELETE FROM ACTIVITY WHERE ACTNAME = '%s'", (CStringA)curact->name);
	PQclear(AssertSql(p));
}

void QuitAct(){
	//Participant quits act
	char p[200];
	sprintf(p, "DELETE FROM PARTICIPATION WHERE ACTNAME = '%s' AND USERNAME = '%s';", (CStringA)curact->name, (CStringA)useruid);
	PQclear(AssertSql(p));
}

bool JoinInAct(){
	//Join in act, check full or not
	char p[200];
	sprintf(p, "SELECT COUNT(*) FROM PARTICIPATION WHERE ACTNAME = '%s';", (CStringA)curact->name);
	pgr *res2 = AssertSql(p);
	int curn;
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	PQclear(res2);
	if (curn >= curact->maxnum) return false;
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE"\
		" ACTNAME IN (SELECT ACTNAME FROM PARTICIPATION WHERE USERNAME = '%s')"\
		" AND ((STTIME <= %d AND FNTIME >= %d) OR (STTIME <= %d AND FNTIME >= %d));",
		(CStringA)useruid, curact->sttime, curact->sttime, curact->fntime, curact->fntime);
	res2 = AssertSql(p);
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	PQclear(res2);
	if (curn) return false;
	sprintf(p, "INSERT INTO PARTICIPATION (ACTNAME, USERNAME) VALUES ('%s', '%s');", (CStringA)curact->name, (CStringA)useruid);
	PQclear(AssertSql(p));
	return true;
}

CString GetRepStr(Reply *rep = curreply){
	CString s1, s2, res;
	s1.Format(_T("%d"), rep->uuid);
	s2.Format(_T("%d"), rep->replyto);
	res = _T("Reply id: #") + s1
		+ _T("\r\nEstablisher: ") + rep->user
		+ _T("\r\nActivity: ") + rep->act;
	if (~rep->replyto)
		res = res + _T("\r\nReply to: #") + s2;
	res = res + _T("\r\nContent: ") + rep->content;
	return res;
	//return _T("Fuck");
}

bool stoitrans(const CString &s, int &x){
	x = 0;
	for (int i = 0, l = s.GetLength(); i < l; ++i)
		if ('0' <= s[i] && s[i] <= '9') x = x * 10 + s[i] - '0';
		else return false;
	return s.GetLength();
}

bool ApplyActivity(const Activity &act){
	//New uuid, check conflict, name unique
	char p[700];
	CString s0 = turn(act.name, 20);
	CString s1 = turn(act.loca, 30), s2 = turn(act.desc, 500);
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE ACTNAME = '%s';", (CStringA)s0);
	pgr *res2 = AssertSql(p);
	int curn;
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	if (curn) return false;
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE LOCATION = '%s' AND "\
		"((STTIME <= %d AND FNTIME >= %d) OR (STTIME <= %d AND FNTIME >= %d));",
		(CStringA)s1, act.sttime, act.sttime, act.fntime, act.fntime);
	res2 = AssertSql(p);
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	if (curn) return false;
	sprintf(p, "INSERT INTO ACTIVITY VALUES ('%s', '%s', '%s', %d, %d, '%s', %d, '%s');",
		(CStringA)s0, (CStringA)useruid, (CStringA)act.status, act.sttime, act.fntime, (CStringA)s1, act.maxnum, (CStringA)s2);
	PQclear(AssertSql(p));
	return true;
}

bool ModifyActivity(const Activity &act){
	//Modify with uuid, name unique
	char p[700];
	CString s0 = turn(act.name, 20);
	CString s1 = turn(act.loca, 30), s2 = turn(act.desc, 500);
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE LOCATION = '%s' AND "\
		"((STTIME <= %d AND FNTIME >= %d) OR (STTIME <= %d AND FNTIME >= %d));",
		(CStringA)s1, act.sttime, act.sttime, act.fntime, act.fntime);
	pgr *res2 = AssertSql(p); int curn;
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	if (curn > 1) return false;
	sprintf(p, "UPDATE ACTIVITY SET STATUS = '%s', STTIME = %d, FNTIME = %d, LOCATION = '%s',"\
		"CAPACITY = %d, DESCRIPTION = '%s' WHERE ACTNAME = '%s';",
		(CStringA)act.status, act.sttime, act.fntime, (CStringA)s1, act.maxnum, (CStringA)s2, (CStringA)s0);
	PQclear(AssertSql(p));
	return true;
}

void GetReplies(const CString &key, Reply *rep, int &nrep){
	char p[1000], tmp[1000];
	sprintf(p, "SELECT * FROM COMMENT");
	if (key.GetLength()){
		sprintf(tmp, " WHERE USERNAME LIKE '%%%s%%' OR ACTNAME LIKE '%%%s%%' OR CONTENT LIKE '%%%s%%';",
			(CStringA)key, (CStringA)key, (CStringA)key);
		strcat(p, tmp);
	}
	pgr *res = AssertSql(p);
	nrep = PQntuples(res);
	for (int i = 0; i < nrep; ++i){
		stoitrans((CString)(CStringA)PQgetvalue(res, i, 0), rep[i].uuid);
		if (!stoitrans((CString)(CStringA)PQgetvalue(res, i, 3), rep[i].replyto)) rep[i].replyto = -1;
		rep[i].user = (CString)(CStringA)PQgetvalue(res, i, 1);
		rep[i].act = (CString)(CStringA)PQgetvalue(res, i, 2);
		rep[i].content = (CString)(CStringA)PQgetvalue(res, i, 4);
	}
}

void InsertReply(const Reply &rep){
	//The user and uuid remain unfilled. user=useruid
	//replyto == -1 means reply to activity.
	char p[1200];
	CString s0 = turn(rep.content, 1000);
	if (~rep.replyto){
		sprintf(p, "INSERT INTO COMMENT (USERNAME, ACTNAME, REPLYTO, CONTENT) VALUES"\
			" ('%s', '%s', %d, '%s')", (CStringA)useruid, (CStringA)rep.act, rep.replyto, (CStringA)s0);
	} else {
		sprintf(p, "INSERT INTO COMMENT (USERNAME, ACTNAME, CONTENT) VALUES"\
			" ('%s', '%s', '%s')", (CStringA)useruid, (CStringA)rep.act, (CStringA)s0);
	}
	PQclear(AssertSql(p));
}

bool FindAct(const CString &s){
	char p[200];
	CString s0 = turn(s, 20);
	/*
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE ACTNAME = '%s' AND STATUS = 'Finished'"\
		" AND EXISTS(SELECT * FROM PARTICIPATION WHERE ACTNAME = '%s' AND USERNAME = '%s');",
		(CStringA)s0, (CStringA)s0, (CStringA)useruid);
	*/
	sprintf(p, "SELECT COUNT(*) FROM ACTIVITY WHERE ACTNAME = '%s';", (CStringA)s0);
	pgr *res2 = AssertSql(p);
	int curn;
	stoitrans((CString)(CStringA)PQgetvalue(res2, 0, 0), curn);
	return curn;
}

int timetoll(const CTime &dt, const CTime &tm){
	CTime curT(dt.GetYear(), dt.GetMonth(), dt.GetDay(),
		tm.GetHour(), tm.GetMinute(), tm.GetSecond());
	static CTime orig(2020, 1, 1, 0, 0, 0);
	CTimeSpan tmp = curT - orig;
	return tmp.GetTotalSeconds();
}

CTime lltotime(int x){
	CTimeSpan t(0, 0, 0, x);
	static CTime orig(2020, 1, 1, 0, 0, 0);
	return orig + t;
}

void _debug(int x){
	/*
	FILE *f = fopen("debugger.log", "w");
	fprintf(f, "%d\n", x);
	fclose(f);
	*/
}