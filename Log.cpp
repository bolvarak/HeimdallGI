///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Log* Log::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Log* Log::Instance(bool bReset) {
		// Check for an existing instance or reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Instantiate the class
			mInstance = new Log;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Log::Log(QObject* qoParent) : QObject(qoParent) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Methods //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Log* Log::Add(QString strKey, QString strValue) {
		// Create the string list
		QStringList qslDataEntry;
		// Add the timestamp
		qslDataEntry.insert(0, QDateTime::currentDateTime().toString("ddd MMM dd, yyyy @ hh:mm:ss"));
		// Add the key name
		qslDataEntry.insert(1, strKey);
		// Add the value
		qslDataEntry.insert(2, strValue);
		// Add the data entry
		this->mData.append(qslDataEntry);
		// Return the instance
		return this;
	}

	Log* Log::Delete(QString strKey) {
		// Iterate over the data
		for (int intEntry = 0; intEntry < this->mData.size(); ++intEntry) {
			// Check the key name
			if (this->mData.at(intEntry).at(1) == strKey) {
				// Remove the entry
				this->mData.removeAt(intEntry);
			}
		}
		// Return the instance
		return this;
	}

	Log* Log::Update(QString strKey, QString strValue) {
		// Iterate over the entries
		for (int intEntry = 0; intEntry < this->mData.size(); ++intEntry) {
			// Check for a match
			if (this->mData.at(intEntry).at(1) == strKey) {
				// Create the string list
				QStringList qslDataEntry;
				// Add the timestamp
				qslDataEntry.insert(0, QDateTime::currentDateTime().toString("ddd MMM dd, yyyy @ hh:mm:ss"));
				// Add the key name
				qslDataEntry.insert(1, strKey);
				// Add the value
				qslDataEntry.insert(2, strValue);
				// Replace the entry
				this->mData.replace(intEntry, qslDataEntry);
			}
		}
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Log::GetHTML() {
		// Create a string placeholder
		QString strResponse = "<pre class=\"heimdall-gi-log-pre\">";
		// Iterate over the map
		for (int intEntry = 0; intEntry < this->mData.size(); ++intEntry) {
			// Append the data to the string
			strResponse
					.append("[")
					.append(this->mData.at(intEntry).at(0))
					.append("] - [")
					.append(this->mData.at(intEntry).at(1))
					.append("] => ")
					.append(this->mData.at(intEntry).at(2))
					.append("<br>");
		}
		// Finalize the string
		strResponse.append("</pre>");
		// Return the data
		return strResponse;
	}

	QString Log::GetJSON(bool bCompact) {
		// Define the JSON document
		QJsonDocument qjdResponse;
		// Define the JSON array
		QJsonArray qjaResponse;
		// Iterate over the data
		for (int intEntry = 0; intEntry < this->mData.size(); ++intEntry) {
			// Define the JSON object
			QJsonObject qjoEntry;
			// Add the timestamp
			qjoEntry.insert("timestamp", QJsonValue(this->mData.at(intEntry).at(0)));
			// Add the label
			qjoEntry.insert("name",      QJsonValue(this->mData.at(intEntry).at(1)));
			// Add the data
			qjoEntry.insert("data",      QJsonValue(this->mData.at(intEntry).at(2)));
			// Append the object to the array
			qjaResponse.append(qjoEntry);
		}
		// Set the array into the document
		qjdResponse.setArray(qjaResponse);
		// Return the JSON
		return qjdResponse.toJson(bCompact ? QJsonDocument::Compact : QJsonDocument::Indented);
	}

	QString Log::GetString() {
		// Create a string placeholder
		QString strResponse = "\n";
		// Iterate over the map
		for (int intEntry = 0; intEntry < this->mData.size(); ++intEntry) {
			// Append the data to the string
			strResponse
					.append("[")
					.append(this->mData.at(intEntry).at(0))
					.append("] - [")
					.append(this->mData.at(intEntry).at(1))
					.append("] => ")
					.append(this->mData.at(intEntry).at(2))
					.append("\n");
		}
		// Finalize the string
		strResponse.append("\n");
		// Return the data
		return strResponse;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
