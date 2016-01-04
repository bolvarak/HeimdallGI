///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_VIEW_H
#define HEIMDALLGI_VIEW_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "QVariantMap"
#include "QVariant"
#include "CGI.h"
#include "HTML.h"
#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This structure maintains meta tags for the view
	 * @brief HeimdallGI::MetaTag
	 */
	struct MetaTag {

		///////////////////////////////////////////////////////////////////////
		/// Properties //////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the meta tag content
		 * @brief HeimdallGI::MetaTag::mContent
		 * @var QString
		 */
		QString mContent;

		/**
		 * @paragraph This property contains the HTTP-EQUIV attribute
		 * @brief HeimdallGI::MetaTag::mHttpEquivalent
		 * @var QString
		 */
		QString mHttpEquivalent;

		/**
		 * @paragraph This property contains the scheme attribute
		 * @brief HeimdallGI::MetaTag::mScheme
		 * @var QString
		 */
		QString mScheme;

		/**
		 * @paragraph This property contains the name attribute
		 * @brief HeimdallGI::MetaTag::mName
		 * @var QString
		 */
		QString mName;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		MetaTag() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the tag's content
		 * @brief HeimdallGI::MetaTag::getContent()
		 * @return QString HeimdallGI::MetaTag::mContent
		 */
		QString getContent() {
			// Return the content for this tag
			return mContent;
		}

		/**
		 * @paragraph This method returns the tag's HTTP-EQUIV attribute
		 * @brief HeimdallGI::MetaTag::getHttpEquivalent()
		 * @return QString HeimdallGI::MetaTag::mHttpEquivalent
		 */
		QString getHttpEquivalent() {
			// Return the HTTP-EQUIV attribute
			return mHttpEquivalent;
		}

		/**
		 * @paragraph This method returns the tag's scheme attribute
		 * @brief HeimdallGI::MetaTag::getScheme()
		 * @return QString HeimdallGI::MetaTag::mScheme
		 */
		QString getScheme() {
			// Return the scheme attribute
			return mScheme;
		}

		/**
		 * @paragraph This method returns the tag's name attribute
		 * @brief HeimdallGI::MetaTag::getName()
		 * @return QString HeimdallGI::MetaTag::mName
		 */
		QString getName() {
			// Return the name attribute
			return mName;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the tag's content
		 * @brief HeimdallGI::MetaTag::setContent()
		 * @param QString strContent
		 * @retrurn void
		 */
		void setContent(QString strContent) {
			// Set the tag's content
			mContent = strContent;
		}

		/**
		 * @paragraph This method sets the tag's HTTP-EQUIV attribute
		 * @brief HeimdallGI::MetaTag::setHttpEquivalent()
		 * @param QString strHttpEquivalent
		 * @return void
		 */
		void setHttpEquivalent(QString strHttpEquivalent) {
			// Set the tag's HTTP-EQUIV
			mHttpEquivalent = strHttpEquivalent;
		}

		/**
		 * @paragraph This method sets the tag's scheme attribute
		 * @brief HeimdallGI::MetaTag::setScheme()
		 * @param QString strScheme
		 * @return void
		 */
		void setScheme(QString strScheme) {
			// Set the tag's scheme
			mScheme = strScheme;
		}

		/**
		 * @paragraph This method sets the tag's name attribute
		 * @brief HeimdallGI::MetaTag::setName()
		 * @param QString strName
		 * @return void
		 */
		void setName(QString strName) {
			// Set the tag's name
			mName = strName;
		}
	};

	/**
	 * @paragraph This structure maintains page values for the view
	 * @brief HeimdallGI::PageValue
	 */
	struct PageValue{

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the name of the page value
		 * @brief HeimdallGI::PageValue::mName
		 * @var QString
		 */
		QString mName;

		/**
		 * @paragraph This property contains the value of the page value
		 * @brief HeimdallGI::PageValue::mValue
		 * @var QVariant
		 */
		QVariant mValue;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		PageValue() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the name set to the page value
		 * @brief HeimdallGI::PageValue::getName()
		 * @return QString HeimdallGI::PageValue::mName
		 */
		QString getName() {
			// Return the page value's name
			return mName;
		}

		/**
		 * @paragraph This method returns the value set to the page value
		 * @brief HeimdallGI::PageValue::getValue()
		 * @return QVariant HeimdallGI::PageValue::mValue
		 */
		QVariant getValue() {
			// Return the page value's value
			return mValue;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the name to the page value
		 * @brief HeimdallGI::PageValue::setName()
		 * @param QString strName
		 * @return void
		 */
		void setName(QString strName) {
			// Set the page value's name
			mName = strName;
		}

		/**
		 * @paragraph This method sets the value to the page value
		 * @brief HeimdallGI::PageValue::setValue()
		 * @param QVariant qvValue
		 * @return void
		 */
		void setValue(QVariant qvValue) {
			// Set the page value's value
			mValue = qvValue;
		}
	};

	/**
	 * @paragraph This structure maintains script tags for the view
	 * @brief HeimdallGI::Script
	 */
	struct Script {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property notifies where this script should be placed
		 * @brief HeimdallGI::Script::mHeaderScript
		 * @var bool
		 */
		bool mHeaderScript;

		/**
		 * @paragraph This property notifies if this script is a link or raw
		 * @brief HeimdallGI::Script::mRaw
		 * @var bool
		 */
		bool mRaw;

		/**
		 * @paragraph This property contains the script source
		 * @brief HeimdallGI::Script::mSource
		 * @var QString
		 */
		QString mSource;

		/**
		 * @paragraph This property contains the script's mime-type
		 * @brief mType
		 */
		QString mType;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Script() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the script's placement
		 * @brief HeimdallGI::Script::getPlacement()
		 * @return bool HeimdallGI::Script::mHeaderScript
		 */
		bool getPlacement() {
			// Return the header script placement
			return mHeaderScript;
		}

		/**
		 * @paragraph This method returns the script source type
		 * @brief HeimdallGI::Script::getRaw()
		 * @return bool HeimdallGI::Script::mRaw
		 */
		bool getRaw() {
			// Return the script source type
			return mRaw;
		}

		/**
		 * @paragraph This method returns the script's source
		 * @brief HeimdallGI::Script::getSource()
		 * @return QString HeimdallGI::Script::mSource
		 */
		QString getSource() {
			// Return the script source
			return mSource;
		}

		/**
		 * @paragraph This method returns the script's Mime-Type
		 * @brief HeimdallGI::Script::getType()
		 * @return QString HeimdallGI::Script::mType
		 */
		QString getType() {
			// Return the script type
			return mType;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the placement of the script
		 * @brief HeimdallGI::Script::setPlacement()
		 * @param bool bHeaderScript
		 * @return void
		 */
		void setPlacement(bool bHeaderScript) {
			// Set the script's placement
			mHeaderScript = bHeaderScript;
		}

		/**
		 * @paragraph This method sets the script source type
		 * @brief HeimdallGI::Script::setRaw()
		 * @param bool bSoureIsRaw
		 * @return void
		 */
		void setRaw(bool bSoureIsRaw) {
			// Set the script source type
			mRaw = bSoureIsRaw;
		}

		/**
		 * @paragraph This method sets the script's source
		 * @brief HeimdallGI::Script::setSource()
		 * @param QString strSource
		 * @return void
		 */
		void setSource(QString strSource) {
			// Set the script source
			mSource = strSource;
		}

		/**
		 * @paragraph This method sets the script's Mime-Type
		 * @brief HeimdallGI::Script::setType()
		 * @param QString strMimeType
		 * @return void
		 */
		void setType(QString strMimeType) {
			// Set the script's Mime-Type
			mType = strMimeType;
		}
	};

	/**
	 * @paragraph This structure maintains styles for the view
	 * @brief HeimdallGI::Style
	 */
	struct Style {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the style's media attribute
		 * @brief HeimdallGI::Style::mMedia
		 * @var QString
		 */
		QString mMedia;

		/**
		 * @paragraph This property contains the style type
		 * @brief HeimdallGI::Style::mRaw
		 * @var bool
		 */
		bool mRaw;

		/**
		 * @paragraph This property contains the relativity of the style
		 * @brief HeimdallGI::Style::mRelativity
		 * @var QString
		 */
		QString mRelativity;

		/**
		 * @paragraph This property contains the style's source
		 * @brief HeimdallGI::Style::mSource
		 * @var QString
		 */
		QString mSource;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		Style() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the style's media attribute
		 * @brief HeimdallGI::Style::getMedia()
		 * @return QString HeimdallGI::Style::mMedia
		 */
		QString getMedia() {
			// Return the style's media attribute
			return mMedia;
		}

		/**
		 * @paragraph This method returns the style's type
		 * @brief HeimdallGI::Style::getRaw()
		 * @return bool HeimdallGI::Style::mRaw
		 */
		bool getRaw() {
			// Return the style's type
			return mRaw;
		}

		/**
		 * @paragraph This method returns the style's relativity
		 * @brief HeimdallGI::Style::getRelativity()
		 * @return QString HeimdallGI::Style::mRelativity
		 */
		QString getRelativity() {
			// Return the style's relativity
			return mRelativity;
		}

		/**
		 * @paragraph This method returns the style's source
		 * @brief HeimdallGI::Style::getSource()
		 * @return QString HeimdallGI::Style::mSource
		 */
		QString getSource() {
			// Return the style's source
			return mSource;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the style's media attribute
		 * @brief HeimdallGI::Style::setMedia()
		 * @param QString strMedia
		 * @return void
		 */
		void setMedia(QString strMedia) {
			// Set the style's media attribute
			mMedia = strMedia;
		}

		/**
		 * @paragraph This method sets the source type
		 * @brief HeimdallGI::Style::setRaw()
		 * @param bool bSourceIsRaw
		 * @return void
		 */
		void setRaw(bool bSourceIsRaw) {
			// Set the style's type
			mRaw = bSourceIsRaw;
		}

		/**
		 * @paragraph This method sets the style's relativity
		 * @brief HeimdallGI::Style::setRelativity()
		 * @param QString strRelativity
		 * @return void
		 */
		void setRelativity(QString strRelativity) {
			// Set the style's relativity
			mRelativity = strRelativity;
		}

		/**
		 * @paragraph This method sets the style's source
		 * @brief HeimdallGI::Style::setSource()
		 * @param QString strSource
		 * @return void
		 */
		void setSource(QString strSource) {
			// Set the style's source
			mSource = strSource;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::View Class Definition ////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class View : public QObject
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
		 * @brief HeimdallGI::View::mInstance
		 * @var HeimdallGI::View*
		 */
		static View* mInstance;

		/**
		 * @paragraph This property contains the layout view file
		 * @brief HeimdallGI::View::mLayout
		 * @var QString
		 */
		QString mLayout;

		/**
		 * @paragraph This property contains a list of meta tags for the header
		 * @brief HeimdallGI::View::mMetaTags
		 * @var QList<MetaTag>
		 */
		QList<MetaTag> mMetaTags;

		/**
		 * @paragraph This property contains the variables for the view
		 * @brief HeimdallGI::View::mPageValues
		 * @var QVariantMap
		 */
		QVariantMap mPageValues;

		/**
		 * @paragraph This property contains the scripts for the view
		 * @brief mScripts
		 * @var QList<Script>
		 */
		QList<Script> mScripts;

		/**
		 * @paragraph This property sets a flag that determines whether the view should be shown or not
		 * @brief HeimdallGI::View::mShowView
		 * @var bool
		 */
		bool mShowView;

		/**
		 * @paragraph This property contains the stylesheets for the header
		 * @brief HeimdallGI::View::mStyles
		 * @var QList<Style>
		 */
		QList<Style> mStyles;

		/**
		 * @paragraph This property contains the link to the template file for this view
		 * @brief HeimdallGI::View::mTemplate
		 * @var QString
		 */
		QString mTemplate;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains the singleton instance of this class
		 * @brief HeimdallGI::View::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		static View* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit View(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a meta tag to the view
		 * @brief HeimdallGI::View::AddMetaTag()
		 * @param QString strName
		 * @param QString strContent
		 * @param QString strHttpEquivalent [NULL]
		 * @param QString strScheme [NULL]
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* addMetaTag(QString strName, QString strContent, QString strHttpEquivalent = NULL, QString strScheme = NULL);

		/**
		 * @paragraph This method adds a script to the view
		 * @brief HeimdallGI::View::AddScript()
		 * @param QString strSource
		 * @param QString strType [HeimdallGI::CGI::ContentTypeJS]
		 * @param bool bSourceIsRaw [false]
		 * @param bool bHeaderScript [true]
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* addScript(QString strSource, QString strType = CGI::ContentTypeJS, bool bSourceIsRaw = false, bool bHeaderScript = true);

		/**
		 * @paragraph This method adds a style to the view
		 * @brief HeimdallGI::View::AddStyle()
		 * @param QString strSource
		 * @param bool bSourceIsRaw [false]
		 * @param QString strRelativity [stylesheet]
		 * @param QString strMedia [NULL]
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* addStyle(QString strSource, bool bSourceIsRaw = false, QString strRelativity = "stylesheet", QString strMedia = NULL);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the layout from the instance
		 * @brief HeimdallGI::View::GetLayout()
		 * @return QString HeimdallGI::View::mLayout
		 */
		QString getLayout();

		/**
		 * @paragraph This method returns the meta tags for the view
		 * @brief HeimdallGI::View::GetMetaTags()
		 * @return QString
		 */
		QString getMetaTags();

		/**
		 * @paragraph This method returns a variable from the view
		 * @brief HeimdallGI::View::GetPageValue()
		 * @param QString strName
		 * @return QVariantMap
		 */
		QVariant getPageValue(QString strName);

		/**
		 * @paragraph This method returns the PageValues map
		 * @brief HeimdallGI::View::GetPageValues()
		 * @return QVariantMap HeimdallGI::View::mPageValues
		 */
		QVariantMap getPageValues();

		/**
		 * @paragraph This method returns the scripts for the view
		 * @brief HeimdallGI::View::GetScripts()
		 * @param bool bHeader [true]
		 * @return QString
		 */
		QString getScripts(bool bHeader = true);

		/**
		 * @paragraph This method returns the styles for the view
		 * @brief HeimdallGI::View::GetStyles()
		 * @return QString
		 */
		QString getStyles();

		/**
		 * @paragraph This method returns the template file for the view
		 * @brief HeimdallGI::View::GetTemplate()
		 * @return QString HeimdallGI::View::mTemplate
		 */
		QString getTemplate();

		/**
		 * @paragraph This method returns the view status
		 * @brief HeimdallGI::View::GetViewStatus()
		 * @return bool HeimdallGI::View::mShowView
		 */
		bool getViewStatus();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the layout into the instance
		 * @brief HeimdallGI::View::SetLayout()
		 * @param QString strLayout
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* setLayout(QString strLayout);

		/**
		 * @paragraph This method sets a variable into the view
		 * @brief HeimdallGI::View::SetPageValue()
		 * @param QString strName
		 * @param QVariant qvValue
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* setPageValue(QString strName, QVariant qvValue);

		/**
		 * @paragraph This method sets the template file into the view
		 * @brief HeimdallGI::View::SetTemplate()
		 * @param QString strTemplate
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* setTemplate(QString strTemplate);

		/**
		 * @paragraph This method sets the view status
		 * @brief HeimdallGI::View::SetViewStatus()
		 * @param bool bShowView [false]
		 * @return HeimdallGI::View* HeimdallGI::View::mInstance
		 */
		View* setViewStatus(bool bShowView = false);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::View Class Definition ////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace HeimdallGI

#endif // HEIMDALLGI_VIEW_H
