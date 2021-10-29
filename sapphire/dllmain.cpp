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
	}

	return true;
}