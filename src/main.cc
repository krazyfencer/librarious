#include <iostream>
#include <sqlite3.h>
using namespace std;

bool execStmt(sqlite3 *db, const string & strStmt)
{
  sqlite3_stmt *stmt = NULL;
  
  if ( sqlite3_prepare_v2(db, strStmt.c_str(), strStmt.size() + 1, &stmt, NULL) != SQLITE_OK )
    {
      cerr << "-- error: preparing stmt " << strStmt << ": "
	   << sqlite3_errmsg(db) << endl;
      return false;
    }

  bool keepTrying = true;
  while ( keepTrying )
    {
      switch ( sqlite3_step(stmt) )
	{
	case SQLITE_BUSY:
	  // keep trying
	  continue;
	case SQLITE_DONE:
	  // all done
	  keepTrying = false;
	  break;
	case SQLITE_ROW:
	  // got a row, keep going
	  continue;
	case SQLITE_MISUSE:
	case SQLITE_ERROR:
	default:
	  cerr << "-- error: preparing stmt " << strStmt << ": "
	       << sqlite3_errmsg(db) << endl;
	  sqlite3_finalize(stmt);
	  return false;  
	}
    }
  
  sqlite3_finalize(stmt);
  return true;  
}

void prepareTables(sqlite3 *db)
{
  execStmt(db, "CREATE TABLE IF NOT EXISTS `bob` (x varchar(255), y varchar(255));"); 
}

int main(int argc, char **argv)
{
  sqlite3 *db = NULL;
  if ( sqlite3_open("books.db", &db) != SQLITE_OK )
    {
      cerr << argv[0] << " -- error: " << sqlite3_errmsg(db) << endl;
      return 1;
    }

  prepareTables(db);
  cout << "hello world" << endl;

  sqlite3_close(db);
  return 0;
}
