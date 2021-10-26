#pragma once
#include "include.hpp"

// better performance over draw texture and such, also can be rendered in 3d space. 
// can be called in update as well instead of ongui. 
// maybe run different parts of esp across two hooks? 

namespace sapphire 
{
	namespace gl_rendering 
	{
		inline std::uintptr_t draw_material;

		enum primitive_mode : int {
			lines = 1,
			line_strip,
			triangles = 4,
			triangle_strip,
			quads = 7
		};

		inline auto gl_start( int mode ) -> void 
		{
			if ( !draw_material )
				return;

			SAPPHIRE_METHOD( set_pass_fn, "UnityEngine::Material.SetPass()", 1, "", -1, bool( * )( std::uintptr_t, int ) );
			SAPPHIRE_METHOD( push_fn, "UnityEngine::GL.PushMatrix()", 0, "", -1, void( * )( void ) );
			SAPPHIRE_METHOD( begin_fn, "UnityEngine::GL.Begin()", 1, "", -1, void( * )( int ) );

			set_pass_fn( draw_material, 0 );
			push_fn( );
			begin_fn( mode );
		}

		inline auto gl_end( ) -> void 
		{
			SAPPHIRE_METHOD( pop_fn, "UnityEngine::GL.PopMatrix()", 0, "", -1, void( * )( void ) );
			SAPPHIRE_METHOD( end_fn, "UnityEngine::GL.End()", 0, "", -1, void( * )( void ) );

			end_fn( );
			pop_fn( );
		}


		inline auto line( math::vector_2d_t start, math::vector_2d_t end, clr_t col ) -> void
		{
			gl_start( sapphire::gl_rendering::primitive_mode::lines );

			SAPPHIRE_METHOD( color_fn, "UnityEngine::GL.Color()", 1, "", -1, void( * )( clr_t ) );
			SAPPHIRE_METHOD( vertex_fn, "UnityEngine::GL.Vertex3()", -1, "", -1, void( * )( float, float, float ) );

			color_fn( col );
			vertex_fn( start.x, start.y, 0 );
			vertex_fn( end.x, end.y, 0 );

			gl_end( );
		}

		inline auto box( math::vector_2d_t pos, math::vector_2d_t size, clr_t col ) -> void
		{
			gl_start( sapphire::gl_rendering::primitive_mode::line_strip );

			SAPPHIRE_METHOD( color_fn, "UnityEngine::GL.Color()", 1, "", -1, void( * )( clr_t ) );
			SAPPHIRE_METHOD( vertex_fn, "UnityEngine::GL.Vertex3()", -1, "", -1, void( * )( float, float, float ) );

			// note - chloe; my attempt at trying to fix the opengl diamond exit rule. seems to work alright someone smarter than me can fix.
			color_fn( col );
			vertex_fn( pos.x + 0.5f, pos.y + 0.5f, 0 );
			vertex_fn( pos.x + size.x + 0.5f, pos.y + 0.5f, 0 );
			vertex_fn( pos.x + size.x + 0.5f, pos.y + size.y + 0.5f, 0 );
			vertex_fn( pos.x + 0.5f, pos.y + size.y + 0.5f, 0 );
			vertex_fn( pos.x + 0.5f, pos.y + 0.5f, 0 );
			vertex_fn( pos.x + 0.5f, pos.y + 0.5f, 0 );

			gl_end( );
		}
	}
}