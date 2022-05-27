#ifndef __CHUNKED_BUFFER_READER_HPP__
#define __CHUNKED_BUFFER_READER_HPP__

#include <cstdint>
#include "chunked_buffer.hpp"

namespace httpclient
{
    class chunked_buffer_reader
    {
    private:
        const chunked_buffer &_buffer;
        std::list<chunked_buffer::chunk>::const_iterator _current_chunk;
        unsigned int _chunk_position;

    public:
        chunked_buffer_reader(const chunked_buffer &buffer);
        unsigned int read(std::uint8_t *bytes, unsigned int size, unsigned int offset = 0);

        // TODO: bool check to see if the end of buffer was detected.
        // TODO: method to read 1 byte.  
    };
}

#endif // __CHUNKED_BUFFER_READER_HPP__
