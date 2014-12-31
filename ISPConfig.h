///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_ISPCONFIG_H
#define HEIMDALLGI_ISPCONFIG_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "QString"
#include "QStringList"
#include "QVariant"
#include "QVariantList"
#include "QVariantMap"
#include "qtsoap.h"
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
			 * @var QtSoapHttpTransport
			 */
			QtSoapHttpTransport mConnection;

			/**
			 * @paragraph This property contains the current executing method
			 * @brief HeimdallGI::ISPConfig::mCurrentMethod
			 * @var HeimdallGI::ISPConfig::SoapMethod
			 */
			SoapMethod mCurrentMethod;

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
			 * @paragraph This method compiles and sends a request to the ISPConfig server with a pre-compiled method
			 * @brief HeimdallGI::ISPConfig::makeRequest()
			 * @param QtSoapQName qsnMethod
			 * @param QVariantMap qvmArguments
			 * @return void
			 */
			void makeRequest(QtSoapQName qsnMethod, QVariantMap qvmArguments);

			/**
			 * @paragraph This method sends a pre-compile request to the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::makeRequest()
			 * @param QtSoapMessage qsmRequest
			 * @return void
			 */
			void makeRequest(QtSoapMessage qsmRequest);

			/**
			 * @paragraph This method converts a QVariantMap to SOAP arguments
			 * @brief HeimdallGI::ISPConfig::mapToArguments()
			 * @param QtSoapMessage qsmRequest
			 * @param QVariantMap qvmArguments
			 * @return void
			 */
			void mapToArguments(QtSoapMessage &qsmRequest, QVariantMap qvmArguments);

			/**
			 * @paragraph This method processes the login response
			 * @brief HeimdallGI::ISPConfig::sendLoginResponse()
			 * @emits HeimdallGI::ISPConfig::startSessionResponseReady()
			 * @return void
			 */
			void sendLoginResponse();

			/**
			 * @paragraph This method processes the logout response
			 * @brief HeimdallGI::ISPConfig::sendLogoutResponse()
			 * @emits HeimdallGI::ISPConfig::endSessionResponseReady()
			 * @return void
			 */
			void sendLogoutResponse();

		///////////////////////////////////////////////////////////////////////
		/// Protected Slots //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected slots:

			/**
			 * @paragraph This slot is executed when the SOAP response is ready
			 * @brief HeimdallGI::ISPConfig::getSoapResponse()
			 * @return void
			 */
			void getSoapResponse();

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Enumerations /////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This enumeration contains method definitions
			 * @brief HeimdallGI::ISPConfig::SoapMethod
			 * @var enum
			 */
			enum SoapMethod {
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
			 * @return bool
			 */
			bool endSession();

			/**
			 * @paragraph This method initializes a remote session with the ISPConfig server
			 * @brief HeimdallGI::ISPConfig::startSession()
			 * @param QString strUsername
			 * @param QString strPassword
			 * @return bool
			 */
			bool startSession(QString strUsername = QString::null, QString strPassword = QString::null);

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the current executing SOAP method
			 * @brief HeimdallGI::ISPConfig::getCurrentMethod()
			 * @return HeimdallGI::ISPConfig::SoapMethod HeimdallGI::ISPConfig::mCurrentMethod
			 */
			SoapMethod getCurrentMethod() { return this->mCurrentMethod;           }

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
			 * @param HeimdallGI::ISPConfig::SoapMethod soapMethod
			 * @return HeimdallGI::ISPConfig* HeimdallGI::ISPConfig::mInstance
			 */
			ISPConfig* setCurrentMethod(SoapMethod soapMethod) { this->mCurrentMethod  = soapMethod;    return this; }

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
			 * @paragraph This signal fires when the logout request has finished
			 * @brief HeimdallGI::ISPConfig::endSessionResponseReady()
			 * @param QVariantMap &qvmResponse
			 * @return void
			 */
			void endSessionResponseReady(QVariantMap &qvmResponse);

			/**
			 * @paragraph This signal fires when the login request has finished
			 * @brief startSessionResponseReady
			 * @param qvmResponse
			 */
			void startSessionResponseReady(QVariantMap &qvmResponse);




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
