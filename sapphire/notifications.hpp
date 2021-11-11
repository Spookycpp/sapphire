#pragma once
#include <vector>
#include <memory>

#include "include.hpp"
#include "unity_gui.hpp"

namespace sapphire
{
	namespace features // fade-out is currently broken. will fix later.
	{
		class c_notify_text
		{
		public:
			managed_system::string m_text;
			clr_t m_color;
			float m_time;

		public:
			c_notify_text( const managed_system::string text, clr_t color, float time ) : m_text( text ), m_color( color ), m_time( time ) { }
		};

		class c_notify
		{
		private:
			std::vector< std::shared_ptr< sapphire::features::c_notify_text > > m_notify_text;
		public:
			c_notify( ) : m_notify_text{} {}

			auto push( managed_system::string text, float timestamp, clr_t color = clr_t( 255, 255, 255, 255 ) ) -> void {
				m_notify_text.push_back( std::make_shared< sapphire::features::c_notify_text >( text, color, timestamp ) );
			}

			auto run( ) -> void {
				float x{ 8 }, y{ 5 }, size{ 11 };
				clr_t color( 0, 0, 0, 0 );

				for ( size_t i{ }; i < m_notify_text.size( ) && !m_notify_text.empty( ); i++ ) {
					auto& notify = m_notify_text[ i ];

					float delta = unity::c_time::get_time( ) - notify->m_time;
					if ( delta > 1.0f || std::abs( delta ) > 5.f )
						m_notify_text.erase( m_notify_text.begin( ) + i );
				}

				if ( m_notify_text.empty( ) )
					return;

				for ( size_t i{}; i < m_notify_text.size( ); ++i ) {
					auto notify = m_notify_text[ i ];

					float delta = unity::c_time::get_time( ) - notify->m_time;

					color = notify->m_color;

					if ( delta > 0.5f || std::abs( delta ) > 2.5f ) {

						float complete = delta / 2.f;
						float alpha = ( 1.f - delta ) * 240;

						color.a = alpha;

						if ( i == 0 && complete < 0.5 )
							y += size * ( 1.f - complete / 0.2f );
					}

					sapphire::rendering::draw_string( { x, y, 300, 20 }, notify->m_text, color, true, false, false );
					y += size;
				}
			}
		};

		namespace notifcations
		{
			inline c_notify object;
		}
	}
}