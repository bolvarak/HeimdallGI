///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "HTML.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	HTML* HTML::mInstance                     = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString HTML::AttributeAlternate          = "alt";
	QString HTML::AttributeCharset            = "charset";
	QString HTML::AttributeClass              = "class";
	QString HTML::AttributeContent            = "content";
	QString HTML::AttributeDescription        = "desciption";
	QString HTML::AttributeHeight             = "height";
	QString HTML::AttributeHypertextReference = "href";
	QString HTML::AttributeHttpEquivalent     = "http-equiv";
	QString HTML::AttributeIdentifier         = "id";
	QString HTML::AttributeMaximumLength      = "maxlength";
	QString HTML::AttributeMedia              = "media";
	QString HTML::AttributeName               = "name";
	QString HTML::AttributePlaceholder        = "placeholder";
	QString HTML::AttributePrefix             = "prefix";
	QString HTML::AttributeProperty           = "property";
	QString HTML::AttributeRelativity         = "rel";
	QString HTML::AttributeSize               = "size";
	QString HTML::AttributeSizes              = "sizes";
	QString HTML::AttributeSource             = "src";
	QString HTML::AttributeStyle              = "style";
	QString HTML::AttributeTitle              = "title";
	QString HTML::AttributeType               = "type";
	QString HTML::AttributeWidth              = "width";
	QString HTML::InputButton                 = "button";
	QString HTML::InputCheckbox               = "checkbox";
	QString HTML::InputFile                   = "file";
	QString HTML::InputHidden                 = "hidden";
	QString HTML::InputImage                  = "image";
	QString HTML::InputPassword               = "password";
	QString HTML::InputRadio                  = "radio";
	QString HTML::InputReset                  = "reset";
	QString HTML::InputSubmit                 = "submit";
	QString HTML::InputText                   = "text";
	QString	HTML::PropertyDisabled            = "disabled";
	QString HTML::PropertyReadOnly            = "readonly";
	QString HTML::PropertyRequired            = "required";
	QString HTML::PropertySelected            = "selected";
	QString HTML::TagAnchor                   = "a";
	QString HTML::TagBody                     = "body";
	QString HTML::TagBold                     = "b";
	QString HTML::TagButton                   = "button";
	QString HTML::TagCaption                  = "caption";
	QString HTML::TagDefinitionDescription    = "dd";
	QString HTML::TagDefinitionList           = "dl";
	QString HTML::TagDefinitionTerm           = "dt";
	QString HTML::TagDivider                  = "div";
	QString HTML::TagFieldset                 = "fieldset";
	QString HTML::TagForm                     = "form";
	QString HTML::TagHead                     = "head";
	QString HTML::TagHeader1                  = "h1";
	QString HTML::TagHeader2                  = "h2";
	QString HTML::TagHeader3                  = "h3";
	QString HTML::TagHeader4                  = "h4";
	QString HTML::TagHeader5                  = "h5";
	QString HTML::TagHorizontalRule           = "hr";
	QString HTML::TagHtml                     = "html";
	QString HTML::TagItalics                  = "i";
	QString HTML::TagImage                    = "img";
	QString HTML::TagInput                    = "input";
	QString HTML::TagLabel                    = "label";
	QString HTML::TagLegend                   = "legend";
	QString HTML::TagLink                     = "link";
	QString HTML::TagListItem                 = "li";
	QString HTML::TagMeta                     = "meta";
	QString HTML::TagOption                   = "option";
	QString HTML::TagOrderedList              = "ol";
	QString HTML::TagParagraph                = "p";
	QString HTML::TagScript                   = "script";
	QString HTML::TagSelect                   = "select";
	QString HTML::TagSpan                     = "span";
	QString HTML::TagStrong                   = "strong";
	QString HTML::TagStyle                    = "style";
	QString HTML::TagTable                    = "table";
	QString HTML::TableBody                   = "tbody";
	QString HTML::TagTableData                = "td";
	QString HTML::TagTableDataHeader          = "th";
	QString HTML::TableFooter                 = "tfoot";
	QString HTML::TagTableHeader              = "thead";
	QString HTML::TagTableRow                 = "tr";
	QString HTML::TagTextarea                 = "textarea";
	QString HTML::TagTitle                    = "title";
	QString HTML::TagUnorderedList            = "ul";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	HTML* HTML::Instance(bool bReset) {
		// Check for an existing instance or a reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new HTML();
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	HTML::HTML(QObject* qoParent) : QObject(qoParent){}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void HTML::ProcessAttributes(SelfClosingElement &scElement, QMap<QString, QString> qmAttributes) {
		// Iterate through the attributes
		for (QMap<QString, QString>::const_iterator itrAttribute = qmAttributes.begin(); itrAttribute != qmAttributes.end(); ++itrAttribute) {
			// Add the attribute to the element
			scElement.addAttribute(itrAttribute.key(), itrAttribute.value());
		}
	}

	void HTML::ProcessAttributes(TagElement &tagElement, QMap<QString, QString> qmAttributes) {
		// Iterate through the attributes
		for (QMap<QString, QString>::const_iterator itrAttribute = qmAttributes.begin(); itrAttribute != qmAttributes.end(); ++itrAttribute) {
			// Add the attribute to the element
			tagElement.addAttribute(itrAttribute.key(), itrAttribute.value());
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Static Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QMap<QString, QString> HTML::GetEmptyAttributeContainer() {
		// Create the attribute container
		QMap<QString, QString> qmAttributes;
		// Return the attribute container
		return qmAttributes;
	}

	QStringList HTML::GetEmptyChildContainer() {
		// Create the child container
		QStringList qslChildren;
		// Return the child container
		return qslChildren;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString HTML::Anchor(QString strHypertextReference, QString strValue, QString strIdentifier, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagAnchor = TagElement(HTML::TagAnchor, false);
		// Add the href to the attributes
		tagAnchor.addAttribute("href", strHypertextReference);
		// Add the id to the attributes
		tagAnchor.addAttribute("id", strIdentifier);
		// Set the value into the attributes
		tagAnchor.addAttribute("value", strValue);
		// Set the attributes into the element
		this->ProcessAttributes(tagAnchor, qmAttributes);
		// Return the element
		return tagAnchor.toString();
	}

	QString	HTML::Button(QString strName, QString strLabel, QString strIdentifier, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagButton = TagElement(HTML::TagButton, false);
		// Add the label to the attributes as the value
		tagButton.addAttribute("value", strLabel);
		// Add the name to the attributes
		tagButton.addAttribute("name", strName);
		// Add the id to the attributes
		tagButton.addAttribute("id", strIdentifier);
		// Set the attributeds into the structure
		this->ProcessAttributes(tagButton, qmAttributes);
		// Return the element
		return tagButton.toString();
	}

	QString HTML::Divider(QStringList qslChildren, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagDivider = TagElement(HTML::TagDivider, false);
		// Create the children placeholder
		QString strChildren;
		// Iterate through the children
		for (int intChild = 0; intChild < qslChildren.size(); ++intChild) {
			// Append the child
			strChildren.append(qslChildren.at(intChild));
		}
		// Set the value
		tagDivider.addAttribute("value", strChildren);
		// Set the attributes
		this->ProcessAttributes(tagDivider, qmAttributes);
		// Return the element as a string
		return tagDivider.toString();
	}

	QString HTML::Dropdown(QString strName, QString strIdentifier, DataProvider dpOptions, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagDropdown = TagElement(HTML::TagSelect, false);
		// Set the name
		tagDropdown.addAttribute("name", strName);
		// Set the ID
		tagDropdown.addAttribute("id", strIdentifier);
		// Set the options
		tagDropdown.addAttribute("value", dpOptions.toString());
		// Set the other attributes into the element
		this->ProcessAttributes(tagDropdown, qmAttributes);
		// Return the element as a string
		return tagDropdown.toString();
	}

	QString HTML::Fieldset(QStringList qslChildren, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagFieldset = TagElement(HTML::TagFieldset, false);
		// Create the children placeholder
		QString strChildren;
		// Iterate through the children
		for (int intChild = 0; intChild < qslChildren.size(); ++intChild) {
			// Append the child
			strChildren.append(qslChildren.at(intChild));
		}
		// Set the children into the element
		tagFieldset.addAttribute("value", strChildren);
		// Set the attributes into the element
		this->ProcessAttributes(tagFieldset, qmAttributes);
		// Return the element as a string
		return tagFieldset.toString();
	}

	QString HTML::Form(QString strAction, QString strMethod, QString strIdentifier, QStringList qslChildren, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagForm = TagElement(HTML::TagForm, false);
		// Set the action
		tagForm.addAttribute("action", strAction);
		// Set the ID of the form
		tagForm.addAttribute("id", strIdentifier);
		// Set the method of the form
		tagForm.addAttribute("method", strMethod);
		// Set the attributes into the element
		this->ProcessAttributes(tagForm, qmAttributes);
		// Create the child placeholder
		QString strChildren;
		// Iterate through the children
		for (int intChild = 0; intChild < qslChildren.size(); ++intChild) {
			// Append the child
			strChildren.append(qslChildren.at(intChild));
		}
		// Set the value into the element
		tagForm.addAttribute("value", strChildren);
		// Return the element as string
		return tagForm.toString();
	}

	QString HTML::Image(QString strSource, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		SelfClosingElement sceImage = SelfClosingElement(HTML::TagImage);
		// Set the source into the element
		sceImage.addAttribute("src", strSource);
		// Set the attributes into the element
		this->ProcessAttributes(sceImage, qmAttributes);
		// Return the element as a string
		return sceImage.toString();
	}

	QString HTML::Input(QString strType, QString strName, QString strIdentifier, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		SelfClosingElement sceInput = SelfClosingElement(strType);
		// Set the name into the element
		sceInput.addAttribute("name", strName);
		// Set the ID into the element
		sceInput.addAttribute("id", strIdentifier);
		// Set the attributes into the element
		this->ProcessAttributes(sceInput, qmAttributes);
		// Return the element as a string
		return sceInput.toString();
	}

	QString HTML::Label(QString strText, QString strFor, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagLabel = TagElement(HTML::TagLabel, false);
		// Set the label into the tag
		tagLabel.addAttribute("value", strText);
		// Set the for attribute into the element
		tagLabel.addAttribute("for", strFor);
		// Set the attributes into the element
		this->ProcessAttributes(tagLabel, qmAttributes);
		// Return the element as a string
		return tagLabel.toString();
	}

	QString HTML::Link(QString strRelativity, QString strType, QString strHypertextReference, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		SelfClosingElement sceLink = SelfClosingElement(HTML::TagLink);
		// Set the relativity of the element
		sceLink.addAttribute("rel", strRelativity);
		// Set the type into the element
		sceLink.addAttribute("type", strType);
		// Set the reference of the element
		sceLink.addAttribute("href", strHypertextReference);
		// Set the attributes into the element
		this->ProcessAttributes(sceLink, qmAttributes);
		// Return the element as a string
		return sceLink.toString();
	}

	QString HTML::Meta(QString strName, QString strContent, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		SelfClosingElement sceMeta = SelfClosingElement(HTML::TagMeta);
		// Set the name of the element
		sceMeta.addAttribute("name", strName);
		// Set the content of the element
		sceMeta.addAttribute("content", strContent);
		// Set the attributes into the element
		this->ProcessAttributes(sceMeta, qmAttributes);
		// Return the element as a string
		return sceMeta.toString();
	}

	QString HTML::SelfClosingTag(QString strType, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		SelfClosingElement tagElement         = SelfClosingElement(strType);
		// Set the attributes into the tag
		this->ProcessAttributes(tagElement, qmAttributes);
		// Return the element as a string
		return tagElement.toString();
	}

	QString HTML::Script(QString strType, QString strSource, bool bScriptIsInline, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagScript = TagElement(HTML::TagScript, (bScriptIsInline ? false : true));
		// Check to see if we need to set the source into the attributes
		if (bScriptIsInline) {
			// Set the value
			tagScript.addAttribute("value", strSource);
		} else {
			// Set the source attribute
			tagScript.addAttribute("src", strSource);
		}
		// Set the type into the element
		tagScript.addAttribute("type", strType);
		// Set the attributes into the element
		this->ProcessAttributes(tagScript, qmAttributes);
		// Return the element as a string
		return tagScript.toString();
	}

	QString HTML::Style(QString strType, QString strSource, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagStyle = TagElement(HTML::TagStyle, false);
		// Set the type into the element
		tagStyle.addAttribute("type", strType);
		// Set the source into the element
		tagStyle.addAttribute("value", strSource);
		// Set the attributes into the element
		this->ProcessAttributes(tagStyle, qmAttributes);
		// Return the element as a string
		return tagStyle.toString();
	}

	QString HTML::Tag(QString strType, bool bValueIsAttribute, QMap<QString, QString> qmAttributes, QStringList qslChildren) {
		// Create the tag element
		TagElement tagElement         = TagElement(strType, bValueIsAttribute);
		// Set the attributes into the tag
		this->ProcessAttributes(tagElement, qmAttributes);
		// Create the children placeholder
		QString strChildren;
		// Iterate through the children
		for (int intChild = 0; intChild < qslChildren.size(); ++intChild) {
			// Append the child
			strChildren.append(qslChildren.at(intChild));
		}
		// Set the value into the element
		if (tagElement.mAttributes.contains("value")) {
			// Append the children
			tagElement.mAttributes["value"].append(strChildren);
		} else {
			// Set the children into the element
			tagElement.addAttribute("value", strChildren);
		}
		// Return the element as a string
		return tagElement.toString();
	}

	QString HTML::TextArea(QString strName, QString strIdentifier, QString strContent, QMap<QString, QString> qmAttributes) {
		// Create the tag element
		TagElement tagTextArea = TagElement(HTML::TagTextarea, false);
		// Set the name into the element
		tagTextArea.addAttribute("name", strName);
		// Set the ID into the element
		tagTextArea.addAttribute("id", strIdentifier);
		// Set the content of the element
		tagTextArea.addAttribute("value", strContent);
		// Set the attributes into the element
		this->ProcessAttributes(tagTextArea, qmAttributes);
		// Return the element as a string
		return tagTextArea.toString();
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
