///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_DBI_H
#define HEIMDALLGI_DBI_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QDebug"
#include "QList"
#include "QMap"
#include "QObject"
#include "QRegularExpression"
#include "QRegularExpressionMatch"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlQuery"
#include "QString"
#include "QStringList"
#include "QVariantMap"
#include "QVariant"
#include "Configuration.h"
#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// DBI Class Definition /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class DBI : public QObject {

		/**
		 * Ensure this class is recognized by Qt
		 */
		Q_OBJECT

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief HeimdallGI::DBI::mInstance
		 * @var HeimdallGI::DBI* this
		 */
		static DBI* mInstance;

		/**
		 * @paragraph This property contains the fields to select, set or update
		 * @brief HeimdallGI::DBI::mFields
		 * @var QMap<QString, QVariantMap>
		 */
		QMap<QString, QVariantMap> mColumns;

		/**
		 * @paragraph This property contains the database connection
		 * @brief HeimdallGI::DBI::mConnection
		 * @var QSqlDatabase
		 */
		QSqlDatabase mConnection;

		/**
		 * @paragraph This property contains the current query
		 * @brief HeimdallGI::DBI::mCurrentQuery
		 * @var QString
		 */
		QString mCurrentQuery;

		/**
		 * @paragraph This property contains the current SQL statement
		 * @brief HeimdallGI::DBI::mCurrentStatement
		 * @var QSqlQuery
		 */
		QSqlQuery mCurrentStatement;

		/**
		 * @paragraph This property contains the database to connect to
		 * @brief HeimdallGI::DBI::mDatabase
		 * @var QString
		 */
		QString mDatabase;

		/**
		 * @paragraph This property contains the GROUP BY statements
		 * @brief HeimdallGI::DBI::mGroupBy
		 * @var QMap<QString, QVariantMap>
		 */
		QMap<QString, QVariantMap> mGroupBy;

		/**
		 * @paragraph This property contains the server host
		 * @brief HeimdallGI::DBI::mHost
		 * @var QString
		 */
		QString mHost;

		/**
		 * @paragraph This property contains the current interface in use
		 * @brief HeimdallGI::DBI::mInterface
		 * @var int
		 */
		int mInterface;

		/**
		 * @paragraph This property contains the joins to be executed
		 * @brief HeimdallGI::DBI::mJoins
		 * @var QList<QVariantMap>
		 */
		QList<QVariantMap> mJoins;

		/**
		 * @paragraph This property contains the limits for the query
		 * @brief HeimdallGI::DBI::mLimits
		 * @var QStringList
		 */
		QStringList mLimits;

		/**
		 * @paragraph This property contains the ORDER BY clauses
		 * @brief HeimdallGI::DBI::mOrderBy
		 * QMap<QString, QVariantMap>
		 */
		QMap<QString, QVariantMap> mOrderBy;

		/**
		 * @paragraph This property contains the database password
		 * @brief HeimdallGI::DBI::mPassword
		 * @var QString
		 */
		QString mPassword;

		/**
		 * @paragraph This property contains the server port
		 * @brief HeimdallGI::DBI::mPort
		 * @var int
		 */
		int mPort;

		/**
		 * @paragraph This property contains the query to be executed
		 * @brief HeimdallGI::DBI::mQuery
		 * @var QString
		 */
		QString mQuery;

		/**
		 * @paragraph This property contains the current query status
		 * @brief HeimdallGI::DBI::mQueryStatus
		 * @var QMap<QString, bool>
		 */
		QMap<QString, bool> mQueryStatus;

		/**
		 * @paragraph This property contains the table name to query
		 * @brief HeimdallGI::DBI::mTable
		 * @var QString
		 */
		QString mTable;

		/**
		 * @paragraph This property contains the table alias
		 * @brief HeimdallGI::DBI::mTableAlias
		 * @var QString
		 */
		QString mTableAlias;

		/**
		 * @paragraph This property contains the database username
		 * @brief HeimdallGI::DBI::mUsername
		 * @var QString
		 */
		QString mUsername;

		/**
		 * @paragraph This property contains the WHERE clauses
		 * @brief HeimdallGI::DBI::mWhereClauses
		 * @var QList<QVariantMap>
		 */
		QList<QVariantMap> mWhereClauses;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method applies the wrapper to the database, table or column name
		 * @brief HeimdallGI::DBI::ApplyWrapper()
		 * @param QString strEntity
		 * @return QString
		 */
		QString ApplyWrapper(QString strEntity);

		/**
		 * @paragraph This method builds the DELETE query
		 * @brief HeimdallGI::DBI::BuildDeleteQuery()
		 * @return void
		 */
		void BuildDeleteQuery();

		/**
		 * @paragraph This method builds the GROUP BY clause
		 * @brief HeimdallGI::DBI::BuildGroupByClause()
		 * @return QString
		 */
		QString BuildGroupByClause();

		/**
		 * @paragraph This method builds the INSERT query
		 * @brief HeimdallGI::DBI::BuildInsertQuery()
		 * @return void
		 */
		void BuildInsertQuery();

		/**
		 * @paragraph This method builds the JOIN statements
		 * @brief HeimdallGI::DBI::BuildJoins()
		 * @return QString
		 */
		QString BuildJoins();

		/**
		 * @paragraph This method builds the LIMIT clause
		 * @brief HeimdallGI::DBI::BuildLimitClause()
		 * @return QString
		 */
		QString BuildLimitClause();

		/**
		 * @paragraph This method builds the ORDER BY clause
		 * @brief HeimdallGI::DBI::BuildOrderByClause()
		 * @return QString
		 */
		QString BuildOrderByClause();

		/**
		 * @paragraph This method builds the SELECT query
		 * @brief HeimdallGI::DBI::BuildSelectQuery()
		 * @return void
		 */
		void BuildSelectQuery();

		/**
		 * @paragraph This method builds the UPDATE query
		 * @brief HeimdallGI::DBI::BuildUpdateQuery()
		 * @return void
		 */
		void BuildUpdateQuery();

		/**
		 * @paragraph This method builds the WHERE clause
		 * @brief HeimdallGI::DBI::BuildWhereClause()
		 * @return QString
		 */
		QString BuildWhereClause();

		/**
		 * @paragraph This method quotes the true value of a column
		 * @brief HeimdallGI::DBI::QuoteTrueValue()
		 * @param QString strValue
		 * @return QString
		 */
		QString QuoteTrueValue(QString strValue);

		/**
		 * @paragraph This is just a helper method to emit a signal
		 * @brief HeimdallGI::DBI::SendStatus()
		 * @param int intStatusCode
		 * @param QString strError [NULL]
		 */
		void SendStatus(int intStatusCode, QString strError = NULL);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	public:

		///////////////////////////////////////////////////////////////////////
		/// Status Codes /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		static int StatusColumnsSet;
		static int StatusComplete;
		static int StatusDeleteBuildStarted;
		static int StatusError;
		static int StatusGroupingSet;
		static int StatusInsertBuildStarted;
		static int StatusJoinsSet;
		static int StatusKeyValuePairsSet;
		static int StatusLimitSet;
		static int StatusOrderSet;
		static int StatusSelectBuildStarted;
		static int StatusStarted;
		static int StatusTableAliasSet;
		static int StatusTableSet;
		static int StatusUpdateBuildStarted;
		static int StatusWhereClauseSet;

		///////////////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant contains the AND condition keyword
		 * @brief HeimdallGI::DBI::AndCondition
		 * @var QString
		 */
		static QString AndCondition;

		/**
		 * @paragraph This constant contains the ASC order keyword
		 * @brief HeimdallGI::DBI::AscendingOrder
		 * @var QString
		 */
		static QString AscendingOrder;

		/**
		 * @paragraph This constant contains the DELETE query template
		 * @brief HeimdallGI::DBI::DeleteQuery
		 * @var QString
		 */
		static QString DeleteQuery;

		/**
		 * @paragraph This constant contains the DESC order keyword
		 * @brief HeimdallGI::DBI::DescendingOrder
		 * @var QString
		 */
		static QString DescendingOrder;

		/**
		 * @paragraph This constant contains the IBM DB2 driver name
		 * @brief HeimdallGI::DBI::DriverDB2
		 * @var QString
		 */
		static QString DriverDB2;

		/**
		 * @paragraph This constant contains the Borland InterBase driver name
		 * @brief HeimdallGI::DBI::DriverInterBase
		 * @var QString
		 */
		static QString DriverInterBase;

		/**
		 * @paragraph This constant contains the MySQL >= 4 driver name
		 * @brief HeimdallGI::DBI::DriverMySQL
		 * @var QString
		 */
		static QString DriverMySQL;

		/**
		 * @paragraph This constant contains the MySQL <= 3 driver name
		 * @brief HeimdallGI::DBI::DriverMySQL3
		 * @var QString
		 */
		static QString DriverMySQL3;

		/**
		 * @paragraph This constant contains the Oracle Call Interface driver name
		 * @brief HeimdallGI::DBI::DriverOCI
		 * @var QString
		 */
		static QString DriverOCI;

		/**
		 * @paragraph This constant contains the ODBC driver name (Includes Microsoft SQL Server)
		 * @brief HeimdallGI::DBI::DriverODBC
		 * @var QString
		 */
		static QString DriverODBC;

		/**
		 * @paragraph This constant contains the PostgreSQL >= 8 driver name
		 * @brief HeimdallGI::DBI::DriverPostgreSQL
		 * @var QString
		 */
		static QString DriverPostgreSQL;

		/**
		 * @paragraph This constant contains the PostgreSQL <= 7 driver name
		 * @brief HeimdallGI::DBI::DriverPostgreSQL7
		 * @var QString
		 */
		static QString DriverPostgreSQL7;

		/**
		 * @paragraph This constant contains the SQLite >= 3 driver name
		 * @brief HeimdallGI::DBI::DriverSQLite
		 * @var QString
		 */
		static QString DriverSQLite;

		/**
		 * @paragraph This constant contains the SQLite <= 2 driver name
		 * @brief HeimdallGI::DBI::DriverSQLite2
		 * @var QString
		 */
		static QString DriverSQLite2;

		/**
		 * @paragraph This constant contains the Sybase Adaptive Server driver name
		 * @brief HeimdallGI::DBI::DriverSybase
		 */
		static QString DriverSybase;

		/**
		 * @paragraph This constant contains the = operator
		 * @brief HeimdallGI::DBI::EqualityOperator
		 * @var QString
		 */
		static QString EqualityOperator;

		/**
		 * @paragraph This constant contains the FULL JOIN query template
		 * @brief HeimdallGI::DBI::FullJoinQuery
		 * @var QString
		 */
		static QString FullJoinQuery;

		/**
		 * @paragraph This constsant contains the > operator
		 * @brief HeimdallGI::DBI::GreaterThanOperator
		 * @var QString
		 */
		static QString GreaterThanOperator;

		/**
		 * @paragraph This constant contains the >= operator
		 * @brief HeimdallGI::DBI::GreaterThanOrEqualToOperator
		 * @var QString
		 */
		static QString GreaterThanOrEqualToOperator;

		/**
		 * @paragraph This constant contains the INNER JOIN query template
		 * @brief HeimdallGI::DBI::InnerJoinQuery
		 * @var QString
		 */
		static QString InnerJoinQuery;

		/**
		 * @paragraph This constant contains the INSERT query template
		 * @brief HeimdallGI::DBI::InsertQuery
		 * @var QString
		 */
		static QString InsertQuery;

		/**
		 * @paragraph This constant contains the Microsoft SQL Server interface definition
		 * @brief HeimdallGI::DBI::InterfaceMSSQL
		 * @var int
		 */
		static int InterfaceMSSQL;

		/**
		 * @paragraph This constant contains the MySQL interface definition
		 * @brief HeimdallGI::DBI::InterfaceMySQL
		 * @var int
		 */
		static int InterfaceMySQL;

		/**
		 * @paragraph This constant contains the Oracle interface definition
		 * @brief HeimdallGI::DBI::InterfaceOCI
		 * @var int
		 */
		static int InterfaceOCI;

		/**
		 * @paragraph This constant contains the PostgreSQL interface definition
		 * @brief HeimdallGI::DBI::InterfacePgSQL
		 * @var int
		 */
		static int InterfacePgSQL;

		/**
		 * @paragraph This constant contains the LEFT JOIN query template
		 * @brief HeimdallGI::DBI::LeftJoinQuery
		 * @var QString
		 */
		static QString LeftJoinQuery;

		/**
		 * @paragraph This constant contains the LIKE operator
		 * @brief HeimdallGI::DBI::LikeOperator
		 * @var QString
		 */
		static QString LikeOperator;

		/**
		 * @paragraph This constant contains the < opertator
		 * @brief HeimdallGI::DBI::LessThanOperator
		 * @var QString
		 */
		static QString LessThanOperator;

		/**
		 * @paragraph This constant contains the <= operator
		 * @brief HeimdallGI::DBI::LessThatOrEqualToOperator
		 * @var QString
		 */
		static QString LessThatOrEqualToOperator;

		/**
		 * @paragraph This constant contains the Microsoft SQL Server database, table and field wrapper
		 * @brief HeimdallGI::DBI::MSSQLWrapper
		 * @var QString
		 */
		static QString MSSQLWrapper;

		/**
		 * @paragraph This constant contains the MySQL database, table and field wrapper
		 * @brief HeimdallGI::DBI::MySQLWrapper
		 * @var QString
		 */
		static QString MySQLWrapper;

		/**
		 * @paragraph This constant contains the <> operator
		 * @brief HeimdallGI::DBI::NotEqualToOperator
		 * @var QString
		 */
		static QString NotEqualToOperator;

		/**
		 * @paragraph This constant contains the Oracle database, table and field wrapper
		 * @brief HeimdallGI::DBI::OCIWrapper
		 * @var QString
		 */
		static QString OCIWrapper;

		/**
		 * @paragraph This constant contains the OR condition keyword
		 * @brief HeimdallGI::DBI::OrCondition
		 * @var QString
		 */
		static QString OrCondition;

		/**
		 * @paragraph This constant contains the PostgreSQL database, table and field wrapper
		 * @brief HeimdallGI::DBI::PgSQLWrapper
		 * @var QString
		 */
		static QString PgSQLWrapper;

		/**
		 * @paragraph This constant contains the RIGHT JOIN query template
		 * @brief HeimdallGI::DBI::RightJoinQuery
		 * @var QString
		 */
		static QString RightJoinQuery;

		/**
		 * @paragraph This constant contains the SELECT query template
		 * @brief HeimdallGI::DBI::SelectQuery
		 * @var QString
		 */
		static QString SelectQuery;

		/**
		 * @paragraph This constant contains the UPDATE query template
		 * @brief HeimdallGI::DBI::UpdateQuery
		 * @var QString
		 */
		static QString UpdateQuery;

		/**
		 * @paragraph This constant contains the wildcard field label
		 * @brief HeimdallGI::DBI::Wildcard
		 * @var QString
		 */
		static QString Wildcard;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit DBI(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::DBI::Singleton()
		 * @param bool bReset [false]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		static DBI* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a column to the instance
		 * @brief HeimdallGI::DBI::AddColumn()
		 * @param QString strColumn
		 * @param QString strValue [NULL]
		 * @param QString strTable [NULL]
		 * @param QString strAlias [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* AddColumn(QString strColumn, QString strValue = NULL, QString strTable = NULL, QString strAlias = NULL);

		/**
		 * @paragraph This method adds a JOIN to the instance
		 * @brief HeimdallGI::DBI::AddJoin()
		 * @param QString strJoinTable
		 * @param QString strJoinField
		 * @param QString strFromField
		 * @param QString strJoinType
		 * @param QString strJoinTableAlias [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* AddJoin(QString strJoinTable, QString strJoinField, QString strFromField, QString strJoinType, QString strJoinTableAlias = NULL);

		/**
		 * @paragraph This method adds a column to the GROUP BY clause
		 * @brief HeimdallGI::DBI::AddGroupByColumn()
		 * @param QString strColumn
		 * @param QString strTable [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* AddGroupByColumn(QString strColumn, QString strTable = NULL);

		/**
		 * @paragraph This method adds an ORDER BY clause to the instance
		 * @brief HeimdallGI::DBI::AddOrderBy()
		 * @param QString strColumn
		 * @param QString strDirection [HeimdallGI::DBI::AscendingOrder]
		 * @param QString strTable [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* AddOrderBy(QString strColumn, QString strDirection = HeimdallGI::DBI::AscendingOrder, QString strTable = NULL);

		/**
		 * @paragraph This method adds a condition to the WHERE clause in the instance
		 * @brief HeimdallGI::DBI::AddWhereClause()
		 * @param QString strColumn
		 * @param QString strValue
		 * @param QString strTable [NULL]
		 * @param QString strOperator [HeimdallGI::DBI::EqualityOperator]
		 * @param QString strCondition [HeimdallGI::DBI::AndCondition]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* AddWhereClause(QString strColumn, QString strValue, QString strTable = NULL, QString strOperator = HeimdallGI::DBI::EqualityOperator, QString strCondition = HeimdallGI::DBI::AndCondition);

		/**
		 * @paragraph This method generates the query
		 * @brief HeimdallGI::DBI::Build()
		 * @see @sub HeimdallGI::DBI::BuildDeleteQuery()
		 * @see @sub HeimdallGI::DBI::BuildInsertQuery()
		 * @see @sub HeimdallGI::DBI::BuildSelectQuery()
		 * @see @sub HeimdallGI::DBI::BuildUpdateQuery()
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* Build();

		/**
		 * @paragraph This method opens a connection to the database
		 * @brief HeimdallGI::DBI::OpenConnection()
		 * @param QString strDriver [NULL]
		 * @param QString strHost [NULL]
		 * @param int intPort [0]
		 * @param QString strUsername [NULL]
		 * @param QString strPassword [NULL]
		 * @param QString strDatabase [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* OpenConnection(QString strDriver = NULL, QString strHost = NULL, int intPort = 0, QString strUsername = NULL, QString strPassword = NULL, QString strDatabase = NULL);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method grabs a column's meta data
		 * @brief HeimdallGI::DBI::GetColumnMetaData()
		 * @param QString strColumn
		 * @return QVariantMap
		 */
		QVariantMap GetColumnMetaData(QString strColumn);

		/**
		 * @paragraph This method loads a table's columns
		 * @brief HeimdallGI::DBI::GetColumns()
		 * @param QString strTable [NULL]
		 * @return QStringList
		 */
		QStringList GetColumns(QString strTable = NULL);

		/**
		 * @paragraph This method returns the database connection object
		 * @brief HeimdallGI::DBI::GetConnection()
		 * @return QSqlDatabase
		 */
		QSqlDatabase GetConnection();

		/**
		 * @paragraph This method returns the last_insert_id
		 * @brief HeimdallGI::DBI::GetLastInsertId()
		 * @return QString
		 */
		QString GetLastInsertId();

		/**
		 * @paragraph This method returns the SQL query
		 * @brief HeimdallGI::DBI::GetQuery()
		 * @return QString
		 */
		QString GetQuery();

		/**
		 * @paragraph This method returns a result row
		 * @brief HeimdallGI::DBI::GetRow()
		 * @return QVariantMap
		 */
		QVariantMap GetRow();

		/**
		 * @paragraph This method returns the current statements result count or affected rows
		 * @brief HeimdallGI::DBI::GetRowCount()
		 * @return int
		 */
		int GetRowCount();

		/**
		 * @paragraph This method returns the entire resultset
		 * @brief HeimdallGI::DBI::GetRows()
		 * @return QList<QVariantMap>
		 */
		QList<QVariantMap> GetRows();

		/**
		 * @paragraph This method returns the current statement
		 * @brief HeimdallGI::DBI::GetStatement()
		 * @return QSqlQuery
		 */
		QSqlQuery GetStatement();

		/**
		 * @paragraph This method returns a table's meta data
		 * @brief HeimdallGI::DBI::GetTableMetaData()
		 * @param QString strTable [NULL]
		 * @return QVariantMap
		 */
		QVariantMap GetTableMetaData(QString strTable = NULL);

		/**
		 * @paragraph This method returns a table's primary key
		 * @brief HeimdallGI::DBI::GetTablePrimaryKey()
		 * @param QString strTable [NULL]
		 * @return QString
		 */
		QString GetTablePrimaryKey(QString strTable = NULL);

		/**
		 * @paragraph This method returns a database's table
		 * @brief HeimdallGI::DBI::GetTables()
		 * @param QString strDatabase [NULL]
		 * @return QStringList
		 */
		QStringList GetTables(QString strDatabase = NULL);

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method drops a database connection into the current instance
		 * @brief HeimdallGI::DBI::SetConnection()
		 * @param QSqlDatabase qsdConnection
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetConnection(QSqlDatabase qsdConnection);

		/**
		 * @paragraph This method sets the database into the instance
		 * @brief HeimdallGI::DBI::SetDatabase()
		 * @param QString strDatabase
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetDatabase(QString strDatabase);

		/**
		 * @paragraph This method sets the server host into the instance
		 * @brief HeimdallGI::DBI::SetHost()
		 * @param QString strHost
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetHost(QString strHost);

		/**
		 * @paragraph This method sets the interface type into the instance
		 * @brief HeimdallGI::DBI::SetInterface()
		 * @param int intInterface
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetInterface(int intInterface);

		/**
		 * @paragraph This method sets the limits into the instance
		 * @brief HeimdallGI::DBI::SetLimit()
		 * @param int intMaximum
		 * @param int intMinimum [NULL]
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetLimit(int intMaximum, int intMinimum = 0);

		/**
		 * @paragraph This method sets the database password into the instance
		 * @brief HeimdallGI::DBI::SetPassword()
		 * @param QString strPassword
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetPassword(QString strPassword);

		/**
		 * @paragraph This method sets the server port into the instance
		 * @brief HeimdallGI::DBI::SetPort()
		 * @param int intPort
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetPort(int intPort);

		/**
		 * @paragraph This method sets the query into the instance
		 * @brief HeimdallGI::DBI::SetQuery()
		 * @param QString strQuery
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetQuery(QString strQuery);

		/**
		 * @paragraph This method sets the table into the instance
		 * @brief HeimdallGI::DBI::SetTable()
		 * @param QString strTable
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetTable(QString strTable);

		/**
		 * @paragraph This method sets the table's alias into the intstance
		 * @brief HeimdallGI::DBI::SetTableAlias()
		 * @param QString strTableAlias
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetTableAlias(QString strTableAlias);

		/**
		 * @paragraph This method sets the database's username into the instance
		 * @brief HeimdallGI::DBI::SetUsername()
		 * @param QString strUsername
		 * @return HeimdallGI::DBI* HeimdallGI::DBI::mInstance
		 */
		DBI* SetUsername(QString strUsername);

	///////////////////////////////////////////////////////////////////////////
	/// Signals //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	signals:

		/**
		 * @paragraph This signal is emitted as the query build process progresses
		 * @brief HeimdallGI::DBI::CurrentStatus()
		 * @param int intStatusCode
		 * @param QString strQuery
		 * @param QString strError
		 * @return void
		 */
		void CurrentStatus(int intStatusCode, QString strQuery, QString strError);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Header ///////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // DBI_H
