
//
//  LockFreeRingBuffer.hpp
//  BufferedAudioInput
//
//  Created by Roy Macdonald on 02-09-23.
//


#pragma once
#include <atomic>
#include <vector>
#include "ofSoundBuffer.h"



///\brief A lock-free ring buffer for float (audio) samples
class LockFreeRingBuffer {
public:
    ///\brief constructor
    ///\param size is the number of samples  the buffer to allocate
    LockFreeRingBuffer(size_t size);
    
    ///\brief gets the number of samples
    size_t size() const {return _buffer.size();}
    
    ///\brief sets the number of samples . This will change the size of the buffer.
    ///\param size is the number of samples  the buffer to allocate
    void allocate(size_t size);
    
    ///\brief Read this buffer's data and put into the passed ofSoundBuffer
    ///\param buffer reference to the buffer where the data is going to be placed.
    /// It is important that the passed buffer is properly allocated and setup, otherwise errors will arise
    void readIntoBuffer(ofSoundBuffer& buffer);
    
    ///\brief Write  the passed ofSoundBuffer's data into the ringBuffer
    ///\param buffer reference to the buffer where the data is going to be taken from.
    /// It is important that the passed buffer is properly allocated and setup, otherwise errors will arise
    void writeFromBuffer(const ofSoundBuffer& buffer);
    
    size_t getReadPosition();


private:
    
    // On return first and second are pointers to positions to write samples to
    // firstCount and secondCount are the number of samples that can be written
    // returns the number of writeable samples.
    size_t writeBegin(float * &first, size_t &firstCount, float * &second, size_t &secondCount);
    
    ///\brief Call this function after finished writting. It will move the writeIndex by numSamples
    ///\param numSamples is the number of samples  actually that were written.
    void writeEnd(size_t numSamples);
    
    // On return first and second are pointers to positions to read samples from
    // firstCount and secondCount are the number of samples that can be read
    // returns the number of readable samples.
    size_t readBegin(const float * &first, size_t &firstCount, const float * &second, size_t &secondCount );
    
    ///\brief Call this function after finished reading. will move the readIndex by numSamples
    ///\param numSamples is the number of samples that where actually read
    void readEnd(size_t numSamples);
    
    ///\brief get the number of readable samples
    size_t getNumReadableSamples() const;
    
    
    std::atomic<size_t>    _readStart;
    std::atomic<size_t>    _writeStart;
    std::vector<float>     _buffer;
    size_t                 _samples;

};