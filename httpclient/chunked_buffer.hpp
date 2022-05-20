#ifndef __CHUNKED_BUFFER_HPP__
#define __CHUNKED_BUFFER_HPP__

#include <cstdint>
#include <list>

namespace httpclient
{
    class chunked_buffer
    {
    public:
        class chunk
        {
        private:
            std::uint8_t *_data;
            unsigned int _size;

        public:
            chunk(const std::uint8_t *data, unsigned int size);
            chunk(chunk &&other);
            ~chunk();

            chunk& operator=(chunk &&other);

            const std::uint8_t *data() const;
            unsigned int size() const;

        private:
            chunk() = delete;
            chunk(const chunk &other) = delete;
            chunk& operator=(const chunk &other) = delete;
        };

    private:
        std::list<chunk> _chunks;

    public:
        chunked_buffer();
        chunked_buffer(chunked_buffer &&other);

        chunked_buffer& operator=(chunked_buffer &&other);

        void append(chunk &&chunk);

        std::list<chunk>::const_iterator begin() const;
        std::list<chunk>::const_iterator end() const;

    private:
        chunked_buffer(const chunked_buffer &other) = delete;
        chunked_buffer& operator=(const chunked_buffer &other) = delete;
    };
}

#endif // __CHUNK_BUFFER_HPP__
