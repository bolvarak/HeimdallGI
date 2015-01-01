///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_ISPCONFIG_H
#define HEIMDALLGI_ISPCONFIG_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QByteArray"
#include "QHostAddress"
#include "QHttpMultiPart"
#include "QHttpPart"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonParseError"
#include "QJsonValue"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QNetworkRequest"
#include "QObject"
#include "QSslConfiguration"
#include "QString"
#include "QStringList"
#include "QUrl"
#include "QUrlQuery"
#include "QVariant"
#include "QVariantList"
#include "QVariantMap"
#include "Configuration.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::ISPConfig Class Definition ///////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class ISPConfig : public QObject
	{
			/**
			 * Ensure this class is recognized by Qt
			 */
			Q_OBJECT

		///////////////////////////////////////////////////////////////////////
		/// Protected Methods & Properties ///////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the singleton instance of this class
			 * @brief HeimdallGI::ISPConfig::mInstance
			 * @var HeimdallGI::ISPConfig*
			 */
			static ISPConfig* mInstance;

			/**
			 * @paragraph This property contains the connetion to the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::mConnection
			 * @var QNetworkAccessManager
			 */
			QNetworkAccessManager mConnection;

			/**
			 * @paragraph This property contains the current executing method
			 * @brief HeimdallGI::ISPConfig::mCurrentMethod
			 * @var HeimdallGI::ISPConfig::JsonMethod
			 */
			JsonMethod mCurrentMethod;

			/**
			 * @paragraph This property tells the interface whether or not an error occurred
			 * @brief HeimdallGI::ISPConfig::mErrorFlag
			 * @var bool
			 */
			bool mErrorFlag;

			/**
			 * @paragraph This property contains the last error message
			 * @brief HeimdallGI::ISPConfig::mErrorMessage
			 * @var QString
			 */
			QString mErrorMessage;

			/**
			 * @paragraph This property contains the response to the caller
			 * @brief HeimdallGI::ISPConfig::mResponse
			 * @var QVariantMap
			 */
			QVariantMap mResponse;

			/**
			 * @paragraph This property tells the interface whether or not to use SSL
			 * @brief HeimdallGI::ISPConfig::mSecureTransport
			 * @var bool
			 */
			bool mSecureTransport;

			/**
			 * @paragraph This property contains the current session ID
			 * @brief HeimdallGI::ISPConfig::mSessionID
			 * @var QString
			 */
			QString mSessionID;

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method compiles and sends a request to the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::makeRequest()
			 * @param QString strMethod
			 * @param QVariantMap qvmArguments
			 * @return void
			 */
			void makeRequest(QString strMethod, QVariantMap qvmArguments);

			/**
			 * @paragraph This method converts a QVariantMap to a multi-part query
			 * @brief HeimdallGI::ISPConfig::mapToQuery()
			 * @param QVariantMap qvmParameters
			 * @return QByteArray
			 */
			QByteArray mapToQuery(QVariantMap qvmParameters);

			/**
			 * @paragraph This method processes the login response
			 * @brief HeimdallGI::ISPConfig::processLoginResponse()
			 * @emits HeimdallGI::ISPConfig::responseReady()
			 * @return void
			 */
			void processLoginResponse();

			/**
			 * @paragraph This method processes the logout response
			 * @brief HeimdallGI::ISPConfig::processLogoutResponse()
			 * @emits HeimdallGI::ISPConfig::responseReady()
			 * @return void
			 */
			void processLogoutResponse();

		///////////////////////////////////////////////////////////////////////
		/// Protected Slots //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected slots:

			/**
			 * @paragraph This slot is executed when the SOAP response is ready
			 * @brief HeimdallGI::ISPConfig::getJsonResponse()
			 * @param QNetworkReply* gnrResponse
			 * @return void
			 */
			void getJsonResponse(QNetworkReply* qnrResponse);

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Enumerations /////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This enumeration contains method definitions
			 * @brief HeimdallGI::ISPConfig::JsonMethod
			 * @var enum
			 */
			enum JsonMethod {
				None    = 0x000,
				Unknown = 0x001,
				Login   = 0x002,
				Logout  = 0x003
			};

			///////////////////////////////////////////////////////////////////
			/// Singleton ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method maintains access to the singleton instance of this class
			 * @brief HeimdallGI::ISPConfig::Instance()
			 * @param bool blnReset [false]
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			static ISPConfig* Instance(bool blnReset = false);

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			explicit ISPConfig(QObject *qoParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Destructor ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			~ISPConfig();

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method kills the remote session with the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::endSession()
			 * @param QString strSessionID
			 * @return void
			 */
			void endSession(QString strSessionID);

			/**
			 * @paragraph This method initializes a remote session with the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::startSession()
			 * @return void
			 */
			void startSession();

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the current executing SOAP method
			 * @brief HeimdallGI::ISPConfig::getCurrentMethod()
			 * @return HeimdallGI::ISPConfig::JsonMethod HeimdallGI::ISPConfig::mCurrentMethod
			 */
			JsonMethod getCurrentMethod() { return this->mCurrentMethod;           }

			/**
			 * @paragraph This method returns the error flag
			 * @brief HeimdallGI::ISPConfig::getErrorFlag()
			 * @return bool HeimdallGI::ISPConfig::mErrorFlag
			 */
			bool getErrorFlag()            { return this->mErrorFlag;                }

			/**
			 * @paragraph This method returns the last error message
			 * @brief HeimdallGI::ISPConfig::getErrorMessage()
			 * @return QString HeimdallGI::ISPConfig::mErrorMessage
			 */
			QString getErrorMessage()      { return this->mErrorMessage;             }

			/**
			 * @paragraph This method returns the last SOAP response from the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::getResponse()
			 * @return QVariantMap HeimdallGI::ISPConfig::mResponse
			 */
			QVariantMap getResponse()    { return this->mConnection.getResponse(); }

			/**
			 * @paragraph This method returns the secure transport flag from the instance
			 * @brief HeimdallGI::ISPConfig::getSecureTransportFlag()
			 * @return bool HeimdallGI::ISPConfig::mSecureTransport
			 */
			bool getSecureTransportFlag()  { return this->mSecureTransport;          }

			/**
			 * @paragraph This method returns the ISPConfig server session ID
			 * @brief HeimdallGI::ISPConfig::getSessionID()
			 * @return QString HeimdallGI::ISPConfig::mSessionID
			 */
			QString getSessionID()         { return this->mSessionID;                }

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the current executing SOAP method
			 * @brief HeimdallGI::ISPConfig::setCurrentMethod()
			 * @param HeimdallGI::ISPConfig::JsonMethod JsonMethod
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setCurrentMethod(JsonMethod JsonMethod) { this->mCurrentMethod  = JsonMethod;    return this; }

			/**
			 * @paragraph This method sets the error flag
			 * @brief HeimdallGI::ISPConfig::setErrorFlag()
			 * @param bool blnFlag
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setErrorFlag(bool blnFlag)              { this->mErrorFlag      = blnFlag;       return this; }

			/**
			 * @paragraph This method sets the error message
			 * @brief HeimdallGI::ISPConfig::setErrorMessage()
			 * @param QString strMessage
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setErrorMessage(QString strMessage)     { this->mErrorMessage   = strMessage;    return this; }

			/**
			 * @paragraph This method sets the response into the instance
			 * @brief HeimdallGI::ISPConfig::setResponse()
			 * @param QVariantMap qvmResponse
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setResponse(QVariantMap qvmResponse)    { this->makeResponse    = qvmResponse;   return this; }

			/**
			 * @paragraph This method sets the secure transport flag
			 * @brief HeimdallGI::ISPConfig::setSecureTransportFlag()
			 * @param bool blnFlag
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setSecureTransportFlag(bool blnFlag)    { this->mSecureTransport = blnFlag;      return this; }

			/**
			 * This method sets the ISPConfig server session ID
			 * @brief HeimdallGI::ISPConfig::setSessionID()
			 * @param QString strSessionID
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setSessionID(QString strSessionID)      { this->mSessionID       = strSessionID; return this; }

		///////////////////////////////////////////////////////////////////////
		/// Signals //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		signals:

			/**
			 * @paragraph This signal fires when the api returns an error
			 * @brief HeimdallGI::ISPConfig::apiError()
			 * @param QString strCode
			 * @param QString strErrorMessage
			 * @return void
			 */
			void apiError(QString strCode, QString strErrorMessage);

			/**
			 * @paragraph This signal fires when an error has occurred during the network transport
			 * @brief HeimdallGI::ISPConfig::networkError()
			 * @param QNetworkReply::NetworkError qnrError
			 * @param QString strErrorMessage
			 * @return void
			 */
			void networkError(QNetworkReply::NetworkError qnrError, QString strErrorMessage);

			/**
			 * @paragraph This signal fires when the request has finished and the response is ready
			 * @brief HeimdallGI::ISPConfig::responseReady()
			 * @param qvmResponse
			 * @return void
			 */
			void responseReady(QVariantMap qvmResponse);

	///////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::ISPConfig Class Definition ///////////////////////////
	/////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif
