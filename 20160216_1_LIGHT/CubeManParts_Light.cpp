#include "stdafx.h"
#include "CubeManParts_Light.h"


CubeManParts_Light::CubeManParts_Light()
{
}


CubeManParts_Light::~CubeManParts_Light()
{
	Destroy();
}

void CubeManParts_Light::Initialize(D3DXVECTOR3& cubeSize /*= D3DXVECTOR3(1, 1, 1)*/, D3DXVECTOR3& pivot /*= D3DXVECTOR3(0, 0, 0)*/, D3DXVECTOR3& baseLocal /*= D3DXVECTOR3(0, 0, 0)*/)
{
	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(cubeSize.x*( -0.5f ) - pivot.x, cubeSize.y*( -0.5f ) - pivot.y, cubeSize.z*( -0.5f ) - pivot.z);
	vertex[1] = D3DXVECTOR3(cubeSize.x*( -0.5f ) - pivot.x, cubeSize.y*( 0.5f ) - pivot.y, cubeSize.z*( -0.5f ) - pivot.z);
	vertex[2] = D3DXVECTOR3(cubeSize.x*( 0.5f ) - pivot.x, cubeSize.y*( 0.5f ) - pivot.y, cubeSize.z*( -0.5f ) - pivot.z);
	vertex[3] = D3DXVECTOR3(cubeSize.x*( 0.5f ) - pivot.x, cubeSize.y*( -0.5f ) - pivot.y, cubeSize.z*( -0.5f ) - pivot.z);
	vertex[4] = D3DXVECTOR3(cubeSize.x*( -0.5f ) - pivot.x, cubeSize.y*( -0.5f ) - pivot.y, cubeSize.z*( 0.5f ) - pivot.z);
	vertex[5] = D3DXVECTOR3(cubeSize.x*( -0.5f ) - pivot.x, cubeSize.y*( 0.5f ) - pivot.y, cubeSize.z*( 0.5f ) - pivot.z);
	vertex[6] = D3DXVECTOR3(cubeSize.x*( 0.5f ) - pivot.x, cubeSize.y*( 0.5f ) - pivot.y, cubeSize.z*( 0.5f ) - pivot.z);
	vertex[7] = D3DXVECTOR3(cubeSize.x*( 0.5f ) - pivot.x, cubeSize.y*( -0.5f ) - pivot.y, cubeSize.z*( 0.5f ) - pivot.z);

	triangles[0] = TextureNormalTriangle(vertex[7], vertex[6], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(0, 0, 1));
	triangles[1] = TextureNormalTriangle(vertex[7], vertex[5], vertex[4], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(0, 0, 1));
	
	triangles[2] = TextureNormalTriangle(vertex[3], vertex[2], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(1, 0, 0));
	triangles[3] = TextureNormalTriangle(vertex[3], vertex[6], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(1, 0, 0));

	triangles[4] = TextureNormalTriangle(vertex[0], vertex[1], vertex[2], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(0, 0, -1));
	triangles[5] = TextureNormalTriangle(vertex[0], vertex[2], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(0, 0, -1));

	triangles[6] = TextureNormalTriangle(vertex[4], vertex[5], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(-1, 0, 0));
	triangles[7] = TextureNormalTriangle(vertex[4], vertex[1], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(-1, 0, 0));
	
	triangles[8] = TextureNormalTriangle(vertex[6], vertex[2], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(0, 1, 0));
	triangles[9] = TextureNormalTriangle(vertex[6], vertex[1], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(0, 1, 0));

	triangles[10] = TextureNormalTriangle(vertex[7], vertex[4], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0), D3DXVECTOR3(0, -1, 0));
	triangles[11] = TextureNormalTriangle(vertex[7], vertex[0], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1), D3DXVECTOR3(0, -1, 0));

	D3DXMatrixIdentity(&world);
	rotationAxisX = 0.0f;
	localTranslation = baseLocal;

	child.clear();

}

void CubeManParts_Light::Destroy()
{
	for ( auto iter = child.begin(); iter != child.end(); ++iter )
	{
		if ( *iter )
		{
			( *iter )->Destroy();
			delete ( *iter );
			( *iter ) = nullptr;
		}
	}
	child.clear();
}

void CubeManParts_Light::Update(D3DXMATRIX* parentWorldMatrix /*= nullptr*/)
{
	float tick = (float)GameManager::GetTick();

	rotationAxisX += ( rotationSpeed * tick );
	if ( stopReservation == true && rotationAxisX < 0.1f && rotationAxisX > -0.1f )
	{
		stopReservation = false;
		rotationAxisX = 0.0f;
		rotationSpeed = 0.0f;
	}

	if (isHandTurnedToLightOn)
	{
		float handLightMaxAngle = D3DX_PI * 0.4f;
		if (rotationAxisX < -handLightMaxAngle)
		{
			rotationAxisX = -handLightMaxAngle;
			rotationSpeed = 0.0f;
			isHandLightOn = true;
		}
	}

	else
	{
		isHandLightOn = false;

		float maxAngle = D3DX_PI * 0.25f;
		if (rotationAxisX > maxAngle)
		{
			rotationAxisX = maxAngle;
			rotationSpeed *= -1;
		}
		else if (rotationAxisX < -maxAngle)
		{
			rotationAxisX = -maxAngle;
			rotationSpeed *= -1;
		}
	}

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationX(&rotationMatrix, rotationAxisX);
	
	D3DXMATRIX localTanslation;
	D3DXMatrixTranslation(&localTanslation, localTranslation.x, localTranslation.y, localTranslation.z);

	world = rotationMatrix * localTanslation;
	if ( parentWorldMatrix )
	{
		world *= ( *parentWorldMatrix );
	}

	for ( auto iter = child.cbegin(); iter != child.cend(); ++iter )
	{
		( *iter )->Update(&world);
	}

	if ( attachedLight )
	{		
		D3DXVECTOR3 pos;
		D3DXVec3TransformCoord(&pos, &attachedLightLocal, &world);
		attachedLight->Position = pos;

		if ( attachedLight->Type == D3DLIGHT_SPOT )
		{
			D3DXVECTOR3 dir = D3DXVECTOR3(0, 0, 1);
			D3DXMATRIX test = localTanslation * ( *parentWorldMatrix );
			D3DXVec3TransformNormal(&dir, &dir, &test);
			attachedLight->Direction = dir;
		}

		GameManager::GetDevice()->SetLight(attachedLightIndex, attachedLight);
	}
}

void CubeManParts_Light::Render()
{
	GameManager::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	GameManager::GetDevice()->SetFVF(FVF_PositionNormalTexture::FVF);
	GameManager::GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],
		sizeof(FVF_PositionNormalTexture));

	for ( auto iter = child.cbegin(); iter != child.cend(); ++iter )
	{
		( *iter )->Render();
	}
}

void CubeManParts_Light::SetTextureUV(D3DXVECTOR2* uvList)
{
	for ( int i = 0; i < TRIANGLE_COUNT; ++i )
	{
		triangles[i].vertex[0].tex = ( *( uvList + ( i * 3 ) ) );
		triangles[i].vertex[1].tex = ( *( uvList + ( i * 3 + 1) ) );
		triangles[i].vertex[2].tex = ( *( uvList + ( i * 3 + 2) ) );
	}
}