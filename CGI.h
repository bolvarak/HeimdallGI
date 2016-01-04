///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HeimdallGI_CGI_H
#define HeimdallGI_CGI_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QtCore/QByteArray"
#include "QtCore/QDateTime"
#include "QtCore/QDebug"
#include "QtCore/QJsonArray"
#include "QtCore/QJsonDocument"
#include "QtCore/QJsonObject"
#include "QtCore/QJsonValue"
#include "QtCore/QList"
#include "QtCore/QMap"
#include "QtCore/QObject"
#include "QtCore/QString"
#include "QtCore/QStringList"
#include "QtCore/QUrl"
#include "QtCore/QVariant"
#include "QtCore/QVariantMap"
#include "QtXml/QXmlInputSource"
#include "QtXml/QXmlReader"
#include "iostream"
#include "string"
#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct Cookie {

		///////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the domain for the cookie
		 * @brief HeimdallGI::Cookie::mDomain
		 * @var QString
		 */
		QString mDomain;

		/**
		 * @paragraph This property contains the expiration of a cookie
		 * @brief HeimdallGI::Cookie::mExpire
		 * @var QDateTime
		 */
		QDateTime mExpire;

		/**
		 * @paragraph This property notates an HTTP only cookie
		 * @brief HeimdallGI::Cookie::mHttpOnly
		 * @var bool
		 */
		bool mHttpOnly;

		/**
		 * @paragraph This property contains the name of the cookie
		 * @brief HeimdallGI::Cookie::mName
		 * @var QString
		 */
		QString mName;

		/**
		 * @paragraph This property contains the path for the cookie
		 * @brief HeimdallGI::Cookie::mPath
		 * @var QString
		 */
		QString mPath;

		/**
		 * @paragraph This property notates a secure cookie
		 * @brief HeimdallGI::Cookie::mSecure
		 * @var bool
		 */
		bool mSecure;

		/**
		 * @paragraph This property contains the value of the cookie
		 * @brief HeimdallGI::Cookie::mValue
		 * @var QString
		 */
		QString mValue;

		///////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor simply initializes a new cookie structure
		 * @brief HeimdallGI::Cookie::Cookie()
		 */
		Cookie() : mExpire(QDateTime()), mHttpOnly(false), mSecure(false) {}

		/**
		 * @paragraph This constructor initializes and sets up a new cookie structure
		 * @brief HeimdallGI::Cookie::Cookie()
		 * @param QString strName
		 * @param QString strValue
		 * @param QDateTime qdtExpiration [QDateTime()]
		 * @param QString strDomain [NULL]
		 * @param QString strPath [NULL]
		 * @param bool bHttpOnly [false]
		 * @param bool bSecure [false]
		 */
		Cookie(QString strName, QString strValue, QDateTime qdtExpiration = QDateTime(), QString strDomain = NULL, QString strPath = NULL, bool bHttpOnly = false, bool bSecure = false) {
			// Set the name
			mName     = strName;
			// Set the value
			mValue    = strValue;
			// Set the expiration
			mExpire   = qdtExpiration;
			// Set the domain name
			mDomain   = strDomain;
			// Set the path
			mPath     = strPath;
			// Set the HTTP only notator
			mHttpOnly = bHttpOnly;
			// Set the secure notator
			mSecure   = bSecure;
		}

		///////////////////////////////////////////////////////////////////
		/// Converters ///////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method converts the cookie to an HTTP header string
		 * @brief HeimdallGI::Cookie::toHeaderValue()
		 * @return QString
		 */
		QString toHeaderValue() {
			// Create the header value container
			QString strHeaderValue = "Set-Cookie:  ";
			// Add the name and value
			strHeaderValue.append(QString("%1=%2; ").arg(QString(QUrl::toPercentEncoding(mName))).arg(QString(QUrl::toPercentEncoding(mValue))));
			// Check for an expiration
			if (mExpire.isNull() == false) {
				// Add the expiration
				strHeaderValue.append(QString("Expires=%1; ").arg(mExpire.toString("ddd, dd MMM yyyy HH:mm:ss").append(" GMT")));
			}
			// Check for a domain
			if (mDomain.isEmpty() == false) {
				// Add the domain
				strHeaderValue.append(QString("Domain=%1; ").arg(mDomain));
			}
			// Check for a path
			if (mPath.isEmpty() == false) {
				// Add the path
				strHeaderValue.append(QString("Path=%1; ").arg(QString(QUrl::toPercentEncoding(mPath))));
			}
			// Check for a secure flag
			if (mSecure == true) {
				// Set the secure flag
				strHeaderValue.append("Secure; ");
			}
			// Check for an HttpOnly flag
			if (mHttpOnly == true) {
				// Set the HttpOnly flag
				strHeaderValue.append("HttpOnly; ");
			}
			// Trim the last character if it's a semi colon
			if (strHeaderValue.at(strHeaderValue.size() - 1) == ';') {
				// Remove the last character
				strHeaderValue.remove((strHeaderValue.size() - 1), 1);
			}
			// Return the string
			return strHeaderValue;
		}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the cookie's domain
		 * @brief HeimdallGI::Cookie::getDomain()
		 * @return QString HeimdallGI::Cookie::mDomain
		 */
		QString getDomain() {
			// Return the domain
			return mDomain;
		}

		/**
		 * @paragraph This method returns the cookie's expiration
		 * @brief HeimdallGI::Cookie::getExpiration()
		 * @return QDateTime HeimdallGI::Cookie::mExpire
		 */
		QDateTime getExpiration() {
			// Return the expiration timestamp
			return mExpire;
		}

		/**
		 * @paragraph This method returns the cookie's HttpOnly flag status
		 * @brief HeimdallGI::Cookie::getHttpOnlyFlag()
		 * @return bool HeimdallGI::Cookie::mHttpOnly
		 */
		bool getHttpOnlyFlag() {
			// Return the HttpOnly flag
			return mHttpOnly;
		}

		/**
		 * @paragraph This method returns the cookie's name
		 * @brief HeimdallGI::Cookie::getName()
		 * @return QString HeimdallGI::Cookie::mName
		 */
		QString getName() {
			// Return the name
			return mName;
		}

		/**
		 * @paragraph This method returns the cookie's path
		 * @brief HeimdallGI::Cookie::getPath()
		 * @return QString HeimdallGI::Cookie::mPath
		 */
		QString getPath() {
			// Return the path
			return mPath;
		}

		/**
		 * @paragraph This method returns the cookie's secure flag status
		 * @brief HeimdallGI::Cookie::getSecureFlag()
		 * @return bool HeimdallGI::Cookie::mSecure
		 */
		bool getSecureFlag() {
			// Return the secure flag
			return mSecure;
		}

		/**
		 * @paragraph This method returns the cookie's value
		 * @brief HeimdallGI::Cookie::getValue()
		 * @return QString HeimdallGI::Cookie::mValue
		 */
		QString getValue() {
			// Return the value
			return mValue;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the cookie's domain
		 * @brief HeimdallGI::Cookie::setDomain()
		 * @param QString strDomain
		 * @return void
		 */
		void setDomain(QString strDomain) {
			// Set the domain
			mDomain = strDomain;
		}

		/**
		 * @paragraph This method sets the cookie's expiration
		 * @brief HeimdallGI::Cookie::setExpiration()
		 * @param QDateTime qdtExpire
		 * @return void
		 */
		void setExpiration(QDateTime qdtExpire) {
			// Set the expiration
			mExpire = qdtExpire;
		}

		/**
		 * @paragraph This method sets the cookie's HttpOnly flag
		 * @brief HeimdallGI::Cookie::setHttpOnlyFlag()
		 * @param bool bHttpOnly
		 * @return void
		 */
		void setHttpOnlyFlag(bool bHttpOnly) {
			// Set the flag
			mHttpOnly = bHttpOnly;
		}

		/**
		 * @paragraph This method sets the cookie's name
		 * @brief HeimdallGI::Cookie::setName()
		 * @param QString strName
		 * @return void
		 */
		void setName(QString strName) {
			// Set the name
			mName = strName;
		}

		/**
		 * @paragraph This method sets the cookie's path
		 * @brief HeimdallGI::Cookie::setPath()
		 * @param QString strPath
		 * @return void
		 */
		void setPath(QString strPath) {
			// Set the path
			mPath = strPath;
		}

		/**
		 * @paragraph This method sets the cookie's security flag
		 * @brief HeimdallGI::Cookie::setSecureFlag()
		 * @param bool bSecure
		 * @return void
		 */
		void setSecureFlag(bool bSecure) {
			// Set the flag
			mSecure = bSecure;
		}

		/**
		 * @paragraph This method sets the cookie's value
		 * @brief HeimdallGI::Cookie::setValue()
		 * @param QString strValue
		 * @return void
		 */
		void setValue(QString strValue) {
			// Set the value
			mValue = strValue;
		}
	};

	struct StackEntry {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the filename
		 * @brief HeimdallGI::StackEntry::mFile
		 * @var QString
		 */
		QString mFile;

		/**
		 * @paragraph This property contains the line number
		 * @brief HeimdallGI::StackEntry::mLineNumber
		 * @var int
		 */
		int mLineNumber;

		/**
		 * @paragraph This property contains the snippet or call
		 * @brief HeimdallGI::StackEntry::mSnippet
		 */
		QString mSnippet;

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor initializes and sets up a StackEntry
		 * @brief HeimdallGI::StackEntry::StackEntry()
		 * @param QString strFile
		 * @param int intLine
		 * @param QString strSnippet
		 */
		StackEntry(QString strFile, int intLine, QString strSnippet) {
			// Set the file
			mFile       = strFile;
			// Set the line number
			mLineNumber = intLine;
			// Set the snippet
			mSnippet    = strSnippet;
		}

		/**
		 * @paragraph This constructor simply initializes a StackEntry
		 * @brief HeimdallGI::StackEntry::StackEntry()
		 */
		StackEntry() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the file name
		 * @brief HeimdallGI::StackEntry::getFile()
		 * @return QString HeimdallGI::StackEntry::mFile
		 */
		QString getFile() {
			// Return the filename
			return mFile;
		}

		/**
		 * @paragraph This method returns the line number
		 * @brief HeimdallGI::StackEntry::getLine()
		 * @return int HeimdallGI::StackEntry::mLineNumber
		 */
		int getLine() {
			// Return the line number
			return mLineNumber;
		}

		/**
		 * @paragraph This method returns the snippet
		 * @brief HeimdallGI::StackEntry::getSnippet()
		 * @return QString HeimdallGI::StackEntry::mSnippet
		 */
		QString getSnippet() {
			// Return the snippet
			return mSnippet;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the filename into the structure
		 * @brief HeimdallGI::StackEntry::setFile()
		 * @param QString strFilename
		 * @return void
		 */
		void setFile(QString strFilename) {
			// Set the filename
			mFile = strFilename;
		}

		/**
		 * @paragraph This method sets the line number into the structure
		 * @brief HeimdallGI::StackEntry::setLine()
		 * @param int intLineNumber
		 * @return void
		 */
		void setLine(int intLineNumber) {
			// Set the line number
			mLineNumber = intLineNumber;
		}

		/**
		 * @paragraph This method sets the snippet into the structure
		 * @brief HeimdallGI::StackEntry::setSnippet()
		 * @param QString strSnippet
		 * @return void
		 */
		void setSnippet(QString strSnippet) {
			// Set the snippet
			mSnippet = strSnippet;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Cgi Class Definition /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This class handles the interaction between the web browser and the application
	 * @brief HeimdallGI::CGI
	 */
	class CGI : public QObject {
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
		 * @brief CGI::mInstance
		 * @var CGI*
		 */
		static CGI* mInstance;

		/**
		 * @paragraph This property contains the callstack for the instance
		 * @brief HeimdallGI::StackEntry::mCallStack
		 * @var QList<HeimdallGI::StackEntry>
		 */
		QList<StackEntry> mCallStack;

		/**
		 * @paragraph This property contains the response content
		 * @brief CGI::mContent
		 * @var QString
		 */
		QString mContent;

		/**
		 * @paragraph This property contains the response content type
		 * @brief HeimdallGI::CGI::mContentType
		 * @var QString
		 */
		QString mContentType;

		/**
		 * @paragraph This property contains the HTTP cookies
		 * @brief CGI::mCookies
		 * @var QVariantMap
		 */
		QVariantMap mCookies;

		/**
		 * @paragraph This property contains the GET data
		 * @brief CGI::mGetParameters
		 * @var QVariantMap
		 */
		QVariantMap mGetParameters;

		/**
		 * @paragraph This property contains a list of new cookies to set
		 * @brief HeimdallGI::CGI::mNewCookies
		 * @var QList<Cookie>
		 */
		QList<Cookie> mNewCookies;

		/**
		 * @paragraph This property contains the POST data
		 * @brief CGI::mPostParameters
		 * @var QMap<QString, QString>
		 */
		QVariantMap mPostParameters;

		/**
		 * @paragraph This property contains the request headers from the client
		 * @brief CGI::mRequestHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mRequestHeaders;

		/**
		 * @paragraph This property contains the response headers to send to the client
		 * @brief CGI::mResponseHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mResponseHeaders;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method processes the HTTP_COOKIE from the header
		 * @brief CGI::processCookies()
		 * @return CGI* CGI::mInstance
		 */
		CGI* processCookies();

		/**
		 * @paragraph This method processes the QUERY_STRING from the header
		 * @brief CGI::processGet()
		 * @return CGI* CGI::mInstance
		 */
		CGI* processGet();

		/**
		 * @paragraph This method processes the request headers into the instance
		 * @brief CGI::processHeaders()
		 * @return CGI* CGI::mInstance
		 */
		CGI* processHeaders();

		/**
		 * @paragraph This method processes the POST data into the instance
		 * @brief CGI::processPost()
		 * @return CGI* CGI::mInstance
		 */
		CGI* processPost();

		/**
		 * @paragraph This method writes the content to the browser/socket/stream
		 * @brief CGI::sendContent()
		 * @return CGI* CGI::mInstance
		 */
		CGI* sendContent();

		/**
		 * @paragraph This method writes the response headers to the browser/socket/stream
		 * @brief CGI::sendHeaders()
		 * @param QString strContentType [NULL]
		 * @return CGI* CGI::mInstance
		 */
		CGI* sendHeaders(QString strContentType = NULL);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the header type for GIF
		 * @brief CGI::ContentImageGIF
		 * @var QString
		 */
		static QString ContentImageGIF;

		/**
		 * @paragraph This property contains the header type for JPEG
		 * @brief CGI::ContentImageJPEG
		 * @var QString
		 */
		static QString ContentImageJPEG;

		/**
		 * @paragraph This property contains the header type for JPG
		 * @brief CGI::ContentImageJPG
		 * @var QString
		 */
		static QString ContentImageJPG;

		/**
		 * @paragraph This property contains the header type for PNG
		 * @brief CGI::ContentImagePNG
		 * @var QString
		 */
		static QString ContentImagePNG;

		/**
		 * @paragraph Thie property contains the header type for SVG
		 * @brief CGI::ContentImageSVG
		 * @var QString
		 */
		static QString ContentImageSVG;

		/**
		 * @paragraph This property contains the header type for TIFF
		 * @brief CGI::ContentImageTIFF
		 * @var QString
		 */
		static QString ContentImageTIFF;

		/**
		 * @paragraph This property contins the header type for FONT
		 * @brief CGI::ContentFont
		 * @var QString
		 */
		static QString ContentFont;

		/**
		 * @paragraph This property contains the header type for EOT
		 * @brief CGI::ContentFontEOT
		 * @var QString
		 */
		static QString ContentFontEOT;

		/**
		 * @paragraph This property contains the header type for OTF
		 * @brief CGI::ContentFontOTF
		 * @var QString
		 */
		static QString ContentFontOTF;

		/**
		 * @paragraph This property contains the header type for TTF
		 * @brief CGI::ContentFontTTF
		 * @var QString
		 */
		static QString ContentFontTTF;

		/**
		 * @paragraph This property contains the header type for WOFF
		 * @brief CGI::ContentFontWOFF
		 * @var QString
		 */
		static QString ContentFontWOFF;

		/**
		 * @paragraph This property contains the header type for ECMAS
		 * @brief CGI::ContentScriptECMAS
		 * @var QString
		 */
		static QString ContentScriptECMAS;

		/**
		 * @paragraph This property contains the header type for VB
		 * @brief CGI::ContentScriptVB
		 * @var QString
		 */
		static QString ContentScriptVB;

		/**
		 * @paragraph This property contains the header type for CSS
		 * @brief CGI::ContentTypeCSS
		 * @var QString
		 */
		static QString ContentTypeCSS;

		/**
		 * @paragraph This property contain the header type for HTML
		 * @brief CGI::ContentTypeHTML
		 * @var QString
		 */
		static QString ContentTypeHTML;

		/**
		 * @paragraph This property contains the header type for JS
		 * @brief CGI::ContentTypeJS
		 * @var QString
		 */
		static QString ContentTypeJS;

		/**
		 * @paragraph This property contains the header type for JSON
		 * @brief CGI::ContentTypeJSON
		 * @var QString
		 */
		static QString ContentTypeJSON;

		/**
		 * @paragraph This property contains the header type for TXT
		 * @brief CGI::ContentTypeText
		 * @var QString
		 */
		static QString ContentTypeText;

		/**
		 * @paragraph This property contains the header type for XML
		 * @brief CGI::ContentTypeXML
		 * @var QString
		 */
		static QString ContentTypeXML;

		/**
		 * @paragraph This property contains the COMSPEC header name
		 * @brief CGI::HeaderComSpec
		 * @var QString
		 */
		static QString HeaderComSpec;

		/**
		 * @paragraph This property contains the DOCUMENT_ROOT header name
		 * @brief CGI::HeaderDocumentRoot
		 * @var QString
		 */
		static QString HeaderDocumentRoot;

		/**
		 * @paragraph This proeprty contains the GATEWAY_INTERFACE header name
		 * @brief CGI::HeaderGatewayInterface
		 * @var QString
		 */
		static QString HeaderGatewayInterface;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT header name
		 * @brief CGI::HeaderHttpAccept
		 * @var QString
		 */
		static QString HeaderHttpAccept;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_ENCODING header name
		 * @brief CGI::HeaderHttpAcceptEncoding
		 * @var QString
		 */
		static QString HeaderHttpAcceptEncoding;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_LANGUAGE header
		 * @brief CGI::HeaderHttpAcceptLanguage
		 * @var QString
		 */
		static QString HeaderHttpAcceptLanguage;

		/**
		 * @paragraph This property contains the HTTP_CONNECTION header name
		 * @brief CGI::HeaderHttpConnection
		 * @var QString
		 */
		static QString HeaderHttpConnection;

		/**
		 * @paragraph This property contains the HTTP_COOKIE header name
		 * @brief CGI::HeaderHttpCookie
		 * @var QString
		 */
		static QString HeaderHttpCookie;

		/**
		 * @paragraph This property contains the HTTP_HOST header name
		 * @brief CGI::HeaderHttpHost
		 * @var QString
		 */
		static QString HeaderHttpHost;

		/**
		 * @paragraph This property contains the HTTP_USER_AGENT header name
		 * @brief CGI::HeaderHttpUserAgent
		 * @var QString
		 */
		static QString HeaderHttpUserAgent;

		/**
		 * @paragraph This property contains the PATH header name
		 * @brief CGI::HeaderPath
		 */
		static QString HeaderPath;

		/**
		 * @paragraph This property contains the QUERY_STRING header name
		 * @brief CGI::eaderQueryString
		 * @var QString
		 */
		static QString HeaderQueryString;

		/**
		 * @paragraph This property contains the REMOTE_ADDR header name
		 * @brief CGI::HeaderRemoteAddress
		 * @var QString
		 */
		static QString HeaderRemoteAddress;

		/**
		 * @paragraph This property contain the REMOTE_PORT header name
		 * @brief CGI::HeaderRemotePort
		 * @var QString
		 */
		static QString HeaderRemotePort;

		/**
		 * @paragraph This property contains the REQUEST_METHOD header name
		 * @brief CGI::HeaderRequestMethod
		 * @var QString
		 */
		static QString HeaderRequestMethod;

		/**
		 * @paragraph This property contains the REQUEST_URI header name
		 * @brief CGI::HeaderRequestUri
		 * @var QString
		 */
		static QString HeaderRequestUri;

		/**
		 * @paragraph This paragraph contains the SCRIPT_FILENAME header name
		 * @brief CGI::HeaderScriptFilename
		 * @var QString
		 */
		static QString HeaderScriptFilename;

		/**
		 * @paragraph This property contains the SCRIPT_NAME header namr
		 * @brief CGI::HeaderScriptName
		 * @var QString
		 */
		static QString HeaderScriptName;

		/**
		 * @paragraph This property contains the SERVER_ADDR header name
		 * @brief CGI::HeaderServerAddress
		 * @var QString
		 */
		static QString HeaderServerAddress;

		/**
		 * @paragraph This property contians the SERVER_ADMIN header name
		 * @brief CGI::HeaderServerAdministrator
		 * @var QString
		 */
		static QString HeaderServerAdministrator;

		/**
		 * @paragraph This property contains the SERVER_NAME header name
		 * @brief CGI::HeaderServerName
		 * @var QString
		 */
		static QString HeaderServerName;

		/**
		 * @paragraph This property contains the SERVER_PORT header name
		 * @brief CGI::HeaderServerPort
		 * @var QString
		 */
		static QString HeaderServerPort;

		/**
		 * @paragraph This property contains the SERVER_PROTOCOL header name
		 * @brief CGI::HeaderServerProtocol
		 * @var QString
		 */
		static QString HeaderServerProtocol;

		/**
		 * @paragraph This property contains the SERVER_SIGNATURE header name
		 * @brief CGI::HeaderServerSignature
		 * @var QString
		 */
		static QString HeaderServerSignature;

		/**
		 * @paragraph This property contains the SERVER_SOFTWARE header name
		 * @brief CGI::HeaderServerSoftware
		 * @var QString
		 */
		static QString HeaderServerSoftware;

		/**
		 * @paragraph This constant contains the 200 OK header
		 * @brief CGI::HeaderStatusOK
		 * @var QString
		 */
		static QString HeaderStatusOK;

		/**
		 * @paragraph This property contains the DELETE data request method name
		 * @brief CGI::MethodDelete
		 * @var QString
		 */
		static QString MethodDelete;

		/**
		 * @paragraph This property contains the GET data request method name
		 * @brief CGI::MethodGet
		 * @var QString
		 */
		static QString MethodGet;

		/**
		 * @paragraph This property contains the HEAD data request method name
		 * @brief CGI::MethodHead
		 * @var QString
		 */
		static QString MethodHead;

		/**
		 * @paragraph This property contains the POST data request method name
		 * @brief CGI::MethodPost
		 * @var QString
		 */
		static QString MethodPost;

		/**
		 * @paragraph This property contains the PUT data request method name
		 * @brief CGI::MethodPut
		 * @var QString
		 */
		static QString MethodPut;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief CGI::Instance()
		 * @param bool bReset [false]
		 * @param QObject* qoParent [0]
		 * @return CGI* CGI::mInstance
		 */
		static CGI* Instance(bool bReset = false, QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor autmatically parses the HTTP headers and data
		 * @brief CGI::CGI()
		 * @param QObject* qoParent [0]
		 */
		explicit CGI(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a cookie to the instance
		 * @brief HeimdallGI::CGI::addCookie()
		 * @param QString strName
		 * @param QString strValue
		 * @param QDateTime qdtExpiration [QDateTime()]
		 * @param QString strDomain [NULL]
		 * @param QString strPath [NULL]
		 * @param bool bHttpOnly [false]
		 * @param bool bSecure [false]
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* addCookie(QString strName, QString strValue, QDateTime qdtExpiration = QDateTime(), QString strDomain = NULL, QString strPath = NULL, bool bHttpOnly = false, bool bSecure = false);

		/**
		 * @paragraph This method is a helper for the router to add parameters from URL routes
		 * @brief HeimdallGI::CGI::addParameter()
		 * @param QString strName
		 * @param QString strValue
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* addParameter(QString strName, QString strValue);

		/**
		 * @paragraph This method adds a response header to the instance
		 * @brief CGI::addResponseHeader()
		 * @param QString strName
		 * @param QString strValue
		 * @return CGI* CGI::mInstance
		 */
		CGI* addResponseHeader(QString strName, QString strValue);

		/**
		 * @paragraph This method adds a stack entry into the stack trace
		 * @brief HeimdallGI::CGI::addStackEntry()
		 * @param QString strFilename
		 * @param int intLineNumber
		 * @param QString strSnippet
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* addStackEntry(QString strFilename, int intLineNumber, QString strSnippet);

		/**
		 * @paragraph This method appends content to the response
		 * @brief HeimdallGI::CGI::appendToContent()
		 * @param QString strContent
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* appendToContent(QString strContent);

		/**
		 * @paragraph This method decodes a query string into a query map
		 * @brief CGI::decodeQuery()
		 * @param QString strQuery
		 * @param QString strPairSeparator ["&"]
		 * @return QVariantMap
		 */
		QVariantMap decodeQuery(QString strQuery, QString strPairSeparator = "&");

		/**
		 * @paragraph This method deletes a cookie from the request
		 * @brief HeimdallGI::CGI::deleteCookie()
		 * @param QString strName
		 * @param bool bSuccess [false]
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* deleteCookie(QString strName, bool &bSuccess);

		/**
		 * @paragraph This method encodes a query map into a query string
		 * @brief CGI::encodeQuery()
		 * @param QMap<QString, QString> qmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString encodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method encodes a query variant map into a query string
		 * @brief CGI::encodeQuery()
		 * @param QVariantMap qvmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString encodeQuery(QVariantMap qvmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method writes the HTTP response to the browser/socket
		 * @brief CGI::writeResponse()
		 * @param QString strContentType [NULL]
		 * @return void
		 */
		void writeResponse(QString strContentType = NULL);

		///////////////////////////////////////////////////////////////////////
		/// Determinants /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method determines if the data is JSON encoded
		 * @brief CGI::isJson()
		 * @param QString strData
		 * @return bool
		 */
		bool isJson(QString strData);

		/**
		 * @paragraph This method determines if the data is XML encoded
		 * @brief CGI::isXml()
		 * @param QString strData
		 * @return bool
		 */
		// bool isXml(QString strData);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the current response content in the instance
		 * @brief CGI::getContent()
		 * @return QString CGI::mContent
		 */
		QString getContent();

		/**
		 * @paragraph This method returns a cookie from the instance if one exists
		 * @brief CGI::GetCookie()
		 * @param QString strName
		 * @return QVariant
		 */
		QVariant getCookie(QString strName);

		/**
		 * @paragraph This method returns the current cookie map in the instance
		 * @brief CGI::getCookies()
		 * @return QVariantMap CGI::mCookies
		 */
		QVariantMap getCookies();

		/**
		 * @paragraph This method returns a GET/POST parameter from the instance if one exists
		 * @brief CGI::getParam()
		 * @param QString strName
		 * @return QVariant
		 */
		QVariant getParam(QString strName);

		/**
		 * @paragraph This method returns the current POST map from the instance
		 * @brief CGI::getPostData()
		 * @return QVariantMap CGI::mPostParameters
		 */
		QVariantMap getPostData();

		/**
		 * @paragraph This method returns the current GET map from the instance
		 * @brief CGI::getQueryData()
		 * @return QVariantMap CGI::mGetParameters
		 */
		QVariantMap getQueryData();

		/**
		 * @paragraph This method returns a request header from the instance if one exists
		 * @brief CGI::getRequestHeader()
		 * @param QString strName
		 * @return QString
		 */
		QString getRequestHeader(QString strName);

		/**
		 * @paragraph This method returns the current request header map in the instance
		 * @brief CGI::getRequestHeaders()
		 * @return QMap<QString, QString> CGI::mRequestHeaders
		 */
		QMap<QString, QString> getRequestHeaders();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the response content into the instance
		 * @brief CGI::setContent()
		 * @param QString strContent
		 * @return CGI* CGI::mInstance
		 */
		CGI* setContent(QString strContent);

		/**
		 * @paragraph This method sets the content type header into the instance
		 * @brief CGI::setContentType()
		 * @param QString strContentType
		 * @return CGI* CGI::mInstance
		 */
		CGI* setContentType(QString strContentType = CGI::ContentTypeHTML);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End Class Definition /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // HeimdallGI_CGI_H
