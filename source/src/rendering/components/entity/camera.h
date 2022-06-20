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
	class Camera
	{
	public:
		// cant create default camera
		Camera( ) noexcept = delete;

		explicit Camera( const Transform &transform ) noexcept;

		// cant copy
		Camera( const Camera & ) = delete;
		Camera &operator=( const Camera & ) = delete;

		// cant move
		Camera( Camera && ) = delete;
		Camera &operator=( Camera && ) = delete;

		NODISCARD mat4 getViewMatrix( ) const noexcept;
		NODISCARD mat4 getProjectionMatrix( ) const noexcept;

		~Camera( ) noexcept = default;

	private:
		const Transform *m_pTransform = nullptr;
	};
} // namespace Nocturn
#endif
