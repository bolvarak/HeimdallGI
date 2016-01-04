///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "PgModel.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Abstract Namespace ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace Abstract
	{
		///////////////////////////////////////////////////////////////////////
		/// Protected Methods ////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		QString PgModel::findColumn(QString strNeedle)
		{
			// Check the map for the column name
			if (this->mColumns.contains(strNeedle)) {
				// We're done
				return strNeedle;
			}
			// Create the iterator
			QMapIterator<QString, QVariant> itrColumns(this->mColumns);
			// Iterate over the columns
			while (itrColumns.hasNext()) {
				// Set the key
				QString strKey = itrColumns.key();
				// Check the key
				if (strKey.replace(QRegExp("/(_|-|\\s)/", Qt::CaseInsensitive), "").toLower() == strNeedle.replace(QRegExp("(_|-|\\s)", Qt::CaseInsensitive), "").toLower()) {
					// We're done
					return strKey;
				}
			}
			// Return an empty key
			return "";
		}

		QString PgModel::insertStatement(bool blnIncludePrimaryKey)
		{
			// Create our vectors
			QStringList qslColumns;
			QStringList qslPlaceholders;
			// Create our iterator
			QMapIterator<QString, QVariant> itrColumns(this->mColumns);
			// Iterate over the columns
			while (itrColumns.hasNext()) {
				// Check the column name
				if ((itrColumns.key().toLower() != this->mPrimaryKey) || blnIncludePrimaryKey) {
					// Add the column to the vector
					qslColumns.append(QString("\"%1\"").arg(itrColumns.key()));
					// Add the value placeholder to the vector
					qslPlaceholders.append(QString(":column_%1").arg(itrColumns.key().toLower()));
				}
			}
			// Return the query
			return QString("INSERT INTO \"%1\" (%2) VALUES (%3)").arg(this->mTable, qslColumns.join(", "), qslPlaceholders.join(", "));
		}

		void PgModel::tableMetaData(bool blnCloseConnectionWhenDone)
		{
			// Create our queries
			QSqlQuery* qryPrimaryKey              = new QSqlQuery(this->mConnection);
			QSqlQuery* qryTableDescription        = new QSqlQuery(this->mConnection);
			// Prepare the primary key query
			qryPrimaryKey->prepare("SELECT \"a\".\"attname\", format_type(\"a\".\"atttypid\", \"a\".\"atttypmod\") AS \"data_type\" FROM \"pg_index\" \"i\" JOIN \"pg_attribute\" \"a\" ON \"a\".\"attrelid\" = \"i\".\"indrelid\" AND \"a\".\"attnum\" = ANY(\"i\".\"indkey\") WHERE \"i\".\"indrelid\" = ?::regclass AND \"i\".\"indisprimary\";");
			// Bind the table name
			qryPrimaryKey->addBindValue(this->mTable);
			// Execute the primary key query
			if (!qryPrimaryKey->exec()) {
				// We're done
				std::cout << QString("Primary Key Determination:  %1").arg(qryPrimaryKey->lastError().text()).toLatin1().constData() << std::endl;
			}
			// Go to the first record in the primary key query
			qryPrimaryKey->seek(0);
			// Set the primary key into the instance
			this->mPrimaryKey                     = qryPrimaryKey->value("attname").toString();
			// We're done with the primary key query
			qryPrimaryKey->finish();
			// Prepare the description query
			qryTableDescription->prepare(QString("SELECT \"column_name\", \"data_type\", \"character_maximum_length\" FROM INFORMATION_SCHEMA.COLUMNS WHERE \"table_name\" = '%1';").arg(this->mTable));
			// Set forward only
			qryTableDescription->setForwardOnly(true);
			// Execute the table description query
			if (!qryTableDescription->exec()) {
				// We're done
				std::cout << QString("Table Description:  %1").arg(qryTableDescription->lastError().text()).toLatin1().constData() << std::endl;
			}
			// Clear the current table description
			this->mTableDescription.clear();
			// Iterate over the table description records
			while (qryTableDescription->next()) {
				// Make sure the column name isn't empty
				if (!qryTableDescription->value("column_name").toString().isEmpty()) {
					// Create the column data vector
					QVector<QString> vecColumnData;
					// Add the column data type
					vecColumnData.append(qryTableDescription->value("data_type").toString());
					// Add the column maximum length
					vecColumnData.append(qryTableDescription->value("character_maximum_length").toString());
					// Add the data to instance
					this->mTableDescription.insert(qryTableDescription->value("column_name").toString(), vecColumnData);
				}
			}
			// We're done with the table description query
			qryTableDescription->finish();
		}

		QString PgModel::updateStatement()
		{
			// Create our vectors
			QStringList qslColumns;
			// Create our iterator
			QMapIterator<QString, QVariant> itrColumns(this->mColumns);
			// Iterate over the columns
			while (itrColumns.hasNext()) {
				// Check the column name
				if ((itrColumns.key().toLower() != this->mPrimaryKey)) {
					// Add the pair to the list
					qslColumns.append(QString("\"%1\" = :column_%2").arg(itrColumns.key(), itrColumns.key().toLower()));
				}
			}
			// Return the query
			return QString("UPDATE \"%1\" SET %2 WHERE \"%3\" = :column_%4;").arg(this->mTable, qslColumns.join(", "), this->mPrimaryKey, this->mPrimaryKey);
		}

		///////////////////////////////////////////////////////////////////////
		/// Public Methods ///////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		PgModel* PgModel::deleteRecord(QVariant qvID)
		{
			// Create the deletion query
			QSqlQuery* qryDelete = new QSqlQuery(this->mConnection);
			// Prepare the SQL statement
			qryDelete->prepare(QString("DELETE FROM \"%1\" WHERE \"%2\" = ?;").arg(this->mTable, this->mPrimaryKey));
			// Check for a provided ID
			if (qvID.isNull()) {
				// Bind the ID
				qryDelete->addBindValue(this->mColumns.value(this->mPrimaryKey));
			} else {
				// Bind the ID
				qryDelete->addBindValue(qvID);
			}
			// Execute the query
			if (!qryDelete->exec()) {
				// We're done
				std::cout << QString("Model Deletion:  %1").arg(qryDelete->lastError().text()).toLatin1().constData() << std::endl;
			}
			// We're done with the query
			qryDelete->finish();
			// We're done
			return this;
		}

		bool PgModel::isEmpty()
		{
			// Return the empty status
			return (this->mIsEmpty || this->mColumns.isEmpty());
		}

		PgModel* PgModel::load(QVariant qvID, QString strColumn)
		{
			// Load the table's meta data
			this->tableMetaData(false);
			// Make sure the connection is open
			if (!this->mConnection.isOpen()) {
				// We're done
				std::cout << this->mConnection.lastError().text().toLatin1().constData() << std::endl;
			}
			// Create the selection query
			QSqlQuery* qrySelection = new QSqlQuery(this->mConnection);
			// Prepare the query
			qrySelection->prepare(QString("SELECT * FROM \"%1\" WHERE \"%2\" = ?;").arg(this->mTable, (strColumn.isEmpty() ? this->mPrimaryKey : strColumn)));
			// We want to go forward only
			qrySelection->setForwardOnly(true);
			// Bind the ID to the query
			qrySelection->addBindValue(qvID);
			// Execute the query
			if (!qrySelection->exec()) {
				// We're done
				std::cout << QString("Model Load:  %1").arg(qrySelection->lastError().text()).toLatin1().constData() << std::endl;
			}
			// Check for results
			if (qrySelection->size() > 0) {
				// Clear the current instance
				this->mColumns.clear();
				// Seek the first record
				qrySelection->seek(0);
				// Create the iterator
				QMapIterator<QString, QVector<QString>> itrColumns(this->mTableDescription);
				// Load the keys from the query
				QVector<QString> vecColumns = this->mTableDescription.keys().toVector();
				// Iterate over the columns
				for (int intIterator = 0; intIterator < vecColumns.size(); ++intIterator) {
					// Add the data to the instance
					this->mColumns.insert(vecColumns.at(intIterator), qrySelection->value(vecColumns.at(intIterator)));
				}
			} else {
				// Set the empty flag
				this->mIsEmpty = true;
			}
			// We're done
			return this;
		}

		PgModel* PgModel::save(bool blnForceInsert)
		{
			// Define the query placeholder
			QString strQuery;
			// Determine if this is an update or insert
			if (this->mColumns.value(this->mPrimaryKey).toString().isEmpty() || this->mPrimaryKey.isEmpty() || blnForceInsert) {
				// Generate the insert statement
				strQuery = this->insertStatement(blnForceInsert);
			} else {
				// Generate the update statement
				strQuery = this->updateStatement();
			}
			// Create our iterator
			QMapIterator<QString, QVariant> itrColumns(this->mColumns);
			// Create the statement
			QSqlQuery* qrySave = new QSqlQuery(this->mConnection);
			// Prepare the statment
			qrySave->prepare(strQuery);
			// Iterate over the columns
			while (itrColumns.hasNext()) {
				// Bind the value
				qrySave->bindValue(QString(":column_%1").arg(itrColumns.key().toLower()), itrColumns.value());
			}
			// Execute the statement
			if (!qrySave->exec()) {
				// We're done
				std::cout << QString("Model Save:  %1").arg(qrySave->lastError().text()).toLatin1().constData() << std::endl;
			}
			// We're finished with the save statement
			qrySave->finish();
			// We're done
			return this;
		}

		PgModel* PgModel::undeleteRecord()
		{
			// Save the model
			return this->save(true);
		}

		///////////////////////////////////////////////////////////////////////
		/// Utilities ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		QVariant PgModel::decrypt(QString strHash, QString strKey, int intRecursion){
			// Create the query
			QSqlQuery* qryDecrypt = new QSqlQuery(this->mConnection);
			// Prepare the query
			qryDecrypt->prepare("SELECT decrypt(?, ?, 'aes');");
			// Decode the hash
			QVariant mixData = QVariant(QByteArray::fromBase64(strHash.toLatin1()));
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Bind the values
				qryDecrypt->addBindValue(mixData);
				qryDecrypt->addBindValue(strKey);
				// Execute the query
				if (!qryDecrypt->exec()) {
					// We're done
					qFatal(QString("[Recursion %1] %2").arg(QString(intIterator + 1), qryDecrypt->lastError().text()).toLatin1().data());
				}
				// Seek the first record
				qryDecrypt->seek(0);
				// Reset the data
				mixData = qryDecrypt->value(0);
			}
			// We're done
			return mixData;
		}

		QString PgModel::encrypt(QVariant mixData, QString strKey, int intRecursion)
		{
			// Create the query
			QSqlQuery* qryEncrypt = new QSqlQuery(this->mConnection);
			// Prepare the query
			qryEncrypt->prepare("SELECT encrypt(?, ?, 'aes');");
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Bind the values
				qryEncrypt->addBindValue(mixData);
				qryEncrypt->addBindValue(strKey);
				// Execute the query
				if (!qryEncrypt->exec()) {
					// We're done
					qFatal(QString("[Iteration %1]:  %2").arg(QString(intIterator + 1), qryEncrypt->lastError().text()).toLatin1().data());
				}
				// Seek the first record
				qryEncrypt->seek(0);
				// Reset the data
				mixData = qryEncrypt->value(0);
			}
			// We're done with this query
			qryEncrypt->finish();
			// Return the base64 encoded hash
			return QString(mixData.toByteArray().toBase64());
		}

		QUuid PgModel::uuid()
		{
			// Create the query
			QSqlQuery* qryUUID = new QSqlQuery(this->mConnection);
			// Prepare the query
			qryUUID->prepare("SELECT uuid_generate_v4();");
			// Check for errors
			if (!qryUUID->exec()) {
				// We're done
				qFatal(qryUUID->lastError().text().toLatin1().data());
			}
			// Seek the first record
			qryUUID->seek(0);
			// Return the UUID
			return QUuid(qryUUID->value(0).toString());
		}

		///////////////////////////////////////////////////////////////////////
		/// Converters ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		QByteArray PgModel::toJson(bool blnObfuscate)
		{
			// Create the JSON object
			QJsonObject qjoModel = QJsonObject::fromVariantMap(this->mColumns);
			// Create the document
			QJsonDocument qjdModel(qjoModel);
			// Return the JSON
			return qjdModel.toJson();
		}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		QVariant PgModel::getColumn(QString strColumn)
		{
			// Find the real column name
			QString strRealColumn = this->findColumn(strColumn);
			// Check for an empty column
			if (strRealColumn.isEmpty()) {
				// We're done
				std::cout << QString("Column Not Found:  %1").arg(strColumn).toLatin1().constData() << std::endl;
			}
			// Return the column value
			return this->mColumns.value(strRealColumn);
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		PgModel* PgModel::setColumn(QString strColumn, QVariant qvValue)
		{
			// Find the real column name
			QString strRealColumn = this->findColumn(strColumn);
			// Check for an empty column
			if (strRealColumn.isEmpty()) {
				// We're done
				std::cout << QString("Column Not Found:  %1").arg(strColumn).toLatin1().constData() << std::endl;
			}
			// Set the column data into the instance
			this->mColumns.insert(strRealColumn, qvValue);
			// We're done
			return this;
		}

		PgModel* PgModel::setConnection(QSqlDatabase dbConnection)
		{
			// Set the connection into the instance
			this->mConnection = dbConnection;
			// We're done
			return this;
		}
	}
}
