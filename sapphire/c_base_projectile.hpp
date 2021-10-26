#pragma once
#include "include.hpp"

class rust::classes::c_base_projectile 
{
public:
	DECLARE_MEMBER( math::vector_t, "Projectile", currentVelocity )
	DECLARE_MEMBER( bool, "BaseProjectile", automatic )
	DECLARE_MEMBER( float, "BaseProjectile", thickness )
	DECLARE_MEMBER( float, "BaseProjectile", projectileVelocityScale )
	DECLARE_MEMBER( float, "BaseProjectile", aimCone )
	DECLARE_MEMBER( float, "BaseProjectile", hipAimCone )
	DECLARE_MEMBER( float, "BaseProjectile", aimConePenaltyMax )
	DECLARE_MEMBER( float, "BaseProjectile", aimconePenaltyPerShot )
	DECLARE_MEMBER( float, "BaseProjectile", stancePenaltyScale )
	DECLARE_MEMBER( float, "BaseProjectile", aimSway )
	DECLARE_MEMBER( float, "BaseProjectile", aimSwaySpeed )

	auto list_size( ) -> std::uint32_t { return *reinterpret_cast< std::uint32_t* >( this + 0x18 ); }

	auto remove_recoil( ) -> void
	{
		SAPPHIRE_FIELD( "BaseProjectile", recoil );
		auto recoil_properties = *reinterpret_cast< std::uintptr_t* >( this + recoil );

		*reinterpret_cast< float* >( recoil_properties + 0x18 ) = 0.f;
		*reinterpret_cast< float* >( recoil_properties + 0x1C ) = 0.f;
		*reinterpret_cast< float* >( recoil_properties + 0x20 ) = 0.f;
		*reinterpret_cast< float* >( recoil_properties + 0x24 ) = 0.f;
	}

	auto remove_sway( ) -> void 
	{
		this->aimSway( ) = 0.f;
		this->aimSwaySpeed( ) = 0.f;
	}

	auto remove_spread( ) -> void 
	{
		this->aimCone( ) = 0.f;
		this->hipAimCone( ) = 0.f;
		this->aimConePenaltyMax( ) = 0.f;
		this->aimconePenaltyPerShot( ) = 0.f;
		this->aimconePenaltyPerShot( ) = 0.f;
	}
};