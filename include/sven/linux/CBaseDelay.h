#pragma once
#pragma pack(push,1)

// This code was automatically generated by the ApiGenerator plugin.
// Prefer updating the generator code instead of editing this directly.
// "u[]" variables are unknown data.

// Example entity: trigger_relay
class CBaseDelay : public CBaseEntity {
public:
    byte u1_0[144];
    float m_flDelay; // Delay before fire.
    string_t m_iszKillTarget; // The name of the kill target, if any.
};
#pragma pack(pop)