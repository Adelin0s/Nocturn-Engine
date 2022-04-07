/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 07-09-2021 12:48:46                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 05-12-2021 19:59:12                                                 *
 * @ Description:                                                                       *
*****************************************************************************************/

#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

#include "rendering/data/vertex.hpp"

#include <iostream>

namespace Nocturn::rendering
{
	class Buffer
	{
	public:
		Buffer() noexcept;
		Buffer(const uint32_t target) noexcept;

		void generate() noexcept;
		void bind() const noexcept;
		void clear() const noexcept;
		void cleanup() noexcept;

		template <typename T>
		void setData(const size_t size, const T* const data, const enum usage) const noexcept
		{
			glBufferData(m_target, size * sizeof(T), data, usage);
		}

		template <typename T>
		void updateData(const uint32_t offset, const uint32_t noElements, const T* const data) const noexcept
		{
			glBufferSubData(m_target, offset, noElements * sizeof(T), data);
		}

		template <typename T>
		void setAttribPointer(const uint32_t index, const uint32_t size, enum type, const size_t stride, const size_t offset, uint32_t divisor = 0) const noexcept
		{
			glVertexAttribPointer(index, size, type, GL_FALSE, stride * sizeof(T), (void*)offset);
			glEnableVertexAttribArray(index);
			if (divisor > 0)
			{
				glVertexAttribDivisor(index, divisor);
			}
		}

		~Buffer() noexcept = default;

	private:
		uint32_t m_id;
		uint32_t m_target;
	};
}
#endif