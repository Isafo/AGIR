#pragma once

struct PixelRGB
{
	float m_r;
	float m_g;
	float m_b;
};

struct TriMaterial
{
	PixelRGB m_diffuse;
	PixelRGB m_emmisive;
	float albedo;
};