///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DBI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DBI* DBI::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Status Codes /////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int DBI::StatusColumnsSet                 = 0x011;
	int DBI::StatusComplete                   = 0x008;
	int DBI::StatusDeleteBuildStarted         = 0x004;
	int DBI::StatusError                      = 0x000;
	int DBI::StatusGroupingSet                = 0x013;
	int DBI::StatusInsertBuildStarted         = 0x005;
	int DBI::StatusJoinsSet                   = 0x012;
	int DBI::StatusKeyValuePairsSet           = 0x010;
	int DBI::StatusLimitSet                   = 0x015;
	int DBI::StatusOrderSet                   = 0x014;
	int DBI::StatusSelectBuildStarted         = 0x006;
	int DBI::StatusStarted                    = 0x001;
	int DBI::StatusTableAliasSet              = 0x003;
	int DBI::StatusTableSet                   = 0x002;
	int DBI::StatusUpdateBuildStarted         = 0x007;
	int DBI::StatusWhereClauseSet             = 0x009;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString DBI::AndCondition                 = "AND";
	QString DBI::AscendingOrder               = "ASC";
	QString DBI::DeleteQuery                  = "DELETE FROM :sTable :sWhere;";
	QString DBI::DescendingOrder              = "DESC";
	QString DBI::DriverDB2                    = "QDB2";
	QString DBI::DriverInterBase              = "QIBASE";
	QString DBI::DriverMySQL                  = "QMYSQL";
	QString DBI::DriverMySQL3                 = "QMYSQL3";
	QString DBI::DriverOCI                    = "QOCI";
	QString DBI::DriverODBC                   = "QODBC";
	QString DBI::DriverPostgreSQL             = "QPSQL";
	QString DBI::DriverPostgreSQL7            = "QPSQL7";
	QString DBI::DriverSQLite                 = "QSQLITE";
	QString DBI::DriverSQLite2                = "QSQLITE2";
	QString DBI::DriverSybase                 = "QTDS";
	QString DBI::EqualityOperator             = "=";
	QString DBI::FullJoinQuery                = "FULL JOIN :sJoinTable :sAsAlias ON (:sJoinAlias.:sJoinField = :sFromAlias.:sFromField)";
	QString DBI::GreaterThanOperator          = ">";
	QString DBI::GreaterThanOrEqualToOperator = ">=";
	QString DBI::InnerJoinQuery               = "INNER JOIN :sJoinTable :sAsAlias ON (:sJoinAlias.:sJoinField = :sFromAlias.:sFromField)";
	QString DBI::InsertQuery                  = "INSERT INTO :sTable (:aFields) VALUES (:aValues);";
	int DBI:: InterfaceMSSQL                  = 0x001;
	int DBI:: InterfaceMySQL                  = 0x002;
	int DBI:: InterfaceOCI                    = 0x003;
	int DBI:: InterfacePgSQL                  = 0x004;
	QString DBI::LeftJoinQuery                = "LEFT JOIN :sJoinTable :sAsAlias ON (:sJoinAlias.:sJoinField = :sFromAlias.:sFromField)";
	QString DBI::LikeOperator                 = "LIKE";
	QString DBI::LessThanOperator             = "<";
	QString DBI::LessThatOrEqualToOperator    = "<";
	QString DBI::MSSQLWrapper                 = "[:sEntityName]";
	QString DBI::MySQLWrapper                 = "`:sEntityName`";
	QString DBI::NotEqualToOperator           = "<>";
	QString DBI::OCIWrapper                   = ":sEntityName";
	QString DBI::OrCondition                  = "OR";
	QString DBI::PgSQLWrapper                 = "\":sEntityName\"";
	QString DBI::RightJoinQuery               = "RIGHT JOIN :sJoinTable :sAsAlias ON (:sJoinAlias.:sJoinField = :sFromAlias.:sFromField)";
	QString DBI::SelectQuery                  = "SELECT :aFields FROM :sTable :sAsAlias :aJoins :sWhere :sGroupBy :sOrderBy :sLimit;";
	QString DBI::UpdateQuery                  = "UPDATE :sTable SET :aFieldValuePairs :sWhere;";
	QString DBI::Wildcard                     = "*";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DBI* DBI::Instance(bool bReset) {
		// Check for an instance or a reset boolean
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new DBI();
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DBI::DBI(QObject* qoParent) : QObject(qoParent) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString DBI::ApplyWrapper(QString strEntity) {
		// Define the return string
		QString strReturn;
		// Determine the interface
		if (this->mInterface == DBI::InterfaceMSSQL) {        // Microsoft SQL Server
			// Store the entity
			strReturn = DBI::MSSQLWrapper;
		} else if (this->mInterface == DBI::InterfaceMySQL) { // MySQL
			// Store the entity
			strReturn = DBI::MySQLWrapper;
		} else if (this->mInterface == DBI::InterfaceOCI) {   // Oracle
			// Store the entity
			strReturn = DBI::OCIWrapper;
		} else if (this->mInterface == DBI::InterfacePgSQL) { // PostgreSQL
			// Store the entity
			strReturn = DBI::PgSQLWrapper;
		}
		// Setup the regular expression
		QRegularExpression qreFunction("^[a-zA-Z]+\\(([a-zA-Z0-9_-`'\\.]+)\\)$");
		// Grab the matches
		QRegularExpressionMatch qremFunction = qreFunction.match(strEntity);
		// Determine if this is a function call with a column name
		if (qremFunction.hasMatch()) {
			// Finalize the return string
			strReturn = strEntity.replace(qremFunction.captured(1), strReturn.replace(":sEntityName", qremFunction.captured(1)));
		} else {
			// Finalize the return string
			strReturn = strReturn.replace(":sEntityName", strEntity);
		}
		// Return the entity
		return strReturn;
	}

	void DBI::BuildDeleteQuery() {
		// Set the WHERE clause
		this->mQuery = this->mQuery.replace(":sWhere", this->BuildWhereClause());
		// Emit the signal
		this->SendStatus(DBI::StatusWhereClauseSet);
	}

	QString DBI::BuildGroupByClause() {
		// Create the column placeholder
		QStringList qslColumns;
		// Loop through the clauses
		for (QMap<QString, QVariantMap>::const_iterator itrGroupBy = this->mGroupBy.begin(); itrGroupBy != this->mGroupBy.end(); ++itrGroupBy) {
			// Define the clause
			QString strClause;
			// Grab the column
			QString strColumn     = itrGroupBy.key();
			// Load the column data
			QVariantMap qvmColumn = itrGroupBy.value();
			// Check for a table
			if (qvmColumn["strTable"].toString().isEmpty() == false) {
				// Add the table
				strClause = strClause.append(this->ApplyWrapper(qvmColumn["strTable"].toString()).append("."));
			} else {
				// Add the instance table or alias
				strClause = strClause.append(this->ApplyWrapper(this->mTableAlias.isEmpty() ? this->mTable : this->mTableAlias).append("."));
			}
			// Add the column
			strClause = strClause.append(this->ApplyWrapper(strColumn));
			// Append the column to the list
			qslColumns.append(strClause);
		}
		// Return the clause
		return (qslColumns.isEmpty() ? NULL : qslColumns.join(", ").prepend("GROUP BY "));
	}

	void DBI::BuildInsertQuery() {
		// Create the columns and values placeholder
		QStringList qslColumns, qslValues;
		// Iterate through the map
		for (QMap<QString, QVariantMap>::const_iterator itrMap = this->mColumns.begin(); itrMap != this->mColumns.end(); ++itrMap) {
			// Add the column
			qslColumns.append(this->ApplyWrapper(itrMap.key()));
			// Add the value
			qslValues.append(this->QuoteTrueValue(itrMap.value()["strValue"].toString()));
		}
		// Build the columns into the query
		this->mQuery.replace(":aFields", qslColumns.join(", "));
		// Build the values into the query
		this->mQuery.replace(":aValues", qslValues.join(", "));
		// Emit the signal
		this->SendStatus(DBI::StatusKeyValuePairsSet);
	}

	QString DBI::BuildJoins() {
		// Create the JOIN statement
		QStringList qslJoins;
		// Iterate through the joins
		for (int intJoin = 0; intJoin < this->mJoins.size(); ++intJoin) {
			// Localize the current join statement
			QVariantMap qvmJoin = this->mJoins.at(intJoin);
			// Set the query statement
			QString strQuery    = qvmJoin["strJoinType"].toString();
			// Build the join statement
			strQuery            = strQuery.replace(":sJoinTable", this->ApplyWrapper(qvmJoin["strJoinTable"].toString())); // Joining Table
			strQuery            = strQuery.replace(":sJoinField", this->ApplyWrapper(qvmJoin["strJoinField"].toString())); // Joining Table Column
			strQuery            = strQuery.replace(":sFromField", this->ApplyWrapper(qvmJoin["strFromField"].toString())); // The Originating Table Column
			// Check for a joining table alias
			if (qvmJoin["strJoinTableAlias"].toString().isEmpty()) {
				// Set the Aliases to the table name
				strQuery        = strQuery.replace(":sAsAlias", "");                                                       // Join Table Alias
				strQuery        = strQuery.replace(":sJoinAlias", this->ApplyWrapper(qvmJoin["strJoinTable"].toString())); // Join Table Name
			} else {
				// Set the table name to the aliases
				strQuery        = strQuery.replace(":sAsAlias", QString("AS ").append(this->ApplyWrapper(qvmJoin["strJoinTableAlias"].toString()))); // Join Table Alias
				strQuery        = strQuery.replace(":sJoinAlias", this->ApplyWrapper(qvmJoin["strJoinTableAlias"].toString()));                       // Join Table Name
			}
			// Add the table alias
			strQuery            = strQuery.replace(":sFromAlias", this->ApplyWrapper(this->mTableAlias.isEmpty() ? this->mTable : this->mTableAlias));
			// Append the JOIN to the list
			qslJoins.append(strQuery);
		}
		// Return the JOIN statements
		return qslJoins.join(" ");
	}

	QString DBI::BuildLimitClause() {
		// Create the LIMIT clause placeholder
		QString strLimit;
		// Check for a LIMIT clause
		if (this->mLimits.isEmpty() == false) {
			// Initialize the LIMIT clause
			strLimit = this->mLimits.join(",").prepend("LIMIT ");
		}
		// Return the LIMIT clause
		return strLimit;
	}

	QString DBI::BuildOrderByClause() {
		// Define the clause list
		QStringList qslOrderBy;
		// Loop through the columns
		for (QMap<QString, QVariantMap>::const_iterator itrColumn = this->mGroupBy.begin(); itrColumn != this->mGroupBy.end(); ++itrColumn) {
			// Create the clause string
			QString strClause;
			// Localize the column
			QString strColumn     = itrColumn.key();
			// Localize the properties
			QVariantMap qvmColumn = itrColumn.value();
			// Check for a table
			if (qvmColumn["strTable"].toString().isEmpty() == false) {
				// Add the table
				strClause = strClause.append(this->ApplyWrapper(qvmColumn["strTable"].toString()).append("."));
			} else {
				// Add the table or alias
				strClause = strClause.append(this->ApplyWrapper(this->mTableAlias.isEmpty() ? this->mTable : this->mTableAlias).append("."));
			}
			// Add the column to the clause
			strClause = strClause.append(this->ApplyWrapper(strColumn).append(" "));
			// Add the direction to the clause
			strClause = strClause.append(qvmColumn["strDirection"].toString());
			// Append the clause to the list
			qslOrderBy.append(strClause);
		}
		// Return the clause
		return (qslOrderBy.isEmpty() ? NULL : qslOrderBy.join(", ").prepend("ORDER BY "));
	}

	void DBI::BuildSelectQuery() {
		// Create a columns placeholder
		QStringList qslColumns;
		// Iterate through the columns
		for (QMap<QString, QVariantMap>::const_iterator itrColumns = this->mColumns.begin(); itrColumns != this->mColumns.end(); ++itrColumns) {
			// Define the current column
			QString strCurrentColumn                    = "";
			// Define the column name
			QString strColumn                           = itrColumns.key();
			// Define the column properties
			QVariantMap qvmProperties                   = itrColumns.value();
			// Check for a table
			if (qvmProperties["strTable"].toString().isEmpty() == false) {
				// Add the table
				strCurrentColumn = strCurrentColumn.append(this->ApplyWrapper(qvmProperties["strTable"].toString()).append("."));
			}
			// Add the actual column
			strCurrentColumn     = strCurrentColumn.append(strColumn == DBI::Wildcard ? DBI::Wildcard : this->ApplyWrapper(strColumn));
			// Check for an alias
			if (qvmProperties["strAlias"].toString().isEmpty() == false) {
				// Set the column alias
				strCurrentColumn = strCurrentColumn.append(QString(" AS ").append(this->ApplyWrapper(qvmProperties["strAlias"].toString())));
			}
			// Append the column to the list
			qslColumns.append(strCurrentColumn);
		}
		// Build the query, starting with the columns
		this->mQuery = this->mQuery.replace(":aFields", qslColumns.join(", "));
		// Emit the signal
		this->SendStatus(DBI::StatusColumnsSet);
		// Set the WHERE clause
		this->mQuery = this->mQuery.replace(":sWhere", this->BuildWhereClause());
		// Emit the signal
		this->SendStatus(DBI::StatusWhereClauseSet);
		// Set the JOIN statements
		this->mQuery = this->mQuery.replace(":aJoins", this->BuildJoins());
		// Emit the signal
		this->SendStatus(DBI::StatusJoinsSet);
		// Set the GROUP BY clause
		this->mQuery = this->mQuery.replace(":sGroupBy", this->BuildGroupByClause());
		// Emit the signal
		this->SendStatus(DBI::StatusGroupingSet);
		// Set the ORDER BY clause
		this->mQuery = this->mQuery.replace(":sOrderBy", this->BuildOrderByClause());
		// Emit the signal
		this->SendStatus(DBI::StatusOrderSet);
		// Set the LIMIT clause
		this->mQuery = this->mQuery.replace(":sLimit", this->BuildLimitClause());
		// Emit the signal
		this->SendStatus(DBI::StatusLimitSet);
	}

	void DBI::BuildUpdateQuery() {
		// Define the columns list
		QStringList qslColumns;
		// Loop through the columns
		for (QMap<QString, QVariantMap>::const_iterator itrColumns = this->mColumns.begin(); itrColumns != this->mColumns.end(); ++itrColumns) {
			// Define the current pair
			QString strPair                             = "";
			// Define the column
			QString strColumn                           = itrColumns.key();
			// Define the column properties
			QVariantMap qvmProperties = itrColumns.value();
			// Set the pair
			strPair = strPair.append(this->ApplyWrapper(strColumn)).append(" = ").append(this->QuoteTrueValue(qvmProperties["strValue"].toString()));
			// Append the pair to the columns list
			qslColumns.append(strPair);
		}
		// Build the query, starting with the key/value pairs
		this->mQuery = this->mQuery.replace(":aFieldValuePairs", qslColumns.join(", "));
		// Emit the signal
		this->SendStatus(DBI::StatusKeyValuePairsSet);
		// Set the WHERE clause
		this->mQuery = this->mQuery.replace(":sWhere", this->BuildWhereClause());
		// Emit the signal
		this->SendStatus(DBI::StatusWhereClauseSet);
	}

	QString DBI::BuildWhereClause() {
		// Define the clause list
		QStringList qslClauses;
		// Iterate through the WHERE clauses
		for (int intClause = 0; intClause < this->mWhereClauses.size(); ++intClause) {
			// Define the current clause
			QString strClause = "";
			// Localize the current clause
			QVariantMap qvmClause = this->mWhereClauses.at(intClause);
			// Check the index of the clause
			if (intClause > 0) {
				// Append the condition
				strClause = strClause.append(qvmClause["strCondition"].toString()).append(" ");
			}
			// Check for a table
			if (qvmClause["strTable"].toString().isEmpty() == false) {
				// Append the table
				strClause = strClause.append(this->ApplyWrapper(qvmClause["strTable"].toString()).append("."));
			}
			// Finalize the clause
			strClause = strClause.append(this->ApplyWrapper(qvmClause["strColumn"].toString()).append(" ")); // Column
			strClause = strClause.append(qvmClause["strOperator"].toString().append(" "));                   // Condition
			strClause = strClause.append(this->QuoteTrueValue(qvmClause["strValue"].toString()));            // Value
			// Append the clause
			qslClauses.append(strClause);
		}
		// Return the statement
		return (qslClauses.isEmpty() ? NULL : qslClauses.join(" ").prepend("WHERE "));
	}

	QString DBI::QuoteTrueValue(QString strValue) {
		// Setup a boolean notififer
		bool bIsNumeric = false;
		// Try for an integer
		strValue.toDouble(&bIsNumeric);
		// Check for true
		if (bIsNumeric == true) { return strValue; }
		// Try for a float
		strValue.toFloat(&bIsNumeric);
		// Check for true
		if (bIsNumeric == true) { return strValue; }
		// Escape quotes
		strValue = strValue.replace("'", "\'");
		// Quote the value
		strValue = strValue.prepend("'");
		strValue = strValue.append("'");
		// Return the value
		return strValue;
	}

	QMap<QString, QVariant> DBI::RecordToMap(QSqlRecord qsrRecord) {
		// Create the record container
		QVariantMap qvmRecord;
		// Iterate over the columns
		for (int intColumn = 0; intColumn < qsrRecord.count(); ++intColumn) {
			// Insert the field into the map
			qvmRecord.insert(qsrRecord.fieldName(intColumn), qsrRecord.value(qsrRecord.indexOf(qsrRecord.fieldName(intColumn))));
		}
		// Return the map
		return qvmRecord;
	}

	void DBI::SendStatus(int intStatusCode, QString strError) {
		// Emit the signal
		emit this->CurrentStatus(intStatusCode, this->mQuery, strError);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DBI* DBI::AddColumn(QString strColumn, QString strValue, QString strTable, QString strAlias) {
		// Define the property map
		QVariantMap qvmProperties;
		// Add the value
		qvmProperties.insert("strValue", strValue);
		// Add the table
		qvmProperties.insert("strTable", strTable);
		// Add the alias
		qvmProperties.insert("strAlias", strAlias);
		// Add the column to the instance
		this->mColumns.insert(strColumn, qvmProperties);
		// Return the instance
		return this;
	}

	DBI* DBI::AddGroupByColumn(QString strColumn, QString strTable) {
		// Setup the group by map
		QVariantMap qvmGroupBy;
		// Add the table
		qvmGroupBy.insert("strTable", strTable);
		// Add the group by column to the instance
		this->mGroupBy.insert(strColumn, qvmGroupBy);
		// Return the instance
		return this;
	}

	DBI* DBI::AddJoin(QString strJoinTable, QString strJoinField, QString strFromField, QString strJoinType, QString strJoinTableAlias) {
		// Define the property map
		QVariantMap qvmProperties;
		// Set the table to join
		qvmProperties.insert("strJoinTable", strJoinTable);
		// Set the field to join on the joining table
		qvmProperties.insert("strJoinField", strJoinField);
		// Set the field to join on from the base table
		qvmProperties.insert("strFromField", strFromField);
		// Set the JOIN type
		qvmProperties.insert("strJoinType", strJoinType);
		// Set the joining table alias
		qvmProperties.insert("strJoinTableAlias", strJoinTableAlias);
		// Add the join to the instance
		this->mJoins.append(qvmProperties);
		// Return the instance
		return this;
	}

	DBI* DBI::AddOrderBy(QString strColumn, QString strDirection, QString strTable) {
		// Create the clause map
		QVariantMap qvmClause;
		// Add the direction
		qvmClause.insert("strDirection", strDirection);
		// Add the table
		qvmClause.insert("strTable", strTable);
		// Add the clause to the instance
		this->mGroupBy.insert(strColumn, qvmClause);
		// Return the instance
		return this;
	}

	DBI* DBI::AddWhereClause(QString strColumn, QString strValue, QString strTable, QString strOperator, QString strCondition) {
		// Define the clause
		QVariantMap qvmClause;
		// Set the column
		qvmClause.insert("strColumn", strColumn);
		// Set the value
		qvmClause.insert("strValue", strValue);
		// Set the table
		qvmClause.insert("strTable", strTable);
		// Set the operator
		qvmClause.insert("strOperator", strOperator);
		// Set the condition
		qvmClause.insert("strCondition", strCondition);
		// Add the clause to the instance
		this->mWhereClauses.append(qvmClause);
		// Return the instance
		return this;
	}

	DBI* DBI::Build() {
		// Before we do anything, we want the query type
		QString strQueryType = this->mQuery;
		// Emit the signal
		this->SendStatus(DBI::StatusStarted);
		// Set the table name into the query
		this->mQuery.replace(":sTable", this->ApplyWrapper(this->mTable));
		// Emit the signal
		this->SendStatus(DBI::StatusTableSet);
		// Check for a table alias
		if (this->mTableAlias.isEmpty()) {
			// Nullify the table alias
			this->mQuery.replace(":sAsAlias", "");
		} else {
			// Set the table alias
			this->mQuery.replace(":sAsAlias", QString("AS ").append(this->ApplyWrapper(this->mTableAlias)));
		}
		// Emit the signal
		this->SendStatus(DBI::StatusTableAliasSet);
		// Determine the query type
		if (strQueryType == DBI::DeleteQuery) {       // DELETE
			// Emit the signal
			this->SendStatus(DBI::StatusDeleteBuildStarted);
			// Build the query
			this->BuildDeleteQuery();
		} else if (strQueryType == DBI::InsertQuery) { // INSERT
			// Emit the signal
			this->SendStatus(DBI::StatusInsertBuildStarted);
			// Build the query
			this->BuildInsertQuery();
		} else if (strQueryType == DBI::SelectQuery) { // SELECT
			// Emit the signal
			this->SendStatus(DBI::StatusSelectBuildStarted);
			// Build the query
			this->BuildSelectQuery();
		} else if (strQueryType == DBI::UpdateQuery) { // UPDATE
			// Emit the signal
			this->SendStatus(DBI::StatusUpdateBuildStarted);
			// Build the query
			this->BuildUpdateQuery();
		}
		// Emit the signal
		this->SendStatus(DBI::StatusComplete);
		// Return the instance
		return this;
	}

	void DBI::Execute(QString strQuery) {
		// Check for a query
		if (strQuery.isEmpty() == false) {
			// Set the query
			this->mQuery = strQuery;
		}
		// Check for a connection
		if (this->mConnection.isOpen() == false) {
			// Open the connection
			this->OpenConnection();
		}
		// Build the query
		this->Build();
		// Set the statement
		QSqlQuery* qsqQuery = new QSqlQuery(this->mConnection);
		// Execute the query
		qsqQuery->exec(this->mQuery);
		// Set the row count
		this->mRecordCount = (qsqQuery->numRowsAffected() ? qsqQuery->numRowsAffected() : qsqQuery->size());
		// Iterate over the query
		while (qsqQuery->next()) {
			qDebug() << qsqQuery;
			// Emit the signal
			this->Row(qsqQuery->record());
			// Append the record to the instance
			this->mRecords.append(QVariant(this->RecordToMap(qsqQuery->record())));
		}
	}


	DBI* DBI::OpenConnection(QString strDriver, QString strHost, int intPort, QString strUsername, QString strPassword, QString strDatabase) {
		// Add the database connection
		this->mConnection = QSqlDatabase::addDatabase(strDriver.isEmpty() ? Configuration::Get("Database.sqlDriver").toString()  : strDriver);
		// Set the hostname
		this->mConnection.setHostName(strHost.isEmpty()                   ? Configuration::Get("Database.serverHost").toString() : strHost);
		// Set the server port
		this->mConnection.setPort((intPort == 0)                          ? Configuration::Get("Database.serverPort").toInt()    : intPort);
		// Set the database name
		this->mConnection.setDatabaseName(strDatabase.isEmpty()           ? Configuration::Get("Database.dataBase").toString()   : strDatabase);
		// Set the username
		this->mConnection.setUserName(strUsername.isEmpty()               ? Configuration::Get("Database.userName").toString()   : strUsername);
		// Set the password
		this->mConnection.setPassword(strPassword.isEmpty()               ? Configuration::Get("Database.userPass").toString()   : strPassword);
		// Open the connection
		if (!this->mConnection.open()) {
			// Throw an error
			qDebug() << this->mConnection.lastError().text();
		}
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Signals ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString DBI::GetQuery() {
		// Return the query
		return this->mQuery;
	}

	int DBI::GetRowCount() {
		// Return the record count
		return this->mRecordCount;
	}

	QList<QVariant> DBI::GetRows() {
		// Return the rows from this instance
		return this->mRecords;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	DBI* DBI::SetConnection(QSqlDatabase qsdConnection) {
		// Drop the connection into the instance
		this->mConnection = qsdConnection;
		// Return the instance
		return this;
	}

	DBI* DBI::SetDatabase(QString strDatabase) {
		// Set the database into the instance
		this->mDatabase = strDatabase;
		// Return the instance
		return this;
	}

	DBI* DBI::SetHost(QString strHost) {
		// Set the server host into the instance
		this->mHost = strHost;
		// Return the instance
		return this;
	}

	DBI* DBI::SetInterface(int intInterface) {
		// Set the interface into the instance
		this->mInterface = intInterface;
		// Return the instance
		return this;
	}

	DBI* DBI::SetLimit(int intMaximum, int intMinimum) {
		// Set the limit into the instance
		this->mLimits.append(QString::number(intMaximum));
		this->mLimits.append(QString::number(intMinimum));
		// Return the instance
		return this;
	}

	DBI* DBI::SetPassword(QString strPassword) {
		// Set the server password into the instance
		this->mPassword = strPassword;
		// Return the instance
		return this;
	}


	DBI* DBI::SetPort(int intPort) {
		// Set the port into the instance
		this->mPort = intPort;
		// Return the instance
		return this;
	}

	DBI* DBI::SetQuery(QString strQuery) {
		// Set the query into the instance
		this->mQuery = strQuery;
		// Return the instance
		return this;
	}

	DBI* DBI::SetTable(QString strTable) {
		// Set the table name into the instance
		this->mTable = strTable;
		// Return the instance
		return this;
	}

	DBI* DBI::SetTableAlias(QString strTableAlias) {
		// Set the table alias into the instance
		this->mTableAlias = strTableAlias;
		// Return the instance
		return this;
	}

	DBI* DBI::SetUsername(QString strUsername) {
		// Set the username into the instance
		this->mUsername = strUsername;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
