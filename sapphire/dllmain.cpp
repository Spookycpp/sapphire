#include "sapphire_crt.hpp"
#include "sapphire_hook.hpp"
#include "sapphire_importer.hpp"
#include "hooks.hpp"

auto DllMain( void*, std::uint32_t call_reason, void* ) -> bool {
	if ( call_reason != 1 )
		return false;

	il2cpp_lib::init( );
	{
		impl::hooks::ddraw_ongui.setup( "UnityEngine::DDraw.OnGUI()", &impl::hooks::hk_ddraw_ongui, 0 ); // should work anywhere as long as we have hook to call it in.
		impl::hooks::bp_client_input.setup( "BasePlayer.ClientInput()", &impl::hooks::hk_bp_client_input );
		impl::hooks::launch_projectile.setup( "BaseProjectile.LaunchProjectile()", &impl::hooks::hk_launch_projectile );
		impl::hooks::on_attacked.setup( "BasePlayer.OnAttacked()", &impl::hooks::hk_on_attacked );

		// I think we can only hook this function in-game. Maybe find another function thats called in game often, or hook inside client input hook.
		static auto projectile_shoot_sig = utl::pattern::find( L"GameAssembly.dll", "4C 8B 0D ? ? ? ? 48 8B 75 28" );
		const auto relative_projectile_shoot = *reinterpret_cast< std::uintptr_t* >( projectile_shoot_sig + *reinterpret_cast< std::int32_t* >( projectile_shoot_sig + 3 ) + 7 );

		if ( relative_projectile_shoot ) {
			const auto projectile_shoot_rpc = **reinterpret_cast< std::uintptr_t*** >( relative_projectile_shoot + 0x30 );
			HOOK_CUSTOM( projectile_shoot_rpc, impl::hooks::o_projectile_shoot_rpc, &impl::hooks::hk_projectile_shoot_rpc );
		}
	}

	return true;
}