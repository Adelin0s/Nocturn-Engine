// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin
//   @ Create Time: 18-12-2022 2:25 PM
//   @ Contact: cucorianu.adelin@protonmail.com
//   @ Modified time: 18-12-2022 2:25 PM
//   @ Description:
// =====================================================================

#ifndef BASE_RENDERER_H
#define BASE_RENDERER_H

namespace Nocturn::Render
{
	class IRenderer
	{
	public:
		IRenderer( ) noexcept = default;

		virtual RStatus Init( ) = 0;
		virtual void Render( const NCamera &Camera ) = 0;

		virtual ~IRenderer( ) noexcept = default;
	};
} // namespace Nocturn::Render
#endif