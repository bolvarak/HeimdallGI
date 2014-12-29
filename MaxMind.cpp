///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "MaxMind.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	MaxMind* MaxMind::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	MaxMind* MaxMind::Instance(bool blnReset) {
		// Check for an existing instance or a reset flag
		if ((mInstance == NULL) || (blnReset == true)) {
			// Create a new instance
			mInstance = new MaxMind;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	MaxMind::MaxMind(QObject* qoParent) : QObject(qoParent) {
		// Reset the city database
		this->mCityDatabase = NULL;
		// Reset the ISP database
		this->mIspDatabase  = NULL;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Destructor ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	MaxMind::~MaxMind() {
		// Close the database streams
		this->closeConnection();
	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void MaxMind::closeDB(GeoIP* gipDatabase) {
		// Check to see if the DB is open
		if (this->dbIsOpen(gipDatabase)) {
			// Delete the database stream
			GeoIP_delete(gipDatabase);
			// Reset the database
			gipDatabase = NULL;
		}
	}

	bool MaxMind::dbIsOpen(GeoIP* gipDatabase) {
		// Return the open status
		return gipDatabase != NULL;
	}

	bool MaxMind::openDB(GeoIP** gipDatabase, const QString &strFileName) {
		// Open the stream to the database
		*gipDatabase = GeoIP_open(strFileName.toLocal8Bit().constData(), GEOIP_MMAP_CACHE);
		// Make sure the connection is open
		if (this->dbIsOpen(*gipDatabase)) {
			// Set the database charset
			GeoIP_set_charset(*gipDatabase, GEOIP_CHARSET_UTF8);
			// We're done
			return true;
		}
		// We're done
		return false;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void MaxMind::closeConnection() {
		// Close the city database
		this->closeDB(this->mCityDatabase);
		// Close the ISP database
		this->closeDB(this->mIspDatabase);
	}

	GeoRecord MaxMind::findByAddress(const QHostAddress &qhaIpAddress) {
		// Make sure the city database is open
		if (this->dbIsOpen(this->mCityDatabase) && !qhaIpAddress.isNull()) {
			// Create the ISP name placeholder
			QString strISP = QString::null;
			const char* chrIspName;
			// Create the record placeholder
			GeoIPRecord* girResponse;
			// Check for IPv6
			if (qhaIpAddress.protocol() == QAbstractSocket::IPv6Protocol) {
				// Grab the record
				girResponse = GeoIP_record_by_addr_v6(this->mCityDatabase, qhaIpAddress.toString().toLatin1().constData());
			} else {
				// Grab the record
				girResponse = GeoIP_record_by_addr(this->mCityDatabase, qhaIpAddress.toString().toLatin1().constData());
			}
			// Make sure the ISP database is open
			if (this->dbIsOpen(this->mIspDatabase)) {
				// Check for IPv6
				if (qhaIpAddress.protocol() == QAbstractSocket::IPv6Protocol) {
					// Grab the ISP name
					chrIspName = GeoIP_org_by_name_v6(this->mIspDatabase, qhaIpAddress.toString().toLatin1().constData());
				} else {
					// Grab the ISP name
					chrIspName = GeoIP_org_by_name(this->mIspDatabase, qhaIpAddress.toString().toLatin1().constData());
				}
				// Make sure we have a name
				if (chrIspName != NULL) {
					// Convert the ISP name to QString
					strISP = QString::fromUtf8(chrIspName);
					// Clear the ISP name from memory
					free((char *) chrIspName);
				}
			} else {
				// Send a warning
				qWarning("HeimdallGI::MaxMind::findByAddress(): MaxMind ISP Database Not Open");
				// Return an empty structure
				return GeoRecord();
			}
			// Make sure we have a record to return
			if (girResponse != NULL) {
				// Set the time zone
				QString strTimeZone       = QString::fromUtf8(GeoIP_time_zone_by_country_and_region(girResponse->country_code, girResponse->region));
				// Set the country
				QString strCountry        = QString::fromUtf8(girResponse->country_name);
				// Set the city
				QString strCity           = QString::fromUtf8(girResponse->city);
				// Set the region placeholders
				QString strRegion         = QString::null;
				const char* chrRegionName = GeoIP_region_name_by_code(girResponse->country_code, girResponse->region);
				// Make sure we have a region name
				if (chrRegionName != NULL) {
					// Set the region
					strRegion = QString::fromUtf8(chrRegionName);
				}
				// Create the response structure
				GeoRecord geoRecord(
					strCity,
					QString::fromUtf8(girResponse->continent_code),
					strCountry,
					QString::fromUtf8(girResponse->country_code),
					strISP,
					girResponse->latitude,
					girResponse->longitude,
					strRegion,
					strTimeZone
				);
				// Delete the response to free up some memory
				GeoIPRecord_delete(girResponse);
				// Return the response
				return geoRecord;
			}
		}
		// Send a warning
		qWarning("HeimdallGI::MaxMind::findByAddress(): MaxMind City Database Not Open");
		// Return an empty structure
		return GeoRecord();
	}

	bool MaxMind::openConnection(const QString &strCityDatabasePath, const QString &strIspDatabasePath) {
		// Make sure we can open the city database
		if (!this->openDB(&this->mCityDatabase, strCityDatabasePath)) {
			// Throw a critical error
			qCritical("Could not open the City Database: %s", qPrintable(strCityDatabasePath));
			// We're done
			return false;
		}
		// Make sure we can open the ISP database
		if (!this->openDB(&this->mIspDatabase, strIspDatabasePath)) {
			// Throw a critical error
			qCritical("Could not open the ISP Database: %s", qPrintable(strIspDatabasePath));
			// We're done
			return false;
		}
		// We're done
		return true;
	}

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}

