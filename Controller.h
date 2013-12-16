///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_CONTROLLER_H
#define HEIMDALLGI_CONTROLLER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "QUrlQuery"
#include "QVariantMap"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Controller Class Definition //////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief HeimdallGI::Controller
	 * @paragraph This class provides a wire frame for the controllers
	 */
	class Controller : public QObject
	{
		/**
		 * @brief Ensure this class is recognized as a Qt object
		 */
		Q_OBJECT

		/**
		 * @brief Ensure this class is recognized as a meta type
		 */
		Q_DECLARE_METATYPE(HeimdallGI::Controller)

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief HeimdallGI::Controller::mInstance
		 * @var HeimdallGI::Controller*
		 */
		static Controller* mInstance;


		/**
		 * @paragraph This property contains the class(es) to append to the body element
		 * @brief HeimdallGI::Controller::mBodyClass
		 * @var QString
		 */
		QString mBodyClass;


		/**
		 * @paragraph This property contains the body element onload subroutine
		 * @brief HeimdallGI::Controller::mBodyOnLoad
		 * @var QString
		 */
		QString mBodyOnLoad;


		/**
		 * @paragraph This property tells the system whether or not to disable the layout rendering
		 * @brief HeimdallGI::Controller::mDisableLayout
		 * @var bool
		 */
		bool mDisableLayout;


		/**
		 * @paragraph This property contains the page layout block name
		 * @brief HeimdallGI::Controller::mLayout
		 * @var QString
		 */
		QString mLayout;


		/**
		 * @paragraph This property contains the page's meta tags
		 * @brief HeimdallGI::Controller::mMetaTags
		 * @var QList<QList<QMap<QString, QString>>>
		 */
		QList<QList<QMap<QString, QString>>> mMetaTags;


		/**
		 * @paragraph This property contains the page title value
		 * @brief HeimdallGI::Controller::mPageTitle
		 * @var QString
		 */
		QString mPageTitle;


		/**
		 * @paragraph This property contains the page variables for the view
		 * @brief HeimdallGI::Controller::mPageValues
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mPageValues;


		/**
		 * @paragraph This property contains the Request associated with this controller
		 * @brief HeimdallGI::Controller::mRequestObject
		 * @var HeimdallGI::Request*
		 */
		HeimdallGI::Request* mRequestObject;


		/**
		 * @paragraph This property contains the page's scripts to load
		 * @brief HeimdallGI::Controller::mScripts
		 * @var QList<QList<QMap<QString, QString>>>
		 */
		QList<QList<QMap<QString, QString>>> mScripts;


		/**
		 * @paragraph This property contains the page's styleshets to load
		 * @brief HeimdallGI::Controller::mStylesheets
		 * @var QList<QList<QMap<QString, QString>>>
		 */
		QList<QList<QMap<QString, QString>>> mStylesheets;


		/**
		 * @paragraph This property contains the view object
		 * @brief HeimdallGI::Controller::mView
		 * @var HeimdallGI::View*
		 */
		HeimdallGI::View* mView;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method checks to see if a queried URI is the current REQUEST_URI
		 * @brief HeimdallGI::Controller::IsCurrentUrl()
		 * @param QString strUrl
		 * @return bool
		 */
		bool IsCurrentUrl(QString strUrl);

		/**
		 * @paragraph This method encodes and sends an HTTP Query String response for AJAX and API method endpoints
		 * @brief HeimdallGI::Controller::SendHttpQueryEndpointResponse()
		 * @param QVariantMap qvmResponse
		 * @return void
		 */
		void SendHttpQueryEndpointResponse(QVariantMap qvmResponse);

		/**
		 * @paragraph This method encodes and sends a JSON response for AJAX and API method endpoints
		 * @brief HeimdallGI::Controller::SendJsonEndpointResponse()
		 * @param QVariantMap qvmResponse
		 * @return void
		 */
		void SendJsonEndpointResponse(QVariantMap qvmResponse);

		/**
		 * @paragraph This method encodes and sends an XML response for AJAX and API method endpoints
		 * @brief HeimdallGI::Controller::SendXmlEndpointResponse()
		 * @param QVariantMap qvmResponse
		 * @return void
		 */
		void SendXmlEndpointResponse(QVariantMap qvmResponse);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant contains the CSS header content-type
		 * @brief HeimdallGI::Controller::ContentTypeCSS
		 * @var QString
		 */
		static QString ContentTypeCSS;

		/**
		 * @paragraph This constant contains the font header content-tyle
		 * @brief HeimdallGI::Controller::ContentTypeFont
		 * @var QString
		 */
		static QString ContentTypeFont;

		/**
		 * @paragraph This constant contains the EOT font header content-type
		 * @brief HeimdallGI::Controller::ContentTypeFontEOT
		 * @var QString
		 */
		static QString ContentTypeFontEOT;

		/**
		 * @paragraph This constant contains the OTF font header content-type
		 * @brief HeimdallGI::Controller::ContentTypeFontOTF
		 * @var QString
		 */
		static QString ContentTypeFontOTF;

		/**
		 * @paragraph This constant contains the TTF font header content-type
		 * @brief HeimdallGI::Controller::ContentTypeFontTTF
		 * @var QString
		 */
		static QString ContentTypeFontTTF;

		/**
		 * @paragraph This constant contains the WOFF font header content-type
		 * @brief HeimdallGI::Controller::ContentTypeFontWOFF
		 * @var QString
		 */
		static QString ContentTypeFontWOFF;

		/**
		 * @paragraph This constant contains the HTML header content-type
		 * @brief HeimdallGI::Controller::ContentTypeHTML
		 * @var QString
		 */
		static QString ContentTypeHTML;

		/**
		 * @paragraph This constant contains the gif header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImageGIF
		 * @var QString
		 */
		static QString ContentTypeImageGIF;

		/**
		 * @paragraoh This constant contains the jpeg header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImageJPEG
		 * @var QString
		 */
		static QString ContentTypeImageJPEG;

		/**
		 * @paragraph This constant contains the jpg header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImageJPG
		 * @var QString
		 */
		static QString ContentTypeImageJPG;

		/**
		 * @paragraph This constant contains the png header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImagePNG
		 * @var QString
		 */
		static QString ContentTypeImagePNG;

		/**
		 * @paragraph This constant contains the svg header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImageSVG
		 * @var QString
		 */
		static QString ContentTypeImageSVG;

		/**
		 * @paragraph This constant contains the tif header content-type
		 * @brief HeimdallGI::Controller::ContentTypeImageTIF
		 * @var QString
		 */
		static QString ContentTypeImageTIF;

		/**
		 * @paragraph This constant contains the JSON header content-type
		 * @brief HeimdallGI::Controller::ContentTypeJSON
		 * @var QString
		 */
		static QString ContentTypeJSON;

		/**
		 * @paragraph This constant contains the ecmascript script type constant
		 * @brief HeimdallGI::Controller::ContentTypeScriptECMA
		 * @var QString
		 */
		static QString ContentTypeScriptECMA;

		/**
		 * @paragraph This constant contains the javascript script type constant
		 * @brief HeimdallGI::Controller::ContentTypeScriptJS
		 * @var QString
		 */
		static QString ContentTypeScriptJS;

		/**
		 * @paragraph This constant contains the vbscript script type constant
		 * @brief HeimdallGI::Controller::ContentTypeScriptVB
		 * @var QString
		 */
		static QString ContentTypeScriptVB;

		/**
		 * @paragraph This constant contains the TXT header content-type
		 * @brief HeimdallGI::Controller::ContentTypeText
		 * @var QString
		 */
		static QString ContentTypeText;

		/**
		 * @paragraph This constant contains the XML header content-type
		 * @brief HeimdallGI::Controller::ContentTypeXML
		 * @var QString
		 */
		static QString ContentTypeXML;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::Controller::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::Controller* HeimdallGI::Controller::mInstance
		 */
		static Controller* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets up the class and is public so that this class can be recognized as a meta type
		 * @brief HeimdallGI::Controller()
		 * @param QObject* qoParent [0]
		 */
		explicit Controller(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a meta tag for the current page
		 * @brief HeimdallGI::Controller::AddMetaTag()
		 * @param QString strName
		 * @param QString strContent
		 * @param QString strHttpEquivalent [NULL]
		 * @param QString strScheme [NULL]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* AddMetaTag(QString strName, QString strContent, QString strHttpEquivalent = NULL, QString strScheme = NULL);

		/**
		 * @paragraph This method adds a script to the current page
		 * @brief HeimdallGI::Controller::AddScript()
		 * @param QString strSource
		 * @param QString strType [HeimdallGI::Controller::ContentTypeScriptJS]
		 * @param bool $bSourceIsLink [true]
		 * @param bool $bForHeader [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* AddScript(QString strSource, QString strType = HeimdallGI::Controller::ContentTypeScriptJS, bool $bSourceIsLink = true, bool $bForHeader = true);

		/**
		 * @paragraph This method adds a stylesheet to the current page
		 * @brief HeimdallGI::Controller::AddStylesheet()
		 * @param QString strSource
		 * @param bool bSourceIsLink [true]
		 * @param QString strMedia [NULL]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* AddStylesheet(QString strSource, bool bSourceIsLink = true, QString strMedia = NULL);

		/**
		 * @paragraph This method redirects the current request
		 * @brief HeimdallGI::Controller::RedirectRequest()
		 * @param QString strUrl
		 * @return void
		 */
		void RedirectRequest(QString strUrl);

		/**
		 * @paragraph This method renders the layout for this controller
		 * @brief HeimdallGI::Controller::RenderLayout()
		 * @return QString
		 */
		QString RenderLayout();

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method generates a blob URL for displaying and downloading binaries
		 * @brief HeimdallGI::Controller::GetBlobUrl()
		 * @param QString strBlob
		 * @param QString strMimeType
		 * @return QString
		 */
		QString GetBlobUrl(QString strBlob, QString strMimeType);

		/**
		 * @paragraph This method returns the body's class attribute
		 * @brief HeimdallGI::Controller::GetBodyClass()
		 * @return QString HeimdallGI::Controller::mBodyClass
		 */
		QString GetBodyClass();

		/**
		 * @paragraph This method returns the body's onload attribute
		 * @brief HeimdallGI::Controller::GetBodyOnLoad()
		 * @return QString HeimdallGI::Controller::mBodyOnLoad
		 */
		QString GetBodyOnLoad();

		/**
		 * @paragraph This method generates a URL to a database image
		 * @brief HeimdallGI::Controller::GetDatabaseImageUrl()
		 * @param QString strTable
		 * @param QString strPrimaryKeyColumn
		 * @param int intPrimaryKey
		 * @param QString strImageColumn
		 * @param QString strMimeTypeColumn
		 * @return QString
		 */
		QString GetDatabaseImageUrl(QString strTable, QString strPrimaryKeyColumn, int intPrimaryKey, QString strImageColumn, QString strMimeTypeColumn);

		/**
		 * @paragraph This method returns the current layout status
		 * @brief HeimdallGI::Controller::GetDisableLayout()
		 * @return bool HeimdallGI::Controller::mDisableLayout
		 */
		bool GetDisableLayout();

		/**
		 * @paragraph This method generates an image URL
		 * @brief HeimdallGI::Controller::GetImageUrl()
		 * @return QString
		 */
		QString GetImageUrl($sImage);

		/**
		 * @paragraph This method returns the current layout block
		 * @brief HeimdallGI::Controller::GetLayout()
		 * @return QString HeimdallGI::Controller::mLayout
		 */
		QString GetLayout();

		/**
		 * @paragraph This method returns the meta tags stored in the controller instance
		 * @brief HeimdallGI::Controller::GetMetaTags()
		 * @return QList<QList<QMap<QString, QString>>> HeimdallGI::Controller::mMetaTags
		 */
		QList<QList<QMap<QString, QString>>> GetMetaTags();

		/**
		 * @paragraph This method returns the meta tags stored in the controller instance as HTML
		 * @brief HeimdallGI::Controller::GetMetaTags()
		 * @return QString
		 */
		QString GetMetaTags();

		/**
		 * @paragraph This method returns the current page title
		 * @brief HeimdallGI::Controller::GetPageTitle()
		 * @return QString HeimdallGI::Controller::mPageTitle
		 */
		QString GetPageTitle();

		/**
		 * @paragraph This method returns a page value if it exists
		 * @brief HeimdallGI::Controller::GetPageValue()
		 * @param Qstring strKey
		 * @return QString
		 */
		QString GetPageValue(QString strKey);

		/**
		 * @paragraph This method returns the request object instance
		 * @brief HeimdallGI::Controller::GetRequest()
		 * @return HeimdallGI::Request* HeimdallGI::Controller::mRequestObject
		 */
		HeimdallGI::Request* GetRequest();

		/**
		 @ paragraph This method returns the scripts that are stored in the instance
		 * @brief HeimdallGI::Controller::GetScripts()
		 * @return QList<QList<QMap<QString, QString>>> HeimdallGI::Controller::mScripts
		 */
		QList<QList<QMap<QString, QString>>> GetScripts();

		/**
		 * @paragraph This method returns the scripts that are stored in the instance as HTML
		 * @brief HeimdallGI::Controller::GetScripts()
		 * @param bool bForHeader [true]
		 * @return QString
		 */
		QString GetScripts(bool bForHeader = true);

		/**
		 * @paragraph This method returns the url for multiple scripts
		 * @brief HeimdallGI::Controller::GetScriptUrl()
		 * @param QStringList qslScripts
		 * @param QString strVersion [NULL]
		 * @param bool bMinify [true]
		 * @return QString
		 */
		QString GetScriptUrl(QStringList qslScripts, QString strVersion = NULL, bool bMinify = true);

		/**
		 * @paragraph This method returns the url for a single script
		 * @brief HeimdallGI::Controller::GetScriptUrl()
		 * @param QString strScript
		 * @param QString strVersion [NULL]
		 * @param bool bMinify [true]
		 * @return QString
		 */
		QString GetScriptUrl(QString strScript, QString strVersion = NULL, bMinify = true);

		/**
		 * @paragraph This method returns the styles that are stored in the instance
		 * @brief HeimdallGI::Controller::GetStyles()
		 * @return QList<QList<QMap<QString, QString>>> HeimdallGI::Controller::mStylesheets
		 */
		QList<QList<QMap<QString, QString>>> GetStyles();

		/**
		 * @paragraph This method returns the styles that are stored in the instance as HTML
		 * @brief HeimdallGI::Controller::GetStyles()
		 * @return QString
		 */
		QString GetStyles();

		/**
		 * @paragraph This method generates a URL for multiple stylesheets
		 * @brief HeimdallGI::Controller::GetStyleUrl()
		 * @param QStringList qslScripts
		 * @param QString strVersion [NULL]
		 * @param bool bMinify [true]
		 * @return QString
		 */
		QString GetStyleUrl(QStringList qslScripts, QString strVersion = NULL, bool bMinify = true);

		/**
		 * @paragraph This method generate a URL for a single stylesheet
		 * @brief HeimdallGI::Controller::GetStyleUrl()
		 * @param QString strStyle
		 * @param QString strVersion [NULL]
		 * @param bool bMinify [true]
		 * @return QString
		 */
		QString GetStyleUrl(QString strStyle, QString strVersion = NULL, bool bMinify = true);

		/**
		 * @paragraph This method builds a URL and returns it
		 * @brief HeimdallGI::Controller::GetUrl()
		 * @param QString strAction
		 * @param QString strController [NULL]
		 * @param QMap<QString, QString> qmParameters [QMap<QString, QString>()]
		 * @return
		 */
		QString GetUrl(QString strAction, QString strController = NULL, QMap<QString, QString> qmParameters = QMap<QString, QString>());

		/**
		 * @paragraph This method returns the current view instance
		 * @brief HeimdallGI::Controller::GetView()
		 * @return HeimdallGI::View* HeimdallGI::Controller::mView
		 */
		HeimdallGI::View* GetView();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the body's class attribute
		 * @brief HeimdallGI::Controller::SetBodyClass()
		 * @param QString strClass
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetBodyClass(QString strClass);

		/**
		 * @paragraph This method sets the body's onload attribute
		 * @brief HeimdallGI::Controller::SetBodyOnload()
		 * @param QString strRoutine
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetBodyOnload(QString strRoutine);

		/**
		 * @paragraph This method sets the layout's status
		 * @brief HeimdallGI::Controller::SetDisableLayout()
		 * @param bool bDisable [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetDisableLayout(bool bDisable = true);

		/**
		 * @paragraph This method turns the current action into an HTML AJAX or API endpoint
		 * @brief HeimdallGI::Controller::SetEndpointHtml()
		 * @param bool bDisableView [false]
		 * @param bool bDisableLayout [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetEndpointHtml(bool bDisableView = false, bool bDisableLayout = true);

		/**
		 * @paragraph This method turns the current action into a JSON AJAX or API endpoint
		 * @brief HeimdallGI::Controller::SendEndpointJson()
		 * @param bool bDisableView [false]
		 * @param bool bDisableLayout [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SendEndpointJson(bool bDisableView = false, bool bDisableLayout = true);

		/**
		 * @paragraph This method turns the current action into a text AJAX or API endpoint
		 * @brief HeimdallGI::Controller::SetEndpointText()
		 * @param bool bDisableView [false]
		 * @param bool bDisableLayout [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetEndpointText(bool bDisableView = false, bool bDisableLayout = true);

		/**
		 * @paragraph This method turns the current action into an XML AJAX or API endpoint
		 * @brief HeimdallGI::Controller::SetEndpointXml()
		 * @param bool bDisableView [false]
		 * @param bool bDisableLayout [true]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetEndpointXml(bool bDisableView = false, bool bDisableLayout = true);

		/**
		 * @paragraph This method sets the content-length header
		 * @brief HeimdallGI::Controller::SetHeaderContentLength()
		 * @param int intLength
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetHeaderContentLength(int intLength);

		/**
		 * @paragraph This method sets the content-length header
		 * @brief HeimdallGI::Controller::SetHeaderContentLength()
		 * @param QString strLength
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetHeaderContentLength(QString strLength);

		/**
		 * @paragraph This method sets the content-type header
		 * @brief HeimdallGI::Controller::SetHeaderContentType()
		 * @param QString strContentType [HeimdallGI::Controller::ContentTypeHTML]
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetHeaderContentType(QString strContentType = HeimdallGI::Controller::ContentTypeHTML);

		/**
		 * @paragraph This method sets the path to the layout block into the instance
		 * @brief HeimdallGI::Controller::SetLayout()
		 * @param QString strLayoutBlock
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetLayout(QString strLayoutBlock);

		/**
		 * @paragraph This method sets the page title into the instance
		 * @brief HeimdallGI::Controller::SetPageTitle()
		 * @param QString strPageTitle
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetPageTitle(QString strPageTitle);

		/**
		 * @paragraph This method sets a page value into the instance
		 * @brief HeimdallGI::Controller::SetPageValue()
		 * @param QString strKey
		 * @param QString strValue
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetPageValue(QString strKey, QString strValue);

		/**
		 * @paragraph This method sets the request object into the instance
		 * @brief HeimdallGI::Controller::SetRequest()
		 * @param HeimdallGI::Request* hgrRequest
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetRequest(HeimdallGI::Request* hgrRequest);

		/**
		 * @paragraph This method sets the view object into the instance
		 * @brief HeimdallGI::Controller::SetView()
		 * @param HeimdallGI::View* hgvView
		 * @return HeimdallGI::Controller* this
		 */
		Controller* SetView(HeimdallGI::View* hgvView);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End //////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // HEIMDALLGI_CONTROLLER_H
