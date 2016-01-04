///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_ABSTRACT_MODEL_H
#define HEIMDALLGI_ABSTRACT_MODEL_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QtCore/QByteArray"
#include "QtCore/QDebug"
#include "QtCore/QJsonArray"
#include "QtCore/QJsonDocument"
#include "QtCore/QJsonObject"
#include "QtCore/QJsonValue"
#include "QtCore/QList"
#include "QtCore/QMap"
#include "QtCore/QMapIterator"
#include "QtCore/QObject"
#include "QtCore/QRegularExpression"
#include "QtCore/QString"
#include "QtCore/QStringList"
#include "QtCore/QUuid"
#include "QtCore/QVariant"
#include "QtCore/QVariantMap"
#include "QtCore/QVector"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlError"
#include "QtSql/QSqlField"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlRecord"
#include "QtSql/QSqlResult"
#include <iostream>


///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////
	/// Abstract Namespace ///////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace Abstract {
		///////////////////////////////////////////////////////////////////////
		/// PgModel Class Definition /////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		class PgModel : public QObject
		{
			///////////////////////////////////////////////////////////////////
			/// QObject Classification ///////////////////////////////////////
			/////////////////////////////////////////////////////////////////

		Q_OBJECT;

			///////////////////////////////////////////////////////////////////
			/// Protected Methods & Properties ///////////////////////////////
			/////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This property contains the columns from the database table
			 * @access protected
			 * @name HeimdallGI::Abstract::mColumns
			 * @var QVariantMap
			 */
			QVariantMap mColumns;

			/**
			 * This property contains the database connection
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::mConnection
			 * @var QSqlDatabase
			 */
			QSqlDatabase mConnection;

			/**
			 * This property tells the instance whether or not the instance is empty
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::mIsEmpty
			 * @var bool
			 */
			bool mIsEmpty;

			/**
			 * This property contains the primary key from the table
			 * @access protected
			 * @name HeimdallGI::Abstract::mPrimaryKey
			 * @var QString
			 */
			QString mPrimaryKey;

			/**
			 * This property contains the table name for the model
			 * @access protected
			 * @name HeimdallGI::Abstract::mTable
			 * @var QString
			 */
			QString mTable;

			/**
			 * This property contains the table description
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::mTableDescription
			 * @var QMap<QString, QVector<QString>>
			 */
			QMap<QString, QVector<QString>> mTableDescription;

			///////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method finds the real name of a column
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::findColumn()
			 * @param QString strNeedle
			 * @return QString
			 */
			QString findColumn(QString strNeedle);

			/**
			 * This method generates the insert statement for the model
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::insertStatement()
			 * @param bool blnIncludePrimaryKey [false]
			 * @return QString
			 */
			QString insertStatement(bool blnIncludePrimaryKey = false);

			/**
			 * This method loads the table's meta data
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::tableMetaData()
			 * @param bool blnCloseConnectionWhenDone [false]
			 * @return void
			 */
			void tableMetaData(bool blnCloseConnectionWhenDone = false);

			/**
			 * This method generates the update statement for the model
			 * @access protected
			 * @name HeimdallGI::Abstract::PgModel::updateStatement()
			 * @return QString
			 */
			QString updateStatement();

			///////////////////////////////////////////////////////////////////
			/// Public Methods & Properties //////////////////////////////////
			/////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////
			/// Factory //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method instantiates the model into a fluid interface
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::Factory()
			 * @param QVariant qvID [QVariant()]
			 * @param QString strColumn [QString()]
			 * @return HeimdallGI::Abstract::PgModel*
			 * @static
			 */
			// static PgModel* Factory(QVariant qvID = QVariant(), QString strColumn = QString());

			///////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method constructs the class and optionally loads data
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel()
			 * @param QVariant qvID [QVariant()]
			 * @param QString strColumn [QString()]
			 */
			// explicit PgModel(QVariant qvID = QVariant(), QString strColumn = QString());

			///////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method deletes the record associated with the current instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::deleteRecord()
			 * @param QVariant qvID [QVariant()]
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* deleteRecord(QVariant qvID = QVariant());

			/**
			 * This method determines whether or not the model is empty
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::isEmpty()
			 * @return bool
			 */
			bool isEmpty();

			/**
			 * This method loads a record into the current instance
			 * @access public
			 * @name HeimdallGI::Abstract::load()
			 * @param QVariant qvID
			 * @param QString strColumn [""]
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* load(QVariant qvID, QString strColumn = "");

			/**
			 * This method saves the current instance to a record
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::save()
			 * @param bool blnForceInsert [false]
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* save(bool blnForceInsert = false);

			/**
			 * This method undoes the delete action for the current instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::undeleteRecord()
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* undeleteRecord();

			///////////////////////////////////////////////////////////////
			/// Utilities ////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method decrypts a hash that was generated by the database server
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::decrypt()
			 * @param QString strHash
			 * @param QString strKey
			 * @param int intRecursion [1]
			 * @return QVariant
			 */
			QVariant decrypt(QString strHash, QString strKey, int intRecursion = 1);

			/**
			 * This method encrypts data using PostgreSQL's crypto module
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::encrypt()
			 * @param QVariant mixData
			 * @param QString strKey
			 * @param int intRecursion [1]
			 * @return QString
			 */
			QString encrypt(QVariant mixData, QString strKey, int intRecursion = 1);

			/**
			 * This method generates a UUIDv4 using PostgreSQL's uuid_osp module
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::uuid()
			 * @return QUuid
			 */
			QUuid uuid();

			///////////////////////////////////////////////////////////////
			/// Converters ///////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method converts the model to JSON
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::toJson()
			 * @param bool blnObfuscate [true]
			 * @return QByteArray
			 */
			QByteArray toJson(bool blnObfuscate = true);

			///////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method returns a column from the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::get()
			 * @param QString strColumn
			 * @return QVariant
			 */
			inline QVariant get(QString strColumn) {
				// Return HeimdallGI::Abstract::PgModel::getColumn()
				return getColumn(strColumn);
			}

			/**
			 * This method returns a column from the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::getColumn()
			 * @param QString strColumn
			 * @return QVariant
			 */
			QVariant getColumn(QString strColumn);

			/**
			 * This method returns the table name from the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::getTable()
			 * @return QString HeimdallGI::Abstract::PgModel::mTable
			 */
			inline QString getTable() {
				// Return the table name from the instance
				return this->mTable;
			}

			///////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////

			/**
			 * This method sets a column value in the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::set()
			 * @param QString strColumn
			 * @param QVariant qvValue
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			inline PgModel* set(QString strColumn, QVariant qvValue) {
				// Return HeimdallGI::Abstract::PgModel::setColumn()
				return setColumn(strColumn, qvValue);
			}

			/**
			 * This method sets a column value in the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::setColumn()
			 * @param QString strColumn
			 * @param QVariant qvValue
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* setColumn(QString strColumn, QVariant qvValue);

			/**
			 * This method sets the connection into the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::setConnection()
			 * @param QSqlDatabase dbConnection
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			PgModel* setConnection(QSqlDatabase dbConnection);

			/**
			 * This method sets the table name for the model into the instance
			 * @access public
			 * @name HeimdallGI::Abstract::PgModel::setTable()
			 * @param QString strTable
			 * @return HeimdallGI::Abstract::PgModel* this
			 */
			inline PgModel* setTable(QString strTable) {
				// Set the table into the instance
				this->mTable = strTable;
				// We're done
				return this;
			}
		};
	}
}

///////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif //HEIMDALLGI_ABSTRACT_MODEL_H
