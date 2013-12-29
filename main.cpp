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
	// Open the database connection
	HeimdallGI::DBI::Instance(true)->OpenConnection();
	// Instantiate the router
	HeimdallGI::Router* hgiRouter  = new HeimdallGI::Router;
	// Add the index route
	hgiRouter
			->AddRoute("/index", new TestController, "Index")
			->AddRoute (NULL,    new TestController, "Index")
			->AddRoute ("/",     new TestController, "Index");
	// Instantiate the logger
	HeimdallGI::Log* hgiLogger = new HeimdallGI::Log;
	// Iterate over the cookies
	for (QMap<QString, QString>::const_iterator itrCookie = HeimdallGI::CGI::Instance()->GetCookies().constBegin(); itrCookie != HeimdallGI::CGI::Instance()->GetCookies().constEnd(); ++itrCookie) {
		// Add the data to the log
		hgiLogger->Add(itrCookie.key(), itrCookie.value());
	}
	// Iterate over the POST data
	for (QMap<QString, QString>::const_iterator itrParameter = HeimdallGI::CGI::Instance()->GetPostData().constBegin(); itrParameter != HeimdallGI::CGI::Instance()->GetPostData().constEnd(); ++itrParameter) {
		// Add the data to the log
		hgiLogger->Add(itrParameter.key(), itrParameter.value());
	}
	// Iterate over the query data
	for (QMap<QString, QString>::const_iterator itrQueryParam = HeimdallGI::CGI::Instance()->GetQueryData().constBegin(); itrQueryParam != HeimdallGI::CGI::Instance()->GetQueryData().constEnd(); ++itrQueryParam) {
		// Add the data to the log
		hgiLogger->Add(itrQueryParam.key(), itrQueryParam.value());
	}
	// Iterate over the request headers
	for (QMap<QString, QString>::const_iterator itrHeader = HeimdallGI::CGI::Instance()->GetRequestHeaders().constBegin(); itrHeader != HeimdallGI::CGI::Instance()->GetRequestHeaders().constEnd(); ++itrHeader) {
		// Add the data to the log
		hgiLogger->Add(itrHeader.key(), itrHeader.value());
	}
	// Instantiate the CGI
	HeimdallGI::CGI::Instance()
			->SetContentType(HeimdallGI::CGI::ContentTypeHTML)                                                                          // Set the content type
			->SetContent(hgiRouter
						 ->SetLogger(hgiLogger)
						 ->Execute(HeimdallGI::CGI::Instance())
						 ->GetTemplate()
						 .append(hgiLogger->GetHTML())) // Execute the Router
			->WriteResponse();                                                                                                          // Send the response
	// Return the application execution status
	return 0;
}
