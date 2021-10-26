#include "hooks.hpp"

static bool has_initialized{ false };

auto impl::hooks::hk_bp_client_input( rust::classes::c_base_player* base_player, void* input_state ) -> void
{
	if ( !has_initialized )
	{
		static auto initialize_method = utl::pattern::find( L"GameAssembly.dll", "48 83 EC 48 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ?" );
		static auto il2cpp_codegen_initialize_method = reinterpret_cast< void ( * )( unsigned int ) >( initialize_method );

		for ( size_t idx{ 0 }; idx < 56229; idx++ )
		{
			il2cpp_codegen_initialize_method( idx );
		}

		has_initialized = true;
	}

	if ( base_player )
	{

		if ( !sapphire::globals::local )
			sapphire::globals::local = base_player;

		if (const auto movement = base_player->movement( ) )
		{
			base_player->modelState( )->set_flag( rust::enums::e_model_state_flag::on_ground );
			*reinterpret_cast< float* >( movement + 0x4c ) = 1.f;
		}

		if ( unity::get_key( unity::key_code::Mouse3 ) )
			base_player->clientTickInterval( ) = 0.99f;
		else
			base_player->clientTickInterval( ) = 0.03f;

		SAPPHIRE_METHOD( draw_get, "UnityEngine::DDraw.Get()", -1, "", -1, void ( * )( ) );
		draw_get( );
	}

	impl::hooks::bp_client_input.get_original< decltype( &impl::hooks::hk_bp_client_input ) >( )( base_player, input_state );
}