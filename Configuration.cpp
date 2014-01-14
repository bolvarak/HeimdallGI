///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Configuration.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Configuration::Configuration(QObject* qoParent) : QObject(qoParent) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Static Settings ///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QVariant Configuration::Get(QString strKey, QMap<QString, QString> qmsReplacements) {
		// Load the configuration
		QSettings qssConfiguration(QString(HGI_CONFIG_FILE), QSettings::IniFormat);
		// Check for replacements
		if (!qmsReplacements.isEmpty()) {
			// Load the property 
			QString strProperty = qssConfiguration.value(strKey.replace(".", "/")).toString();
			// Traverse the replacements
			for (QMap<QString, QString>::const_iterator itrReplacement = qmsReplacements.constBegin(); itrReplacement != qmsReplacements.constEnd(); ++itrReplacement) {
				// Make the replacement
				strProperty.replace(QString("${%1}").arg(itrReplacement.key()), itrReplacement.value());
			}
			// Return the property
			return QVariant(strProperty);
		}
		// Return the property
		return qssConfiguration.value(strKey.replace(".", "/"));
	}

	bool Configuration::Set(QString strKey, QVariant qvValue) {
		// Load the configuration
		QSettings qssConfiguration(HGI_CONFIG_FILE, QSettings::IniFormat);
		// Set the property
		return qssConfiguration.setProperty(strKey.replace(".", "/").toLatin1(), qvValue);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
