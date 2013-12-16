///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CGI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::mInstance                    = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString CGI::ContentImageGIF           = "image/gif";
	QString CGI::ContentImageJPEG          = "image/jpeg";
	QString CGI::ContentImageJPG           = "image/jpg";
	QString CGI::ContentImagePNG           = "image/png";
	QString CGI::ContentImageSVG           = "image/svg+xml";
	QString CGI::ContentImageTIFF          = "image/tiff";
	QString CGI::ContentFont               = "application/font";
	QString CGI::ContentFontEOT            = "application/vnd.ms-fontobject";
	QString CGI::ContentFontOTF            = "font/opentype";
	QString CGI::ContentFontTTF            = "font/ttf";
	QString CGI::ContentFontWOFF           = "font/woff";
	QString CGI::ContentScriptECMAS        = "text/ecmascript";
	QString CGI::ContentScriptVB           = "text/vbscript";
	QString CGI::ContentTypeCSS            = "text/css";
	QString CGI::ContentTypeHTML           = "text/html";
	QString CGI::ContentTypeJS             = "text/javascript";
	QString CGI::ContentTypeJSON           = "application/json";
	QString CGI::ContentTypeText           = "text/plain";
	QString CGI::ContentTypeXML            = "text/xml";
	QString CGI::HeaderComSpec             = "COMSPEC";
	QString CGI::HeaderDocumentRoot        = "DOCUMENT_ROOT";
	QString CGI::HeaderGatewayInterface    = "GATEWAY_INTERFACE";
	QString CGI::HeaderHttpAccept          = "HTTP_ACCEPT";
	QString CGI::HeaderHttpAcceptEncoding  = "HTTP_ACCEPT_ENCODING";
	QString CGI::HeaderHttpAcceptLanguage  = "HTTP_ACCEPT_LANGUAGE";
	QString CGI::HeaderHttpConnection      = "HTTP_CONNECTION";
	QString CGI::HeaderHttpCookie          = "HTTP_COOKIE";
	QString CGI::HeaderHttpHost            = "HTTP_HOST";
	QString CGI::HeaderHttpUserAgent       = "HTTP_USER_AGENT";
	QString CGI::HeaderPath                = "PATH";
	QString CGI::HeaderQueryString         = "QUERY_STRING";
	QString CGI::HeaderRemoteAddress       = "REMOTE_ADDR";
	QString CGI::HeaderRemotePort          = "REMOTE_PORT";
	QString CGI::HeaderRequestMethod       = "REQUEST_METHOD";
	QString CGI::HeaderRequestUri          = "REQUEST_URI";
	QString CGI::HeaderScriptFilename      = "SCRIPT_FILENAME";
	QString CGI::HeaderScriptName          = "SCRIPT_NAME";
	QString CGI::HeaderServerAddress       = "SERVER_ADDR";
	QString CGI::HeaderServerAdministrator = "SERVER_ADMIN";
	QString CGI::HeaderServerName          = "SERVER_NAME";
	QString CGI::HeaderServerPort          = "SERVER_PORT";
	QString CGI::HeaderServerProtocol      = "SERVER_PROTOCOL";
	QString CGI::HeaderServerSignature     = "SERVER_SIGNATURE";
	QString CGI::HeaderServerSoftware      = "SERVER_SOFTWARE";
	QString CGI::HeaderStatusOK            = "200 OK";
	QString CGI::MethodDelete              = "DELETE";
	QString CGI::MethodGet                 = "GET";
	QString CGI::MethodHead                = "HEAD";
	QString CGI::MethodPost                = "POST";
	QString CGI::MethodPut                 = "PUT";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This method maintains access to the singleton instance of this class
	 * @brief CGI::Instance()
	 * @param bool bReset [false]
	 * @param QObject* qoParent [0]
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::Instance(bool bReset, QObject* qoParent) {
	  // Check for an existing instance or a reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new CGI(qoParent);
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This constructor sets up the class to read the HTTP headers and interact with the QtCGI
	 * @brief CGI::QtCGI()
	 * @param QObject* qoParent [0]
	 */
	CGI::CGI(QObject* qoParent) : QObject(qoParent) {
		// Process the request and return
		this->ProcessHeaders() // Headers
			->ProcessCookies()   // Cookies
			->ProcessGet()       // Query String
			->ProcessPost();     // POST data
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This method processes the cookies into the instance
	 * @brief CGI::ProcessCookies()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::ProcessCookies() {
		// Load the cookies
		QString strCookies = this->mRequestHeaders.value(CGI::HeaderHttpCookie);
		// Check for cookies
		if (!strCookies.isEmpty()) {
			// Set the cookies into the instance
			this->mCookies = this->DecodeQuery(strCookies, ";");
		}
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method processes the QUERY_STRING into the instance
	 * @brief CGI::ProcessGet()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::ProcessGet() {
		// Load the Query String
		QString strQuery = this->mRequestHeaders.value(CGI::HeaderQueryString);
		// Check for a query string
		if (!strQuery.isEmpty()) {
			// Set the GET variables into the instance
			this->mGetParameters = this->DecodeQuery(strQuery);
		}
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method processes the request headers into the instance
	 * @brief CGI::ProcessHeaders()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::ProcessHeaders() {
		// Add the DOCUMENT_ROOT header
		this->mRequestHeaders.insert(CGI::HeaderDocumentRoot,        QString(qgetenv(CGI::HeaderDocumentRoot.toLatin1().data())));
		// Add the GATEWAY_INTERFACE header
		this->mRequestHeaders.insert(CGI::HeaderGatewayInterface,    QString(qgetenv(CGI::HeaderGatewayInterface.toLatin1().data())));
		// Add the HTTP_ACCEPT header
		this->mRequestHeaders.insert(CGI::HeaderHttpAccept,          QString(qgetenv(CGI::HeaderHttpAccept.toLatin1().data())));
		// Add the HTTP_ACCEPT_ENCODING header
		this->mRequestHeaders.insert(CGI::HeaderHttpAcceptEncoding,  QString(qgetenv(CGI::HeaderHttpAcceptEncoding.toLatin1().data())));
		// Add the HTTP_ACCEPT_LANGUAGE header
		this->mRequestHeaders.insert(CGI::HeaderHttpAcceptLanguage,  QString(qgetenv(CGI::HeaderHttpAcceptLanguage.toLatin1().data())));
		// Add the HTTP_CONNECTION header
		this->mRequestHeaders.insert(CGI::HeaderHttpConnection,      QString(qgetenv(CGI::HeaderHttpConnection.toLatin1().data())));
		// Add the HTTP_COOKIE header
		this->mRequestHeaders.insert(CGI::HeaderHttpCookie,          QString(qgetenv(CGI::HeaderHttpCookie.toLatin1().data())));
		// Add the HTTP_HOST header
		this->mRequestHeaders.insert(CGI::HeaderHttpHost,            QString(qgetenv(CGI::HeaderHttpHost.toLatin1().data())));
		// Add the HTTP_USER_AGENT header
		this->mRequestHeaders.insert(CGI::HeaderHttpUserAgent,       QString(qgetenv(CGI::HeaderHttpUserAgent.toLatin1().data())));
		// Add the PATH header
		this->mRequestHeaders.insert(CGI::HeaderPath,                QString(qgetenv(CGI::HeaderPath.toLatin1().data())));
		// Add the QUERY_STRING header
		this->mRequestHeaders.insert(CGI::HeaderQueryString,         QString(qgetenv(CGI::HeaderQueryString.toLatin1().data())));
		// Add the REMOTE_ADDR header
		this->mRequestHeaders.insert(CGI::HeaderRemoteAddress,       QString(getenv(CGI::HeaderRemoteAddress.toLatin1().data())));
		// Add the REMOTE_PORT header
		this->mRequestHeaders.insert(CGI::HeaderRemotePort,          QString(qgetenv(CGI::HeaderRemotePort.toLatin1().data())));
		// Add the REQUEST_METHOD header
		this->mRequestHeaders.insert(CGI::HeaderRequestMethod,       QString(qgetenv(CGI::HeaderRequestMethod.toUpper().toLatin1().data())));
		// Add the REQUEST_URI header
		this->mRequestHeaders.insert(CGI::HeaderRequestUri,          QString(qgetenv(CGI::HeaderRequestUri.toLatin1().data())));
		// Add the SCRIPT_FILENAME header
		this->mRequestHeaders.insert(CGI::HeaderScriptFilename,      QString(qgetenv(CGI::HeaderScriptFilename.toLatin1().data())));
		// Add the SCRIPT_NAME header
		this->mRequestHeaders.insert(CGI::HeaderScriptName,          QString(qgetenv(CGI::HeaderScriptName.toLatin1().data())));
		// Add the SERVER_ADDR header
		this->mRequestHeaders.insert(CGI::HeaderServerAddress,       QString(qgetenv(CGI::HeaderServerAddress.toLatin1().data())));
		// Add the SERVER_ADMIN header
		this->mRequestHeaders.insert(CGI::HeaderServerAdministrator, QString(qgetenv(CGI::HeaderServerAdministrator.toLatin1().data())));
		// Add the SERVER_NAME header
		this->mRequestHeaders.insert(CGI::HeaderServerName,          QString(qgetenv(CGI::HeaderServerName.toLatin1().data())));
		// Add the SERVER_PORT header
		this->mRequestHeaders.insert(CGI::HeaderServerPort,          QString(qgetenv(CGI::HeaderServerPort.toLatin1().data())));
		// Add the SERVER_PROTOCOL header
		this->mRequestHeaders.insert(CGI::HeaderServerProtocol,      QString(qgetenv(CGI::HeaderServerProtocol.toLatin1().data())));
		// Add the SERVER_SIGNATURE header
		this->mRequestHeaders.insert(CGI::HeaderServerSignature,     QString(qgetenv(CGI::HeaderServerSignature.toLatin1().data())));
		// Add the SERVER_SOFTWARE header
		this->mRequestHeaders.insert(CGI::HeaderServerSoftware,      QString(qgetenv(CGI::HeaderServerSoftware.toLatin1().data())));
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method processes the POST data into the instance
	 * @brief CGI::ProcessPost()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::ProcessPost() {
		// Make sure this is a POST request
		if (this->mRequestHeaders.value(CGI::HeaderRequestMethod).toUpper() == CGI::MethodPost) {
			// Create the post data placeholder
			std::string strPostData;
			// Loop throug the POST lines
			std::getline(std::cin, strPostData);
			// Make sure we don't have an empty POST set
			if (!QString::fromStdString(strPostData).isEmpty()) {
				// Set the POST data into the instance
				this->mPostParameters = this->DecodeQuery(QString().fromStdString(strPostData));
			}
		}
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method writes the content body to the browser/socket/stream
	 * @brief CGI::SendContent()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::SendContent() {
		// Write the content
		std::cout << this->mContent.toStdString().c_str() << std::endl;
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method writes the response headers to the browser/socket/stream
	 * @brief CGI::SendHeaders()
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::SendHeaders(QString strContentType) {
		// Add the OK header
		this->AddResponseHeader("Status", CGI::HeaderStatusOK);
		// Set the content type
		this->AddResponseHeader("Content-Type", (strContentType.isEmpty() ? this->mContentType : strContentType));
		// Add the content length header
		this->AddResponseHeader("Content-Length", QString::number(this->mContent.length()));
		// Iterate over the headers
		for (QMap<QString, QString>::const_iterator itrHeaders = (this->mResponseHeaders.end() - 1); itrHeaders != 0; --itrHeaders) {
			// Print the header
			std::cout << itrHeaders.key().toStdString().c_str() << ": " << itrHeaders.value().toStdString().c_str() << "\r\n";
		}
		// Send an extra newline
		std::cout << "\r\n";
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This method is a helper for the router to add parameters from URL routes
	 * @brief CGI::AddParameter()
	 * @param QString strName
	 * @param QString strValue
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::AddParameter(QString strName, QString strValue) {
		// Add the value to the GET parameters
		this->mGetParameters.insert(strName, QUrl::fromPercentEncoding(strValue.replace("+", " ").toLatin1()));
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method sets a response header into the instance
	 * @brief CGI::AddResponseHeader()
	 * @param QString strName
	 * @param QString strValue
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::AddResponseHeader(QString strName, QString strValue) {
		// Set the response header into the instance
		this->mResponseHeaders.insert(strName, strValue);
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method decodes a query string into a query map
	 * @brief CGI::DecodeQuery()
	 * @param QString strQuery
	 * @param QString strPairSeparator ["&"]
	 * @return QMap<QString, QString>
	 */
	QMap<QString, QString> CGI::DecodeQuery(QString strQuery, QString strPairSeparator) {
		// Create the map placeholder
		QMap<QString, QString> qmQuery;
		// Split the parameters
		QStringList qslParameters = strQuery.split(strPairSeparator);
		// Loop through the parameters
		foreach (QString strPair, qslParameters) {
			// Split the key/value pair
			QStringList qslPair = strPair.split("=");
			// Set the pair into the map
			qmQuery.insert(QUrl::fromPercentEncoding(qslPair.at(0).toLatin1()).replace("+", " "), QUrl::fromPercentEncoding(qslPair.at(1).toLatin1()).replace("+", " "));
		}
		// Return the map
		return qmQuery;
	}

	/**
	 * @paragraph This method converts a query map into a query string
	 * @brief CGI::EncodeQuery()
	 * @param QMap<QString, QString> qmQuery
	 * @param QString strPairGlue ["&"]
	 * @return QString
	 */
	QString CGI::EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue) {
		// Create the query placeholder
		QStringList qslQuery;
		// Loop through the parameters
		foreach (QString strKey, qmQuery) {
			// Create the pair list
			QStringList qslPair;
			// Add the key
			qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
			// Add the value
			qslPair.append(QString(QUrl::toPercentEncoding(qmQuery.value(strKey))).replace(" ", "+"));
			// Append the pair to the query string
			qslQuery.append(qslPair.join("="));
		}
		// Return the query string
		return qslQuery.join(strPairGlue);
	}

	/**
	 * @paragraph This method converts a query variant map into a query string
	 * @brief CGI::EncodeQuery()
	 * @param QVariantMap qvmQuery
	 * @param QString strPairGlue ["&"]
	 * @return QString
	 */
	QString CGI::EncodeQuery(QVariantMap qvmQuery, QString strPairGlue) {
		// Create the query placeholder
		QStringList qslQuery;
		// Loop through the parameters
		foreach (QString strKey, qvmQuery.keys()) {
			// Create the pair list
			QStringList qslPair;
			// Add the keyt
			qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
			// Add the valie
			qslPair.append(QString(QUrl::toPercentEncoding(qvmQuery.value(strKey).toString())).replace(" ", "+"));
			// Append the pair to the query string
			qslQuery.append(qslPair.join("="));
		}
		// Return the query string
		return qslQuery.join(strPairGlue);
	}

	/**
	 * @paragraph This method writes the response to the browser/socket/stram
	 * @brief CGI::WriteResponse()
	 * @return void
	 */
	void CGI::WriteResponse(QString strContentType) {
		// Write the data to the requester
		this->SendHeaders(strContentType)  // Headers
			->SendContent(); // Content
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This method returns the current content from the instance
	 * @brief CGI::GetContent()
	 * @return QString CGI::mContent
	 */
	QString CGI::GetContent() {
		// Return the content from the instance
		return this->mContent;
	}

	/**
	 * @paragraph This method returns a cookies from the instance if it exists
	 * @brief CGI::GetCookie()
	 * @param QString strName
	 * @return QString
	 */
	QString CGI::GetCookie(QString strName) {
		// Check for the cookie
		if (this->mCookies.contains(strName)) {
			// Return the cookie
			return this->mCookies.value(strName);
		}
		// Elsewise, return null
		return NULL;
	}

	/**
	 * @paragraph This method returns the current cookie map from the instance
	 * @brief CGI::GetCookies()
	 * @return QMap<QString, QString> CGI::mCookies
	 */
	QMap<QString, QString> CGI::GetCookies() {
		// Return the current cookie map
		return this->mCookies;
	}

	/**
	 * @paragraph This method returns a GET/POST parameter from the instance if it exists
	 * @brief CGI::GetParam()
	 * @param QString strName
	 * @return QString
	 */
	QString CGI::GetParam(QString strName) {
		// Check for the parameter in POST
		if (this->mPostParameters.contains(strName)) {
			// Return the POST parameter
			return this->mPostParameters.value(strName);
		}
		// Check for the parameter in GET
		if (this->mGetParameters.contains(strName)) {
			// Return the GET parameter
			return this->mGetParameters.value(strName);
		}
		// Elsewise, return null
		return NULL;
	}

	/**
	 * @paragraph This method returns the current POST map from the instance
	 * @brief CGI::GetPostData()
	 * @return QMap<QString, QString> CGI::mPostParameters
	 */
	QMap<QString, QString> CGI::GetPostData() {
		// Return the POST data
		return this->mPostParameters;
	}

	/**
	 * @paragraph This method returns the current GET map from the instance
	 * @brief CGI::GetQueryData()
	 * @return QMap<QString, QString> CGI::mGetParameters
	 */
	QMap<QString, QString> CGI::GetQueryData() {
		// Return the GET data
		return this->mGetParameters;
	}

	/**
	 * @paragraph This method returns a request header from the instance if it exists
	 * @brief CGI::GetRequestHeader()
	 * @param QString strName
	 * @return QString
	 */
	QString CGI::GetRequestHeader(QString strName) {
		// Check to see if the request header exists
		if (this->mRequestHeaders.contains(strName)) {
			// Return the request header
			return this->mRequestHeaders.value(strName);
		}
		// Elsewise, return null
		return NULL;
	}

	/**
	 * @paragraph This method returns the current request headers from the instance
	 * @brief CGI::GetRequestHeaders()
	 * @return QMap<QString, QString> CGI::mRequestHeaders
	 */
	QMap<QString, QString> CGI::GetRequestHeaders() {
		// Return the response headers
		return this->mRequestHeaders;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This method sets the response content into the instance
	 * @brief CGI::SetContent()
	 * @param QString strContent
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::SetContent(QString strContent) {
		// Set the contnt into the instance
		this->mContent = strContent;
		// Return the instane
		return this;
	}

	/**
	 * @paragraph This method sets the content type header into the instance
	 * @brief CGI::SetContentType()
	 * @param QString strContentType
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::SetContentType(QString strContentType) {
		// Set the content type into the instance
		this->mContentType = strContentType;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
