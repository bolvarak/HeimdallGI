///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TestController.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TestController::TestController(QObject* qoParent) : QObject(qoParent) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// View Methods /////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestController::Index(HeimdallGI::CGI* &objRequest, HeimdallGI::View* &objView) {
	bool bNull;
	// Delete the cookies
	objRequest->DeleteCookie("testing_cookies", bNull);
	objRequest->DeleteCookie("testing cookies", bNull);
	// Set the page title
	objView->SetPageValue("pageTitle", "Hello World!");
	// Set the page name
	objView->SetPageValue("pageName", "Hello World");
	// Set the block file
	objView->SetTemplate("test/index");
	// Create a list for data
	QStringList qslPageValue;
	// Loop to 25
	for (int intIteration = 0; intIteration < 25; ++intIteration) {
		// Append the data
		qslPageValue.append(QString("Iteration %1").arg(QString::number(intIteration + 1)));
	}
	// Set the page value
	objView->SetPageValue("iterationTest", qslPageValue);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Slots ////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TestController::RowFetched(QSqlRecord qsrRow) {
	// Create the row container
	QVariantMap qvmRow;
	// Set the row data
	qvmRow.insert("ID",   qsrRow.value(qsrRow.indexOf("Id")));
	qvmRow.insert("Name", qsrRow.value(qsrRow.indexOf("Name")));
	// Append the row to the instance
	this->mRecords.append(qvmRow);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TestController* TestController::SetLogger(HeimdallGI::Log *&objLogger) {
	// Set the logger into the instance
	this->mLogger = objLogger;
	// Return the instance
	return this;
}
