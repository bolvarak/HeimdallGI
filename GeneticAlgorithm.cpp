///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GeneticAlgorithm.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GeneticAlgorithm* GeneticAlgorithm::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GeneticAlgorithm::NetowrkStarted         = true;
	bool GeneticAlgorithm::NetworkStopped         = false;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GeneticAlgorithm* GeneticAlgorithm::Instance(bool bReset) {
		// Check for an instance or reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Instantiate the class
			mInstance = new GeneticAlgorithm;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GeneticAlgorithm::GeneticAlgorithm(QObject* qoParent) : QObject(qoParent) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GeneticAlgorithm::Crossover(QVector<int> &qviMaternal, QVector<int> &qviPaternal, QVector<int> &qviOffspringAlpha, QVector<int> &qviOffspringBeta) {
		// Return the archal set if the crossover rate is too small or the archals are the same
		if ((GeneticAlgorithm::RandomFloatingPoint() > this->mCrossoverRate) || (qviMaternal == qviPaternal)) {
			// Set the alpha offspring
			qviOffspringAlpha = qviMaternal;
			// Set the beta offspring
			qviOffspringBeta  = qviPaternal;
			// We're done
			return;
		}
		// Determine the crossover point
		int intCrossoverPoint = GeneticAlgorithm::RandomInteger(0, (this->mChromosomeLength - 1));
		// Swap the bits
		for (int intGene = 0; intGene < intCrossoverPoint; ++intGene) {
			// Add the alpha genome
			qviOffspringAlpha.push_back(qviMaternal.at(intGene));
			// Add the beta genome
			qviOffspringBeta.push_back(qviPaternal.at(intGene));
		}
		for (int intGenome = intCrossoverPoint; intGenome < qviMaternal.size(); ++intGenome) {
			// Add the alpha genome
			qviOffspringAlpha.push_back(qviPaternal.at(intGenome));
			// Add the beta genome
			qviOffspringBeta.push_back(qviMaternal.at(intGenome));
		}
	}

	QVector<int> GeneticAlgorithm::Decode(QVector<int> &qviEncodedBits) {
		// Set the directions placeholder
		QVector<int> qviDirections;
		// Iterate through the chromosomes
		for (int intGene = 0; intGene < qviEncodedBits.size(); intGene += this->mGeneLength) {
			// Localize the current genet
			QVector<int> qviCurrentGene;
			// Loop through the bits
			for (int intBit = 0; intBit < this->mGeneLength; ++intBit) {
				// Add the bit
				qviCurrentGene.push_back(qviEncodedBits.at(intGene + intBit));
			}
			// Decode the bit
			qviDirections.push_back(GeneticAlgorithm::BinaryToInteger(qviCurrentGene));
		}
		// Return the decoded bits
		return qviDirections;
	}

	void GeneticAlgorithm::Mutate(QVector<int> &qviBits) {
		// Iterate over the bits
		for (int intBit = 0; intBit < qviBits.size(); ++intBit) {
			// Check for flip capabilities
			if (GeneticAlgorithm::RandomFloatingPoint() < this->mMutationRate) {
				// Flip the bit
				qviBits.at(intBit) = !qviBits.at(intBit);
			}
		}
	}

	Genome& GeneticAlgorithm::Selection() {
		// Create the slice container
		double dblSlice       = (GeneticAlgorithm::RandomFloatingPoint() * this->mTotalFitness);
		// Create the total container
		double dblTotal       = 0.0;
		// Iterate over the population
		for (int intGenome = 0; intGenome < this->mPopulation; ++intGenome) {
			// Increment the total fitness
			dblTotal += this->mGenomes.at(intGenome).mFitness;
			// Check for fitness
			if (dblTotal > dblSlice) {
				// Return the selected genome
				return this->mGenomes.at(intGenome);
			}
		}
		// Return an empty genome
		return Genome();
	}

	void GeneticAlgorithm::UpdateFitnessScores() {

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Static Methods ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int GeneticAlgorithm::BinaryToInteger(QVector<int> &qviBinary) {
		// Set the default value
		int intValue = 0;
		// Set the multiplier
		int intMultiplier   = 1;
		// Iterate through the bits
		for (int intBit = qviBinary.size(); intBit > 0; --intBit) {
			// Set the new value
			intValue += (qviBinary.at(intBit - 1) * intMultiplier);
			// Update the multiplier
			intMultiplier *= 2;
		}
		// Return the value
		return intValue;
	}

	float GeneticAlgorithm::RandomFloatingPoint() {
		// Return the random floating point
		return (rand() / (RAND_MAX + 1.0));
	}

	int GeneticAlgorithm::RandomInteger(int intFirst, int intLast) {
		// Return the random integer
		return (rand() % (intLast - intFirst + 1) + intFirst);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GeneticAlgorithm::Epoch() {
		// Update the fitness scores
		this->UpdateFitnessScores();
		// Initialize the new offspring population
		int intOffspring = 0;
		// Create the offspring container
		QVector<Genome> qvgOffspring;
		// Loop through the offspring population
		while (intOffspring < this->mPopulation) {
			// Select the maternal genome
			Genome gmeMaternal = this->Selection();
			// Select the paternal genome
			Genome gmePaternal = this->Selection();
			// Create the offspring containers
			Genome gmeOffspringAlpha, gmeOffspringBeta;
			// Execute the crossover sequence
			this->Crossover(gmeMaternal.mBits, gmePaternal.mBits, gmeOffspringAlpha.mBits, gmeOffspringBeta.mBits);
			// Execute the mutation sequence
			this->Mutate(gmeOffspringAlpha.mBits);
			this->Mutate(gmeOffspringBeta.mBits);
			// Aggregate the offspring into the populous
			qvgOffspring.push_back(gmeOffspringAlpha);
			qvgOffspring.push_back(gmeOffspringBeta);
			// Increment the offspring count
			intOffspring += 2;
		}
		// Aggregate the offspring into the populous
		this->mGenomes     = qvgOffspring;
		// Increment the generation
		this->mGeneration += 1;
		// Emit the signal
		emit this->NewEpoch(this->mGenomes, this->mGenomes);
	}

	GeneticAlgorithm* GeneticAlgorithm::Execute() {
		// Create the population
		this->InitializePopulation();
		// Update the status of the network
		this->SetStatus(HeimdallGI::GeneticAlgorithm::NetowrkStarted);
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::InitializePopulation() {
		// Clear the existing population
		this->mGenomes.clear();
		// Loop through the population
		for (int intGenome = 0; intGenome < this->mPopulation; ++intGenome) {
			//Add the genome
			this->mGenomes.push_back(Genome(this->mChromosomeLength));
		}
		// Reset the generation
		this->mGeneration   = 0;
		// Reset the fittest genome
		this->mFittestGene  = 0;
		// Reset the best fitness score
		this->mBestFitness  = 0;
		// Reset the total fitness score
		this->mTotalFitness = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int GeneticAlgorithm::GetBits() {
		// Return the number of bits
		return this->mBits;
	}

	double GeneticAlgorithm::GetCrossoverRate() {
		// Return the crossover rate
		return this->mCrossoverRate;
	}

	int GeneticAlgorithm::GetFittest() {
		// Return the fittest gene
		return this->mFittestGene;
	}

	int GeneticAlgorithm::GetGeneLength() {
		// Return the gene length
		return this->mGeneLength;
	}

	int GeneticAlgorithm::GetGeneration() {
		// Return the current generation
		return this->mGeneration;
	}

	double GeneticAlgorithm::GetMutationRate() {
		// Return the mutation rate
		return this->mMutationRate;
	}

	int GeneticAlgorithm::GetPopulation() {
		// Return the population size
		return this->mPopulation;
	}

	bool GeneticAlgorithm::GetStatus() {
		// Return the current status
		return this->mBusy;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GeneticAlgorithm* GeneticAlgorithm::SetBits(int intNumberOfBits) {
		// Set the number of bits
		this->mBits = intNumberOfBits;
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::SetCrossoverRate(double dblCrossoverRate) {
		// Set the crossover rate
		this->mCrossoverRate = dblCrossoverRate;
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::SetGeneLength(int intGeneLength) {
		// Set the gene length
		this->mGeneLength = intGeneLength;
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::SetMutationRate(double dblMutationRate) {
		// Set the mutation rate
		this->mMutationRate = dblMutationRate;
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::SetPopulation(int intPopulationSize) {
		// Set the population
		this->mPopulation = intPopulationSize;
		// Return the instance
		return this;
	}

	GeneticAlgorithm* GeneticAlgorithm::SetStatus(bool bStatus) {
		// Set the status
		this->mBusy = bStatus;
		// Emit the signal
		emit this->StatusChanged(this->mBusy);
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace HeimdallGI
