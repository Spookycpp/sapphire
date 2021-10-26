#include <string>

#include "hooks.hpp"

auto impl::hooks::hk_ddraw_ongui( std::uintptr_t rcx ) -> void 
{
	sapphire::rendering::init( );

	SAPPHIRE_METHOD( get_current_event_fn, "UnityEngine::Event.get_current()", 0, "", -1, std::uintptr_t( * )( ) );
	SAPPHIRE_METHOD( get_type_fn, "UnityEngine::Event.get_type()", 0, "", -1, unity::event_type( * )( std::uintptr_t ) );

	const auto current = get_current_event_fn( );
	const auto event_type = get_type_fn( current );

	if ( event_type == unity::event_type::repaint )
	{
		sapphire::features::visuals::object.run( );

		SAPPHIRE_METHOD( get_screen_width_fn, "UnityEngine::Screen.get_width()", 0, "", -1, int ( * )( ) );
		SAPPHIRE_METHOD( get_screen_height_fn, "UnityEngine::Screen.get_height()", 0, "", -1, int ( * )( ) );

		if ( sapphire::globals::local )
		{
			const auto watermark_text = L"sapphire | ti: " + std::to_wstring( sapphire::globals::local->clientTickInterval( ) ) + L" | " + sapphire::globals::local->name( );

			sapphire::rendering::draw_string( { 8, get_screen_height_fn( ) - 40.f, 300, 50 }, watermark_text.c_str( ), { 255, 255, 255, 255 }, true, false, false );
			sapphire::rendering::draw_string( { get_screen_width_fn( ) / 2.f - 2.f, get_screen_height_fn( ) / 2.f - 12.f, 20, 20 }, L"$", { 211, 3, 252, 255 }, false, true, false );

			if ( sapphire::globals::local->clientTickInterval( ) > 0.045f )
				sapphire::rendering::draw_string( { get_screen_width_fn( ) / 2.f - 2.f, get_screen_height_fn( ) / 2.f + 5, 300, 20 }, L"desyncing", { 120, 5, 5, 255 }, false, true, false );

			sapphire::features::hitmarkers::object.run( );
		}

		sapphire::features::notifcations::object.run( );
	}
}