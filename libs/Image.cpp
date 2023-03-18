#include "Image.h"

Image::Image(unsigned int width, unsigned int height) : m_size({width, height})
{
}

Image::Image(tools::Vector2U size) : m_size(size)
{

}