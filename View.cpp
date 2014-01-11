///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "View.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	View* View::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	View* View::Instance(bool bReset) {
		// Check for an instance or reset notification
		if ((mInstance == NULL) || (bReset == false)) {
			// Create a new instance
			mInstance = new View();
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	View::View(QObject* qoParent) : QObject(qoParent), mShowView(true) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	View* View::AddMetaTag(QString strName, QString strContent, QString strHttpEquivalent, QString strScheme) {
		// Create the structure
		MetaTag structMetaTag;
		// Set the name
		structMetaTag.setName(strName);
		// Set the content
		structMetaTag.setContent(strContent);
		// Set the HTTP-EQUIV
		structMetaTag.setHttpEquivalent(strHttpEquivalent);
		// Set the scheme
		structMetaTag.setScheme(strScheme);
		// Add the tag to the view
		this->mMetaTags.append(structMetaTag);
		// Return the instance
		return this;
	}

	View* View::AddScript(QString strSource, QString strType, bool bSourceIsRaw, bool bHeaderScript) {
		// Create the structure
		Script structScript;
		// Set the source
		structScript.setSource(strSource);
		// Set the type
		structScript.setType(strType);
		// Set the source type
		structScript.setRaw(bSourceIsRaw);
		// Set the placement
		structScript.setPlacement(bHeaderScript);
		// Add the script to the view
		this->mScripts.append(structScript);
		// Return the instance
		return this;
	}

	View* View::AddStyle(QString strSource, bool bSourceIsRaw, QString strRelativity, QString strMedia) {
		// Create the structure
		Style structStyle;
		// Set the source
		structStyle.setSource(strSource);
		// Set the source type
		structStyle.setRaw(bSourceIsRaw);
		// Set the relativity
		structStyle.setRelativity(strRelativity);
		// Set the media
		structStyle.setMedia(strMedia);
		// Add the style to the view
		this->mStyles.append(structStyle);
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString View::GetMetaTags() {
		// Create the return string
		QStringList qslMetaTags;
		// Iterate over the meta tags
		for (int intMetaTag = 0; intMetaTag < this->mMetaTags.size(); ++intMetaTag) {
			// Localize the meta tag
			MetaTag mtTag = this->mMetaTags.at(intMetaTag);
			// Create the attribute placeholder
			QMap<QString, QString> qmAttributes;
			// Check for HTTP Equivalent
			if (!mtTag.getHttpEquivalent().isEmpty()) {
				// Set the http-equiv attribute
				qmAttributes.insert("http-equiv", mtTag.getHttpEquivalent());
			}
			// Check for a scheme
			if (!mtTag.getScheme().isEmpty()) {
				// Set the scheme attribute
				qmAttributes.insert("scheme", mtTag.getScheme());
			}
			// Add the tag to the list
			qslMetaTags.append(HTML::Instance()->Meta(mtTag.getName(), mtTag.getContent(), qmAttributes));
		}
		// Return the meta tags
		return qslMetaTags.join("\n");
	}

	QVariant View::GetPageValue(QString strName) {
		// Return the value
		return this->mPageValues[strName];
	}

	QVariantMap View::GetPageValues() {
		// Return the page values
		return this->mPageValues;
	}

	QString View::GetScripts(bool bHeader) {
		// Create the return placeholder
		QStringList qslScripts;
		// Iterate over the scripts
		for (int intScript = 0; intScript < this->mScripts.size(); ++intScript) {
			// Localize the script
			Script tagScript = this->mScripts.at(intScript);
			// Check for header/footer
			if (tagScript.getPlacement() == bHeader) {
				// Append the script tag to the list
				qslScripts.append(HTML::Instance()->Script(tagScript.getType(), tagScript.getSource(), (tagScript.getRaw() ? true : false), HTML::GetEmptyAttributeContainer()));
			}
		}
		// Return the scripts
		return qslScripts.join("\n");
	}

	QString View::GetStyles() {
		// Create the return placeholder
		QStringList qslStyles;
		// Iterate over the styles
		for (int intStyle = 0; intStyle < this->mStyles.size(); ++intStyle) {
			// Localize the script
			Style tagStyle = this->mStyles.at(intStyle);
			// Check to see if the style is inline
			if (tagStyle.getRaw()) {
				// Append the element
				qslStyles.append(HTML::Instance()->Style(CGI::ContentTypeCSS, tagStyle.getSource(), HTML::GetEmptyAttributeContainer()));
			} else {
				// Create the attributes placeholder
				QMap<QString, QString> qmAttributes;
				// Check for media
				if (!tagStyle.getMedia().isEmpty()) {
					// Add the media to the attributes
					qmAttributes.insert("media", tagStyle.getMedia());
				}
				// Append the element
				qslStyles.append(HTML::Instance()->Link(tagStyle.getRelativity().isEmpty() ? "" : tagStyle.getRelativity(), CGI::ContentTypeCSS, tagStyle.getSource(), qmAttributes));
			}
		}
		// Return the styles
		return qslStyles.join("\n");
	}

	QString View::GetTemplate() {
		// Return the view template
		return this->mTemplate;
	}

	bool View::GetViewStatus() {
		// Return the view status
		return this->mShowView;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	View* View::SetPageValue(QString strName, QVariant strValue) {
		// Add the page value
		this->mPageValues.insert(strName, strValue);
		// Return the instance
		return this;
	}

	View* View::SetTemplate(QString strTemplate) {
		// Set the template into the instance
		this->mTemplate = strTemplate;
		// Return the instance
		return this;
	}

	View* View::SetViewStatus(bool bShowView) {
		// Set the view status
		this->mShowView = bShowView;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
