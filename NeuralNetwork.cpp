///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "NeuralNetwork.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NeuralNetwork* NeuralNetwork::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int NeuralNetwork::HiddenLayer          = 0x100;
	int NeuralNetwork::InputLayer           = 0x200;
	int NeuralNetwork::OutputLayer          = 0x300;
	int NeuralNetwork::HiddenToHiddenLayer  = 0x001;
	int NeuralNetwork::HiddenToInputLayer   = 0x002;
	int NeuralNetwork::HiddenToOutputLayer  = 0x003;
	int NeuralNetwork::InputToHiddenLayer   = 0x004;
	int NeuralNetwork::InputToInputLayer    = 0x005;
	int NeuralNetwork::InputToOutputLayer   = 0x006;
	int NeuralNetwork::OutputToHiddenLayer  = 0x007;
	int NeuralNetwork::OutputToInputLayer   = 0x008;
	int NeuralNetwork::OutputToOutputLayer  = 0x009;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NeuralNetwork* NeuralNetwork::Instance(bool bReset) {
		// Check for an existing instance or a reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new NeuralNetwork;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NeuralNetwork::NeuralNetwork(QObject* qoParent) : QObject(qoParent) {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void NeuralNetwork::AppendNeuronToHiddenLayer(Neuron &netNeuron, int intIndex) {
		// Check for the existance of the index
		if ((this->mHiddenNeurons.size() - 1) >= intIndex) {
			// Add the Neuron
			this->mHiddenNeurons[intIndex].append(netNeuron);
			// We're done
			return;
		}
		// Create the new index
		QList<Neuron> qlpNew;
		// Add the Neuron
		qlpNew.append(netNeuron);
		// Create the new index
		this->mHiddenNeurons.insert(intIndex, qlpNew);
	}

	void NeuralNetwork::AppendNeuronToInputLayer(Neuron &netNeuron, int intIndex) {
		// Check for the existance of the index
		if ((this->mInputNeurons.size() - 1) >= intIndex) {
			// Add the Neuron
			this->mInputNeurons[intIndex].append(netNeuron);
			// We're done
			return;
		}
		// Create the new index
		QList<Neuron> qlpNew;
		// Add the Neuron
		qlpNew.append(netNeuron);
		// Create the new index
		this->mInputNeurons.insert(intIndex, qlpNew);
	}

	void NeuralNetwork::AppendNeuronToOutputLayer(Neuron &netNeuron, int intIndex) {
		// Check for the existance of the index
		if ((this->mOutputNeurons.size() - 1) >= intIndex) {
			// Add the Neuron
			this->mOutputNeurons[intIndex].append(netNeuron);
			// We're done
			return;
		}
		// Crete the new index
		QList<Neuron> qlpNew;
		// Add the Neuron
		qlpNew.append(netNeuron);
		// Create the new index
		this->mOutputNeurons.insert(intIndex, qlpNew);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Static Methods ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float NeuralNetwork::DeltaWeight(int intError, float fltInput, float fltWeight) {
		// Return the delta weight
		return (float) (fltWeight + intError * fltInput);
	}

	bool NeuralNetwork::RandomBoolean() {
		// Generate a random number and check it
		if (NeuralNetwork::RandomInteger(0, 1)) {
			// We have a truth value, return
			return true;
		}
		// We have a falsey value, return
		return false;
	}

	int NeuralNetwork::RandomInteger(int intMiniumum, int intMaximum) {
		// Return the random integer
		return (rand() % (intMaximum - intMiniumum + 1) + intMiniumum);
	}

	float NeuralNetwork::RandomWeight(float fltMinMax) {
		// Generate the number
		float fltWeight = ((float) rand() / ((float) (RAND_MAX)) * fltMinMax);
		// Randomly select a negation
		if (NeuralNetwork::RandomBoolean() == false) {
			// Reset the weight
			fltWeight -= fltMinMax;
		}
		// Return the random weight
		return fltWeight;
	}

	float NeuralNetwork::Sigmoid(float fltX) {
		// Return the sigmoid
		return (float) (1 / 1 + exp((double) - fltX));
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NeuralNetwork* NeuralNetwork::AddConnection(int intSourceLayer, int intSourceNeuron, int intTargetLayer, int intTargetNeuron, float fltWeight) {
		// Initialize the connection
		Axon netConnection;
		// Set the source neuron
		netConnection.setSource(intSourceLayer, intSourceNeuron);
		// Set the target neuron
		netConnection.setTarget(intTargetLayer, intTargetNeuron);
		// Set the weight
		netConnection.setWeight((fltWeight == -2.0) ? NeuralNetwork::RandomWeight() : fltWeight);
		// Append the connection to the network
		this->mConnections.append(netConnection);
		// Return the instance
		return this;
	}

	NeuralNetwork* NeuralNetwork::AddNeuron(float fltInput, float fltWeight, int intLayer, int intIndex) {
		// Create the new Neuron
		Neuron netNeuron(fltInput, fltWeight);
		// Determine the layer
		if (intLayer == NeuralNetwork::InputLayer) {         // Input Layer
			// Set the Neuron into the input layer
			this->AppendNeuronToInputLayer(netNeuron, intIndex);
		} else if (intLayer == NeuralNetwork::HiddenLayer) { // Hidden Layer
			// Set the Neuron into the hidden layer
			this->AppendNeuronToHiddenLayer(netNeuron, intIndex);
		} else if (intLayer == NeuralNetwork::OutputLayer) { // Output Layer
			// Set the Neuron into the output layer
			this->AppendNeuronToOutputLayer(netNeuron, intIndex);
		}
		// Return the instance
		return this;
	}

	NeuralNetwork* NeuralNetwork::AutoConnect() {

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Network Execution Methods ////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QVector<int> NeuralNetwork::FeedForward() {

	}

	QVector<int> NeuralNetwork::FeedForward(QVector<float> vecInputs) {
		// Traverse the vector
		for (int intInput = 0; intInput < vecInputs.size(); ++intInput) {
			// Add the neuron
			this->AddNeuron(vecInputs.at(intInput), NeuralNetwork::RandomWeight(), NeuralNetwork::InputLayer);
		}

	}

	QVector<int> NeuralNetwork::FeedForward(int intNumberOfInputs, ...) {
		// Store the variable arguments
		va_list lstArguments;
		// Initialize the arguments
		va_start(lstArguments, intNumberOfInputs);
		// Traverse the arguments
		for (int intArgument = 0; intArgument < intNumberOfInputs; ++intArgument) {
			// Add the neuron
			this->AddNeuron(va_arg(lstArguments, float), NeuralNetwork::RandomWeight(), NeuralNetwork::InputLayer);
		}
		// Clean up
		va_end(lstArguments);
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
