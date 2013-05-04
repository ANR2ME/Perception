/********************************************************************
Vireio Perception: Open-Source Stereoscopic 3D Driver
Copyright (C) 2013 Chris Drain

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#include "D3DProxyStereoSurface.h"
#include "Direct3DDevice9.h"
#include "Main.h"
#include "D3DProxyDeviceFactory.h"

D3DProxyStereoSurface::D3DProxyStereoSurface(IDirect3DSurface9* pLeftSurface, IDirect3DSurface9* pRightSurface) : BaseDirect3DSurface9(pLeftSurface)
{
	m_pRightSurface = pRightSurface;
}

D3DProxyStereoSurface::~D3DProxyStereoSurface()
{
	OutputDebugString("Release Right \n");
	if(m_pRightSurface) {
		int newRefCount = m_pRightSurface->Release();
		
		if (newRefCount > 0) {
			char buf[128];
			sprintf_s(buf, "Error: count = %d\n", newRefCount);
			OutputDebugString(buf);
		}

		m_pRightSurface = NULL;
	}
}


bool D3DProxyStereoSurface::IsStereo()
{
	return m_pRightSurface != NULL;
}



IDirect3DSurface9* D3DProxyStereoSurface::getMonoSurface()
{
	if (!m_pSurface)
		OutputDebugString("m_pLeftSurface is null\n");
	if (!m_pRightSurface)
		OutputDebugString("m_pRightSurface is null\n");
	return getLeftSurface();
}

IDirect3DSurface9* D3DProxyStereoSurface::getLeftSurface()
{
	return m_pSurface;
}

IDirect3DSurface9* D3DProxyStereoSurface::getRightSurface()
{
	return m_pRightSurface;
}




HRESULT WINAPI D3DProxyStereoSurface::SetPrivateData(REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	if (IsStereo())
		m_pRightSurface->SetPrivateData(refguid, pData, SizeOfData, Flags);

	return BaseDirect3DSurface9::SetPrivateData(refguid, pData, SizeOfData, Flags);
}



HRESULT WINAPI D3DProxyStereoSurface::FreePrivateData(REFGUID refguid)
{
	if (IsStereo())
		m_pRightSurface->FreePrivateData(refguid);

	return BaseDirect3DSurface9::FreePrivateData(refguid);
}

DWORD WINAPI D3DProxyStereoSurface::SetPriority(DWORD PriorityNew)
{
	if (IsStereo())
		m_pRightSurface->SetPriority(PriorityNew);

	return BaseDirect3DSurface9::SetPriority(PriorityNew);
}


void WINAPI D3DProxyStereoSurface::PreLoad()
{
	if (IsStereo())
		m_pRightSurface->PreLoad();

	return BaseDirect3DSurface9::PreLoad();
}


HRESULT WINAPI D3DProxyStereoSurface::LockRect(D3DLOCKED_RECT* pLockedRect, CONST RECT* pRect, DWORD Flags)
{
	if (IsStereo())
		m_pRightSurface->LockRect(pLockedRect, pRect, Flags);

	return BaseDirect3DSurface9::LockRect(pLockedRect, pRect, Flags);
}

HRESULT WINAPI D3DProxyStereoSurface::UnlockRect()
{
	if (IsStereo())
		m_pRightSurface->UnlockRect();

	return BaseDirect3DSurface9::UnlockRect();
}



HRESULT WINAPI D3DProxyStereoSurface::ReleaseDC(HDC hdc)
{
	if (IsStereo())
		m_pRightSurface->ReleaseDC(hdc);

	return BaseDirect3DSurface9::ReleaseDC(hdc);
}



