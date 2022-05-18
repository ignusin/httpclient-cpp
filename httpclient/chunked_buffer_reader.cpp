#include "chunked_buffer_reader.hpp"
#include <memory>

namespace hc = httpclient;

/*
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
*/

hc::chunked_buffer_reader::chunked_buffer_reader(const hc::chunked_buffer &buffer)
    : _buffer(buffer), _current_chunk(buffer.begin()), _chunk_position(0)
{
}

unsigned int hc::chunked_buffer_reader::read(
    std::uint8_t *bytes, unsigned int size, unsigned int offset)
{
    if (_current_chunk == _buffer.end())
    {
        return 0;
    }

    unsigned int read_count = 0;
    unsigned int bytes_position = offset;
    
    while (bytes_position < size && _current_chunk != _buffer.end())
    {
        const chunked_buffer::chunk &chunk = *_current_chunk;
        unsigned int copy_count = chunk.size() - _chunk_position;

        if (copy_count == 0)
        {
            ++_current_chunk;
            _chunk_position = 0;
        }
        else
        {
            if (copy_count>= size - bytes_position)
            {
                copy_count = size - bytes_position;
            }

            memcpy(bytes + bytes_position, chunk.data() + _chunk_position, copy_count);

            bytes_position += copy_count;
            _chunk_position += copy_count;

            if (_chunk_position == chunk.size())
            {
                ++_current_chunk;
                _chunk_position = 0;
            }
        }

        read_count = copy_count;
    }

    return read_count;
}
