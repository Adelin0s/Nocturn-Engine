/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 07-09-2021 19:31:44                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 15-02-2022 20:34:33                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application/config/config.hpp"
#include "rendering/components/entity/entity.h"

#include "core/components/transform.h"

#include "core/types/typedef.hpp"

namespace Nocturn
{
	class NCamera
	{
	public:
		// cant create default camera
		NCamera( ) noexcept = delete;

		explicit NCamera( const Transform &transform ) noexcept;

		// cant copy
		NCamera( const NCamera & ) = delete;
		NCamera &operator=( const NCamera & ) = delete;

		// cant move
		NCamera( NCamera && ) = delete;
		NCamera &operator=( NCamera && ) = delete;

		NODISCARD mat4 GetViewMatrix( ) const noexcept;
		NODISCARD mat4 GetProjectionMatrix( ) const noexcept;

		~NCamera( ) noexcept = default;

	private:
		const Transform *m_pTransform = nullptr;
	};
} // namespace Nocturn
#endif
