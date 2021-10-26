#pragma once
#include "il2cpp_lib.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "color.hpp"
#include "system.hpp"

#include "unity_sdk.hpp"

#define DECLARE_MEMBER( type, klass, name ) type & name( ) { SAPPHIRE_FIELD( klass, ##name ) return *reinterpret_cast< type* >( this + name ); }

#include "rust.hpp"

#include "c_base_projectile.hpp"
#include "c_base_weapon.hpp"
#include "c_base_player.hpp"
#include "c_hit_info.hpp"
#include "c_model_state.hpp"
#include "c_networkable.hpp"
#include "c_player_eyes.hpp"
#include "c_transform.hpp"
#include "c_walk_movement.hpp"

#include "silent_aim.hpp"
#include "visuals.hpp"
#include "notifications.hpp"
#include "hitmarkers.hpp"