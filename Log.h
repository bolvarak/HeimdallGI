///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_LOG_H
#define HEIMDALLGI_LOG_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QDateTime"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QList"
#include "QObject"
#include "QString"
#include "QStringList"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Log Class Definition /////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Log : public QObject
	{

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
		 * @brief HeimdallGI::Log::mInstance
		 * @var HeimdallGI::Log*
		 */
		static Log* mInstance;

		/**
		 * @paragraph This property contains the log data
		 * @brief HeimdallGI::Log::mData
		 * @var QList<QStringList>
		 */
		QList<QStringList> mData;

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::Log::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::Log* HeimdallGI::Log::mInstance
		 */
		static Log* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit Log(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a data entry to the log
		 * @brief HeimdallGI::Log::Add()
		 * @param QString strKey
		 * @param QString strValue
		 * @return HeimdallGI::Log* HeimdallGI::Log::mInstance
		 */
		Log* Add(QString strKey, QString strValue);

		/**
		 * @paragraph This method removes a data entry from the log
		 * @brief HeimdallGI::Log::Delete()
		 * @param QString strKey
		 * @return HeimdallGI::Log* HeimdallGI::Log::mInstance
		 */
		Log* Delete(QString strKey);

		/**
		 * @paragraph This method updates a data entry in the log
		 * @brief HeimdallGI::Log::Update()
		 * @param QString strKey
		 * @param QString strValue
		 * @return HeimdallGI::Log* HeimdallGI::Log::mInstance
		 */
		Log* Update(QString strKey, QString strValue);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the log data as HTML
		 * @brief HeimdallGI::Log::GetHTML()
		 * @return QString
		 */
		QString GetHTML();

		/**
		 * @paragraph This method returns the log data as JSON
		 * @brief HeimdallGI::Log::GetJSON()
		 * @param bool bCompact [true]
		 * @return QString
		 */
		QString GetJSON(bool bCompact = true);

		/**
		 * @paragraph This method returns the log data as a CLI string
		 * @brief HeimdallGI::Log::GetString()
		 * @return QString
		 */
		QString GetString();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::Log Class Definition /////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif