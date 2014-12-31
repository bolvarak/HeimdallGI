///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "ISPConfig.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig* mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig* ISPConfig::Instance(bool blnReset) {
		// Check for an existing instance or a reset flag
		if ((mInstance == NULL) || (blnReset == true)) {
			// Create a new instance
			mInstance = new ISPConfig;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig::ISPConfig(QObject *qoParent) : QObject(qoParent) {
		// Connect the response signal
		connect(&mConnection, SIGNAL(responseReady(), this, SLOT(getSoapResponse());
		// Default the error flag
		this->mErrorFlag       = false;
		// Default the error message
		this->mErrorMessage    = QString::null;
		// Default the secure transport flag
		this->mSecureTransport = false;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Destructor ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig::~ISPConfig() {}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void ISPConfig::makeRequest(QString strMethod, QVariantMap qvmArguments) {
		// Reset the error state
		this->mErrorFlag    = false;
		this->mErrorMessage = QString::null;
		// Create the SOAP message
		QtSoapMessage qsmRequest;
		// Set the method
		qsmRequest.setMethod(strMethod, Configuration::Get("ispConfig.uri").toString());
		// Add the arguments
		this->mapToArguments(qsmRequest, qvmArguments);
		// Set the host
		this->mConnection.setHost(Configuration::Get("ispConfig.host").toString(), this->mSecureTransport, Configuration::Get("ispConfig.port").toInt());
		// Set the action
		this->mConnection.setAction(QString("%1/%2").arg(Configuration::Get("ispConfig.uri").toString(), strMethod));
		// Submit the request
		this->mConnection.submitRequest(qsmRequest, "/remote/index.php");
	}

	void ISPConfig::makeRequest(QtSoapQName qsnMethod, QVariantMap qvmArguments) {
		// Reset the error state
		this->mErrorFlag    = false;
		this->mErrorMessage = QString::null;
		// Create the SOAP message
		QtSoapMessage qsmRequest;
		// Set the method
		qsmRequest.setMethod(qsnMethod);
		// Add the arguments
		this->mapToArguments(qsmRequest, qvmArguments);
		// Set the host
		this->mConnection.setHost(Configuration::Get("ispConfig.host").toString(), this->mSecureTransport, Configuration::Get("ispConfig.port").toInt());
		// Set the action
		this->mConnection.setAction(QString("%1/%2").arg(Configuration::Get("ispConfig.uri").toString(), qsnMethod.name()));
		// Submit the request
		this->mConnection.submitRequest(qsmRequest, "/remote/index.php");
	}

	void ISPConfig::makeRequest(QtSoapMessage qsmRequest) {
		// reset the error state
		this->mErrorFlag    = false;
		this->mErrorMessage = QString::null;
		// Set the host
		this->mConnection.setHost(Configuration::Get("ispConfig.host").toString(), this->mSecureTransport, Configuration::Get("ispConfig.port").toInt());
		// Set the action
		this->mConnection.setAction(QString("%1/%2").arg(Configuration::Get("ispConfig.uri"), qsmRequest.method().name()));
		// Submit the request
		this->mConnection.submitRequest(qsmRequest, "/remote/index.php");
	}

	void ISPConfig::mapToArguments(QtSoapMessage &qsmRequest, QVariantMap qvmArguments) {
		// Iterate over the arguments
		for (QVariantMap::const_iterator itrArguments = qvmArguments.constBegin(); itrArguments != qvmArguments.constEnd(); ++itrArguments) {
			// Check the type
			if (itrArguments.value().canConvert(QMetaType::Bool)) {       // Boolean
				// Add the argument
				qsmRequest.addMethodArgument(itrArguments.key(), "", itrArguments.value().toBool());
			} else if (itrArguments.value().canConvert(QMetaType::Int)) { // Integer
				// Add the argument
				qsmRequest.addMethodArgument(itrArguments.key(), "", itrArguments.value().toInt());
			} else {                                                      // String
				// Add the argument
				qsmRequest.addMethodArgument(itrArguments.key(), "", itrArguments.value().toString());
			}
		}
	}

	void ISPConfig::sendLoginResponse() {
		// Empty the response
		this->mResponse.clear();
		// Set the session ID
		this->mResponse.insert("sessionID", this->mConnection.getResponse().returnValue()["session_id"].toString());
		// We're done, emit the signal
		emit this->startSessionResponseReady(this->mResponse);
	}

	void ISPConfig::sendLogoutResponse() {
		// Empty the response
		this->mResponse.clear();
		// We're done, emit the signal
		emit this->endSessionResponseReady(this->mResponse);
	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Slots //////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void ISPConfig::getSoapResponse() {
		// Determine the method
		switch(this->mCurrentMethod) {
			// Login
			case SoapMethod::Login  : return this->sendLoginResponse();  break;
			// Logout
			case SoapMethod::Logout : return this->sendLogoutResponse(); break;
		}
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////


	bool ISPConfig::endSession() {}


	bool ISPConfig::startSession(QString strUsername, QString strPassword) {
		// Check for local username
		if (strUsername == QString::null) {
			// Set the username from the configuration
			strUsername = Configuration::Get("ispConfig.userName").toString();
		}
		// Check for local password
		if (strPassword == QString::null) {
			// Set the password from the configuration
			strPassword = Configuration::Get("ispConfig.passWord").toString();
		}
		// Set the current executing method
		this->mCurrentMethod = SoapMethod::Login;
		// Send the request
		this->makeRequest("login", {
			"username" = strUsername,
			"password" = strPassword
		});
		// Wait for the response
	}


///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}

