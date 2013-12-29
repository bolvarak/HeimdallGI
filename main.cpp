///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QCoreApplication"
#include "QDebug"
#include "QList"
#include "QPluginLoader"
#include "QString"
#include "QVariant"
#include "CGI.h"
#include "DBI.h"
#include "Log.h"
#include "NeuralNetwork.h"
#include "Router.h"
#include "Template.h"
#include "TestController.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Main() ///////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This function is the entry point to your HeimdallGI application
 * @brief main()
 * @param int intArguments
 * @param char* chrArguments
 * @return int
 */
int main(int intArguments, char* chrArguments[]) {
	/**
	 * @paragraph Seed the random number generator, this is required if you wish to use HeimdallGI::NeuralNetwork
	 */
	srand((unsigned int) time(NULL));
	// Initialize the HeimdallGI application
	QCoreApplication qcaHeimdallGI(intArguments, chrArguments);
	// Instantiate the CGI wrapper
	HeimdallGI::CGI* hgiCGI        = new HeimdallGI::CGI;
	// Instantiate the router
	HeimdallGI::Router* hgiRouter  = new HeimdallGI::Router;
	// Instantiate the logger
	HeimdallGI::Log* hgiLogger     = new HeimdallGI::Log;
	// Add the index route
	hgiRouter
			->AddRoute("/index", new TestController, "Index")
			->AddRoute (NULL,    new TestController, "Index")
			->AddRoute ("/",     new TestController, "Index");
	// Iterate over the cookies
	for (QMap<QString, QString>::const_iterator itrCookie = hgiCGI->GetCookies().constBegin(); itrCookie != hgiCGI->GetCookies().constEnd(); ++itrCookie) {
		// Add the data to the log
		hgiLogger->Add(itrCookie.key(), itrCookie.value());
	}
	// Iterate over the POST data
	for (QMap<QString, QString>::const_iterator itrParameter = hgiCGI->GetPostData().constBegin(); itrParameter != hgiCGI->GetPostData().constEnd(); ++itrParameter) {
		// Add the data to the log
		hgiLogger->Add(itrParameter.key(), itrParameter.value());
	}
	// Iterate over the query data
	for (QMap<QString, QString>::const_iterator itrQueryParam = hgiCGI->GetQueryData().constBegin(); itrQueryParam != hgiCGI->GetQueryData().constEnd(); ++itrQueryParam) {
		// Add the data to the log
		hgiLogger->Add(itrQueryParam.key(), itrQueryParam.value());
	}
	// Iterate over the request headers
	for (QMap<QString, QString>::const_iterator itrHeader = hgiCGI->GetRequestHeaders().constBegin(); itrHeader != hgiCGI->GetRequestHeaders().constEnd(); ++itrHeader) {
		// Add the data to the log
		hgiLogger->Add(itrHeader.key(), itrHeader.value());
	}
	// Instantiate the CGI
	hgiCGI
			->SetContentType(HeimdallGI::CGI::ContentTypeHTML) // Set the content type
			->SetContent(hgiRouter
						 ->SetLogger(hgiLogger)
						 ->Execute(hgiCGI, hgiCGI->GetRequestHeader("REQUEST_URI"))
						 ->GetTemplate()
						 .append(hgiLogger->GetHTML()))      // Execute the Router
			->WriteResponse();                                 // Send the response
	// Return the application execution status
	return qcaHeimdallGI.exec();
}
