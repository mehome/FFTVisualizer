#pragma once
#include "Resources.h"
#include "PacketQueue.h"
class AudioPlayer
{
public:
	AudioPlayer()
	{

	}
	virtual ~AudioPlayer()
	{

	}

	void run(PacketQueue<ConvertedSampleContainer>* queue)
	{
		while (!queue->isFinished())
		{
			std::unique_ptr<ConvertedSampleContainer> input = queue->popPacket();
			playSamples(std::move(input));
		}
	}

	/**
	* Initializes the AudioPlayer
	*/
	virtual void init(PlayerInitInfo initInfo) = 0;


	/**
	* Initializes the output attributes of the ConverterInitInfo to match a format supported by the Player.
	* For example, if the input stream is a Octagonal channel layout, but the player only supports up to 4 channels,
	* the outChannelLayout and outChannelCount will be adjusted to signal the Converter to mix these channels.
	*/
	virtual void finalizeConverterInfo(ConverterInitInfo& converterInfo) = 0;

	/**
	* Takes a batch of already converted audio samples and queues them into the audio buffer.
	* To know which format this has to be converted to, call finalizeConverterInfo first
	*/
	virtual void playSamples(std::unique_ptr<ConvertedSampleContainer> container) = 0;

private:

};