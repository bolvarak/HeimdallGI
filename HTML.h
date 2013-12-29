///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_HTML_H
#define HEIMDALLGI_HTML_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "QMap"
#include "QString"
#include "QStringList"
#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This structure generates the options for a select tag
	 * @brief HeimdallGI::DataProvider()
	 */
	struct DataProvider {

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the label/value option pairs
			 * @brief HeimdallGI::DataProvider::mDataPairs
			 * @var QMap<QString, QString>
			 */
			QMap<QString, QString> mDataPairs;

			/**
			 * @paragraph This property contains the selected option value
			 * @brief HeimdallGI::DataProvider::mSelectedValue
			 * @var QString
			 */
			QString mSelectedValue;

			///////////////////////////////////////////////////////////////////
			/// Construct ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor simply sets up the structure
			 * @brief HeimdallGI::DataProvider::DataProvider()
			 */
			DataProvider()
			{}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method adds an option to the structure instane
			 * @brief HeimdallGI::DataProvider::addOption()
			 * @param QString strLabel
			 * @return void
			 */
			void addOption(QString strValue, QString strLabel)
			{
				// Add the option to the structure instance
				this->mDataPairs.insert(strLabel, strValue);
			}

			/**
			 * @paragraph This method generates the option elements for this data provider
			 * @brief HeimdallGI::DataProvider::toString()
			 * @return QString
			 */
			QString toString()
			{
				// Define the return string
				QString strDataProvider;
				// Create the attributes iterator
				QMap<QString, QString>::iterator itrOptions;
				// Loop through the attributes
				for (itrOptions = this->mDataPairs.begin(); itrOptions != this->mDataPairs.end(); ++itrOptions) {
					// Add the option to the data provider
					strDataProvider.append(QString("<option value=\"%1\" %2>%4</option>").arg(itrOptions.value(), (itrOptions.value() == this->mSelectedValue ? "selected" : ""), itrOptions.key()));
				}
				// Return the data provider
				return strDataProvider;
			}

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the selected value for this data provider
			 * @brief HeimdallGI::DataProvider::setSelectedValue()
			 * @param QString strValue
			 * @return void
			 */
			void setSelectedValue(QString strValue)
			{
				// Set the selected value into the structure instance
				this->mSelectedValue = strValue;
			}
	};

	/**
	 * @paragraph This is the base element structure
	 * @brief HeimdallGI::Element()
	 */
	struct Element {

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the element's key/value pair attributes
			 * @brief HeimdallGI::Element::mAttributes
			 * @var QMap<QString, QString>
			 */
			QMap<QString, QString> mAttributes;

			/**
			 * @paragraph This property contain the element's properties
			 * @brief HeimdallGI::Element::mProperties
			 * @var QSringList
			 */
			QStringList mProperties;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor simply sets up the stucture
			 * @brief Element::Element()
			 */
			Element()
			{}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method adds an attribute to the structure
			 * @brief HeimdallGI::Element::addAttribute()
			 * @param QString strName
			 * @param QString strValue
			 * @return void
			 */
			void addAttribute(QString strName, QString strValue)
			{
				// Add the attribute into the structure instance
				this->mAttributes.insert(strName, strValue);
			}

			/**
			 * @paragraph This method adds a property to the structure
			 * @brief HeimdallGI::Element::addProperty()
			 * @param QString strProperty
			 * @return void
			 */
			void addProperty(QString strProperty)
			{
				// Set the property into the structure instance
				this->mProperties.append(strProperty);
				// Remove duplicates
				this->mProperties.removeDuplicates();
			}
	};

	/**
	 * @paragraph This structure generates self-closing tags such as link and meta tags
	 * @brief HeimdallGI::SelfClosingElement()
	 */
	struct SelfClosingElement : public Element
	{
			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the tag type
			 * @brief HeimdallGI::Element::mType
			 * @var QString
			 */
			QString mType;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This contructor sets the element type into the strucure
			 * @brief HeimdallGI::SelfClosingElement()
			 * @param QString strType
			 */
			SelfClosingElement(QString strType)
			{
				// Set the element type into the structure instance
				this->mType = strType;
			}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method builds the element and returns it
			 * @brief HeimdallGI::SelfClosingElement::toString()
			 * @return QString
			 */
			QString toString()
			{
				// Create the element string placeholder
				QString strElement = "<";
				// Add the type to the string
				strElement.append(this->mType);
				// Create the attributes iterator
				QMap<QString, QString>::iterator itrAttributes;
				// Loop through the attributes
				for (itrAttributes = this->mAttributes.begin(); itrAttributes != this->mAttributes.end(); ++itrAttributes) {
					// Add the attribute to the element
					strElement.append(QString(" %1=\"%2\"").arg(itrAttributes.key(), itrAttributes.value()));
				}
				// Loop through the properties
				foreach (QString strProperty, this->mProperties) {
					// Add the property to the element
					strElement.append(QString(" %1").arg(strProperty));
				}
				// Finalize the element
				strElement.append(">");
				// Return the element
				return strElement;
			}
	};

	/**
	 * @paragraph This structure generates normal tag elements like div and p
	 * @brief HeimdallGI::TagElement()
	 */
	struct TagElement : public Element
	{
			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the element type
			 * @brief HeimdallGI::TagElement::mType
			 * @var QString
			 */
			QString mType;

			/**
			 * @paragraph This property tells the strcture whether or not the value is an attribute on in between the tags
			 * @brief HeimdallGI::TagElement::mValueIsAttribute
			 * @var bool
			 */
			bool mValueIsAttribute;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor sets up the structure instance for normal tag generation
			 * @brief TagElement
			 * @param strType
			 * @param bValueIsAttribute
			 */
			TagElement(QString strType, bool bValueIsAttribute = true)
			{
				// Set the element type into the structure instance
				this->mType             = strType;
				// Set the value placement identifier into the structure instance
				this->mValueIsAttribute = bValueIsAttribute;
			}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method builds and returns the HTML tag element
			 * @brief HeimdallGI::TagElement::toString()
			 * @return QString
			 */
			QString toString()
			{
				// Create the element string placeholder
				QString strElement = "<";
				// Add the type to the string
				strElement.append(this->mType);
				// Create the attributes iterator
				QMap<QString, QString>::iterator itrAttributes;
				// Loop through the attributes
				for (itrAttributes = this->mAttributes.begin(); itrAttributes != this->mAttributes.end(); ++itrAttributes) {
					// Check the key
					if ((itrAttributes.key() == "value") && (this->mValueIsAttribute == false)) {
						// Continue to the next iteration
						continue;
					}
					// Add the attribute to the element
					strElement.append(QString(" %1=\"%2\"").arg(itrAttributes.key(), itrAttributes.value()));
				}
				// Loop through the properties
				foreach (QString strProperty, this->mProperties) {
					// Add the property to the element
					strElement.append(QString(" %1").arg(strProperty));
				}
				// Close the opening tag
				strElement.append(">");
				// Check to see if the value is not an attribute
				if (this->mValueIsAttribute == false) {
					// Add the value
					strElement.append(this->mAttributes.value("value", ""));
				}
				// Finalize the element
				strElement.append(QString("</%1>").arg(this->mType));
				// Return the element
				return strElement;
			}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HTML Class Definition ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This class handles the generation of HTML elements
	 * @brief HTML
	 */
	class HTML : public QObject
	{
			/**
			 * @brief Ensure this class is recognized as a Qt object
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
			 * @brief HTML::mInstance
			 * @var HTML*
			 */
			static HTML* mInstance;

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method processes the attributes into a SelfClosingElement
			 * @brief HeimdallGI::HTML::ProcessAttributes()
			 * @param HeimdallGI::SelfClosingElement scElement
			 * @param QMap<QString, QString> qmAttributes
			 */
			void ProcessAttributes(SelfClosingElement &scElement, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method processes the attributes into a TagElement
			 * @brief HeimdallGI::HTML::ProcessAttributes()
			 * @param HeimdallGI::TagElement tagElement
			 * @param QMap<QString, QString> qmAttributes
			 * @return void
			 */
			void ProcessAttributes(TagElement &tagElement, QMap<QString, QString> qmAttributes);

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constant defines the text for the alt attribute name
			 * @brief HTML::AttributeAlternate
			 * @var QString
			 */
			static QString AttributeAlternate;

			/**
			 * @paragraph This constant defines the text for the charset attribute name
			 * @brief HTML::AttributeCharset
			 * @var QString
			 */
			static QString AttributeCharset;

			/**
			 * @paragraph This constant defines the text for the class attribute name
			 * @brief HTML::AttributeClass
			 * @var QString
			 */
			static QString AttributeClass;

			/**
			 * @paragraph This constant defines the text for the content attribute name
			 * @brief HTML::AttributeContent
			 * @var QString
			 */
			static QString AttributeContent;

			/**
			 * @paragraph This constant defines the text for the description attribute name
			 * @brief HTML::AttributeDescription
			 * @var QString
			 */
			static QString AttributeDescription;


			/**
			 * @paragraph This constant defines the text for the height attribute name
			 * @brief HTML::AttributeHeight
			 * @var QString
			 */
			static QString AttributeHeight;

			/**
			 * @paragraph This constant defines the text for the href attribute name
			 * @brief HTML::AttributeHypertextReference
			 * @var QString
			 */
			static QString AttributeHypertextReference;

			/**
			 * @paragraph This constant defines the text for the http-equiv attribute name
			 * @brief HTML::AttributeHttpEquivalent
			 * @var QString
			 */
			static QString AttributeHttpEquivalent;

			/**
			 * @paragraph This constant defines the text for the id attribute name
			 * @brief HTML::AttributeIdentifier
			 * @var QString
			 */
			static QString AttributeIdentifier;

			/**
			 * @paragraph This constant defines the text for the maxlength attribute name
			 * @brief HTML::AttributeMaximumLength
			 * @var QString
			 */
			static QString AttributeMaximumLength;

			/**
			 * @paragraph This constant defines the text for the media attribute name
			 * @brief HTML::AttributeMedia
			 * @var QString
			 */
			static QString AttributeMedia;

			/**
			 * @paragraph This constant defines the text for the name attribute name
			 * @brief HTML::AttributeName
			 * @var QString
			 */
			static QString AttributeName;

			/**
			 * @paragraph This constant defines the text for the placeholder attribute name
			 * @brief HTML::AttributePlaceholder
			 * @var QString
			 */
			static QString AttributePlaceholder;

			/**
			 * @paragraph This constant defines the text for the prefix attribute name
			 * @brief HTML::AttributePrefix
			 * @var QString
			 */
			static QString AttributePrefix;

			/**
			 * @paragraph This constant defines the text for the property attribute name
			 * @brief HTML::AttributeProperty
			 * @var QString
			 */
			static QString AttributeProperty;

			/**
			 * @paragraph This constant defines the text for the rel attribute name
			 * @brief HTML::AttributeRelativity
			 * @var QString
			 */
			static QString AttributeRelativity;

			/**
			 * @paragraph This constant defines the text for the size attribute name
			 * @brief HTML::AttributeSize
			 * @var QString
			 */
			static QString AttributeSize;

			/**
			 * @paragraph This constant defines the text for the sizes attribute name
			 * @brief HTML::AttributeSizes
			 * @var QString
			 */
			static QString AttributeSizes;

			/**
			 * @paragraph This constant defines the text for the src attribute name
			 * @brief HTML::AttributeSource
			 * @var QString
			 */
			static QString AttributeSource;

			/**
			 * @paragraph This constant defines the text for the style attribute name
			 * @brief HTML::AttributeStyle
			 * @var QString
			 */
			static QString AttributeStyle;

			/**
			 * @paragraph This constant defines the text for the title attribute name
			 * @brief HTML::AttributeTitle
			 * @var QString
			 */
			static QString AttributeTitle;

			/**
			 * @paragraph This constant defines the text for the type attribute name
			 * @brief HTML::AttributeType
			 * @var QString
			 */
			static QString AttributeType;

			/**
			 * @paragraph This constant defines the text for the width attribute name
			 * @brief HTML::AttributeWidth
			 * @var QString
			 */
			static QString AttributeWidth;

			/**
			 * @paragraph This constant defines the text for the type attribute for the button input
			 * @brief HTML::InputButton
			 * @var QString
			 */
			static QString InputButton;

			/**
			 * @paragraph This constant defines the text for the type attribute for the checkbox input
			 * @brief HTML::InputCheckbox
			 * @var QString
			 */
			static QString InputCheckbox;

			/**
			 * @paragraph This constant defines the text for the type attribute for the file input
			 * @brief HTML::InputFile
			 * @var QString
			 */
			static QString InputFile;

			/**
			 * @paragraph This constant defines the text for the type attribute for the hidden input
			 * @brief HTML::InputHidden
			 * @var QString
			 */
			static QString InputHidden;

			/**
			 * @paragraph This constant defines the text for the type attribute for the image input
			 * @brief HTML::InputImage
			 * @var QString
			 */
			static QString InputImage;

			/**
			 * @paragraph This constant defines the text for the type attribute for the password input
			 * @brief HTML::InputPassword
			 * @var QString
			 */
			static QString InputPassword;

			/**
			 * @paragraph This constant defines the text for the type attribute for the radio input
			 * @brief HTML::InputRadio
			 * @var QString
			 */
			static QString InputRadio;

			/**
			 * @paragraph This constant defines the text for the type attribute for the reset input
			 * @brief HTML::InputReset
			 * @var QString
			 */
			static QString InputReset;

			/**
			 * @paragraph This constant defines the text for the type attribute for the submit input
			 * @brief HTML::InputSubmit
			 * @var QString
			 */
			static QString InputSubmit;

			/**
			 * @paragraph This constant defines the text for the type attribute for the text input
			 * @brief HTML::InputText
			 * @var QString
			 */
			static QString InputText;

			/**
			 * @paragraph This constant defines the text for the disabled property name
			 * @brief HTML::PropertyDisabled
			 * @var QString
			 */
			static QString PropertyDisabled;

			/**
			 * @paragraph This constant defines the text for the readonly property name
			 * @brief HTML::PropertyReadOnly
			 * @var QString
			 */
			static QString PropertyReadOnly;

			/**
			 * @paragraph This constant defines the text for the required property name
			 * @brief HTML::PropertyRequired
			 * @var QString
			 */
			static QString PropertyRequired;

			/**
			 * @paragraph This constant defines the text for the selected property name
			 * @brief HTML::PropertySelected
			 * @var QString
			 */
			static QString PropertySelected;

			/**
			 * @paragraph This constant defines the text for the a tag
			 * @brief HTML::TagAnchor
			 * @var QString
			 */
			static QString TagAnchor;

			/**
			 * @paragraph This constant defines the text for the body tag
			 * @brief HTML::TagBody
			 * @var QString
			 */
			static QString TagBody;

			/**
			 * @paragraph This constant defines the text for the b tag
			 * @brief HTML::TagBold
			 * @var QString
			 */
			static QString TagBold;

			/**
			 * @paragraph This constant defines the text for the button tag
			 * @brief HTML::TagButton
			 * @var QString
			 */
			static QString TagButton;

			/**
			 * @paragraph This constant defines the text for the caption tag
			 * @brief HTML::TagCaption
			 * @var QString
			 */
			static QString TagCaption;

			/**
			 * @paragraph This constant defines the text for the dd tag
			 * @brief HTML::TagDefinitionDescription
			 * @var QString
			 */
			static QString TagDefinitionDescription;

			/**
			 * @paragraph This constant defines the text for the dl tag
			 * @brief HTML::TagDefinitionList
			 * @var QString
			 */
			static QString TagDefinitionList;

			/**
			 * @paragraph This constant defines the text for the dt tag
			 * @brief HTML::TagDefinitionTerm
			 * @var QString
			 */
			static QString TagDefinitionTerm;

			/**
			 * @paragraph This constant defines the text for the div tag
			 * @brief HTML::TagDivider
			 * @var QString
			 */
			static QString TagDivider;

			/**
			 * @paragraph This constant defines the text for the fieldset tag
			 * @brief HTML::TagFieldset
			 * @var QString
			 */
			static QString TagFieldset;

			/**
			 * @paragraph This constant defines the text for the form tag
			 * @brief HTML::TagForm
			 * @var QString
			 */
			static QString TagForm;

			/**
			 * @paragraph This constant defines the text for the head tag
			 * @brief HTML::TagHead
			 * @var QString
			 */
			static QString TagHead;

			/**
			 * @paragraph This constant defines the text for the h1 tag
			 * @brief HTML::TagHeader1
			 * @var QString
			 */
			static QString TagHeader1;

			/**
			 * @paragraph This constant defines the text for the h2 tag
			 * @brief HTML::TagHeader2
			 * @var QString
			 */
			static QString TagHeader2;

			/**
			 * @paragraph This constant defines the text for the h3 tag
			 * @brief HTML::TagHeader3
			 * @var QString
			 */
			static QString TagHeader3;

			/**
			 * @paragraph This constant defines the text for the h4 tag
			 * @brief HTML::TagHeader4
			 * @var QString
			 */
			static QString TagHeader4;

			/**
			 * @paragraph This constant defines the text for the h5 tag
			 * @brief HTML::TagHeader5
			 * @var QString
			 */
			static QString TagHeader5;

			/**
			 * @paragraph This constant defines the text for the hr tag
			 * @brief HTML::TagHorizontalRule
			 * @var QString
			 */
			static QString TagHorizontalRule;

			/**
			 * @paragraph This constant defines the text for the html tag
			 * @brief HTML::TagHtml
			 * @var QString
			 */
			static QString TagHtml;

			/**
			 * @paragraph This constant defines the text for th img tag
			 * @brief HTML::TagImage
			 * @var QString
			 */
			static QString TagImage;

			/**
			 * @paragraph This constant defines the text for the input tag
			 * @brief HTML::TagInput
			 * @var QString
			 */
			static QString TagInput;

			/**
			 * @paragraph This constant defines the text for the i tag
			 * @brief HTML::TagItalics
			 * @var QString
			 */
			static QString TagItalics;

			/**
			 * @paragraph This constant defines the text for the label tag
			 * @brief HTML::TagLabel
			 * @var QString
			 */
			static QString TagLabel;

			/**
			 * @paragraph This constant defines the text for the legend tag
			 * @brief HTML::TagLegend
			 * @var QString
			 */
			static QString TagLegend;

			/**
			 * @paragraph This constant defines the text for the link tag
			 * @brief HTML::TagLink
			 * @var QString
			 */
			static QString TagLink;

			/**
			 * @paragraph This constant defines the text for the li tag
			 * @brief HTML::TagListItem
			 * @var QString
			 */
			static QString TagListItem;

			/**
			 * @paragraph This constant defines the text for the meta tag
			 * @brief HTML::TagMeta
			 * @var QString
			 */
			static QString TagMeta;

			/**
			 * @paragraph This constant defines the text for the option tag
			 * @brief HTML::TagOption
			 * @var QString
			 */
			static QString TagOption;

			/**
			 * @paragraph This constant defines the text for the ol tag
			 * @brief HTML::TagOrderedList
			 * @var QString
			 */
			static QString TagOrderedList;

			/**
			 * @paragraph This constant defines the text for the p tag
			 * @brief HTML::TagParagraph
			 * @var QString
			 */
			static QString TagParagraph;

			/**
			 * @paragraph This constant defines the text for the script tag
			 * @brief HTML::TagScript
			 * @var QString
			 */
			static QString TagScript;

			/**
			 * @paragraph This constant defines the text for the select tag
			 * @brief HTML::TagSelect
			 * @var QString
			 */
			static QString TagSelect;

			/**
			 * @paragraph This constant defines the text for the span tag
			 * @brief HTML::TagSpan
			 * @var QString
			 */
			static QString TagSpan;

			/**
			 * @paragraph This constant defines the text for the strong tag
			 * @brief HTML::TagStrong
			 * @var QString
			 */
			static QString TagStrong;

			/**
			 * @paragraph This constant defines the text for the style tag
			 * @brief HTML::TagStyle
			 * @var QString
			 */
			static QString TagStyle;

			/**
			 * @paragraph This constant defines the text for the table tag
			 * @brief HTML::TagTable
			 * @var QString
			 */
			static QString TagTable;

			/**
			 * @paragraph This constant defines the text for the tbody tag
			 * @brief HTML::TagTableBody
			 * @var QString
			 */
			static QString TableBody;

			/**
			 * @paragraph This constant defines the text for the td tag
			 * @brief HTML::TagTableData
			 * @var QString
			 */
			static QString TagTableData;

			/**
			 * @paragraph This constant defines the text for the th tag
			 * @brief HTML::TagTableDataHeader
			 * @var QString
			 */
			static QString TagTableDataHeader;

			/**
			 * @paragraph This constant defines the text for the tfoot tag
			 * @brief HTML::TagTableFooter
			 * @var QString
			 */
			static QString TableFooter;

			/**
			 * @paragraph This constant defines the text for the thead tag
			 * @brief HTML::TagTableHeader
			 * @var QString
			 */
			static QString TagTableHeader;

			/**
			 * @paragraph This constant defines the text for the tr tag
			 * @brief HTML::TagTableRow
			 * @var QString
			 */
			static QString TagTableRow;

			/**
			 * @paragraph This constant defines the text for the textarea tag
			 * @brief HTML::TagTextarea
			 * @var QString
			 */
			static QString TagTextarea;

			/**
			 * @paragraph This constant defines the text for the title tag
			 * @brief HTML::TagTitle
			 * @var QString
			 */
			static QString TagTitle;

			/**
			 * @paragraph This constant defines the text for the u tag
			 * @brief HTML::TagUnderline
			 * @var QString
			 */
			static QString TagUnderline;

			/**
			 * @paragraph This constant defines the text for the ul tag
			 * @brief HTML::TagUnorderedList
			 * @var QString
			 */
			static QString TagUnorderedList;

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////////
			/// Singleton ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method maintains access to the singleton instance of this class
			 * @brief HTML::Instance()
			 * @param bool bReset [false]
			 * @return HTML* HTML::mInstance
			 */
			static HTML* Instance(bool bReset = false);

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			explicit HTML(QObject* qoParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Static ///////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method is a utility method to return an empty attribute map
			 * @brief HeimdallGI::HTML::GetEmptyAttributeContainer()
			 * @return QMap<QString, QString>
			 */
			static QMap<QString, QString> GetEmptyAttributeContainer();

			/**
			 * @paragraph This method is a utility method to return an empty child list
			 * @brief HeimdallGI::HTML::GetEmptyChildContainer()
			 * @return QStringList
			 */
			static QStringList GetEmptyChildContainer();

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method generates an a tag
			 * @brief HTML::Anchor()
			 * @param QString strHypertextReference
			 * @param QString strValue
			 * @param QString strIdentifier
			 * @param QString strName
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Anchor(QString strHypertextReference, QString strValue, QString strIdentifier, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a button tag
			 * @brief HTML::Button()
			 * @param QString strName
			 * @param QString strLabel
			 * @param QString strIdentifier
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Button(QString strName, QString strLabel, QString strIdentifier, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a div tag
			 * @brief HTML::Divider()
			 * @param QStringList qslChildren
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Divider(QStringList qslChildren, QMap<QString, QString> qmAttributes);


			/**
			 * @paragraph This method generates a select tag dropdown
			 * @brief HTML::Dropdown()
			 * @param QString strName
			 * @param QString strIdentifier
			 * @param HeimdallGI::DataProvider dpOptions
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Dropdown(QString strName, QString strIdentifier, DataProvider dpOptions, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a fieldset tag
			 * @brief HTML::Fieldset()
			 * @param QStringList qslChildren
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Fieldset(QStringList qslChildren, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a form tag
			 * @brief HTML::Form()
			 * @param QString strAction
			 * @param QString strMethod
			 * @param QString strIdentifier
			 * @param QList<HeimdallGI::Element> qlChildren
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Form(QString strAction, QString strMethod, QString strIdentifier, QStringList qslChildren, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates an img tag
			 * @brief HTML::Image()
			 * @param QString strSource
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Image(QString strSource, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates an input tag
			 * @brief HTML::Input()
			 * @param QString strType
			 * @param QString strName
			 * @param QString strIdentifier
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Input(QString strType, QString strName, QString strIdentifier, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a label tag
			 * @brief HTML::Label()
			 * @param QString strText
			 * @param QString strFor
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Label(QString strText, QString strFor, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a link tag
			 * @brief HTML::Link()
			 * @param QString strRelativity
			 * @param QString strType
			 * @param QString strHypertextReference
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Link(QString strRelativity, QString strType, QString strHypertextReference, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a meta tag
			 * @brief HTML::Meta()
			 * @param QString strName
			 * @param QString strContent
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Meta(QString strName, QString strContent, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a custom self-closing tag
			 * @brief HeimdallGI::HTML::SelfClosingTag()
			 * @param QString strType
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString SelfClosingTag(QString strType, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates a script tag
			 * @brief HTML::Script()
			 * @param QString strType
			 * @param QString strSource
			 * @param bool bScriptIsInline
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Script(QString strType, QString strSource, bool bScriptIsInline, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method genertes a style tag
			 * @brief HTML::Style()
			 * @param QString strType
			 * @param QString strSource
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString Style(QString strType, QString strSource, QMap<QString, QString> qmAttributes);

			/**
			 * @paragraph This method generates an HTML tag
			 * @brief HTML::Tag()
			 * @param QString strType
			 * @param bool bValueIsAttribute
			 * @param QMap<QString QString> qmAttributes
			 * @param QStringList qslChildren
			 * @return
			 */
			QString Tag(QString strType, bool bValueIsAttribute, QMap<QString, QString> qmAttributes, QStringList qslChildren);

			/**
			 * @paragraph This method generates a textarea tag
			 * @brief HTML::TextArea()
			 * @param QString strName
			 * @param QString strIdentifier
			 * @param QString strContent
			 * @param QMap<QString, QString> qmAttributes
			 * @return QString
			 */
			QString TextArea(QString strName, QString strIdentifier, QString strContent, QMap<QString, QString> qmAttributes);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::HTML Class Definition ////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
#endif // HEIMDALLGI_HTML_H
