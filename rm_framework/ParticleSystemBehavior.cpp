#include "stdafx.h"
#include "ParticleSystemBehavior.h"


CParticleSystemBehavior::CParticleSystemBehavior()
{
}


CParticleSystemBehavior::~CParticleSystemBehavior()
{
}

void
CParticleSystemBehavior::Update(float dt_)
{

}

/*void
CParticleSystemBehavior::CreateParticle(CVector3 pos, CVector3 velocity_, float size_)
{
	CGameObject * pParticle = new CGameObject();


	pParticle->GetTransform()->SetPosition(pos_);
	pParticle->GetTransform()->SetSize(size_, size_, 0.1f);
	pParticle->SetRenderable(new CSprite()); //
	pParticle->SetMaterial(new CColourMaterial(true));
	//true means additive texture – if your texture is on a black background. Switch this to false for a texture on a transparent background
	pParticle->GetMaterial()->SetTexture(17); //a suitable texture
	pParticle->AddBehavior(new CConstantVelocityBehavior(velocity_));
	pParticle->AddBehavior(new CParticleBehavior());
	m_pGameObject->AddChild(pParticle); //add particle as child of particle system

	//if the particle uses a spritesheet texture
	pParticle->AddBehavior(new CSpriteSheetAnimationBehavior(5, 4, 15));
	//do you want the particles to turn to face the camera? Probably!
	pParticle->AddBehavior(new CFaceCameraBehavior());
	//do we want the particles to fall to earth?
	pParticle->AddBehavior(new CFallUnderGravityBehavior());
	//make transparent particles render properly
	pParticle->GetMaterial()->EnableTransparentDepthSort();

	//make 10 particles randomly arranged with a certain arc#
	// m_fAngle would be a variable defining that arc

	for (int i = 0; i< 10; i++)
	{

		//make random angles in range - m_fAngle/2 to + m_fAngle/2
		float angleDeg = -0.5*m_fAngle + (float)(rand() % ((int)m_fAngle));
		CVector3 velocity;
		velocity.m_fX = (float)sin(angleDeg *PI / 180.0f);
		velocity.m_fY = (float)cos(angleDeg *PI / 180.0f);
		velocity.m_fZ = 0.0f;
		velocity *= 5.0f;

		//add some randomisation to the speed
		velocity *= (0.75f + 0.005f * (float)(rand() % 100));

		//add slight z offset to avoid z order flickering
		CVector3 pos = m_pGameObject->GetTransform()->GetPosition();
		pos.m_fZ += i*0.1f;

		//randomize the size
		float size = 2.0f + 0.02f*(float)(rand() % 100);
		//make the particle
		CreateParticle(pos, velocity, size);
	}

}*/

