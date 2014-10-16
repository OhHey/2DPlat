#include "DXUtil.h"

void Utility::GetTextureDim(ID3D11Resource* res, UINT* width, UINT* height)
{
	D3D11_RESOURCE_DIMENSION dim;
	res->GetType(&dim);
	switch(dim)
	{
	case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
		{
			auto texture = reinterpret_cast<ID3D11Texture2D*>(res);
			D3D11_TEXTURE2D_DESC desc;
			texture->GetDesc(&desc);
			if(width) *width = desc.Width;			//IN PIXELS
			if(height) *height =  desc.Height;		//IN PIXELS
		}
		break;

	default:
		{
			if(width) *width = 0;
			if(height) *height = 0;
		}
		break;
	}
}