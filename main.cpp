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
	hgiRouter->AddRoute("/index", new TestController, "Index")
			->AddRoute (NULL,     new TestController, "Index")
			->AddRoute ("/",      new TestController, "Index");
	// Define a header string
	QString strHeaders;
	// Iterate over the headers
	for (QMap<QString, QString>::const_iterator itrHeader = HeimdallGI::CGI::Instance()->GetRequestHeaders().constBegin(); itrHeader != HeimdallGI::CGI::Instance()->GetRequestHeaders().constEnd(); ++itrHeader) {
		// Append the string
		strHeaders.append("[").append(itrHeader.key()).append("] => ").append(itrHeader.value()).append("\n");
	}
	// Instantiate the CGI
	HeimdallGI::CGI::Instance()
			->SetContentType(HeimdallGI::CGI::ContentTypeHTML)                                     // Set the content type
			->SetContent(hgiRouter->Execute(HeimdallGI::CGI::Instance())->GetTemplate().append(strHeaders)) // Execute the Router
			->WriteResponse();                                                                     // Send the response
	// Return the application execution status
	return 0;
}
