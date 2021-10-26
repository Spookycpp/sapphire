#include <windows.h>
#include <string>

#include "hooks.hpp"

auto impl::hooks::hk_on_attacked( void* instance, rust::classes::c_hit_info* hit_info ) -> void
{
	impl::hooks::on_attacked.get_original< decltype( &impl::hooks::hk_on_attacked ) >( )( instance, hit_info );
}