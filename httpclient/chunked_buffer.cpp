#include "chunked_buffer.hpp"
#include <memory>
#include <iostream>

namespace hc = httpclient;

hc::chunked_buffer::chunked_buffer()
{
}

hc::chunked_buffer::chunked_buffer(hc::chunked_buffer &&other)
{
    _chunks = std::move(other._chunks);
}

hc::chunked_buffer& hc::chunked_buffer::operator=(hc::chunked_buffer &&other)
{
    _chunks = std::move(other._chunks);
    return *this;
}

void hc::chunked_buffer::append(hc::chunked_buffer::chunk &&chunk)
{
    _chunks.push_back(std::move(chunk));
}

std::list<hc::chunked_buffer::chunk>::const_iterator hc::chunked_buffer::begin() const
{
    return _chunks.begin();
}

std::list<hc::chunked_buffer::chunk>::const_iterator hc::chunked_buffer::end() const
{
    return _chunks.end();
}

hc::chunked_buffer::chunk::chunk(const std::uint8_t *data, unsigned int size)
{
    _data = new uint8_t[size];
    memcpy(_data, data, size);

    _size = size;
}

hc::chunked_buffer::chunk::chunk(chunk &&other) : _data(new uint8_t[0]), _size(0)
{
    *this = std::move(other);
}

hc::chunked_buffer::chunk::~chunk()
{
    delete[] _data;
    _size = 0;
}

hc::chunked_buffer::chunk& hc::chunked_buffer::chunk::operator=(hc::chunked_buffer::chunk &&other)
{
    delete[] _data;
    _size = 0;

    _data = other._data;
    _size = other._size;

    other._data = new uint8_t[0];
    other._size = 0;

    return *this;
}

const std::uint8_t *hc::chunked_buffer::chunk::data() const
{
    return _data;
}

unsigned int hc::chunked_buffer::chunk::size() const
{
    return _size;
}
