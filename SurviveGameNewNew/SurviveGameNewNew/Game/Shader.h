#pragma once

#include "../Engine/Engine.h"

#include "../Class/Dir.h"

namespace My {
	class PixelShaderMap;
	struct PixelShader_Table
	{
		LPPixelShader g_pPixelShader;
		LPConstantTable g_pConstantTable;
		D3DXCONSTANT_DESC texDesc;
	};

	class VertexShaderMap;
	struct VertexShader_Table
	{
		LPVertexShader g_pVertexShader;
		LPConstantTable g_pConstantTable;
	};
}

class My::PixelShaderMap : public std::map<std::wstring, PixelShader_Table>
{
public:
	void onInit(const std::wstring& path);
	void onDestroy();
};

class My::VertexShaderMap : public std::map<std::wstring, VertexShader_Table>
{
public:
	void onInit(const std::wstring& path);
	void onDestroy();
};



namespace My {
	extern PixelShaderMap pixelShaderMap;
	extern VertexShaderMap vertexShaderMap;
}