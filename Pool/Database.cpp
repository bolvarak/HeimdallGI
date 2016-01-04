///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Database.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Pool Namespace ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace Pool
	{
		///////////////////////////////////////////////////////////////////////
		/// Public Static Methods ////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		bool Database::add(QString strDriver, QString strHost, int intPort, QString strDatabase, QString strUsername, QString strPassword, QString strConnectionName)
		{
			// Add the new connection
			QSqlDatabase dbConnection = QSqlDatabase::addDatabase(strDriver, strConnectionName.isEmpty() ? QSqlDatabase::defaultConnection : strConnectionName);
			// Set the host name
			dbConnection.setHostName(strHost);
			// Set the host port
			dbConnection.setPort(intPort);
			// Set the database name
			dbConnection.setDatabaseName(strDatabase);
			// Set the database username
			dbConnection.setUserName(strUsername);
			// Set the database password
			dbConnection.setPassword(strPassword);
			// Try to open the connection
			if (!dbConnection.open()) {
				// We're done
				qFatal(QString("HeimdallGI::Pool::Database::add():  %1").arg(dbConnection.lastError().text()).toLatin1().constData());
				// We're done
				return false;
			}
			// We're done
			return true;
		}

		QSqlDatabase Database::get(QString strConnectionName)
		{
			// Return the connection
			return QSqlDatabase::database(strConnectionName.isEmpty() ? QSqlDatabase::defaultConnection : strConnectionName, true);
		}

		void Database::remove(QString strConnectionName)
		{
			// Check for a connection name
			if (strConnectionName.isEmpty() == false) {
				// Remove the default connection
				return QSqlDatabase::removeDatabase(strConnectionName);
			}
		}
	}
}
