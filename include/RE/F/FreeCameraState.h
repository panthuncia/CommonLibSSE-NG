#pragma once

#include "RE/B/BSTPoint.h"
#include "RE/N/NiPoint3.h"
#include "RE/P/PlayerInputHandler.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class NiNode;

	class FreeCameraState :
		public TESCameraState,     // 00
		public PlayerInputHandler  // 20
	{
	public:
		inline static constexpr auto RTTI = RTTI_FreeCameraState;
		inline static constexpr auto VTABLE = VTABLE_FreeCameraState;

		~FreeCameraState() override;  // 00

		// override (TESCameraState)
		void Begin() override;                                               // 01
		void End() override;                                                 // 02
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03
		void GetRotation(NiQuaternion& a_rotation) override;                 // 04
		void GetTranslation(NiPoint3& a_translation) override;               // 05

		// override (PlayerInputHandler)
		bool CanProcess(InputEvent* a_event) override;                                          // 01
		void ProcessButton(ButtonEvent* a_event, PlayerControlsData* a_movementData) override;  // 04

		// members
		NiPoint3         translation;    // 30
		BSTPoint2<float> rotationInput;  // 3C
		BSTPoint2<float> unk44;          // 44
		std::uint16_t    unk4C;          // 4C
		bool             useRunSpeed;    // 4E
		std::uint8_t     unk4F;          // 4F
	};
	static_assert(sizeof(FreeCameraState) == 0x50);
}
