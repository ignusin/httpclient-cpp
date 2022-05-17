#ifndef __CHUNKED_BUFFER_READER_HPP__
#define __CHUNKED_BUFFER_READER_HPP__

#include "chunked_buffer.hpp"

namespace httpclient
{
    class chunked_buffer_reader
    {
    private:
        const chunked_buffer &_buffer;
        std::list<chunked_buffer::chunk>::const_iterator _currentChunk;
        unsigned int _chunkPosition;

    public:
        chunked_buffer_reader(const chunked_buffer &buffer);
        void read(uint8_t *bytes, unsigned int size, unsigned int offset = 0);
    };
}

#endif // __CHUNKED_BUFFER_READER_HPP__
